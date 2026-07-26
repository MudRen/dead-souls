/*    /domains/Praxis/order.c
 *    from Nightmare IV
 *    a work order for a high mortal room
 *    created by Descartes of Borg 940701
 */

#include <lib.h>
#include <dirs.h>
//#include <security.h>

inherit LIB_ITEM;

int __Light, __Indoors;
string __Short, __Long, __Exit, __NewRoom;

private string create_file();

void create() {
    ::create();
    SetKeyName("work order");
    SetId( ({ "order", "work order" }) );
    SetShort("一份工作订单");
    SetLong("一份让工人们按照你的意愿修改房产的订单。"
            "要修改你的房产，进入其中任何一间房间，然后输入 \"build <房间名>\"。"
            "例如，要建造你的书房，输入："
            "\"build the study\"。你输入命令时的房间名是人们在简略模式下进入房间时看到的内容。"
            "在这种情况下，人们会看到\"The study\"。然后你会被问一些关于房间的问题。"
           );
    SetMass(10);
    SetValue(99);
    true();
}

void init() {
    ::init();
    add_action("cmd_build", "build");
}

protected int cmd_build(string str) {
    if(!str) return notify_fail("建造哪个房间？\n");
    if(file_size(ESTATES_DIRS+"/"+geteuid(this_player())) != -2)
        return notify_fail("你需要一个房产目录！\n");
    /*
       if(!high_mortalp(this_player()))
       return notify_fail("Only high mortals may build!\n");
     */
    if(strsrch(file_name(environment(this_player())),
                ESTATES_DIRS+"/"+geteuid(this_player())) != 0)
        return notify_fail("你只能在自己的地盘上建造！\n");
    __Short = str;
    message("prompt", "房间是 0) 室外，还是 1) 室内？", this_player());
    input_to("input_indoors");
    return 1;
}

protected void input_indoors(string str) {
    int x;

    x = to_int(str);
    if(x && x != 1) {
        message("system", "这不是一个有效的值。", this_player());
        return;
    }
    __Indoors = x;
    message("system", "房间的光照程度如何？", this_player());
    message("system", "    0 最暗，3 最亮", this_player());
    message("prompt", "\n请输入光照值：", this_player());
    input_to("input_light");
}

protected void input_light(string str) {
    int x;

    x = to_int(str);
    if(x && x != 1 && x != 2 && x != 3) {
        message("system", "无效的光照数值。", this_player());
        return;
    }
    __Light = x;
    message("system", "请输入房间的详细描述。"
            "详细描述是玩家在详细模式下进入房间时看到的内容。"
            "明显的出口会自动附加显示。此外，如果你添加了任何气味或声音描述，"
            "默认的气味和声音也会自动附加。所以请不要在这里描述声音或气味。", this_player());
    message("system", "请像写邮件一样输入详细描述。", this_player());
    rm(DIR_TMP+"/"+geteuid(this_player())+".estate");
    this_player()->edit(DIR_TMP+"/"+geteuid(this_player())+".estate",
            "done_edit", this_object());
}

void abort() {
    rm(DIR_TMP+"/"+geteuid(this_player())+".estate");
    message("system", "建造已中止。", this_player());
}

void done_edit(mixed *unused) {
    string str;

    if(!(str = read_file(DIR_TMP+"/"+geteuid(this_player())+".estate"))) {
        message("system", "没有详细描述！", this_player());
        return;
    }
    __Long = replace_string(str, "\n", " ");
    message("prompt", "\n你希望在哪个方向建造"+__Short+"？",
            this_player());
    input_to("input_exit");
}

protected void input_exit(string str) {
    mapping valid_exits;
    string file;

    if(member_array(str, environment(this_player())->query_exits())
            != -1) {
        message("system", "那个方向已经有房间了！", this_player());
        return;
    }
    valid_exits = ([ "north": "south", "south": "north", "east":"west",
            "west":"east", "up":"down", "down":"up", "southeast":"northwest",
            "northwest":"southeast", "southwest":"northeast",
            "northeast":"southwest" ]);
    if(!valid_exits[str]) {
        message("system", "那不是一个真正的方向！", this_player());
        return;
    }
    __Exit = "$"+(file=file_name(environment(this_player())))+";$"+valid_exits[str];
    __NewRoom= create_file();
    //seteuid(UID_ESTATES);
    write_file(file, "AddExit: $"+__NewRoom+";$"+str+"\n");
    write_file(__NewRoom, "SetProperty: $indoors;#"+__Indoors+"\n");
    write_file(__NewRoom, "SetProperty: $light;#"+__Light+"\n");
    write_file(__NewRoom, "SetShort: $"+__Short+"\n");
    write_file(__NewRoom, "SetLong: $"+__Long+"\n");
    write_file(__NewRoom, "AddExit: "+__Exit+"\n");
    //seteuid(getuid());
    message("system", "房间已开始建造。工程完成后，你将看到你的新增部分。", this_player());
    this_object()->remove();
}

private string create_file() {
    string dir, str;
    int x;

    x = sizeof(get_dir((dir = ESTATES_DIRS+"/"+geteuid(this_player())+"/")));
    while(file_exists(str = dir+"room"+x)) x++;
    return str;
}
