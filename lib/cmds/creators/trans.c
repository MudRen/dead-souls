/*    /cmds/creator/trans.c
 *    from the Foundation II LPC Library
 *    moves a player to your location
 *    created by Descartes of Borg 950425
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    object ob;

    if( !args || args == "" ) return "传送谁？";
    if( !(ob = find_player(convert_name(args))) && !(ob = find_living(args)) )
        return "当前不存在该生物。";
    if( environment(ob) == environment(this_player()) )
        return ob->GetCapName() + "就在这里。";
    if(archp(ob) && !archp(this_player())){
        write("你不能传送管理员。");
        tell_player(ob, this_player()->GetName()+"刚刚试图传送你。");
        return 1;
    }
    ob->SetProperty("ReturnSite",base_name(environment(ob)));
    message("system", "你已被 " +
            this_player()->GetName() + " 召唤。", ob);
    if( !(ob->eventMoveLiving(environment(this_player()))) )
        return "无法移动 " + ob->GetCapName() + "。";
    else message("system", "你将 " + ob->GetCapName() +
            " 传送到了你身边。", this_player());
    return 1;
}

string GetHelp() {
    return ("Syntax: trans <living>\n\n"
            "Brings a living thing to your location.\n"
            "See also: return, goto, move, expel");
}
