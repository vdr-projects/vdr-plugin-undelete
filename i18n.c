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
    "  -m        --visible_in_mainmenu    Plugin wird im Hautmenü angezeigt\n  -M        --hide_in_mainmenu       kein Eintrag im Hauptmenü für das Plugin\n                                     es kann über das Setup-Menü gestartet werden\n  -n Name   --mainmenu_name=Name     Name für den Eintrag im Hauptmenü\n                                     (diese Option setzt auch -m)\n  -c        --confirm_del_rec        Bestätigung für das Löschen von Aufnahmen\n  -C        --not_confirm_del_rec    keine Bestätigung (löschen Aufnahmen)\n  -d        --confirm_del_dir        Bestätigung beim Löschen von Verzeichnissen\n  -D        --not_confirm_del_dir    keine Bestätigung (löschen Verzeichnissen)\n  -s        --confirm_undel_rec      Bestätigung Wiederherstellung von Aufnahmen\n  -S        --not_confirm_undel_rec  keine Best. Wiederherstellung von Aufnahmen\n  -t        --confirm_undel_dir      Bestätigung Wiederherstellung von Verzei.\n  -T        --not_confirm_undel_dir  keine Best. Wiederherstellung von Verzei.\n  -v        --verbose                erweiterte Protokollierung aktivieren\n  -V        --noverbose              keine erweiterte Protokollierung\n            --nosetup_commandline    Option 'Kommandozeile hat Vorrang'\n                                     im Setup-Menü verbergen\n  @config-file                       Komandozeilenoptionen auch aus der angegebenen\n                                     Datei lesen\n\n  Hinweis: Mit Aufnahmen sind hier die gelöschten Aufnahmen gemeint",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },

  { "Undelete",
    "Wiederherst.",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Deleted Recordings",
    "Gelöschte Aufnahmen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "undelete for recordings",
    "Wiederherstellung gelöschter Aufnahmen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "DelRec",
    "Löschung",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "HelpKeys",
    "Hilfstasten",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "UnDelRec",
    "Wiederherstellung",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "unknow",
    "unbekannt",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Display$please wait ...",
    "bitte warten ...",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Display$prepare recording display...",
    "Listenanzeige wird vorbereitet...",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Display$remove empty directories...",
    "Entferne leere Verzeichnisse...",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Error$Recording with the same name exists!",
    "Aufnahme mit selben Namen ist vorhanden!",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Menu$Undelete recordings",
    "Aufnahmen wiederherstellen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Question$Delete recording definitive?",
    "Aufnahme endgültig löschen?",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Question$Delete recordings in diretory definitive?",
    "Aufnahmen in Verzeichnis endgültig löschen?",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Question$Undelete recording?",
    "Aufnahme wiederherstellen?",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Question$Undelete recordings in directory?",
    "Aufnahmen in Verzeichnis wiederherstellen?",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Setup$Confirm delete deleted recordings",
    "Aufnahme löschen bestätigen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Setup$Confirm delete directories",
    "Verzeichnisse löschen bestätigen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Setup$Confirm undelete deleted recordings",
    "Wiederherstellung Aufn. bestätigen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Setup$Confirm undelete directories",
    "Wiederherstellung Verz. bestätigen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Setup$Display deleted recordings now",
    "Gelöschte Aufnahmen jetzt anzeigen",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Setup$  Name for Mainmenu",
    "  Eintragname im Hauptmenü",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Setup$Preferr Command Line Parameter",
    "Kommandozeile hat Vorrang",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Setup$Verbose Log Mode",
    "Ausführliche Protokollierung",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { "Setup$Visible in Mainmenu",
    "Im Hauptmenü sichtbar",
    "",// TODO Slovenski
    "",// TODO Italiano
    "",// TODO Nederlands
    "",// TODO Português
    "",// TODO Français
    "",// TODO Norsk
    "",// TODO suomi
    "",// TODO Polski
    "",// TODO Español
    "",// TODO Ellinika
    "",// TODO Svenska
    "",// TODO Romaneste
    "",// TODO Magyar
    "",// TODO Català
  },
  { NULL }
  };
