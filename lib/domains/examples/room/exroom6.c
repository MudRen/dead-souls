#include <lib.h>
#include "ex.h"

#define SPIDER "/domains/town/npc/spider"

inherit LIB_ROOM;

int pre_north();

void create()
{
    ::create();
    SetAmbientLight(30);
    SetShort( "有阻挡出口的房间" );
    SetLong(@EndText
这里没什么东西。当然，我们在长描述中不会提到蜘蛛，
因为它可能已经死了。
EndText
    );
    SetExits( ([
        "south" : "/domains/examples/room/exroom5",
      ]) );

    AddExit("north", EXPATH + "exroom7", (: pre_north :));

    SetInventory(  ([  
        SPIDER :  1,
      ]));
}

void init()
{
    ::init();
}

/*  In the pre_north() function, I am going to add a special treat!
    If a creator is invisible, you can bypass the spider completely!
    Woo! Woo!
 */

int pre_north(string dir) 
{
    if( this_player()->GetInvis(1))
        return 1;
    /*  If the spider is present, the player can not go that way. We
        are also checking to see if the spider is still alive since
        we don't want a corpse to click  menacingly. :)
        If I were to only put if(present("spider")), then the dead
        corpse would block the path and click menacingly.
        By putting the if(living(present("spider", this_object())))
        we accomplish two checks on one line. Simple and elegant.*/
    if(present("spider", this_object()) && living(present("spider",this_object())) )
    {
        write("蜘蛛挡住了你的去路，发出威胁性的咔嗒声！\n");
        say("蜘蛛挡住了" + possessive_noun(this_player()->GetName()) + "的去路，发出威胁性的咔嗒声！\n");
        return 0;
    }  
    //if we get to here, the spider is not present, so we treat as a
    //normal exit. ie: do nothing. return 1 allows the exit, if you remember.
    return 1;
}
