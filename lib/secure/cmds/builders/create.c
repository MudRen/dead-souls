#include <lib.h>
#include <modules.h>
#include ROOMS_H
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    string arg;
    object staff;
    int room;

    if(!(PLAYERS_D->CheckBuilder(this_player()))){
        write("此命令仅供建造者和创造者使用。");
        return 1;
    }

    if(!str || str == "") {
        write("你需要更具体一些。请输入 'help create'");
        return 1;
    }

    staff = present("tanstaafl",this_player());
    if(!staff) {
        write("你必须持有创造者法杖才能使用此命令。");
        write("如果你不知道放在哪里了，可以从你工作间的箱子里");
        write("再拿一根。");
        return 1;
    }

    if(sscanf(str,"room%s",arg) == 1 ||
            sscanf(str,"enter%s",arg) == 1 ||
            sscanf(str,"exit%s",arg) == 1 ) room = 1;

    if(room) staff->make(arg);
    else staff->gmake(str);

    return 1;
}

string GetHelp() {
    return ("语法:\n"
            "        create room <方向> <文件>\n"
            "        create room none <文件>\n"
            "        create npc <文件>\n"
            "        create barkeep <文件>\n"
            "        create vendor <文件>\n"
            "        create trainer <文件>\n"
            "        create armor <文件>\n"
            "        create worn_storage <文件>\n"
            "        create weapon <文件>\n"
            "        create item <文件>\n"
            "        create container <文件>\n"
            "        create bed <文件>\n"
            "        create chair <文件>\n"
            "        create table <文件>\n"
            "        create book <文件>\n"
            "        create door <方向> <文件>\n"
            "        create exit <方向> <文件>\n"
            "\n此命令创建你所指定类型的通用副本。如果是房间，\n"
            "会将你所在的房间复制到你指定的方向。如果是其他对象，\n"
            "一个通用对象会出现在你所在的房间中。对象生成后，\n"
            "你可以使用 \"modify\" 命令对其进行修改，这些修改\n"
            "会自动保存。\n\n"
            "参见: modify, copy, delete, add, initfix");
}
