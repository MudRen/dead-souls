/*
// File     :  /domains/Praxis/court_room.c
// Comment  :  The Court where High Justice is served.
// 94-07-02 :  Pallando @ Nightmare wrote it
 */
#include <lib.h>
#include ROOMS_H
#include <council.h>

#define COUNCIL_CHAMBER "/domains/Praxis/council"

inherit LIB_ROOM;

object defendant;

void create()
{
    ::create();
    SetProperties( ([
                "indoors" : 1,
                "light" : 2,
                "no castle" : 1,
                "no teleport" : 1,
                "no bump" : 1,
                "no attack" : 1,
                "no steal" : 1,
                "no magic" : 1,
                ]) );
    SetShort( "高等法院" );
    SetLong(
            "这个房间的巨大规模让你目眩。从你站的地方看不到天花板。"
            "房间的一端是一把巨大的椅子，椅子前面是一张桌子。"
            "椅子和桌子都是用这片土地上最好的木材制成的。"
            "桌子旁边有第二把椅子，供证人坐。"
            "房间的另一侧是一排排椅子，中间有一条过道。"
            "两扇门通往房间外面，北边是市政厅，东边是治安官办公室。\n"
           );
    SetExits( ([
                "north" : "/domains/Praxis/town_hall",
                "east"  : "/domains/Praxis/sheriff",
                ]) );
    SetItems( ([
                "view" : "普拉克西斯的壮观全景。",
                "gavel" : "一个木制锤状物体，用于敲击。",
                "chair" : "用最好的木材制成。",
                "desk" : "一张用最好的木材制成的大桌子。",
                ({ "door", "doors" }) :
                "通往房间外面的大型木门。",
                "ceiling" : "天花板延伸到视野之外。",
                "room" : "一个非常大、宽敞的房间，有一种相当正式的氛围。",
                "office" : "普拉克西斯治安官的办公室。",
                "wood" : "最高品质的木材，专门由精灵森林的树木制成。",
                ]) );
}

varargs int justicep( mixed arg )
{
    if( !arg ) arg = this_player();
    if( objectp( arg ) ) arg = geteuid( arg );
    return -1 != member_array( arg, JUSTICES) || member_array( arg, POLICECOM );
}

int release_objects( object ob )
{
    return ob != defendant;
}

void init()
{
    add_action( "cmd_law", "law" );
    ::init();
    if( !creatorp( this_player() ) && !justicep( this_player() ) )
        return;
    add_action( "cmd_summon", "summon" );
    add_action( "cmd_verdict", "verdict" );
    add_action( "cmd_sentence", "sentence" );
}

int cmd_law( string title )
{
    return COUNCIL_CHAMBER-> cmd_law( title );
}


int cmd_summon( string arg )
{
    object victim;

    if( !arg )
        return notify_fail( "语法：summon <玩家名>\n" );
    if( victim = present( arg, this_object() ) )
    {
        if( victim == defendant )
            return notify_fail( arg + "已经在被告席上了。\n" );
    }
    else notify_fail( "治安官们没有" + arg + "。\n" );
    if( defendant )
        tell_object( defendant, "你的审判暂停了。你可以离开。\n" );
    defendant = victim;
    say( defendant-> query_cap_name() + "被传唤到被告席。\n" );
    return 1;
}

int cmd_verdict( string arg )
{
    if( !arg )
        return notify_fail( "语法：verdict guilty|innocent|none\n" );
    if( !defendant )
        return notify_fail( "你必须先传唤被告。\n" );
    switch( arg )
    {
        case "innocent":
        case "free":
        case "insufficient evidence":
            say( "裁决：被告被判无罪。\n" );
            defendant-> set_outlaw( 0 );
            defendant = 0;
            break;
        case "guilty":
            say( "裁决：被告有罪。\n" );
            defendant-> set_outlaw( 1 );
            break;
        case "none":
        default:
            say( "裁决：被告状态无变化。\n" );
            defendant = 0;
            break;
    }
    return 1;
}

int cmd_sentence( string arg )
{
    mapping executions;
    object criminal;

    //executions = ROOM_SHERIFF-> valid_execution();
    executions = ([]);
    if( !arg || undefinedp( executions[arg] ) )
        return notify_fail(
                "语法：sentence <惩罚>\n当前选项：\n  "+
                implode( keys( executions ), "\n  " ) + "\n" );
    if( !defendant )
        return notify_fail( "你必须先传唤被告。\n" );
    say( sprintf(
                "%s说：%s，你已被正当程序判定有罪，\n"
                "  现在必须让正义得到伸张。法律的意志是，\n"+
                "  你将被从这里带到刑场，\n"+
                "  在那里你将遭受%s的折磨直到死亡。\n",
                this_player()-> query_cap_name(),
                defendant-> query_cap_name(),
                arg ) );

    criminal = defendant;
    defendant = 0;
    //ROOM_SHERIFF-> add_prisoner( criminal );
    //ROOM_SHERIFF-> execute( criminal, arg );

    return 1;
}


/* EOF */
