//      /bin/user/_money.c
//      from the Dead Souls mudlib
//      a comand to allow players to search their pockets
//      created by Descartes of Borg 25 april 1993


#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    string *currs;
    string borg;
    int i, tmp;

    if(str) return 0;  /* to allow the wiz command to work */
    currs = this_player()->GetCurrencies();
    currs = filter(currs, (: this_player()->GetCurrency($1) > 0 :));
    if( !currs || !sizeof(currs) ) {
        write("你身无分文。");
        say(this_player()->GetName()+" 翻了翻空空的口袋。");
        return 1;
    }
    say(this_player()->GetName()+" 翻了翻口袋，检查了一些钱币。");
    message("my_action", "你在口袋里发现了 "+
            ((sizeof(currs) > 1) ? "这些货币: " : "只有: "), this_player());
    for(borg = "", i=0, tmp = sizeof(currs); i<tmp; i++) {
        borg += ((this_player()->GetCurrency(currs[i]))+" "+currs[i]);
        if(i == tmp-1) borg +=(".\n");
        else if(tmp > 2 && i == tmp-2) borg += (", and ");
        else if(tmp == 2) borg +=(" and ");
        else borg +=(", ");
    }
    message("my_action", borg, this_player());
    return 1;
}

string GetHelp() {
    return ("用法: money\n\n"
            "让你翻口袋查看所有类型的货币。");
}
