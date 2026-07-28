/*    /cmds/creator/clone.c
 *    from the Dead Souls LPC Library
 *    clones objects for cres
 *    created by Descartes of Borg 950409
 *    Version: @(#) clone.c 1.2@(#)
 *    Last modified: 96/10/08
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    object ob, dest;
    string file, res, nom;

    if( args == "" || !args ) return "克隆什么？";
    file = absolute_path(this_player()->query_cwd(), args);
    if( file[<2..] != ".c" ) file = file + ".c";
    if( file_size(file) < 0  ){
        ob = get_object(args);
        if(ob){
            file = base_name(ob)+".c";
        }
    }
    if( res = catch(ob = new(file)) ) 
        return "Error in cloning object: " + res;
    if( !ob ){
        write("克隆文件失败: " + file);
        if(!file_exists(file)){
            write("文件 "+file+" 似乎不存在。");
        }
        return 1;
    }
    dest = ( living(ob) ? environment(this_player()) : this_player() );
    if( !(ob->eventMove(dest)) &&
            !(ob->eventMove(environment(this_player()))) ) {
        message("system", "无法正确移动该物体。",
                this_player());
        return 1;
    }
    if( !(nom = ob->GetShort()) ) nom = "某个奇怪的东西";
    if( !(res = this_player()->GetMessage("clone", ob)) )
        res = this_player()->GetName() + " 克隆了 " + nom + "。";
    message("info", "你克隆了 " + nom + " ( " + file + " )。",
            this_player());
    message("other_action", res, environment(this_player()), 
            ({ this_player() }));
    return 1;
}

string GetHelp() {
    return ("Syntax: clone <filename | object>\n\n"
            "Clones the object from the code stored in the file named.  "
            "If for some reason the object cannot be moved to your "
            "inventory (it is alive, you cannot carry it, etc.), then "
            "it will be moved into your environment.\n"
            "See also: dest, message");
}
