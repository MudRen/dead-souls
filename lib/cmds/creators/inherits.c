#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

varargs int cmd(string str){
    string tmp, thing, file, *inheriteds;
    object ob;
    if(!str || sscanf(str,"%s %s",file,thing) != 2){
        write("语法: inherits FILE THING");
        return 1;
    }

    ob = get_object(thing);
    if(!ob){
        write("抱歉，找不到那个东西。");
        return 1;
    }
    thing = (ob->GetShort() || thing);

    if(last(file,2) == ".c") file = truncate(file,2);

    tmp = DEFINES_D->GetDefine(file);

    if(tmp) file = tmp;

    write("正在检查 " + identify(ob) + " 是否继承了 " +
            file + " ，请稍候...");
    if(file){
        if(inherits(file, ob)){
            write(thing+" inherits "+file+".");
            return 1;
        }
        inheriteds = deep_inherit_list(ob);
        foreach(string item in inheriteds){
            if(!grepp(item, file)) inheriteds -= ({ item });
        }
    }
    if(!sizeof(inheriteds)){
        write("未找到匹配项。"+ thing +
                " 似乎没有继承该文件。");
        return 1;
    }
    write("未找到精确匹配，但以下是一些可能的匹配: ");
    write(implode(inheriteds,"\n"));
    return 1;
}

string GetHelp(){
    return ("Syntax: inherits <FILE> <THING>\n\n"+
            "Tries to match FILE with the list of inherited files "+
            "for THING.\nSee also: showtree, findobj, findfun, showfuns");
}
