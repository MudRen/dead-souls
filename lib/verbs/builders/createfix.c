#include <lib.h>
#include <daemons.h>
#include <modules.h>
#include <virtual.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("createfix");
    SetRules("OBJ", "here");
    SetErrorMessage("createfix什么？");
    SetHelp("语法: createfix <OBJ>\n\n"
            "如果你对指定对象的文件有写权限，此命令会添加一个::create调用。"
            "缺少此调用会导致许多对象损坏或行为不可预测。"
            "\n另见: initfix, copy, create, delete, modify, reload, add");
}

mixed can_createfix_obj(string str) {
    if(!creatorp(this_player()))
        return "此命令仅适用于建造者和创造者。";
    else return 1;
}

mixed can_createfix_word(string str) { return can_createfix_obj("foo"); }

mixed do_createfix_obj(object ob) {
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
        write("玩家无法使用createfix。");
        return 1;
    }

    if(staff->eventAddCreate(base_name(ob)+".c") == 2) {
        write("文件已经有一个有效的create函数。");
    }

    else write("完成。");
    reload(ob);
    return 1;
}

mixed do_createfix_word(string wrd) {
    object ob = environment(this_player());
    return do_createfix_obj(ob);
}
