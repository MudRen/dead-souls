#include <lib.h>
#include "ex.h"

inherit LIB_ROOM;

void create()
{
    ::create();
    SetAmbientLight(30);
    SetShort( "移动玩家示例" );
    SetLong(@EndText
这是一个用于演示移动玩家的示例房间。这里没什么可看的。
但是，惊喜的是，这里有一个可以拉动的拉杆。

我们将稍微复杂一点，当玩家拉动拉杆时会触发一些特殊效果。
EndText
    );

    SetExits( ([  
        "south" : EXPATH + "exroom2",
        "north" : EXPATH + "exroom4",
      ]));

}

void init()
{
    ::init();
    add_action("aa_pull","pull");
}

int aa_pull(string str)
{
    if (str!="lever")
    {
        write( "拉什么？\n" );
        return 1;
    }
    write(@EndText
你拉动了拉杆，一只大手抓住了你！
它把你带到了未知的地方。好吧，其实是已知的地方。
到达后四处看看吧，这基本上是瞬间完成的。
EndText);
    say(this_player()->GetName() + "拉动了拉杆！");
    this_player()->eventMoveLiving(EXPATH + "exroom1", "forcibly when a big hand takes " + objective(this_player()) + " away",
      this_player()->GetName() + " is dropped from the sky by a big hand." 
    );
    return 1;
}

/*  The eventMoveLiving() function transports the player who pulls
    the lever to another room.  It also writes a message in the room
    that the player leaves and in the room they are sent to.
 */
