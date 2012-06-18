/*
 * undelete: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: vdrtools.h 0.1 2004/10/08 02:03:31 hflor Exp $
 */

#ifndef __VDRTOOLS_H
#define __VDRTOOLS_H

#include <vdr/keys.h>
#include <vdr/osd.h>
#include <vdr/osdbase.h>

char *SkipQuote(char *s);
char *ExchangeChars(char *s, bool ToFileSystem);

#ifdef UND_Debug1
const char *KeyName(eKeys Key);
const char *OSStateName(eOSState OSState);
#endif


#endif //__VDRTOOLS_H
