/*    /cmds/player/spells.c
 *    From Dead Souls LPMud
 *    created by Descartes of Borg 961028
 *    Version: @(#) spells.c 1.3@(#)
 *    Last modified: 96/10/28
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    object who = previous_object();
    string* spells = ({});
    string tmp;
    int len;

    tmp = "你知道以下法术：\n";
    foreach(string spell, int val in who->GetSpellBook()) {
        spells += ({ sprintf("%:-20s: %:-3d%%", spell, val) });
    }
    if( !sizeof(spells) ) {
        tmp += "你不知道任何法术。";
    }
    else {
        foreach(string spell in spells) {
            int i = strlen(spell);

            if( i > len ) {
                len = i;
            }
        }
        len = (who->GetScreen())[0]/(len+2);
        tmp += format_page(spells, len);
    }
    who->eventPrint(tmp);
    return 1;
}

string GetHelp(){
    return ("用法: spells\n\n"
            "列出你法术书中所有法术及其熟练度。\n"
            "参考: skills, stats, status");
}
