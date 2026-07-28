/*    /cmd *    from Dead Souls
 *    help for the cd command (located inside the player object)
 *    created by Descartes of Borg 940723
 */

#include <lib.h>

inherit LIB_DAEMON;

string GetHelp() {
    return ("语法: cd [目录]\n\n"
            "定义在用户对象内部。\n"
            "将当前工作目录更改为你指定的目录。\n"
            "如果未指定目录，将切换到你的主目录。\n"
            "另见: pwd, mkdir, rmdir");
}
