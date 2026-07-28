/*    /cmds/creator/home.c
 *    from the Dead Souls LPC Library
 *    command to take a creator home
 *    created by Descartes of Borg long ago (modified 950331)
 */

#include <lib.h>
#include <objects.h>
#include <daemons.h>

inherit LIB_DAEMON;
string arg;

mixed GoHome(string str) {
    object ob, prev;
    string who, room;

    prev = environment(this_player());
    if( !str || str == "" || !creatorp(this_player())){
        who = this_player()->GetKeyName();
    }
    else who = lower_case(str);
    if(!user_exists(who)) return "没有这样的用户。";
    room = PLAYERS_D->GetHomeRoom(who);
    if(!room || !strsrch(room, "/tmp/")){
        str = user_path(who, 1);
        if(!directory_exists(str)) return "该用户没有主目录。";
        str = user_path(who, 1)+"workroom.c";
        arg = str;
        if(!unguarded((: file_exists(arg) :)))
            return capitalize(who)+" 没有可用的工作间。";
    }
    else str = room;
    catch(ob = load_object(str));
    if(!ob){
        if(who != this_player()->GetKeyName())
            return "\n"+capitalize(who)+"的工作间有问题。";
        return "\n你的工作间有问题。";
    }
    if(ob == prev)
        return "你抽搐了一下。";
    if(who == this_player()->GetKeyName())
        if( this_player()->eventMoveLiving(ob,"$N 回家了。","$N 回到了家。") ) {
            return 1;
        }
    if(who != this_player()->GetKeyName())
        if( this_player()->eventMoveLiving(ob,"$N 去拜访"+capitalize(who)+"了。",
                    "$N 来访了。") ) {
            return 1;
        }
    return "你留在原地不动。";
}

mixed cmd(string str){
    return unguarded( (: GoHome($(str)) :) );
}

string GetHelp(){
    return ("语法: home\n        home [创造者]\n\n"
            "不带参数时，此命令将你传送回你的工作间。\n"
            "带参数时，将你传送至指定创造者的工作间。\n"
            "非创造者的建造者只能回到自己的工作间。\n"
            "参见: goto, trans, homeroom");
}
