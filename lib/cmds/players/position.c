#include <lib.h>
#include <position.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    int pos;
    object ob;
    string ret;

    if(str) ob = get_object(str);
    if(!ob || !living(ob)){
        if(str){
            write("找不到该生物。");
            return 1;
        }
        ob = this_player();
        ret = "你正在 ";
    }
    else {
        ret = ob->GetShort()+" 正在 ";
    }

    pos = ob->GetPosition();

    switch(pos){
        case POSITION_STANDING : ret += "站立。";break;
        case POSITION_SITTING : ret += "坐着。";break;
        case POSITION_LYING : ret += "躺着。";break;
        case POSITION_FLYING : ret += "飞行。";break;
        case POSITION_KNEELING : ret += "跪着。";break;
        case POSITION_FLOATING : ret += "漂浮。";break;
        case POSITION_SWIMMING : ret += "游泳。";break;
        default : ret += "这里。";
    }

    write(ret);
    return 1;
}

string GetHelp() {
    return ("用法: position [生物]\n\n"
            "报告指定人物的姿势，如果不提供参数则报告你自己的姿势。");
}
