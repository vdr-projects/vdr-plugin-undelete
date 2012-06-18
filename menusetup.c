/*
 * undelete: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: menusetup.c 0.2 2004/10/10 12:23:20 hflor Exp $
 */

#include "menusetup.h"
#include "undelete.h"
#include "menuundelete.h"
#include "i18n.h"
#include "vdrtools.h"
#include <vdr/plugin.h>

// --- cMenuSetupUndelete -------------------------------------------------------

cMenuSetupUndelete::cMenuSetupUndelete(void)
{
#ifdef PL_Debug2
  dsyslog("%s: cMenuSetupUndelete::cMenuSetupUndelete", plugin_name);
#endif
  store = false;

  #define StoreValue(T) T.o = T.u
  #define StoreValueFile(T) strcpy(T.o, T.u)

  // var pos7
  StoreValue     (commandline_preference);
  StoreValue     (confirmdel);
  StoreValue     (confirmdeldir);
  StoreValue     (confirmundel);
  StoreValue     (confirmundeldir);
  StoreValueFile (mainmenu_name);
  StoreValue     (mainmenu_visible);
  StoreValue     (verbose);

  #undef StoreValue
  #undef StoreValueFile

  Set();
}

cMenuSetupUndelete::~cMenuSetupUndelete(void)
{
#ifdef PL_Debug2
  dsyslog("%s: cMenuSetupUndelete::~cMenuSetupUndelete store=%s", plugin_name, store ? "true" : "false");
#endif
  if (!store)
  {

    #define RestoreValue(T) T.u = T.o
    #define RestoreValueFile(T) strcpy(T.u, T.o)

    // var pos8
    RestoreValue     (commandline_preference);
    RestoreValue     (confirmdel);
    RestoreValue     (confirmdeldir);
    RestoreValue     (confirmundel);
    RestoreValue     (confirmundeldir);
    RestoreValueFile (mainmenu_name);
    RestoreValue     (mainmenu_visible);
    RestoreValue     (verbose);

    #undef RestoreValue
    #undef RestoreValueFile
  }
}

void cMenuSetupUndelete::Store(void)
{
#ifdef PL_Debug2
  dsyslog("%s: cMenuSetupUndelete::Store", plugin_name);
#endif

  #define SaveValue(T, N) if (T.u != T.o) SetupStore(N, T.u);
  #define SaveValueFile(T, N) if (strcmp(T.u, T.o)) SetupStore(N, T.u);

  // var pos9
  SaveValue     (commandline_preference, "commandline");
  SaveValue     (confirmdel,             "confdel");
  SaveValue     (confirmdeldir,          "confdeldir");
  SaveValue     (confirmundel,           "confundel");
  SaveValue     (confirmundeldir,        "confundeldir");
  SaveValueFile (mainmenu_name,          "name");
  SaveValue     (mainmenu_visible,       "visible");
  SaveValue     (verbose,                "verbose");

  #undef SaveValue
  #undef SaveValueFile

  store = true;
}

void cMenuSetupUndelete::Set(void)
{
#ifdef PL_Debug2
  dsyslog("%s: cMenuSetupUndelete::Set Current=%d", plugin_name, Current());
#endif
  int current = Current();
  Clear();

  #define DisplayLine(T) !T.h && (!commandline_preference.u || !T.c)

  Add(new cOsdItem         (tr("Setup$Display deleted recordings now"),                  osUser1));
  if (DisplayLine(commandline_preference))
    Add(new cMenuEditBoolItem(tr("Setup$Preferr Command Line Parameter"),                &commandline_preference.u));
  if (DisplayLine(mainmenu_visible))
    Add(new cMenuEditBoolItem(tr("Setup$Visible in Mainmenu"),                           &mainmenu_visible.u));
  if (DisplayLine(mainmenu_name) && mainmenu_visible.u)
    Add(new cMenuEditStrItem (tr("Setup$  Name for Mainmenu"),                           mainmenu_name.u, sizeof(mainmenu_name.u), tr(FileNameChars)));
  if (DisplayLine(confirmdel))
    Add(new cMenuEditBoolItem(tr("Setup$Confirm delete deleted recordings"),             &confirmdel.u));
  if (DisplayLine(confirmdeldir))
    Add(new cMenuEditBoolItem(tr("Setup$Confirm delete directories"),                    &confirmdeldir.u));
  if (DisplayLine(confirmundel))
    Add(new cMenuEditBoolItem(tr("Setup$Confirm undelete deleted recordings"),           &confirmundel.u));
  if (DisplayLine(confirmundeldir))
    Add(new cMenuEditBoolItem(tr("Setup$Confirm undelete directories"),                  &confirmundeldir.u));
  if (DisplayLine(verbose))
    Add(new cMenuEditBoolItem(tr("Setup$Verbose Log Mode"),                              &verbose.u));

  #undef DisplayLine

#ifdef PL_Debug2
  dsyslog("%s: Count=%d", plugin_name, Count());
#endif
  SetCurrent(Get(current));
}

eOSState cMenuSetupUndelete::ProcessKey(eKeys Key)
{
#ifdef PL_Debug3
  bool noneKey = Key == kNone;
  if (!noneKey)
    dsyslog("%s: cMenuSetupUndelete::ProcessKey Key=%s", plugin_name, KeyName(Key));
#endif

  int m_commandline_preference = commandline_preference.u;
  int m_mainmenu_visible = mainmenu_visible.u;

  eOSState state = cMenuSetupPage::ProcessKey(Key);
#ifdef PL_Debug3
  if (!noneKey || (state != osUnknown && state != osContinue))
  {
    dsyslog("%s: cMenuSetupUndelete::ProcessKey OSState=%s", plugin_name, OSStateName(state));
    noneKey = false;
  }
#endif

  if (m_commandline_preference != commandline_preference.u || m_mainmenu_visible != mainmenu_visible.u)
  {
    Set();
    Display();
  }

  switch (state)
  {
    case osUser1:    state = AddSubMenu(new cMenuUndelete);
                     break;
    default:         break;
  }

#ifdef PL_Debug3
  if (!noneKey || (state != osUnknown && state != osContinue))
    dsyslog("%s: cMenuSetupUndelete::ProcessKey returned OSState=%s", plugin_name, OSStateName(state));
#endif
  return state;
}
