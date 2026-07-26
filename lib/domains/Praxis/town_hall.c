/*
// File     :  /domains/Praxis/town_hall.c
// Comment  :  Entrance for Court room and Council chambers
// 94-07-02 :  Pallando @ Nightmare wrote it
 */
#include <lib.h>
#include <objects.h>

#define COUNCIL_CHAMBER "/domains/Praxis/council"

inherit LIB_ROOM;

object *listeners = ({ });


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
    SetShort( "普拉克西斯市政厅" );
    SetLong(
            "这是一座宏伟的大厅；墙上挂满了华丽的挂毯，"
            "拱形屋顶由粗大的大理石柱支撑。一道宽阔的弧形楼梯"
            "通往楼上的议会厅。通往街道的出口在北边。"
           );
    SetItems( ([
                "hall" : "它有五个成年男子那么高。",
                "roof" : "如果你\"听议会\"，也许你能听到他们。",
                "hangings" : "它们描绘了作为议员的高尚自我牺牲精神。",
                "columns" : "顶部有石像鬼装饰。",
                "staircase" : "它在两根柱子之间。",
                "chambers" : "如果你仔细听，也许能听到议会的声音。",
                "court" : "审判在这里进行。",
                "street" : "修道院南边的博克拉路。",
                "gargoyles" : "它们看起来毫无生气。",
                "gargoyle" : "它像石墙一样无法穿透。",
                ]) );
    SetExits( ([
                "south" : "/domains/Praxis/court_room",
                "north" : "/domains/Praxis/e_boc_la1",
                ]) );
    SetListen( "council", (: "listen_council" :) );
}
int pre_exit_up()
{
    if( leaderp( this_player() ) || creatorp( this_player() ) )
        return 1;
    write( "一个石像鬼挡住了你的去路。\n" );
    return 0;
}
string listen_council( string arg )
{
    return "你开始倾听议会的辩论。\n";
}
int release_objects( object ob )
{
    if( -1 != member_array( ob, listeners ) )
    {
        tell_object( ob, "你停止了倾听议会。\n" );
        listeners -= ({ ob });
    }
    return 1;
}
void receive_message( string msg_class, string msg )
{
    message( msg_class, msg, listeners );
}

/* EOF */
void init(){
    ::init();
}
