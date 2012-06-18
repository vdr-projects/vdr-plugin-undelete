/*
 * undelete: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: menuundelete.c 0.3 2005/10/04 12:35:20 hflor Exp $
 */

#include "menuundelete.h"
#if VDRVERSNUM < 10307
#include "menuitemtext.h"
#endif
#include "undelete.h"
#include "i18n.h"
#include "vdrtools.h"
#include <vdr/interface.h>
#include <vdr/videodir.h>
#include <vdr/remote.h>
#include <vdr/recording.h>
#ifdef HAVE_ICONPATCH
#include <vdr/iconpatch.h>
#endif

#ifndef RECEXT
#define RECEXT       ".rec"
#define DELEXT       ".del"
#endif

// --- cMenuRecordingSelectItem --------------------------------------------------------

cMenuRecordingSelectItem::cMenuRecordingSelectItem(cRecording *Recording, int Level)
{
  filename = strdup(Recording->FileName());
  totalEntries = newEntries = 0;
  start = Recording->start;
  SetText(Recording->Title('\t', true, Level));
  if ((isdir = (*Text() == '\t')))
    name = strdup(Text() + 2);
  else
    name = strdup(Recording->Name());
  level = Level;
#ifdef UND_Debug2
  dsyslog("%s: cMenuRecordingSelectItem::cMenuRecordingSelectItem FileName=%s Level=%d Name=%s", plugin_name, filename, level, name);
#endif
}

cMenuRecordingSelectItem::~cMenuRecordingSelectItem()
{
#ifdef UND_Debug2
  dsyslog("%s: cMenuRecordingSelectItem::~cMenuRecordingSelectItem FileName=%s Name=%s", plugin_name, filename, name);
#endif
  FREENULL(filename);
  FREENULL(name);
}

bool cMenuRecordingSelectItem::operator< (const cListObject &ListObject)
{
  cMenuRecordingSelectItem *temp = (cMenuRecordingSelectItem *)&ListObject;
  if (isdir != temp->isdir)
    return isdir;
  if (isdir)
    return strcasecmp(name, temp->name) < 0;
  return start < temp->start;
}

void cMenuRecordingSelectItem::IncrementCounter(bool New)
{
  totalEntries++;
  if (New)
    newEntries++;
  char *buffer = NULL;
  asprintf(&buffer, "%d\t%d\t%s", totalEntries, newEntries, name);
  SetText(buffer, false);
#ifdef UND_Debug2
  dsyslog("%s: cMenuRecordingSelectItem::IncrementCounter FileName=%s New=%s Buffer=%s", plugin_name, filename, New ? "true" : "false", buffer);
#endif
}

void cMenuRecordingSelectItem::RefreshCounter(void)
{
#ifdef UND_Debug2
  dsyslog("%s: cMenuRecordingSelectItem::RefeshCounter FileName=%s", plugin_name, filename);
#endif
  if (isdir)
  {
    char *dirname = DirName();
    if (dirname)
    {
      totalEntries = 0;
      newEntries = 0;
      for (cRecording *recording = DeletedRecordings.First(); recording; recording = DeletedRecordings.Next(recording))
        if (strncmp(recording->FileName(), dirname, strlen(dirname)) == 0)
          IncrementCounter(recording->IsNew());
      free(dirname);
    }
  }
}

char *cMenuRecordingSelectItem::DirName(void)
{
  if (isdir)
  {
    char *temp = strdup(filename);
    char *last = temp + strlen(VideoDirectory) + 1;
    for (int i = level; *last && i >= 0; i--)
    {
      last = strchr(last, '/');
      if (!last)
        break;
      last++;
    }
    if (last)
      *last = 0;
    return temp;
  } else
    return NULL;
}

// --- cMenuRecordingSelect --------------------------------------------------------

