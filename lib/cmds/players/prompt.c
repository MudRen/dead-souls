#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if(!sizeof(str)){
        write(this_player()->GetPromptString());
        return 1;
    }
    this_player()->SetPrompt(str);
    this_player()->reset_prompt();
    return 1;
}

string GetHelp() {
    string cre = "$P 显示当前工作目录\n"+
        "要显示创造者角色的名字和当前目录：\nprompt $N $P >\n用黄色显示：\n"+
        "prompt %%^^YELLOW%%^^$N $P >%%^^RESET%%^^";
    if(!creatorp(this_player())) cre = "";
    return ("用法: prompt [选项]\n\n"
            "此命令允许你自定义提示符。你可以使用受保护的提示符：\n"
            "prompt >\n"
            "或者你可以选择特殊标记来创建活动提示符。可用标记有：\n"
            "$V 显示隐身状态\n"
            "$D 显示日期（服务器时间，非游戏时间）\n"
            "$T 显示时间（服务器时间，非游戏时间）\n"
            "$C 显示命令编号\n"
            "$H 显示最大生命值\n"
            "$h 显示当前生命值\n"
            "$G 显示最大魔法值\n"
            "$g 显示当前魔法值\n"
            "$I 显示最大体力值\n"
            "$i 显示当前体力值\n"
            "$M 显示mud名称\n"
            "$N 显示玩家名称\n"
            +cre+
            "\n玩家战斗信息：\n"
            "prompt hp:$h/$H mp:$g/$G sp:$i/$I > \n"
            "或: prompt status\n\n"
            "你可以使用相应的颜色标签为提示符元素着色，例如：\n"
            "prompt %%^^RED%%^^$M %%^^RESET%%^^ >\n"
            "\n参考: reprompt, env, colors");
}
