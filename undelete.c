/*
 * undelete: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: undelete.c 0.3 2005/10/04 14:35:20 hflor Exp $
 */

#include "undelete.h"
#include "menuundelete.h"
#include "menusetup.h"
#include "i18n.h"
#include "vdrtools.h"
#include <getopt.h>
#include <ctype.h>
#include <vdr/recording.h>

static const char *VERSION           = "0.0.3";
static const char *DESCRIPTION       = "undelete for recordings";

// Global variables that control the overall behaviour:

// var pos2
tParamFile  undeleteconfigfile     = { false, false, false, "undelete.conf", "undelete.conf" };
tParamInt   commandline_preference = { false, false, false, true };
tParamInt   confirmdel             = { false, false, false, true };
tParamInt   confirmdeldir          = { false, false, false, true };
tParamInt   confirmundel           = { false, false, false, true };
tParamInt   confirmundeldir        = { false, false, false, true };
tParamFile  mainmenu_name          = { false, false, false, "Undelete recordings" };
tParamInt   mainmenu_visible       = { false, false, false, false };
tParamInt   verbose                = { false, false, false, false, true };

char        plugin_name[MaxFileName]  = "Undelete";
bool        PurgeRecording = false;
bool        SalvageRecording = false;
#if VDRVERSNUM >= 10311
cRecordings DeletedRecordings(true);
#else
cRecordings DeletedRecordings;
#endif
char        *WorkFilename = NULL;

void DisplaySetings(void)
{
  #define WriteSource(T)   plugin_name, T.r ? 'r' : ' ', T.c ? 'c' : ' '
  #define IsDefault(T)     WriteSource(T), T.u == T.d ? '*' : ' '
  #define IsDefaultFile(T) WriteSource(T), strcmp(T.u, T.d) ? ' ' : '*'
  #define BoolValue(T)     IsDefault(T), T.u ? "yes" : "no"

  // var pos3
  if (verbose.u)
  {
    isyslog("%s: commandline_preference     = [ %c%c%c ] %s", BoolValue(commandline_preference));
    isyslog("%s: mainmenu_visible           = [ %c%c%c ] %s", BoolValue(mainmenu_visible));
    if (mainmenu_visible.u)
      isyslog("%s: mainmenu_name              = [ %c%c%c ] %s", IsDefaultFile(mainmenu_name), mainmenu_name.u);
    isyslog("%s: confirm undelete           = [ %c%c%c ] %s", BoolValue(confirmundel));
    isyslog("%s: confirm undelete directory = [ %c%c%c ] %s", BoolValue(confirmundeldir));
    isyslog("%s: confirm delete             = [ %c%c%c ] %s", BoolValue(confirmdel));
    isyslog("%s: confirm delete directory   = [ %c%c%c ] %s", BoolValue(confirmdeldir));
    isyslog("%s: verbose                    = [ %c%c%c ] %s", BoolValue(verbose));
  }

#ifdef UND_Debug1
  if (!verbose.u)
  {
    dsyslog("%s: commandline_preference     = [ %c%c%c ] %s", BoolValue(commandline_preference));
    dsyslog("%s: mainmenu_visible           = [ %c%c%c ] %s", BoolValue(mainmenu_visible));
    if (mainmenu_visible.u)
      dsyslog("%s: mainmenu_name              = [ %c%c%c ] %s", IsDefaultFile(mainmenu_name), mainmenu_name.u);
    dsyslog("%s: confirm undelete           = [ %c%c%c ] %s", BoolValue(confirmundel));
    dsyslog("%s: confirm undelete directory = [ %c%c%c ] %s", BoolValue(confirmundeldir));
    dsyslog("%s: confirm delete             = [ %c%c%c ] %s", BoolValue(confirmdel));
    dsyslog("%s: confirm delete directory   = [ %c%c%c ] %s", BoolValue(confirmdeldir));
    dsyslog("%s: verbose                    = [ %c%c%c ] %s", BoolValue(verbose));
  }
#endif

  #undef WriteSource
  #undef IsDefault
  #undef IsDefaultFile
  #undef BoolValue
}

