/*
 * undelete: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: menuundelete.h 0.2 2004/10/10 12:23:20 hflor Exp $
 */

#ifndef __MENUUNDELETE_H
#define __MENUUNDELETE_H

#include <vdr/menu.h>
#include <vdr/menuitems.h>

// --- cMenuRecordingSelectItem --------------------------------------------------------

class cMenuRecordingSelectItem : public cOsdItem {
private:
  char *filename;
  char *name;
  int level;
  time_t start;
  bool isdir;
  int totalEntries;
  int newEntries;
public:
  cMenuRecordingSelectItem(cRecording *Recording, int Level);
  ~cMenuRecordingSelectItem(void);
  virtual bool operator< (const cListObject &ListObject);
  void IncrementCounter(bool New);
  void RefreshCounter(void);
  const char *FileName(void) { return filename; }
  char *DirName(void);
  const char *Name(void) { return name; }
  bool IsDirectory(void) { return isdir; }
  };

// --- cMenuRecordingSelect --------------------------------------------------------

class cMenuRecordingSelect : public cOsdMenu {
private:
  char *base;
  int level;
  void SetHelpKeys(void);
  cRecording *GetRecording(cMenuRecordingSelectItem *Item);
  eOSState Open(bool OpenSubMenus = false);
  eOSState UnDelete(void);
  eOSState Delete(void);
  eOSState Summary(void);
public:
  cMenuRecordingSelect(const char *Base = NULL, int Level = 0, bool OpenSubMenus = false);
  ~cMenuRecordingSelect(void);
  virtual eOSState ProcessKey(eKeys Key);
  };
  
// --- cMenuUndelete --------------------------------------------------------

class cMenuUndelete : public cOsdMenu {
private:
public:
  cMenuUndelete(void);
  ~cMenuUndelete(void);
  virtual eOSState ProcessKey(eKeys Key);
  };


#endif //__MENUUNDELETE_H
