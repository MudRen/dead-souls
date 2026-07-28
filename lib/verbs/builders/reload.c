#include <lib.h>
#include <daemons.h>
#include <modules.h>
#include ROOMS_H
#include <commands.h>

inherit LIB_VERB;

string libfile = "foo";
int quiet = 0;

protected void create() {
    verb::create();
    SetVerb("reload");
    SetRules("OBJ", "STR OBJ", "STR here", "here", "every STR");
    SetErrorMessage("reload什么？");
    SetHelp("语法: reload [every] <OBJ>\n\n"
            "此命令将你指定对象的文件加载到内存中，并用新副本替换当前副本。"
            "例如，如果你更改了你持有的一把剑的某些属性，"
            "\"reload sword\"将更新更改，你将持有一把更新后的剑。\n"
            "  使用-r标志时，它会递归加载目标对象继承的所有对象。"
            "如果其中任何对象或目标对象的文件加载失败，则不会更新该对象。\n"
            "    如果你\"reload every npc\"，那么任何继承LIB_NPC的已加载对象都会被重新加载。"
            "其他可以这样使用的有效库对象有: room, sentient, armor, item。\n"
            "请注意，如果有太多物品需要重新加载，命令会因\"评估超时\"错误而失败。\n"
            "    由于加载时间较长，书籍不包含在\"every\"关键字中。\n"
            "请注意，重新加载一扇门也会重新加载该门相邻的房间。\n"
            "\n另见: copy, create, delete, modify, initfix, add");
}

mixed can_reload_obj(string str) {
    if(!builderp(this_player())) return "此命令仅适用于建造者和创造者。";
    else return 1;
}

mixed can_reload_every_str(string str){
    if(!builderp(this_player())) return "此命令仅适用于建造者和创造者。";
    else return 1;
}

mixed can_reload_str_obj(string str){
    return can_reload_obj(str);
}

mixed can_reload_word(string str){
    return can_reload_obj("foo"); 
}

mixed can_reload_str_word(string str, string str2){ 
    return can_reload_obj("foo"); 
}

mixed do_reload_obj(object ob) {
    string s1,s2, foo = "空对象: ";
    if(ob && ob->GetDoor()) ob = load_object(ob->GetDoor());
    if(!creatorp(this_player()) && strsrch(base_name(ob), homedir(this_player()))){
        write("建造者只能重新加载属于他们自己的物品。");
        return 1;
    }
    if(!ob || userp(ob)) {
        if(ob) foo = base_name(ob)+": ";
        if(!quiet){
            write(foo+"无法重新加载。");
        }
        return -1;
    }
    if(ob && ob->GetDirectionMap()){
        write(base_name(ob)+"是虚拟房间，不能进行普通重新加载。");
        return 1;
    }
    if(!strsrch(base_name(ob),"/open") ||
            sscanf(base_name(ob),"/realms/%s/tmp/%s",s1,s2) == 2){
        write(base_name(ob)+"是临时文件，不能重新加载。");
        return 1;
    }
    reload(ob, 0, quiet);
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
    return 1;
}

mixed do_reload_str_obj(string str, object ob) {
    if(str == "-r") reload(ob, 1, quiet);
    else return reload(ob, 0, quiet);
}

mixed do_reload_word(string wrd) {
    object ob = environment(this_player());
    if(wrd == "here") return do_reload_obj(ob);
    else return "失败。";
}

mixed do_reload_str_word(string wrd1, string wrd2) {
    object ob = environment(this_player());
    if(wrd1 == "-r" && wrd2 = "here") reload(ob, 1);
    else return "失败。";
}

mixed do_reload_every_str(string str){
    object *ob_pool = ({});
    int count;
    if(!archp(this_player())){
        write("此动词仅适用于大法师。");
        return 1;
    }

    switch(str){
        case "npc" : libfile = LIB_NPC; break;
        case "sentient" : libfile = LIB_SENTIENT; break;
        case "room" : libfile = LIB_ROOM; break;
        case "weapon" : libfile = LIB_WEAPON; break;
        case "item" : libfile = LIB_ITEM; break;
        case "container" : libfile = LIB_STORAGE; break;
        case "armor" : libfile = LIB_ARMOR; break;
        case "worn_storage" : libfile = LIB_WORN_STORAGE; break;
        default : libfile = str;
    }

    if(!file_exists(libfile) && !file_exists(libfile+".c")){
        write("没有这样的库文件。");
        return 1;
    }

    if(last(libfile,2) == ".c") libfile = truncate(libfile,2);
    load_object("/secure/cmds/creators/update")->cmd("-a -r "+libfile);

    ob_pool = filter(objects(), (: ( inherits(libfile, $1) ) :) );
    if(!sizeof(ob_pool)) 
        ob_pool = filter(objects(), (: ( base_name($1) == libfile ) :) );

    if(!sizeof(ob_pool)) {
        write("未找到。");
        return 1;
    }

    quiet = 1;
    call_out("unQuiet", 6);
    write("正在重新加载...");
    foreach(object ob in ob_pool){
        if(do_reload_obj(ob) > 0) count++;
    }
    quiet = 0;

    write("完成。已重新加载"+count+"个对象。");
    libfile = "foo";
    return 1;
}

void unQuiet(){
    quiet = 0;
}