cMenuRecordingSelect::cMenuRecordingSelect(const char *Base, int Level, bool OpenSubMenus)
:cOsdMenu(Base ? Base : tr("Deleted Recordings"), 6, 6, 6)
{
#ifdef UND_Debug2
  dsyslog("%s: cMenuRecordingSelect::cMenuRecordingSelect Base=%s Level=%d OpenSubMenus=%s", plugin_name, Base, Level, OpenSubMenus ? "true" : "false");
#endif
#if VDRVERSNUM < 10307
#ifdef HAVE_ELCHI
  Interface->Status(tr("Display$prepare recording display..."), Setup.Theme == themeVanilla ? clrBlack : (eDvbColor)fginfofont, Setup.Theme == themeVanilla ? clrCyan : clrInfoLine);
#else
  Interface->Status(tr("Display$prepare recording display..."));
#endif
  Interface->Flush();
#else
  STATUS(tr("Display$prepare recording display..."));
#endif
  base = Base ? strdup(Base) : NULL;
  level = Level;
  Display();
  cMenuRecordingSelectItem *LastItem = NULL;
  char *LastItemText = NULL;
  for (cRecording *recording = DeletedRecordings.First(); recording; recording = DeletedRecordings.Next(recording))
  {
    if (!Base || (strstr(recording->Name(), Base) == recording->Name() && recording->Name()[strlen(Base)] == '~'))
    {
      cMenuRecordingSelectItem *Item = new cMenuRecordingSelectItem(recording, level);
      if (*Item->Text() && (!LastItem || strcmp(Item->Text(), LastItemText) != 0))
      {
        Add(Item);
        LastItem = Item;
        FREENULL(LastItemText);
        LastItemText = strdup(LastItem->Text());
      } else
        delete Item;
      if (LastItem)
      {
        if (LastItem->IsDirectory())
          LastItem->IncrementCounter(recording->IsNew());
      }
    }
  }
  free(LastItemText);
  LastItem = Current() < 0 ? NULL : (cMenuRecordingSelectItem *)Get(Current());
  Sort();
  if (LastItem)
  {
    SetCurrent(LastItem);
    if (OpenSubMenus && Open(true) == osContinue)
      return;
  } else
    SetCurrent(First());
  SetHelpKeys();
}

cMenuRecordingSelect::~cMenuRecordingSelect()
{
#ifdef UND_Debug2
  dsyslog("%s: cMenuRecordingSelect::~cMenuRecordingSelect Base=%s Level=%d", plugin_name, base, level);
#endif
  FREENULL(base);
}

void cMenuRecordingSelect::SetHelpKeys(void)
{
#ifdef UND_Debug2
  dsyslog("%s: cMenuRecordingSelect::SetHelpKeys", plugin_name);
#endif

  cMenuRecordingSelectItem *ri = (cMenuRecordingSelectItem *)Get(Current());
  if (ri)
  {
    if (ri->IsDirectory())
      SetHelp(tr("Open"), tr("Undelete"), tr("Delete"), NULL);
    else
    {
      cRecording *recording = GetRecording(ri);
#if VDRVERSNUM >= 10325
      SetHelp(NULL, tr("Undelete"), tr("Delete"), (recording && recording->Info()->Title() && *recording->Info()->Title()) ? tr("Summary") : NULL);
#else
      SetHelp(NULL, tr("Undelete"), tr("Delete"), (recording && recording->Summary() && *recording->Summary()) ? tr("Summary") : NULL);
#endif
    }
  } else
  {
    SetHelp(NULL);
  }
}

cRecording *cMenuRecordingSelect::GetRecording(cMenuRecordingSelectItem *Item)
{
  cRecording *recording = DeletedRecordings.GetByName(Item->FileName());
  if (!recording)
     ERROR(tr("Error while accessing recording!"));
  return recording;
}

eOSState cMenuRecordingSelect::Open(bool OpenSubMenus)
{
  cMenuRecordingSelectItem *ri = (cMenuRecordingSelectItem *)Get(Current());
  if (ri)
  {
    if (ri->IsDirectory())
    {
      const char *t = ri->Name();
      char *buffer = NULL;
      if (base)
      {
        asprintf(&buffer, "%s~%s", base, t);
        t = buffer;
      }
      AddSubMenu(new cMenuRecordingSelect(t, level + 1, OpenSubMenus));
      FREENULL(buffer);
      return osContinue;
    }
  }
  return osUnknown;
}

