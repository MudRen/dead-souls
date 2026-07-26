/*
 *  /domains/Praxis/room/vote_hall.c
 *  from the Dead Souls mudlib
 *  So that players can vote
 *  by Kalinash on 961026
 */

#include <lib.h>
#include <daemons.h>
#include <voting.h>

inherit LIB_ROOM;

mixed ReadList();

protected void create() {
    ::create();
    SetTown("Ylsrim");
    SetClimate("indoors");
    SetProperties( ([ "no kill" : 1, "no attack" : 1, "no steal" : 1,
                "no magic" : 1, "light" : 3, "no bump" : 1, "no teleport" : 1 ]) );
    SetShort("投票大厅");
    SetLong("你在伊尔斯利姆的投票大厅里。人们来这里提名职业领袖候选人并投票。墙上张贴着一份名单。");
    SetItems( ([ "list" : "这是候选人名单。" ]) );
    SetRead( "list", (: ReadList :) );
    SetObviousExits("down");
    SetExits( ([ "down" : "/domains/Ylsrim/room/bazaar" ]) );
}

mixed ReadList() {
    string msg;

    if( VOTING_D->GetStatus() == VOTE_NOT_RUNNING ) {
        this_player()->eventPrint("由于选举目前没有进行，名单是空的。");
        return 1;
    }

    msg = "\t亡魂职位候选人\n\n";

    foreach( string sClass in CLASSES_D->GetClasses() ) {
        msg += capitalize( sClass ) + " : ";
        foreach( string sName in VOTING_D->GetCandidates(sClass) )
            msg += capitalize(sName) + ", ";
        if( msg[strlen(msg)-2] == ',' )        
            msg = msg[0..strlen(msg)-3];
        msg += "\n";
    }

    this_player()->eventPrint( msg );
    return 1;
}

mixed CanNominate( object who ) { return 1; }
mixed CanVote( object who ) { return 1; }
mixed CanWithdraw( object who ) { return 1; }

mixed eventNominate( object who, string str ) {
    int iErr;

    if( creatorp( who ) ) {
        who->eventPrint("创造者不能投票！");
        return 1;
    }

    iErr = VOTING_D->eventAddCandidate( who->GetClass(), str );

    switch( iErr ) {
        case VOTE_NOT_RUNNING :
            this_player()->eventPrint("选举目前没有进行！");
            break;

        case VOTE_MODE_VOTING :
            this_player()->eventPrint("提名候选人的时期已过，请改为投票。");
            break;

        case VOTE_ERROR :
            this_player()->eventPrint("出现错误，你现在无法提名某人。");
            break;

        case VOTE_NOT_CLASS_MEMBER :
            this_player()->eventPrint( capitalize(str) + " 不是"
                    + pluralize( who->GetClass() ) + "的成员。");
            break;

        case VOTE_ALREADY_RUNNING :
            this_player()->eventPrint( capitalize(str) + " 已经在参选了。" );
            break;
    }
    return 1;
}

mixed eventVote( object who, string str ) {
    int    iErr;
    string sClass;

    sClass = who->GetClass();
    iErr = VOTING_D->eventCastVote( sClass, who->GetName(), str );

    switch( iErr ) {
        case VOTE_NOT_RUNNING :
            this_player()->eventPrint("选举目前没有进行！");
            break;

        case VOTE_MODE_CANDIDATES :
            this_player()->eventPrint("投票尚未开始，请改为提名候选人。");
            break;

        case VOTE_NOT_PRIMARY :
            this_player()->eventPrint("只有你的主要角色才能投票。");
            break;

        case VOTE_NOT_CLASS_MEMBER :
            this_player()->eventPrint( str + " 不是"
                    + pluralize(who->GetClass()) + "的候选人。");
            break;

        case VOTE_ALREADY_VOTED :
            this_player()->eventPrint("你已经投过票了！");
            break;

        case VOTE_SUCCESS :
            this_player()->eventPrint("你投出了你的一票！");
            break;
    }

    return 1;
}

mixed eventWithdraw( object who ) {
    int iErr;

    iErr = VOTING_D->eventRemoveCandidate( who->GetClass(), who->GetName()
            );

    switch( iErr ) {
        case VOTE_NOT_RUNNING :
            this_player()->eventPrint("选举目前没有进行！");
            break;

        case VOTE_MODE_VOTING :
            this_player()->eventPrint("选举已经开始，现在退出太晚了。");
            break;

        case VOTE_NOT_CANDIDATE :
            this_player()->eventPrint("你不是候选人。");
            break;
    }

    return 1;
}
void init(){
    ::init();
}
