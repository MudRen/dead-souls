#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str){
    if(!sizeof(str)){
        this_player()->SetUserPath(0);
    }
    else {
        if(!directory_exists(str)){
            write("该路径似乎不可访问。未做更改。");
        }
        else {
            if(last(str, 1) != "/") str += "/";
            this_player()->SetUserPath(str);
        }
    }
    write("你当前的主目录: "+user_path(this_player()));
    return 1;
}

string GetHelp() {
    return ("语法: homedir [目录]\n\n"
            "将指定目录设为你的\"主目录\"，\n"
            "即输入 \"cd\" 不带参数时切换到的目录。\n"
            "如果不指定目录，主目录会重置为默认值。\n"
            "注意: 更改主目录可能会影响 QCS 放置你创建的物品的位置。\n"
            "另见: pwd, cd, env, homeroom");
}