eOSState cMenuRecordingSelect::UnDelete(void)
{
  if (HasSubMenu() || Count() == 0)
     return osContinue;
  if (WorkFilename)
  {
     esyslog("%s: Error previous jobs not completed (%s)", plugin_name, WorkFilename);
     return osContinue;
  }
  cMenuRecordingSelectItem *ri = (cMenuRecordingSelectItem *)Get(Current());
  if (ri && ((!ri->IsDirectory() && (!confirmundel.u || Interface->Confirm(tr("Question$Undelete recording?")))) || (ri->IsDirectory() && (!confirmundeldir.u || Interface->Confirm(tr("Question$Undelete recordings in directory?"))))))
  {
    if (ri->IsDirectory())
      WorkFilename = ri->DirName(); // WorkFilename is NULL see up
    else
      WorkFilename = strdup(ri->FileName());
    cRemote::Put((eKeys)kUnDelRec);
    cOsdMenu::Del(Current());
    Display();
    if (!Count())
      return osBack;
  }
  return osContinue;
}

eOSState cMenuRecordingSelect::Delete(void)
{
  if (HasSubMenu() || Count() == 0)
     return osContinue;
  if (WorkFilename)
  {
     esyslog("%s: Error previous jobs not completed (%s)", plugin_name, WorkFilename);
     return osContinue;
  }
  cMenuRecordingSelectItem *ri = (cMenuRecordingSelectItem *)Get(Current());
  if (ri && ((!ri->IsDirectory() && (!confirmdel.u || Interface->Confirm(tr("Question$Delete recording definitive?")))) || (ri->IsDirectory() && (!confirmdeldir.u || Interface->Confirm(tr("Question$Delete recordings in diretory definitive?"))))))
  {
    if (ri->IsDirectory())
      WorkFilename = ri->DirName(); // WorkFilename is NULL see up
    else
      WorkFilename = strdup(ri->FileName());
    cRemote::Put((eKeys)kDelRec);
    cOsdMenu::Del(Current());
    Display();
    if (!Count())
      return osBack;
  }
  return osContinue;
}

eOSState cMenuRecordingSelect::Summary(void)
{
  if (HasSubMenu() || Count() == 0)
    return osContinue;
  cMenuRecordingSelectItem *ri = (cMenuRecordingSelectItem *)Get(Current());
  if (ri && !ri->IsDirectory())
  {
    cRecording *recording = GetRecording(ri);
#if VDRVERSNUM >= 10325
    if (recording && recording->Info()->Title() && *recording->Info()->Title())
#else
    if (recording && recording->Summary() && *recording->Summary())
#endif
#if VDRVERSNUM >= 10307
#if VDRVERSNUM >= 10325
      return AddSubMenu(new cMenuText(tr("Summary"), recording->Info()->Title()));
#else
      return AddSubMenu(new cMenuText(tr("Summary"), recording->Summary()));
#endif
#else
#if VDRVERSNUM >= 10325
      return AddSubMenu(new cMenuItemText(tr("Summary"), recording->Info()->Title()));
#else
      return AddSubMenu(new cMenuItemText(tr("Summary"), recording->Summary()));
#endif
#endif
  }
  return osContinue;
}

