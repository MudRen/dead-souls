/*    /cmds/creator/exits.c
 *    from the Dead Souls LPC Library
 *    Command to display exit and enter info for rooms
 *    by Kalinash 100195
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(){
    string *asExits, sDir, sExit;
    string *asEnters;
    object oEnv;

    if ( !( oEnv = environment( this_player() ) ) )
        return "你没有有效的环境。";
    if(oEnv->GetRiders()) oEnv = environment( oEnv );
    if ( !oEnv )
        return "无效的环境。";

    asExits = oEnv->GetExits();
    asEnters = oEnv->GetEnters();

    message( "Nmy_action", sprintf("\t *** %s ***\n\n", identify( oEnv ) ),
            this_player() );

    if ( !( sizeof( asExits ) ) )
        message( "my_action", "这个房间没有出口。", this_player() );
    else {
        message( "Nmy_action", "这个房间有以下出口：\n\n",
                this_player() );
        foreach( sExit in asExits ) {
            message( "my_action", sprintf( "\t%10s -> %s", sExit,
                        oEnv->GetExit( sExit ) ), this_player() );
        }
    }

    if ( !( sizeof( asEnters ) ) )
        message( "my_action", "\n这个房间没有入口。", this_player() );
    else {
        message( "Nmy_action", "\n这个房间有以下入口：\n\n",
                this_player() );
        foreach( sExit in asEnters ) {
            message( "my_action", sprintf( "\t%10s -> %s", sExit,
                        oEnv->GetEnter( sExit ) ), this_player() );
        }
    }

    return 1;
}

string GetHelp(){ 
    return ("语法：exits\n\n显示当前房间的出口和入口信息。");
}
