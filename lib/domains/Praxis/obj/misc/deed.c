/*    /domains/Praxis/order.c
 *    from Nightmare IV
 *    a deed for a high mortal room
 *    created by Descartes of Borg 940701
 */

#include <lib.h>
#include <dirs.h>
#include <daemons.h>
//#include <security.h>

inherit LIB_ITEM;

int __Light, __Indoors;
string __Short, __Long, __Exit, __NewRoom, __EstateLong;

private string create_file();

void create() {
    ::create();
    SetKeyName("deed");
    SetId( ({ "estate deed", "deed" }) );
    SetShort("一张房产契约");
    SetLong("这是一张属于你自己的高等级玩家房产契约，附带一份工程单，"
            "工人们将按照你的意愿开始建造你的房产。"
            "要建造房产，请前往你希望建造的位置，然后输入："
            "\"build estate\"。系统会询问你一些关于房产入口房间的问题。"
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
    if(str != "estate") return 0;
    if(!high_mortalp(this_player()))
        return notify_fail("只有高等级玩家才能建造！\n");
    if(environment(this_player())->GetProperty("indoors")) {
        message("system", "你不能在室内建造房产！", this_player());
        return 1;
    }
    if(sizeof(filter_array(all_inventory(environment(this_player())),
                    "estates", this_object())) >=
            environment(this_player())->GetProperty("allow estate")) {
        message("system", "该区域无法建造房产。",this_player());
        return 1;
    }
    if(file_size(ESTATES_DIRS+"/"+geteuid(this_player())) != -2) {
        //seteuid(UID_ESTATES);
        mkdir(ESTATES_DIRS+"/"+geteuid(this_player()));
        seteuid(getuid());
    }
    __Exit = "$"+file_name(environment(this_player()))+";$exit";
    message("system", "请用一到两行描述你的房产：",
            this_player());
    input_to("input_long");
    return 1;
}

protected void input_long(string str) {
    if(str == "") {
        message("system", "输入无效。", this_player());
        return;
    }
    __EstateLong = str;
    message("system", "请为从这里进入的房间提供一个简短描述。"
            "这是在简略模式下显示的描述，例如"
            "\""+this_player()->query_CapName()+"的房产入口\"。", this_player());
    message("prompt", "请输入简短描述：", this_player());
    input_to("input_short");
}

protected void input_short(string str) {
    __Short = str;
    message("prompt", "房间是 0) 室外，还是 1) 室内？", this_player());
    input_to("input_indoors");
    return;
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
    __NewRoom= create_file();
    //seteuid(UID_ESTATES);
    write_file(__NewRoom, "SetProperty: $indoors;#"+__Indoors+"\n");
    write_file(__NewRoom, "SetProperty: $light;#"+__Light+"\n");
    write_file(__NewRoom, "SetShort: $"+__Short+"\n");
    write_file(__NewRoom, "SetLong: $"+__Long+"\n");
    write_file(__NewRoom, "AddExit: "+__Exit+"\n");
    ESTATES_D->add_estate(this_player()->query_CapName(), __NewRoom,
            file_name(environment(this_player())), __EstateLong);
    //seteuid(getuid());
    message("system", "房间已开始建造。工程完成后，你将看到你的房产。", this_player());
    this_object()->remove();
}

private string create_file() {
    string dir, str;
    int x;

    x = sizeof(get_dir((dir = ESTATES_DIRS+"/"+geteuid(this_player())+"/")));
    while(file_exists(str = dir+"room"+x)) x++;
    return str;
}

protected int estates(object ob) {
    return ob->id("estate");
}
