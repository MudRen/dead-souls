/*    /verbs/players/vote.c
 *    from the Dead Souls  Object Library
 *    Allows players to vote
 *    created by Kalinash 961021
 *    Version: @(#) vote.c 1.1@(#)  Last modified: 96/10/21
 */

#include <lib.h>
#include "include/vote.h"

inherit LIB_VERB;

protected void create(){
    verb::create();
    SetVerb("vote");
    SetRules("for STR");
    SetErrorMessage("你想投票给谁？");
    SetHelp("用法：vote for <名字>\n\n"
            "如果在投票处，可以为你支持的候选人投票。");
}

mixed can_vote_for_str(){
    object env;
    mixed  err;
    if( !(env = environment(this_player())) ) return 0;
    err = env->CanVote( this_player() );
    if( !err ) return "这里似乎不是合适的地方。";
    else return err;
}

mixed do_vote_for_str( string str ){
    object env;
    if( !str || !(env = environment(this_player())) ) return 0;
    return env->eventVote( this_player(), str );
}
