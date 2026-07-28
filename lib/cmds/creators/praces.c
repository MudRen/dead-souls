/*  /cmds/creator/mraces.c
 *  A tool for cres which displays a listing of all available player races
 *  Blitz@NM-IVD
 */

#include <lib.h>
#include <daemons.h>

mixed cmd(string str) {
    string *types;

    types = load_object(RACES_D)->GetRaces(1);
    if( !sizeof(types) ) {
        return "当前没有列表。";
    }
    types = sort_array(types, 1);
    message("help", format_page(types, 5), this_player() );
    return 1;
}

string GetHelp() {
    return ("语法：praces\n\n"
            "一个简单的创造者工具，列出可用的玩家种族。");
}

