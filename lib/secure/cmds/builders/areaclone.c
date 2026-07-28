#include <lib.h>

string GetHelp();

inherit LIB_DAEMON;

int cmd(string str) {
    object ob, env;
    string which, what, nom, ret;

    if(sscanf(str,"%s %s",which, what) != 2){
        write(GetHelp());
        return 1;
    }

    str = which;

    switch(str){
        case "weap" : str = "weap";break;
        case "weapons" : str = "weap";break;
        case "weapon" : str = "weap";break;
        case "ob" : str = "obj";break;
        case "obs" : str = "obj";break;
        case "objs" : str = "obj";break;
        case "objects" : str = "obj";break;
        case "meals" : str = "meal";break;
        case "npcs" : str = "npc";break;
        case "mob" : str = "npc";break;
        case "mobs" : str = "npc";break;
        case "mon" : str = "npc";break;
        case "monster" : str = "npc";break;
        case "monsters" : str = "npc";break;
        case "rooms" : str = "room";break;
        case "arm" : str = "armor";break;
        case "armors" : str = "armor";break;
    }

    env = environment(this_player());

    if(!env || strsrch(base_name(env), homedir(this_player()))){
        if(creatorp(this_player())){
            write("你是一名创造者。请使用 clone 命令。");
        }
        else {
            write("你只能在自己的区域内执行此操作。");
        }
        return 1;
    }

    if(str == "room"){
        write("房间无法克隆。请尝试: areagoto");
        return 1;
    }

    str = homedir(this_player()) + "/area/" + str + "/" + what;
    if(last(str,2) != ".c") str += ".c";
    write("已选择文件: "+str);

    if(!file_exists(str)){
        write(str + " 不存在！");
        return 1;
    }

    if( ret = catch(ob = new(str)) ){
        write("克隆对象时出错: " + ret);
        return 1;
    }

    if(!ob){
        write("克隆文件失败: " + str);
        return 1;
    }

    if( !(ob->eventMove(this_player())) &&
            !(ob->eventMove(environment(this_player()))) ) {
        write("无法正确移动该对象。");
        return 1;
    }

    nom = ob->GetShort();

    if( !(ret = this_player()->GetMessage("clone", ob)) )
        ret = this_player()->GetName() + "克隆了" + nom + "。";

    say(ret);
    write("你克隆了" + nom + "( " + str + " )。");

    return 1;
}

string GetHelp(){
    return ("语法: areaclone [ npc | weapon | armor | obj ] <名称>\n\n"
            "允许建造者克隆自己创建的物品副本。要查看可用物品，\n"
            "请使用 arealist 命令。\n"
            "参见: arealist, areagoto");
}
