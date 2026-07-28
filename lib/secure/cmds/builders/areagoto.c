#include <lib.h>

string GetHelp();

inherit LIB_DAEMON;

int cmd(string str) {
    if(!sizeof(str)){
        write(GetHelp());
        return 1;
    }

    str = homedir(this_player()) + "/area/room/" + str;
    if(last(str,2) != ".c") str += ".c";

    if(!directory_exists(homedir(this_player()) + "/area")){
        write(homedir(this_player()) + "/area/ 不存在！");
        return 1;
    }

    if(!file_exists(str)){
        write("文件 "+str+" 不存在。");
        return 1;
    }

    if(strsrch(str,homedir(this_player()))){
        write("你只能使用此命令前往你控制的房间。");
        return 1;
    }

    if(catch(load_object(truncate(str,2)))){
        write("该房间有问题。你留在原地不动。");
        return 1;
    }

    this_player()->eventMoveLiving(str);

    return 1;
}

string GetHelp(){
    return ("语法: areagoto <房间>\n\n"
            "允许建造者前往其控制的房间。要查看此类房间列表: arealist room\n"
            "参见: arealist, areaclone");
}
