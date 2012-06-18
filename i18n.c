/*
 * undelete: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: i18n.c 0.2 2004/10/10 12:23:20 hflor Exp $
 */

#include "i18n.h"

const tI18nPhrase Phrases[] = {
  { "  -m        --visible_in_mainmenu    Show the plugin in the mainmenu\n  -M        --hide_in_mainmenu       Hide the plugin in the mainmenu\n                                     You can start the Plugin in the setupmenu\n  -n Name   --mainmenu_name=Name     Select Name for entry in the mainmenu\n                                     (set also -m)\n  -c        --confirm_del_rec        show confirmation for delete recording\n  -C        --not_confirm_del_rec    delete recording without confirmation\n  -d        --confirm_del_dir        show confirmation for delete directory\n  -D        --not_confirm_del_dir    delete directory without confirmation\n  -s        --confirm_undel_rec      show confirmation for undelete recording\n  -S        --not_confirm_undel_rec  undelete recording without confirmation\n  -t        --confirm_undel_dir      show confirmation for undelete directory\n  -T        --not_confirm_undel_dir  undelete directory without confirmation\n  -v        --verbose                Enable more logging\n  -V        --noverbose              Disable more loggig\n            --nosetup_commandline    Hide the 'Preferr Command Line Parameter'\n                                     form setup-menu\n  @config-file                       Read also parameters from this file\n  note: recording means deleted recordings (there not show in VDR)",
    "  -m        --visible_in_mainmenu    Plugin wird im Hautmen� angezeigt\n  -M        --hide_in_mainmenu       kein Eintrag im Hauptmen� f�r das Plugin\n                                     es kann �ber das Setup-Men� gestartet werden\n  -n Name   --mainmenu_name=Name     Name f�r den Eintrag im Hauptmen�\n                                     (diese Option setzt auch -m)\n  -c        --confirm_del_rec        Best�tigung f�r das L�schen von Aufnahmen\n  -C        --not_confirm_del_rec    keine Best�tigung (l�schen Aufnahmen)\n  -d        --confirm_del_dir        Best�tigung beim L�schen von Verzeichnissen\n  -D        --not_confirm_del_dir    keine Best�tigung (l�schen Verzeichnissen)\n  -s        --confirm_undel_rec      Best�tigung Wiederherstellung von Aufnahmen\n  -S        --not_confirm_undel_rec  keine Best. Wiederherstellung von Aufnahmen\n  -t        --confirm_undel_dir      Best�tigung Wiederherstellung von Verzei.\n  -T        --not_confirm_undel_dir  keine Best. Wiederherstellung von Verzei.\n  -v        --verbose                erweiterte Protokollierung aktivieren\n  -V        --noverbose              keine erweiterte Protokollierung\n            --nosetup_commandline    Option 'Kommandozeile hat Vorrang'\n                                     im Setup-Men� verbergen\n  @config-file                       Komandozeilenoptionen auch aus der angegebenen\n                                     Datei lesen\n\n  Hinweis: Mit Aufnahmen sind hier die gel�schten Aufnahmen gemeint",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },

  { "Undelete",
    "Wiederherst.",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Deleted Recordings",
    "Gel�schte Aufnahmen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "undelete for recordings",
    "Wiederherstellung gel�schter Aufnahmen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "DelRec",
    "L�schung",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "HelpKeys",
    "Hilfstasten",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "UnDelRec",
    "Wiederherstellung",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "unknow",
    "unbekannt",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Display$please wait ...",
    "bitte warten ...",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Display$prepare recording display...",
    "Listenanzeige wird vorbereitet...",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Display$remove empty directories...",
    "Entferne leere Verzeichnisse...",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Error$Recording with the same name exists!",
    "Aufnahme mit selben Namen ist vorhanden!",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Menu$Undelete recordings",
    "Aufnahmen wiederherstellen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Question$Delete recording definitive?",
    "Aufnahme endg�ltig l�schen?",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Question$Delete recordings in diretory definitive?",
    "Aufnahmen in Verzeichnis endg�ltig l�schen?",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Question$Undelete recording?",
    "Aufnahme wiederherstellen?",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Question$Undelete recordings in directory?",
    "Aufnahmen in Verzeichnis wiederherstellen?",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Setup$Confirm delete deleted recordings",
    "Aufnahme l�schen best�tigen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Setup$Confirm delete directories",
    "Verzeichnisse l�schen best�tigen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Setup$Confirm undelete deleted recordings",
    "Wiederherstellung Aufn. best�tigen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Setup$Confirm undelete directories",
    "Wiederherstellung Verz. best�tigen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Setup$Display deleted recordings now",
    "Gel�schte Aufnahmen jetzt anzeigen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Setup$  Name for Mainmenu",
    "  Eintragname im Hauptmen�",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Setup$Preferr Command Line Parameter",
    "Kommandozeile hat Vorrang",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Setup$Verbose Log Mode",
    "Ausf�hrliche Protokollierung",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { "Setup$Visible in Mainmenu",
    "Im Hauptmen� sichtbar",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Portugu�s
    "",// TODO Fran�ais
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Espa�ol
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Catal�
  },
  { NULL }
  };
