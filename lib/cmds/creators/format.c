/* fake wiz command for the help format made by Valodin Jan 93 */
// NB A nicer solution is to make the help command check a directory in
// /doc if you are a wizard.
//          Signed... Campaign '93 "Keep /bin for commands"

#include <lib.h>

inherit LIB_DAEMON;

int cmd(string str)
{
    write("这是一个虚拟巫师命令。试试 \"help format\" 来获取\n关于某些巫师命令指定对象的信息。\n");
    return 1;
}

string GetHelp(){
    return ("NOTE: This is not a command in itself.\n" +
            "Certain wizard commands require that you specify\n" +
            "objects in a certain format.\n" +
            "The format uses prefixes to specify types of\n" +
            "objects as follows:\n" +
            "  !ob   ob is NOT an NPC or player\n" +
            "  %ob   ob is a player\n" +
            "  $ob   ob is an NPC\n" +
            "  #int  int is an ordinal value, e.g. 0, 1 , 2...\n" +
            "  /str  str is a filename of an object\n" +
            "Objects can also be \"me\", which is your player\n" +
            "  object, or \"here\", which is you environment.\n");
    write("用前缀表示的对象通过一些功能符号连接:\n" +
            "  object@environment  表示在某个环境中的对象。\n" +
            "    环境可以是对象或 object@environment。\n" +
            "  e(object)  表示对象所在的环境。\n\n");
    write("例如:\n" +
            "  !sword@%descartes  是 Descartes 背包中的剑。\n" +
            "  #2@!bag@$orc@here  是你面前兽人持有的袋子里的第3个物品。\n" +
            "     注意: #0 是第一个对象。\n" +
            "  $orc@/d/standard/square  是不应该出现在广场上的兽人。\n" +
            "参见: patch\n"+
            "参见手册: to_object, get_object, get_objects\n"+
            "");
}
