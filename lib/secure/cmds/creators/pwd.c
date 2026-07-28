/*   
 *    Help for the pwd command (located inside the player object)
 */

#include <lib.h>

inherit LIB_DAEMON;

string GetHelp() {
    return ("语法: pwd\n\n"
            "定义在用户对象内部。\n"
            "显示你的当前工作目录。\n"
            "另见: cd");
}
