#include <lib.h>

string GetHelp();

inherit LIB_DAEMON;

int cmd(string str) {
    string ret, *ret_arr;
    switch(str){
        case "weap" : str = "weap";break;
        case "weapons" : str = "weap";break;
        case "weapon" : str = "weap";break;
        case "ob" : str = "obj";break;
        case "obs" : str = "obj";break;
        case "objs" : str = "obj";break;
        case "objects" : str = "obj";break;
        case "object" : str = "obj";break;
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

    if(!sizeof(str)){
        write(GetHelp());
        return 1;
    }

    write("已选择分类: "+str);
    str = homedir(this_player()) + "/area/" + str;

    if(!directory_exists(homedir(this_player()) + "/area")){
        write(homedir(this_player()) + "/area/ 不存在！");
        return 1;
    }

    if(!directory_exists(str)){
        write(str + " 不存在！");
        return 1;
    }

    ret_arr = sort_array(get_dir(str + "/"),1);
    ret = "";

    foreach(string element in ret_arr){
        if(last(element,2) == ".c"){
            element = truncate(element,2);
            ret += element + "\n";
        }
    }

    if(!sizeof(ret)){
        write("没有文件。");
        return 1;
    }

    this_player()->eventPage( ({ ret }) );
    return 1;
}

string GetHelp(){
    return ("语法: arealist [ npc | room | weapon | armor | obj ]\n\n"
            "列出执行命令的建造者所控制的指定分类下的可用文件。\n"
            "例如，要查看建造者拥有的房间列表，可以执行: arealist room\n"
            "参见: areaclone, areagoto");
}
