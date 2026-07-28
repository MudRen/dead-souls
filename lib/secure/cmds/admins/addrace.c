/*    /secure/cmds/admins/addrace.c
 *    from the NIghtmare V Object Library
 *    creates new races
 *    created by Descartes of Borg 960528
 *    Version: 1.2
 *    Last Modified: 97/01/03
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string file;
    int player;

    if( !args || args == "" ) return "语法: addrace <种族名> [1 | 0]";
    if( sscanf(args, "%s %d", file, player) != 2 ) {
        file = args;
    }
    if( !file_exists(file=DIR_SECURE_CFG "/races/" + file) )
        return "文件未找到: " + file;
    RACES_D->AddRace(file, player);
    previous_object()->eventPrint("种族已添加。");
    return 1;
}

string GetHelp(){
    return ("语法: addrace <种族名> [0 | 1]\n\n"
            "允许你向种族守护进程中的种族数据添加一个新种族。"
            "具体来说，你需要先创建一个配置文件，然后使用此命令将新种族"
            "加载到种族守护进程中。可选的第二个参数指定该种族是否为"
            "玩家种族。如果省略或为0，则该种族仅限NPC使用。"
            "如果为1，则玩家也可以使用。\n"
            "注意: 种族文件中的 PLAYER_RACE 设置会覆盖此标志。\n"
            "文件格式说明请参见:\n"
            "http://dead-souls.net/ds-creator-faq.html#2.45\n\n"
            "/secure/cfg/races/human 中有一个人类的示例。"
            "你会注意到人类没有特殊抗性。抗性、属性、肢体和手指"
            "出现的次数不重要，只要它们按抗性、属性、肢体、手指的"
            "顺序出现在文件中即可。此外，父肢体需要在任何子肢体"
            "*之前*列出。例如，右手可以在右臂之后的任何时间出现，"
            "但必须在右臂之后。\n"
            "这个系统确实比较复杂，但比硬编码这些值要好得多。\n"
            "示例: addrace murlok 0\n"
            "另见: addclass, addemote");
}
