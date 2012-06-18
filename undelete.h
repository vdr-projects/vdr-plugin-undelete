/*
 * undelete: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: undelete.h 0.2 2004/10/10 12:23:20 hflor Exp $
 */

#ifndef __UNDELETE_H
#define __UNDELETE_H

#include <vdr/config.h>
#include <vdr/recording.h>
#include <vdr/plugin.h>

#define FREENULL(T) { if (T) { free(T); T = NULL; } }
#if VDRVERSNUM >= 10307
#define MAXOSDTEXTWIDTH 45
#define AKTOSDTEXTWIDTH 45
#define ERROR(E)  Skins.Message(mtError, E)
#define INFO(I)   Skins.Message(mtInfo, I)
#define STATUS(S) Skins.Message(mtStatus, S)
#else
#define MAXOSDTEXTWIDTH MAXOSDWIDTH
#define AKTOSDTEXTWIDTH Setup.OSDwidth
#define ERROR(E)  Interface->Error(E)
#define INFO(I)   Interface->Info(I)
#endif

#define kUnDelRec  (kNone + 110)
#define kDelRec    (kNone + 111)
#define kHelpKeys  (kNone + 112)

// Global variables that control the overall behaviour:

struct tParamInt {
  bool c;               // read command line
  bool r;               // read config file
  bool h;               // hide in setup menu
  int d;                // default
  int u;                // used
  int s;                // config file
  int o;                // old value for setup menu
  };

struct tParamChar {
  bool c;               // read command line
  bool r;               // read config file
  bool h;               // hide in setup menu
  char d;               // default
  char u;               // used
  char s;               // config file
  char o;               // old value for setup menu
  };

struct tParamFile {
  bool c;               // read command line
  bool r;               // read config file
  bool h;               // hide in setup menu
  char d[MaxFileName];  // default
  char u[MaxFileName];  // used
  char s[MaxFileName];  // config file
  char o[MaxFileName];  // old value for setup menu
  char e[MaxFileName];  // expanded name (environment)
  };

// var pos1

extern tParamInt   commandline_preference;
extern tParamInt   confirmdel;
extern tParamInt   confirmdeldir;
extern tParamInt   confirmundel;
extern tParamInt   confirmundeldir;
extern tParamFile  mainmenu_name;
extern tParamInt   mainmenu_visible;
extern tParamInt   verbose;

extern char        plugin_name[];
extern bool        PurgeRecording;
extern bool        SalvageRecording;
extern cRecordings DeletedRecordings;
extern char        *WorkFilename;

void ExpandEnvironment(tParamFile *FileStruc);

// --- cPluginUndelete ----------------------------------------------------------

class cPluginUndelete : public cPlugin {
private:
  // Add any member variables or functions you may need here.
  bool ProcessArg(int argc, char *argv[]);

public:
  cPluginUndelete(void);
  virtual ~cPluginUndelete();
  virtual const char *Version(void);
  virtual const char *Description(void);
  virtual const char *CommandLineHelp(void);
  virtual bool ProcessArgs(int argc, char *argv[]);
  virtual bool Start(void);
  virtual const char *MainMenuEntry(void);
  virtual cOsdObject *MainMenuAction(void);
  virtual cMenuSetupPage *SetupMenu(void);
  virtual bool SetupParse(const char *Name, const char *Value);
  };

#endif //__UNDELETE_H