void ExpandEnvironment(tParamFile *FileStruc)
{
#ifdef UND_Debug2
  dsyslog("%s: ExpandEnvironment text=%s", plugin_name, FileStruc->u);
#endif
  char *s;
  char *p;
  strn0cpy(FileStruc->e, FileStruc->u, sizeof(FileStruc->e));
  while ((s = strstr(FileStruc->e, "$(")) || (s = strstr(FileStruc->e, "${")))
  {
    char c = *(s + 1) == '(' ? ')' : '}';
    p = strchr(s, c); // search closing ) or }
    if (p)
    {
      *p++ = 0;
      *s = 0;
      s += 2;
      char *e = getenv(s);
      if (e)
      {
        char *buffer = NULL;
        asprintf(&buffer, "%s%s%s", FileStruc->e, e, p);
        strn0cpy(FileStruc->e, buffer, sizeof(FileStruc->e));
        FREENULL(buffer);
      } else
      {
        esyslog("%s: environmentvariable '%s' not found path=%s", plugin_name, s, FileStruc->u);
        FileStruc->e[0] = 0;
      }
    } else
    {
      esyslog("%s: missing ')' after '$(' path=%s", plugin_name, FileStruc->u);
      FileStruc->e[0] = 0;
    }
  }
  while ((p = strstr(FileStruc->e, "//")))
    strcpy(p, p + 1);
#ifdef UND_Debug2
  dsyslog("%s: ExpandEnvironment return=%s", plugin_name, FileStruc->e);
#endif
}

// --- cPluginUndelete ----------------------------------------------------------

cPluginUndelete::cPluginUndelete(void)
{
#ifdef UND_Debug1
  dsyslog("%s: cPluginUndelete::cPluginUndelete", plugin_name);
#endif
  // Initialize any member variables here.
  // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
  // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!
}

cPluginUndelete::~cPluginUndelete()
{
#ifdef UND_Debug1
  dsyslog("%s: cPluginUndelete::~cPluginUndelete", plugin_name);
#endif
  // Clean up after yourself!
}

bool cPluginUndelete::ProcessArg(int argc, char *argv[])
{
  int c;
  static struct option long_options[] = {
    { "confirm_del_rec",           no_argument,       NULL, 'c' },
    { "not_confirm_del_rec",       no_argument,       NULL, 'C' },
    { "confirm_del_dir",           no_argument,       NULL, 'd' },
    { "not_confirm_del_dir",       no_argument,       NULL, 'D' },
    { "visible_in_mainmenu",       no_argument,       NULL, 'm' },
    { "hide_in_mainmenu",          no_argument,       NULL, 'M' },
    { "mainmenu_name",             required_argument, NULL, 'n' },
    { "confirm_undel_rec",         no_argument,       NULL, 's' },
    { "not_confirm_undel_rec",     no_argument,       NULL, 'S' },
    { "confirm_undel_dir",         no_argument,       NULL, 't' },
    { "not_confirm_undel_dir",     no_argument,       NULL, 'T' },
    { "verbose",                   no_argument,       NULL, 'v' },
    { "noverbose",                 no_argument,       NULL, 'V' },
    { "nosetup_commandline",       no_argument,       NULL, 1   },
    { "ns_commandline",            no_argument,       NULL, 1   },
    { NULL }
  };

  if (argc >= 1)
    strn0cpy(plugin_name, argv[0], sizeof(plugin_name));

  for (c = 1; c < argc; c++)
    dsyslog("%s: parameter%d=%s", plugin_name, c, argv[c]);

  #define Setvalue(T) T.c = true; T.u
  #define SetvalueFile(T) T.c = true; strn0cpy(T.u, optarg, sizeof(T.u))

  while ((c = getopt_long(argc, argv, "cCdDmMn:sStTvV", long_options, NULL)) != -1)
  {
    // var pos4
    switch (c)
    {
      case 1:   commandline_preference.h = true;
                break;
      case 'c': Setvalue(confirmdel) = true;
                break;
      case 'C': Setvalue(confirmdel) = false;
                break;
      case 'd': Setvalue(confirmdeldir) = true;
                break;
      case 'D': Setvalue(confirmdeldir) = false;
                break;
      case 'm': Setvalue(mainmenu_visible) = true;
                break;
      case 'M': Setvalue(mainmenu_visible) = false;
                break;
      case 'n': SetvalueFile(mainmenu_name);
                Setvalue(mainmenu_visible) = true;
                break;
      case 's': Setvalue(confirmundel) = true;
                break;
      case 'S': Setvalue(confirmundel) = false;
                break;
      case 't': Setvalue(confirmundeldir) = true;
                break;
      case 'T': Setvalue(confirmundeldir) = false;
                break;
      case 'v': Setvalue(verbose) = true;
                break;
      case 'V': Setvalue(verbose) = false;
                break;
      default:  return false;
    }
  }

  #undef Setvalue
  #undef SetvalueFile

  if (optind < argc && argv[optind][0] == '@')
  {
    strn0cpy(undeleteconfigfile.u, &argv[optind][1], sizeof(undeleteconfigfile.u));
    optind++;
  }
  return optind >= argc;
}