eOSState cMenuRecordingSelect::ProcessKey(eKeys Key)
{
#ifdef UND_Debug3
  bool noneKey = Key == kNone;
  if (!noneKey)
    dsyslog("%s: cMenuRecordingSelect::ProcessKey Key=%s", plugin_name, KeyName(Key));
#endif
  bool hSubMenu = HasSubMenu();

  eOSState state = cOsdMenu::ProcessKey(Key);
#ifdef UND_Debug3
  if (!noneKey || (state != osUnknown && state != osContinue))
  {
    dsyslog("%s: cMenuRecordingSelect::ProcessKey OSState=%s", plugin_name, OSStateName(state));
    noneKey = false;
  }
#endif


  if (hSubMenu && !HasSubMenu())
  {
    if (Key == kYellow || Key == kGreen)
    {
      cOsdMenu::Del(Current());
      if (!Count())
        state = osBack;
    }
    if (state == osContinue)
    {
      for (cMenuRecordingSelectItem *ri = (cMenuRecordingSelectItem *)First(); ri; ri = (cMenuRecordingSelectItem *)Next(ri))
        ri->RefreshCounter();
      Display();
    }
  }

  switch (state)
  {
    case osUnknown:  switch (Key)
                     {
                       case kBack:   state = osBack;
                       case kOk:     
                       case kRed:    state = Open();
                                     break;
                       case kGreen:  state = UnDelete();
                                     break;
                       case kYellow: state = Delete();
                                     break;
                       case kBlue:   state = Summary();
                                     break;
                       default: break;
                     }
                     break;
    default:         break;
  }
  if (!HasSubMenu() && Key != kNone && !WorkFilename)
  {
    SetHelpKeys();
    cMenuRecordingSelectItem *ri = (cMenuRecordingSelectItem *)Get(Current());
    if (ri)
    {
      ri->RefreshCounter();
      RefreshCurrent();
    }
  }

#ifdef UND_Debug3
  if (!noneKey || (state != osUnknown && state != osContinue))
    dsyslog("%s: cMenuRecordingSelect::ProcessKey returned OSState=%s", plugin_name, OSStateName(state));
#endif
  return state;
}

// --- cMenuUndelete --------------------------------------------------------

cMenuUndelete::cMenuUndelete(void)
:cOsdMenu(tr("Deleted Recordings"), 6, 6)
{
#ifdef UND_Debug2
  dsyslog("%s: cMenuUndelete::cMenuUndelete", plugin_name);
#endif
#if VDRVERSNUM < 10307
#ifdef HAVE_ELCHI
  Interface->Status(tr("Display$prepare recording display..."), Setup.Theme == themeVanilla ? clrBlack : (eDvbColor)fginfofont, Setup.Theme == themeVanilla ? clrCyan : clrInfoLine);
#else
  Interface->Status(tr("Display$prepare recording display..."));
#endif
  Interface->Flush();
#else
  STATUS(tr("Display$prepare recording display..."));
#endif
#if VDRVERSNUM >= 10311
  DeletedRecordings.Load();
#else
  DeletedRecordings.Load(true);
#endif
  AddSubMenu(new cMenuRecordingSelect);
  PurgeRecording = false;
  SalvageRecording = false;
}

cMenuUndelete::~cMenuUndelete()
{
#ifdef UND_Debug2
  dsyslog("%s: cMenuUndelete::~cMenuUndelete", plugin_name);
#endif
  if (PurgeRecording)
  {
#if VDRVERSNUM < 10307
#ifdef HAVE_ELCHI
    Interface->Status(tr("Display$remove empty directories..."), Setup.Theme == themeVanilla ? clrBlack : (eDvbColor)fginfofont, Setup.Theme == themeVanilla ? clrCyan : clrInfoLine);
#else
    Interface->Status(tr("Display$remove empty directories..."));
#endif
    Interface->Flush();
#else
    STATUS(tr("Display$remove empty directories..."));
#endif
    RemoveEmptyVideoDirectories();
  }
  DeletedRecordings.Clear();
  
#if VDRVERSNUM >= 10311
  if (SalvageRecording)
#if VDRVERSNUM >= 10333
    Recordings.Update();
#else
    Recordings.TriggerUpdate();
#endif
#endif
}

