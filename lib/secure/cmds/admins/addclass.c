/*    /secure/cmds/admins/addclass.c
 *    from the NIghtmare V Object Library
 *    creates new classes
 *    created by Descartes of Borg 960528
 *    Version: %I%
 *    Last Modified: %D%
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string file;

    if( !args || args == "" ) return "语法: addclass <职业名>";
    if( !file_exists(file=DIR_SECURE_CFG "/classes/" + args) )
        return "文件未找到: " + file;
    CLASSES_D->AddClass(file);
    previous_object()->eventPrint("职业已添加。");
    return 1;
}

string GetHelp(string str) {
    return ("语法: addclass <职业名>\n\n"
            "允许你向职业守护进程中的职业数据添加一个新职业。"
            "具体来说，你需要先创建一个配置文件，然后使用此命令将新职业"
            "加载到职业守护进程中。文件应位于 " + DIR_SECURE_CFG +
            "/classes 目录下。文件格式如下:\n"
            "职业名称\n"
            "主职业1:多职业名称1\n"
            "...\n"
            "主职业N:多职业名称N\n"
            "技能1:技能平均值1:技能职业1\n"
            "...\n"
            "技能N:技能平均值N:技能职业N\n"
            "/secure/cfg/classes/fighter 中有一个战士的示例。"
            "这个系统确实比较复杂，但比硬编码这些值要好得多。"
            "此外，正在开发一个基于Web的管理客户端，使职业创建"
            "变成简单的表单填写。\n"
            "另见: addemote, addrace");
}