const char *cPluginUndelete::Version(void)
{
  return VERSION;
}

const char *cPluginUndelete::Description(void)
{
  return tr(DESCRIPTION);
}

const char *cPluginUndelete::CommandLineHelp(void)
{
  // Return a string that describes all known command line options.            column 80 --> |
  return tr("  -m        --visible_in_mainmenu    Show the plugin in the mainmenu\n"
            "  -M        --hide_in_mainmenu       Hide the plugin in the mainmenu\n"
            "                                     You can start the Plugin in the setupmenu\n"
            "  -n Name   --mainmenu_name=Name     Select Name for entry in the mainmenu\n"
            "                                     (set also -m)\n"
            "  -c        --confirm_del_rec        show confirmation for delete recording\n"
            "  -C        --not_confirm_del_rec    delete recording without confirmation\n"
            "  -d        --confirm_del_dir        show confirmation for delete directory\n"
            "  -D        --not_confirm_del_dir    delete directory without confirmation\n"
            "  -s        --confirm_undel_rec      show confirmation for undelete recording\n"
            "  -S        --not_confirm_undel_rec  undelete recording without confirmation\n"
            "  -t        --confirm_undel_dir      show confirmation for undelete directory\n"
            "  -T        --not_confirm_undel_dir  undelete directory without confirmation\n"
            "  -v        --verbose                Enable more logging\n"
            "  -V        --noverbose              Disable more loggig\n"
            "            --nosetup_commandline    Hide the 'Preferr Command Line Parameter'\n"
            "                                     form setup-menu\n"
            "  @config-file                       Read also parameters from this file"
            "\n"
            "  note: recording means deleted recordings (there not show in VDR)");

/* only for translation:
         "  -m        --visible_in_mainmenu    Plugin wird im Hautmenü angezeigt\n"
         "  -M        --hide_in_mainmenu       kein Eintrag im Hauptmenü für das Plugin\n"
         "                                     es kann über das Setup-Menü gestartet werden\n"
         "  -n Name   --mainmenu_name=Name     Name für den Eintrag im Hauptmenü\n"
         "                                     (diese Option setzt auch -m)\n"
         "  -c        --confirm_del_rec        Bestätigung für das Löschen von Aufnahmen\n"
         "  -C        --not_confirm_del_rec    keine Bestätigung (löschen Aufnahmen)\n"
         "  -d        --confirm_del_dir        Bestätigung beim Löschen von Verzeichnissen\n"
         "  -D        --not_confirm_del_dir    keine Bestätigung (löschen Verzeichnissen)\n"
         "  -s        --confirm_undel_rec      Bestätigung Wiederherstellung von Aufnahmen\n"
         "  -S        --not_confirm_undel_rec  keine Best. Wiederherstellung von Aufnahmen\n"
         "  -t        --confirm_undel_dir      Bestätigung Wiederherstellung von Verzei.\n"
         "  -T        --not_confirm_undel_dir  keine Best. Wiederherstellung von Verzei.\n"
         "  -v        --verbose                erweiterte Protokollierung aktivieren\n"
         "  -V        --noverbose              keine erweiterte Protokollierung\n"
         "            --nosetup_commandline    Option 'Kommandozeile hat Vorrang'\n"
         "                                     im Setup-Menü verbergen\n"
         "  @config-file                       Komandozeilenoptionen auch aus der angegebenen\n"
         "                                     Datei lesen\n"
         "\n"
         "  Hinweis: Mit Aufnahmen sind hier die gelöschten Aufnahmen gemeint"
*/
         // free: a b e f g h i j k l o p q r u w x y z
}

