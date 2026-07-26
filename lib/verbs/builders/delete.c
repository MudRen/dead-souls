#include <lib.h>
#include <daemons.h>
#include ROOMS_H
#include <modules.h>
#include <commands.h>

inherit LIB_VERB;

int eventDeleteExit(string str);
int eventDeleteObject(object ob1, object ob2);

protected void create() {
    verb::create();
    SetVerb("delete");
    SetRules("enter STR", "room STR", "enter STR", "exit STR", "OBJ", "OBJ from OBJ", "OBJ from here", "OBJ from room");
    SetErrorMessage("Delete what?");
    SetHelp("语法: delete exit <DIRECTION>\n"
            "        delete <OBJECT>\n"
            "        delete <OBJECT> from <OBJECT>\n"
            "  此命令从另一个对象的永久库存中移除一个对象。"
            "当只指定一个对象时，此命令假定你要从当前房间的库存中移除该对象。\n"
            "  如果使用\"exit\"关键字，此命令会尝试移除你指定方向的出口。\n"
            "另见: add, copy, create, delete, modify, reload, initfix");
}


mixed can_delete_exit_str(string str) {
    return 1;
}

mixed can_delete_enter_str(string str) {
    return 1;
}

mixed can_delete_room_str(string str) {
    return 1;
}

mixed can_delete_obj(object ob){
    return 1;
}

mixed can_delete_obj_from_obj(object ob1, object ob2){
    return 1;
}

mixed can_delete_obj_from_here(object ob){
    return 1;
}

mixed can_delete_obj_from_room(object ob){
    return 1;
}

mixed do_delete_exit_str(string str) {
    return eventDeleteExit(str);
}

mixed do_delete_enter_str(string str) {
    return do_delete_exit_str(str);
}

mixed do_delete_room_str(string str) {
    return do_delete_exit_str(str);
}

mixed do_delete_obj(object ob){
    return eventDeleteObject(ob, environment(this_player()));
}

mixed do_delete_obj_from_obj(object ob1, object ob2){
    return eventDeleteObject(ob1,ob2);
}

mixed do_delete_obj_from_room(object ob){
    return do_delete_obj_from_obj(ob, environment(this_player()));
}

mixed do_delete_obj_from_here(object ob){
    return do_delete_obj_from_obj(ob, environment(this_player()));
}

int eventDeleteObject(object ob1, object ob2){
    string door;
    object staff;
    staff = present("tanstaafl",this_player());
    if(!staff) {
        write("你必须手持创造者之杖才能使用此命令。");
        write("如果你不知道把它放在哪里了，可以从你工作室的箱子里再拿一个。");
        return 1;
    }

    if(userp(ob1) || userp(ob2)){
        write("不行。");
        return 1;
    }

    if(environment(ob1) != ob2) {
        write("那里不存在该物品。");
        return 1;
    }

    if(!check_privs(this_player(),base_name(ob2))){
        write("你没有足够的权限对"+ob2->GetShort()+"执行此操作。失败。");
        return 0;
    }

    door = ob1->GetDoor();
    if(door){
        staff->eventDeleteDoor(door);
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

    staff->eventGeneralStuff(base_name(ob1)+".c");
    staff->eventGeneralStuff(base_name(ob2)+".c");
    staff->eventDeleteItem(ob1, ob2);
    return 1;
}

int eventDeleteExit(string str){
    string filename;
    string *exits;
    string *enters;
    object *players;
    object staff;
    staff = present("tanstaafl",this_player());
    if(!staff) {
        write("你必须手持创造者之杖才能使用此命令。");
        write("如果你不知道把它放在哪里了，可以从你工作室的箱子里再拿一个。");
        return 1;
    }

    filename = base_name(environment(this_player()))+".c";
    exits = load_object(filename)->GetExits();
    enters = load_object(filename)->GetEnters();

    if(member_array(str,exits) == -1 && member_array(str,enters) == -1) {
        write("这里不存在该出口。");
        return 1;
    }

    if(base_name(environment(this_player())) == ROOM_START){
        write("你应该手动编辑起始房间。更改已取消。");
        return 1;
    }

    if(!check_privs(this_player(),filename)){
        write("你不能从不属于你的房间删除出口。");
        return 1;
    }

    players = get_livings(environment(this_player()),1);
    if(member_array(str,exits) != -1) staff->eventRemoveExit(str, filename);
    else staff->eventRemoveEnter(str, filename);
    load_object("/secure/cmds/creators/update")->cmd("-a "+filename);
    players->eventMove(load_object(filename));

    exits = load_object(filename)->GetExits();

    if(member_array(str,exits) == -1) {
        write("出口已成功移除。");
        say(this_player()->GetCapName()+"移除了一个出口。");
        return 1;
    }

    else {
        write("出口移除失败。");
        return 1;
    }

}
