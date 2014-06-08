/*
 * undelete: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: vdrtools.h 0.4 2005/11/16 18:39:18 hflor Exp $
 */

#ifndef __VDRTOOLS_H
#define __VDRTOOLS_H

#include <vdr/keys.h>
#include <vdr/osd.h>
#include <vdr/osdbase.h>

bool GetVDRSize(const char *dir, long long &llSize);
char *SkipQuote(char *s);
char *ExchangeChars(char *s, bool ToFileSystem);

#ifdef UND_Debug1
  #define UND_Debug
#endif
#ifdef UND_Debug2
  #define UND_Debug
#endif
#ifdef UND_Debug3
  #define UND_Debug
#endif

#ifdef UND_Debug
const char *KeyName(eKeys Key);
const char *OSStateName(eOSState OSState);
#endif

#endif //__VDRTOOLS_H
