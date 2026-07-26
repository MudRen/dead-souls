#include <lib.h>
#include <daemons.h>
#include ROOMS_H
#include <modules.h>
#include <commands.h>

inherit LIB_VERB;

mixed do_add_obj_to_obj(object ob, object ob2);

protected void create() {
    verb::create();
    SetVerb("add");
    SetRules("OBJ", "OBJ to OBJ", "OBJ to here", "OBJ to room");
    SetErrorMessage("Add what?");
    SetHelp("语法: add <OBJ> to <OBJ>\n"
            "        add <OBJ>\n"
            "此命令将第一个对象添加到第二个对象的永久库存中，"
            "前提是你对两个文件都有访问权限。系统会提示你输入。"
            "如果目标是NPC，你可以输入一个命令让NPC在创建时执行，"
            "例如: wear shirt\n"
            "否则，在提示时输入你想要的物品数量。\n"
            "\n另见: copy, create, delete, modify, reload, initfix ");
}



mixed can_add_obj_to_obj(string one, string two){
    if(!builderp(this_player())) return "此命令不适用于普通玩家。";
    return 1;
}
mixed can_add_obj_to_here(string one) { return 1; }
mixed can_add_obj(string one) { return 1; }
mixed can_add_obj_to_room(string one) { return 1; }


mixed do_add_obj_to_here(object ob){
    return do_add_obj_to_obj(ob, environment(this_player()));
}

mixed do_add_obj_to_room(object ob){
    return do_add_obj_to_obj(ob, environment(this_player()));
}

mixed do_add_obj(object ob){
    return do_add_obj_to_obj(ob, environment(this_player()));
}

mixed do_add_obj_to_obj(object ob, object ob2) {
    object staff;
    string str, sourcefile;
    staff = present("tanstaafl",this_player());
    if(!staff) {
        write("你必须手持创造者之杖才能使用此命令。");
        write("如果你不知道把它放在哪里了，可以从你工作室的箱子里再拿一个。");
        return 1;
    }
    str = base_name(ob2)+".c";
    sourcefile = base_name(ob)+".c";

    if(userp(ob)){
        write("你不能对玩家执行此操作。");
        return 1;
    }

    if(!living(ob2) &&
            !inherits(LIB_STORAGE,ob2) &&
            !inherits(LIB_WORN_STORAGE,ob2) &&
            !inherits(LIB_ROOM,ob2)){
        write("该对象不是用来容纳其他对象的。添加操作已中止。");
        write("如果你确定这是不正确的，那么目标对象可能缺少一个有效的init函数。");
        write("请使用initfix命令修复它。");
        return 0;
    }

    if(!check_privs(this_player(),str)){
        write("你没有足够的权限对"+str+"执行此操作。添加失败。");
        return 0;
    }

    if(!check_read(sourcefile)){
        write("你没有足够的权限对"+sourcefile+"执行此操作。添加失败。");
        return 0;
    }

    if(!file_exists(sourcefile) || !file_exists(str)) {
        write("该文件已不存在。");
        return 0;
    }

    if(base_name(ob2) == LIB_DUMMY) ob = environment(this_player());
    if(base_name(ob) == LIB_DUMMY) {
        write("这不是你可以添加到其他东西上的物品。");
        return 1;
    }

    if(starts_with(base_name(ob2),"/lib/")) {
        write("这看起来是一个库对象。修改已取消。");
        return 1;
    }

    if(ob2->GetNoModify()){
        write("此对象必须手动修改。");
        return 1;
    }

    if(staff->eventAddItem(ob2, base_name(ob)))
        if(ob) ob->eventMove(ROOM_FURNACE);
    return 1;
}
