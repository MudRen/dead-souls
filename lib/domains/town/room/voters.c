#include <lib.h>
#include <daemons.h>
#include <voting.h>

inherit LIB_ROOM;

mixed ReadList();

protected void create() {
    room::create();
    SetTown("town");
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("选民登记处");
    SetLong("这间小办公室是人们履行投票公民义务的地方。你也可以在这里 'nominate 候选人'。这里有一份候选人名单。市政厅的主厅在西南方。");
    SetItems( ([ "list" : "这是候选人名单。" ]) );
    SetExits( ([ 
                "southwest" : "/domains/town/room/thall",
                ]) );
    SetRead( "list", (: ReadList :) );
    SetProperties (([
                "no attack":1, 
                "no bump":1, 
                "no steal":0, 
                "no magic":0, 
                "no paralyze":0, 
                "no teleport":0]));
    SetInventory(([
                ]));
}

mixed ReadList() {
    string msg, admin;

    admin = "\n管理员可用的特殊命令：\n";
    admin += "tally\t\t\t报告投票统计。\n";
    admin += "nextday\t\t\t将投票日程推进一天。\n";
    admin += "startvote\t\t开始投票。\n";
    admin += "endvote\t\t\t结束投票。\n";
    admin += "votestatus\t\t报告投票状态。\n";
    admin += "votemode\t\t报告投票守护进程的运行模式。\n\n";

    if(archp(this_player())) this_player()->eventPrint( admin );

    if( VOTING_D->GetStatus() == VOTE_NOT_RUNNING ) {
        this_player()->eventPrint(VOTING_D->GetCurrentCouncil());
        return 1;
    }

    msg = VOTING_D->GetCurrentCouncil();
    msg += "\n\t亡灵之魂职位候选人\n\n";

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
            this_player()->eventPrint("选举现在没有进行！");
            break;

        case VOTE_MODE_VOTING :
            this_player()->eventPrint("提名候选人的时间已经过了，请改为投票。");
            break;

        case VOTE_ERROR :
            this_player()->eventPrint("出现错误，你现在无法提名某人。");
            break;

        case VOTE_NOT_CLASS_MEMBER :
            this_player()->eventPrint( capitalize(str) + "不是"
                    + pluralize( who->GetClass() ) + "的成员。");
            break;

        case VOTE_ALREADY_RUNNING :
            this_player()->eventPrint( capitalize(str) + "已经在参选了。" );
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
            this_player()->eventPrint("选举现在没有进行！");
            break;

        case VOTE_MODE_CANDIDATES :
            this_player()->eventPrint("投票还没有开始。我们仍在提名候选人。请改为提名候选人。");
            break;

        case VOTE_NOT_PRIMARY :
            this_player()->eventPrint("只有你的主角色可以投票。");
            break;

        case VOTE_NOT_CLASS_MEMBER :
            this_player()->eventPrint( str + "不是"
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
            this_player()->eventPrint("选举现在没有进行！");
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

mixed tally(){
    write("投票守护进程说：\"投票已统计。\"");
    return VOTING_D->eventTallyVotes();
}
mixed nextday(){
    write("投票守护进程说：\"投票日程推进了一天。\"");
    return VOTING_D->eventNextDay();
}
mixed startvote(){
    return VOTING_D->eventStartVoting();
}
mixed endvote(){
    write("投票守护进程说：\"投票已结束。\"");
    return VOTING_D->eventEndVoting();
}
mixed votestatus(){
    write("投票守护进程说：\"状态位运算符。\"");
    return VOTING_D->GetStatus();
}
mixed votemode(){
    write("投票守护进程说：\"模式位运算结果。\"");
    return VOTING_D->GetMode();
}

void init(){
    ::init();
    add_action("tally","tally");
    add_action("nextday","nextday");
    add_action("startvote","startvote");
    add_action("endvote","endvote");
    add_action("votestatus","votestatus");
    add_action("votemode","votemode");
}
