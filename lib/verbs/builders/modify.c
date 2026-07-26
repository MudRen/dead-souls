#include <lib.h>
#include <daemons.h>
#include ROOMS_H
#include <modules.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("modify");
    SetRules("OBJ STR", "here STR", "room STR");
    SetErrorMessage("Modify what how?");
    SetHelp("语法: modify <OBJ | here> <SETTING> <VALUE>\n\n"
            "如果你对指定对象的文件有写权限，此命令会根据你提供的参数"
            "对该文件进行更改。例如，要更改你所在房间的简短描述：\n"
            "modify here short a nice new room\n"
            "要修改一个兽人NPC的描述（如果他在你当前房间）：\n"
            "modify orc long a polite, well-groomed orc.\n\n"
            "可用设置: \n----\n"
            "%^GREEN%^room%^RESET%^: "+MODULES_CREATE->GetSettings("room")+"\n--\n"
            "%^GREEN%^npc%^RESET%^: "+MODULES_CREATE->GetSettings("npc")+"\n--\n"
            "%^GREEN%^barkeep%^RESET%^: "+MODULES_CREATE->GetSettings("barkeep")+"\n--\n"
            "%^GREEN%^vendor%^RESET%^: "+MODULES_CREATE->GetSettings("vendor")+"\n--\n"
            "%^GREEN%^weapon%^RESET%^: "+MODULES_CREATE->GetSettings("weapon")+"\n--\n"
            "%^GREEN%^item%^RESET%^: "+MODULES_CREATE->GetSettings("item")+"\n--\n"
            "%^GREEN%^armor%^RESET%^: "+MODULES_CREATE->GetSettings("armor")+"\n--\n"
            "%^GREEN%^worn_storage%^RESET%^: "+MODULES_CREATE->GetSettings("worn_storage")+"\n--\n"
            "%^GREEN%^chair%^RESET%^: "+MODULES_CREATE->GetSettings("chair")+"\n--\n"
            "%^GREEN%^bed%^RESET%^: "+MODULES_CREATE->GetSettings("bed")+"\n--\n"
            "%^GREEN%^table%^RESET%^: "+MODULES_CREATE->GetSettings("table")+"\n--\n"
            "%^GREEN%^container%^RESET%^: "+MODULES_CREATE->GetSettings("storage")+"\n----\n"
            "%^GREEN%^meal%^RESET%^: "+MODULES_CREATE->GetSettings("meal")+"\n----\n"
            "%^GREEN%^drink%^RESET%^: "+MODULES_CREATE->GetSettings("meal")+"\n----\n"
            "%^GREEN%^door%^RESET%^: "+MODULES_CREATE->GetSettings("door")+"\n----\n"
            "%^GREEN%^book%^RESET%^: "+MODULES_CREATE->GetSettings("book")+"\n----\n"
            "\n另见: copy, create, delete, reload, initfix, add");
}

mixed can_modify_obj_str(string str) {
    if(!builderp(this_player())) return "此命令仅适用于建造者和创造者。";
    else return 1;
}

mixed can_modify_word_str(string str) { return can_modify_obj_str("foo"); }

mixed do_modify_obj_str(object ob, string str) {
    object staff;
    staff = present("tanstaafl",this_player());
    if(!staff) {
        write("你必须手持创造者之杖才能使用此命令。");
        write("如果你不知道把它放在哪里了，可以从你工作室的箱子里再拿一个。");
        return 1;
    }

    if(ob->GetDirectionMap()){
        write("这是一个虚拟物品。不能使用QCS修改它。");
        return 1;
    }

    if(ob->GetNoModify() && !grepp(lower_case(str),"modify")) {
        write("这需要手动编辑。");
        return 1;
    }

    if(base_name(ob) == LIB_DUMMY &&
            !ob->GetDoor()) ob = environment(this_player());
    else if(base_name(ob) == LIB_DUMMY) ob = load_object(ob->GetDoor());

    if(starts_with(base_name(ob),"/lib/")) {
        write("这看起来是一个库对象。修改已取消。");
        return 1;
    }

    if(userp(ob)){
        write("你不能修改玩家。");
        return 1;
    }

    //staff->eventGeneralStuff(base_name(ob)+".c");
    return staff->eventModify(ob, str);
}

mixed do_modify_word_str(string wrd, string str) {
    object staff, ob;
    staff = present("tanstaafl",this_player());
    if(!staff) {
        write("你必须手持创造者之杖才能使用此命令。");
        write("如果你不知道把它放在哪里了，可以从你工作室的箱子里再拿一个。");
        return 1;
    }

    ob = environment(this_player());

    if(starts_with(base_name(ob),"/lib/")) {
        write("这看起来是一个库对象。修改已取消。");
        return 1;
    }

    return do_modify_obj_str(ob, str);
}