eOSState cMenuUndelete::ProcessKey(eKeys Key)
{
#ifdef UND_Debug3
  bool noneKey = Key == kNone;
  if (!noneKey)
    dsyslog("%s: cMenuUndelete::ProcessKey Key=%s", plugin_name, KeyName(Key));
#endif

  eOSState state = cOsdMenu::ProcessKey(Key);
#ifdef UND_Debug3
  if (!noneKey || (state != osUnknown && state != osContinue))
  {
    dsyslog("%s: cMenuUndelete::ProcessKey OSState=%s", plugin_name, OSStateName(state));
    noneKey = false;
  }
#endif

  if (state == osUnknown)
  {
    cRecording *recording = NULL;
    bool processrecording = false;
    if (WorkFilename && (Key == kDelRec || Key == kUnDelRec))
    {
#if VDRVERSNUM < 10307
#ifdef HAVE_ELCHI
      Interface->Status(tr("Display$please wait ..."), Setup.Theme == themeVanilla ? clrBlack : (eDvbColor)fginfofont, Setup.Theme == themeVanilla ? clrCyan : clrInfoLine);
#else
      Interface->Status(tr("Display$please wait ..."));
#endif
      Interface->Flush();
#else
      STATUS(tr("Display$please wait ..."));
#endif
    }
    switch (Key)
    {
      case kUnDelRec: state = osContinue;
                      if (WorkFilename)
                      {
                        for (recording = DeletedRecordings.First(); recording; recording = DeletedRecordings.Next(recording))
                          if (strncmp(recording->FileName(), WorkFilename, strlen(WorkFilename)) == 0)
                          {
                            if (verbose.u)
                              isyslog("%s: undelete recording=%s", plugin_name, recording->FileName());
                            char *NewName = strdup(recording->FileName());
                            char *ext = strrchr(NewName, '.');
                            if (strcmp(ext, DELEXT) == 0)
                            {
                              strncpy(ext, RECEXT, strlen(ext));
                              if (access(NewName, F_OK) == 0)
                              {
                                ERROR(tr("Error$Recording with the same name exists!"));
                                if (verbose.u)
                                  isyslog("%s: Recording with the same name exists!", plugin_name);
                              } else
                              {
                                if (!RenameVideoFile(recording->FileName(), NewName))
                                  esyslog("%s: Error while rename deleted recording (%s) to (%s)", plugin_name, recording->FileName(), NewName);
                                SalvageRecording = true;
                              }
                            }
                            free(NewName);
                            cRemote::Put((eKeys)kUnDelRec);
                            DeletedRecordings.Del(recording);
                            processrecording = true;
                            break;
                          }
                      }
                      break;
      case kDelRec:   state = osContinue;
                      if (WorkFilename)
                      {
                        for (recording = DeletedRecordings.First(); recording; recording = DeletedRecordings.Next(recording))
                          if (strncmp(recording->FileName(), WorkFilename, strlen(WorkFilename)) == 0)
                          {
                            if (verbose.u)
                              isyslog("%s: purge deleted recording=%s", plugin_name, recording->FileName());
                            if (!RemoveVideoFile(recording->FileName()))
                              esyslog("%s: Error while remove deleted recording (%s)", plugin_name, recording->FileName());
                            PurgeRecording = true;
                            cRemote::Put((eKeys)kDelRec);
                            DeletedRecordings.Del(recording);
                            processrecording = true;
                            break;
                          }
                      }
                      break;
      case kHelpKeys: if (!HasSubMenu())
                        state = osBack;
      default:        break;
    }
    if (WorkFilename && !processrecording)
    {
      FREENULL(WorkFilename); // restore Helpkeys in cMenuRecordingSelect::ProcessKey
#if VDRVERSNUM < 10307
#ifdef HAVE_ELCHI
      Interface->Status(NULL, Setup.Theme == themeVanilla ? clrBlack : (eDvbColor)fginfofont, Setup.Theme == themeVanilla ? clrCyan : clrInfoLine);
#else
      Interface->Status(NULL);
#endif
      Interface->Flush();
#else
      STATUS(NULL);
#endif
      cRemote::Put((eKeys)kHelpKeys);
    }
  }
  if (!WorkFilename && !HasSubMenu())
    state = osBack;

#ifdef UND_Debug3
  if (!noneKey || (state != osUnknown && state != osContinue))
    dsyslog("%s: cMenuUndelete::ProcessKey returned OSState=%s", plugin_name, OSStateName(state));
#endif
  return state;
}
