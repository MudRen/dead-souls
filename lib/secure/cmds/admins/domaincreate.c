#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;
string gfilecont;

mixed cmd(string args) {
    string domain_path;
    string *subdirs = ({"save","room","weap","armor","npc","etc","adm","doors","meals","obj","virtual/void", "chamber", "vehicle"});
    string *alphabet = ({",", "#", ";", "^", "&", "(", ")","\"","\'","\`","?", " " });
    subdirs += ({"txt","virtual"});
    alphabet += ({ "@", "!", "$", "%", "=", "{", "}", "[", "]", ":", "<", ">", "\*" });
    alphabet += ({ "\\", "\/", "\|" });

    if(!archp(previous_object()) || this_player()->GetForced()){
        return "No.";
    }

    if(!args || args == "" || args == "/domains" || args == "/domains/" ||
            args == "domain"){
        write(this_object()->GetHelp());
        return 1;
    }

    if(first(args, 9) == "/domains/"){
        domain_path = args;
    }
    else domain_path = "/domains/"+args;

    if(sscanf(domain_path,"/domains/%s",args) != 1) return 0;
    if(last(args,1) == "/") args = truncate(args,1);

    foreach(string booboo in alphabet){
        args = replace_string(args, booboo, "_");
    }

    domain_path = "/domains/"+args;

    write("域路径为："+domain_path);

    if(directory_exists(domain_path)){
        write("该域已存在。");
        return 1;
    }

    mkdir_recurse(domain_path);

    foreach(string dir in subdirs){
        string newdir = domain_path + "/" + dir;
        write("正在创建："+newdir);
        mkdir_recurse(newdir);
    }

    cp("/obj/room.c",domain_path+"/room/start.c");
    cp("/std/death.c",domain_path+"/room/death.c");
    cp("/std/void.c",domain_path+"/room/void.c");
    cp("/std/pod.c",domain_path+"/room/pod.c");
    cp("/std/freezer.c",domain_path+"/room/freezer.c");
    cp("/std/furnace.c",domain_path+"/room/furnace.c");
    cp("/std/wiz_hall.c",domain_path+"/room/wiz_hall.c");
    gfilecont = read_file("/std/server.txt");
    gfilecont = replace_string(gfilecont,"CHANGEME",args);
    write_file(domain_path+"/virtual/server.c",gfilecont,1);
    gfilecont = read_file("/std/virtual_void.txt");
    gfilecont = replace_string(gfilecont,"CHANGEME",args);
    write_file(domain_path+"/virtual/void.c",gfilecont,1);

    write("好的。");
    return 1;
}

string GetHelp(string args) {
    return ("语法：domaincreate <域名>\n\n"
            "此命令在 /domains 目录下创建一个新的域目录，"
            "并添加域所需的适当子目录。\n"
            "另见：domainadmin, admintool");
}
