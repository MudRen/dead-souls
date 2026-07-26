#include <lib.h>

inherit LIB_COMMAND;

int cmd(string str){
    int level;
    if(!str){
        write("你当前的辐射光照度: "+this_player()->GetRadiantLight()+"。");
        return 1;
    }
    if(sscanf(str,"%d",level) != 1){
        write("请指定一个数字光照等级。");
        return 1;
    }
    if(level < 0 || level > 100){
        write("请输入0到100之间的光照等级。");
        return 1;
    }
    this_player()->SetRadiantLight(level);
    write("你当前的辐射光照度: "+this_player()->GetRadiantLight()+"。");
    return 1;
}

string GetHelp(){
    return "Syntax: lightme [NUMBER]\n\n"+
        "Reports or changes the amount of light your body radiates.";
}
