#include <lib.h>
#include ROOMS_H

inherit LIB_DAEMON;

int cmd(string str) {
    object *rooms = ({});

    write("当前加载的对象数量: "+sizeof(objects()));

    write("正在销毁熔炉中的对象...\n");
    flush_messages(this_player());
    update(ROOM_FURNACE);


    write("正在销毁无环境对象...");
    flush_messages(this_player());

    reap_other();
    reap_other();

    write("完成。");

    write("当前加载的对象数量: "+sizeof(objects()));
    return 1;
}

string GetHelp(){
    return ("Syntax: flushobs\n\n"+
            "Immediately incinerates anything in the furnace and "+
            "destructs all cloned non-interactive objects that "+
            "lack an environment.");
}