bool cPluginUndelete::ProcessArgs(int argc, char *argv[])
{
  // Implement command line argument processing here if applicable.
  return ProcessArg(argc, argv);
}

bool cPluginUndelete::Start(void)
{
  // Start any background activities the plugin shall perform.
  RegisterI18n(Phrases);

#ifdef UND_Debug1
  dsyslog("%s: cPluginUndelete::Start undeleteconfigfile=%s", plugin_name, undeleteconfigfile.u);
#endif

  char *p;
  char *q = strdup(ConfigDirectory(""));
  asprintf(&p, "%s%s%s", q, *(q + strlen(q) - 1) == '/' ? "" : "/", undeleteconfigfile.u);
  if (!access(undeleteconfigfile.u, F_OK) && !access(undeleteconfigfile.u, R_OK) || !access(p, F_OK) && !access(p, R_OK))
  {
    #define MAXARGS 100
    int fargc = 1;
    char *fargv[MAXARGS];
    char buffer[MAXPARSEBUFFER];
    bool done;
    FILE *f;

    if (!access(undeleteconfigfile.u, F_OK))
    {
      f = fopen(undeleteconfigfile.u, "r");
#ifdef UND_Debug1
      dsyslog("%s: cPluginUndelete::Start open undeleteconfigfile=%s", plugin_name, undeleteconfigfile.u);
#endif
    } else
    {
      f = fopen(p, "r");
#ifdef UND_Debug1
      dsyslog("%s: cPluginUndelete::Start open undeleteconfigfile=%s", plugin_name, p);
#endif
    }
    free(p);
    free(q);
    if (!f)
    {
      esyslog("%s: ERROR: cannot open config file: [%s]%s", plugin_name, ConfigDirectory(""), undeleteconfigfile.u);
      return false;
    }
    while (fgets(buffer, sizeof(buffer), f) > 0)
    {
      p = skipspace(stripspace(buffer));
      q = NULL;
      done = false;
      while (!done)
      {
        if (!q)
          q = p;
        switch (*p)
        {
          case '\\': strcpy(p, p + 1);
                     if (*p)
                       p++;
                     else
                     {
                       esyslog("%s: ERROR: missing character after \\", plugin_name);
                       return false;
                     }
                     break;
          case '"':
          case '\'': if ((p = SkipQuote(p)) == NULL)
                       return false;
                     break;
          default:   if (!*p || isspace(*p))
                     {
                       done = !*p;
                       *p = 0;
                       if (q)
                       {
                         if (fargc < MAXARGS - 1)
                         {
                           if (*q != '#')
                             fargv[fargc++] = strdup(q);
                         } else
                         {
                           esyslog("%s: ERROR: plugin argument list too long", plugin_name);
                           return false;
                         }
                         q = NULL;
                       }
                     }
                     if (!done)
                       p = *p ? p + 1 : skipspace(p + 1);
        }
      }
    }
    fclose(f);
    fargv[0] = strdup(plugin_name);
    fargv[fargc] = NULL;
    optind = 0; // to reset the getopt() data
    if (fargc > 1)
      if (!ProcessArg(fargc, fargv))
      {
        esyslog("%s: ERROR: cannot parse config file: [%s]%s", plugin_name, ConfigDirectory(""), undeleteconfigfile.u);
        return false;
      }
      while(fargc) free(fargv[--fargc]);
  } else
  {
    free(p);
    free(q);
    if (strcmp(undeleteconfigfile.u, undeleteconfigfile.d))
    {
      esyslog("%s: ERROR: config file not found: [%s]%s", plugin_name, ConfigDirectory(""), undeleteconfigfile.u);
      return false;
    } else if (verbose.u)
      isyslog("%s: INFO: config file not found: [%s]%s", plugin_name, ConfigDirectory(""), undeleteconfigfile.u);
  }

  strn0cpy(mainmenu_name.d, tr("Menu$Undelete recordings"), sizeof(mainmenu_name.d));
  
  // default parameter                --> d_
  // read parameter from commandline  --> c_  (data in u_)
  // value parameter from config-file --> s_
  // read parameter from config-file  --> r_
  // paramater used                   --> u_

  #define SetParam(T) { if (!T.c || (!commandline_preference.u && T.r)) T.u = (!T.c && !T.r) ? T.d : T.s; }
  #define SetParamFile(T) { if (!T.c || (!commandline_preference.u && T.r)) strcpy(T.u, (!T.c && !T.r) ? T.d : T.s); }

  commandline_preference.u = commandline_preference.r ? commandline_preference.s : commandline_preference.d;

  // var pos5
  SetParamFile (undeleteconfigfile);
  SetParam     (confirmdel);
  SetParam     (confirmdeldir);
  SetParam     (confirmundel);
  SetParam     (confirmundeldir);
  SetParamFile (mainmenu_name);
  SetParam     (mainmenu_visible);
  SetParam     (verbose);

  #undef SetParam
  #undef SetParamFile

  if (verbose.u)
    isyslog("%s: Start", plugin_name);
  DisplaySetings();
  return true;
}

