#include <lib.h>
#include ROOMS_H

inherit LIB_DAEMON;

int cmd(string str) {
    object *rooms = ({});

    write("正在编译已加载房间的列表...");
    flush_messages(this_player());

    rooms = filter(objects(), (: inherits(LIB_ROOM, $1) :) );


    if(archp(previous_object())){

        foreach(object room in rooms){
            write("正在更新："+base_name(room));
            update(base_name(room));
        }

        update(ROOM_FURNACE);
        reap_other();
        reap_other();

        write("完成。");

        return 1;
    }
    write("您不是管理员。此命令被禁止。");
    return 1;
}

string GetHelp() {
    return ("语法：resetall\n\n"
            "卸载并重新加载当前内存中的所有房间。"
            "这往往会销毁房间中的所有非交互对象，"
            "并将所有玩家送到起始房间或虚空，"
            "因此请谨慎使用此命令。");
}
