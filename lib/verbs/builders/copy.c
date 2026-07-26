#include <lib.h>
#include <daemons.h>
#include ROOMS_H
#include <modules.h>
#include <commands.h>

inherit LIB_VERB;

mixed do_copy_obj_str(object ob, string str);

int success;
string sourcefile, targetfile;

protected void create() {
    verb::create();
    SetVerb("copy");
    SetRules("STR", "OBJ STR");
    SetErrorMessage("Copy what?");
    SetHelp("语法: copy <OBJ> <NAME>\n"
            "        copy <FILENAME>\n\n"
            "以房间的文件名作为参数，此命令将该房间的所有内容（出口除外）"
            "复制到你当前的房间。\n\n"
            "当你指定一个对象并提供文件名时，此命令会复制该对象的文件"
            "并将其命名为你提供的名称。\n\n"
            "\n另见: create, delete, modify, reload, initfix, add" );
}

mixed can_copy_obj_str(object ob, string str) { return 1; }
mixed can_copy_str(string str) { return 1; }

mixed do_copy_obj_str(object ob, string str) {
    object staff;
    staff = present("tanstaafl",this_player());
    if(!staff) {
        write("你必须手持创造者之杖才能使用此命令。");
        write("如果你不知道把它放在哪里了，可以从你工作室的箱子里再拿一个。");
        return 1;
    }
    if(userp(ob)){
        write("不行。");
        return 1;
    }
    success = 0;
    sourcefile = "";
    targetfile = "";
    if(last(str,2) != ".c") str += ".c";
    str = absolute_path(this_player()->query_cwd(), str);
    if( !directory_exists(path_prefix(str)) ) {
        write("目录未找到。");
        return 1;
    }

    sourcefile = base_name(ob)+".c";
    targetfile = str;
    if(!check_privs(this_player(),str) ||
            (!check_privs(this_player(),sourcefile) &&
             strsrch(sourcefile,"/obj/"))){
        write("你没有足够的权限执行此操作。复制失败。");
        return 0;
    }
    if(!file_exists(sourcefile)) {
        write("该文件已不存在。");
        return 0;
    }
    else unguarded( (: success = cp(sourcefile, targetfile) :) );
    if(success) {
        write("复制成功。");
        return 1;
    }
    else write("复制失败。");
    return 0;
}

mixed do_copy_str(string str) {
    string str2, tmp, new_room;
    mixed source_update;
    object staff;
    staff = present("tanstaafl",this_player());
    if(!staff) {
        write("你必须手持创造者之杖才能使用此命令。");
        write("如果你不知道把它放在哪里了，可以从你工作室的箱子里再拿一个。");
        return 1;
    }
    str2 = str;
    str = absolute_path(this_player()->query_cwd(), str);

    if(last(str,2) != ".c") str += ".c";

    if( !file_exists(str) ){
        str = path_prefix(base_name(environment(this_player())))+"/"+str2;
        if(last(str,2) != ".c") str += ".c";
    }

    if( !file_exists(str) ){
        write("目录未找到。");
        return 1;
    }

    else if( !(tmp = read_file(str)) || !tmp || tmp == ""){
        write("无法读取文件 " + str + "。");
        return 1;
    }

    if((!check_privs(this_player(),str) && strsrch(str,"/obj/") ) ||
            !check_privs(this_player(),base_name(environment(this_player()))+".c")){
        write("你没有足够的权限执行此操作。复制失败。");
        return 1;
    }
    source_update = load_object("/secure/cmds/creators/update")->cmd("-a "+str);
    if(!source_update || !intp(source_update) || source_update == 0) {
        write("你的源文件无法正确更新。请先修复它。复制已中止。");
        return 1;
    }

    if(!inherits("/lib/std/room",load_object(str))) {
        write("你要复制的文件不是一个有效的房间。复制已中止。");
        return 1;
    }

    new_room = base_name(environment(this_player()));

    load_object("/secure/cmds/creators/bk")->cmd(new_room+".c");
    write("已备份此房间。要从此备份恢复，请输入: ");
    write("restore "+last_string_element(new_room,"/"));
    write("然后: update");

    staff->eventCopyRoom(str,new_room+".c");
    load_object("/secure/cmds/creators/update")->cmd("-a "+new_room);
    this_player()->eventMoveLiving(new_room);
    write("房间复制完成。");
    return 1;
}