const char *cPluginUndelete::MainMenuEntry(void)
{
  return mainmenu_visible.u ? mainmenu_name.u : NULL;
}

cOsdObject *cPluginUndelete::MainMenuAction(void)
{
#ifdef UND_Debug1
  dsyslog("%s: cPluginUndelete::MainMenuAction", plugin_name);
#endif
  return new cMenuUndelete;
}

cMenuSetupPage *cPluginUndelete::SetupMenu(void)
{
#ifdef UND_Debug1
  dsyslog("%s: cPluginUndelete::SetupMenu", plugin_name);
#endif
  return new cMenuSetupUndelete;
}


bool cPluginUndelete::SetupParse(const char *Name, const char *Value)
{
  #define SetParam(T) { T.r = true; T.s = strtol(Value, NULL, 0); }
  #define SetParamFile(T) { T.r = true; strn0cpy(T.s, Value, sizeof(T.s)); }

  // Parse your own setup parameters and store their values.
  dsyslog("%s: Setupparameter %s=%s", plugin_name, Name, Value);
  // var pos6

  if      (!strcasecmp(Name, "commandline"))  SetParam     (commandline_preference)
  else if (!strcasecmp(Name, "confdel"))      SetParam     (confirmdel)
  else if (!strcasecmp(Name, "confdeldir"))   SetParam     (confirmdeldir)
  else if (!strcasecmp(Name, "confundel"))    SetParam     (confirmundel)
  else if (!strcasecmp(Name, "confundeldir")) SetParam     (confirmundeldir)
  else if (!strcasecmp(Name, "name"))         SetParamFile (mainmenu_name)
  else if (!strcasecmp(Name, "visible"))      SetParam     (mainmenu_visible)
  else if (!strcasecmp(Name, "verbose"))      SetParam     (verbose)
  else
    return false;
  return true;

  #undef SetParam
  #undef SetParamChar
  #undef SetParamFile
}

VDRPLUGINCREATOR(cPluginUndelete); // Don't touch this!
