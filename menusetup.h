/*
 * undelete: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: menusetup.h 0.2 0.1 2004/10/08 02:03:31 hflor Exp $
 */

#ifndef __MENUSETUP_H
#define __MENUSETUP_H

#include <vdr/menu.h>
#include <vdr/menuitems.h>

// --- cMenuSetupUndelete -------------------------------------------------------

class cMenuSetupUndelete : public cMenuSetupPage {
private:
  int   store;
protected:
  virtual void Store(void);
public:
  cMenuSetupUndelete(void);
  virtual ~cMenuSetupUndelete(void);
  virtual void Set(void);
  virtual eOSState ProcessKey(eKeys Key);
  };

#endif //__MENUSETUP_H
