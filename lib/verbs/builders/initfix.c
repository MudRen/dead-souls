#include <lib.h>
#include <daemons.h>
#include <modules.h>
#include <virtual.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("initfix");
    SetRules("OBJ", "here");
    SetErrorMessage("initfix what?");
    SetHelp("语法: initfix <OBJ>\n\n"
            "如果你对指定对象的文件有写权限，此命令会添加一个init(){}函数。"
            "缺少此函数会导致许多对象损坏或行为不可预测。\n"
            "请注意，对门使用initfix也会重新加载门相邻的房间。\n"
            "\n另见: copy, create, delete, modify, reload, add");
}

mixed can_initfix_obj(string str) {
    if(!creatorp(this_player()))
        return "此命令仅适用于建造者和创造者。";
    else return 1;
}

mixed can_initfix_word(string str) { return can_initfix_obj("foo"); }

mixed do_initfix_obj(object ob) {
    object staff;
    string *virts = ({ LIB_VIRT_LAND, LIB_VIRT_SKY, LIB_VIRTUAL,
            LIB_VIRT_MAP, LIB_VIRT_SPACE, LIB_VIRT_SURFACE, LIB_VIRT_SUBSURFACE });
    staff = present("tanstaafl",this_player());
    if(!staff) {
        write("你必须手持创造者之杖才能使用此命令。");
        write("如果你不知道把它放在哪里了，可以从你工作室的箱子里再拿一个。");
        return 1;
    }

    if(ob->GetDoor()) ob = load_object(ob->GetDoor());

    foreach(string element in virts){
        if(inherits(element, ob)){
            write("这是一个虚拟物品。修改已中止。");
            return 1;
        }
    }

    if(first(base_name(ob),5) == "/lib/") {
        write("这看起来是一个库文件。修改已中止。");
        return 1;
    }

    if(interactive(ob)) {
        write("玩家无法使用initfix。");
        return 1;
    }

    if(staff->eventAddInit(base_name(ob)+".c") == 2) {
        write("文件已经有一个有效的init函数。");
    }

    else write("完成。");
    if(ob && inherits(LIB_DOOR,ob)){
        string *doors = environment(this_player())->GetDoors();
        if(!sizeof(doors)) return 1;
        foreach(string dir in doors){
            string substr = environment(this_player())->GetDoor(dir);
            if(last(substr,2) == ".c") substr = truncate(substr,2);
            if(substr == base_name(ob)){
                reload(load_object(environment(this_player())->GetExit(dir)));
                reload(environment(this_player()));
            }
        }
    }
    if(ob) reload(ob);
    return 1;
}

mixed do_initfix_word(string wrd) {
    object ob = environment(this_player());
    return do_initfix_obj(ob);
}
