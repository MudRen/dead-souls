#include <lib.h>
#include "ex.h"

inherit LIB_ROOM;

int myvar;

void create()
{
    ::create();
    SetAmbientLight(30);
    SetShort( "主文件示例" );
    SetLong(@EndText
|---------------------------------------------------------------|-------------|
这是一个用于演示文件继承的示例房间。这个文件被另外两个
文件继承。它本身也是一个功能完整的房间。这里有一个可以
拉动的拉杆。
继承此文件的房间在东边。
EndText
    );

    //  You'll notice that for SetLong(), I've put @EndText at the top and EndText at the bottom
    //    and have not put in quotes.  When using this style of code, it is important to make sure
    //    you manually enter to the next line to wrap the lines on the player's screen.
    //    This can be a tedious if you do not know how many lines to enter before you need to
    //    continue on the next line.  If you look back to the Entrance to the Hall of Examples,
    //    You will see a handy line I've used to know when to stop a line and continue on
    //    the next.  I've included it in the room description for your convenience.  the
    //    normal screen default is 79 characters.  Whenever you would like to recreate the line
    //    at the top, type 'margins'

    SetExits( ([
        "south" : EXPATH + "exroom1",
        "north" : EXPATH + "exroom3",
        "east"  : EXPATH + "exroom2a"
      ]) );
    SetItems( ([
        "lever" : "一个可以拉动的拉杆。",
      ]) );

    myvar = 0;
}

//   The CanReceive() function is very helpful to do checks on an interactive object
//     that enters the room.  In this case, we are checking to see if the object that
//     enters is a creator player object.  If it is, then we will give a message to
//     that object with the write() funciton.  I've put some color tags to set the color
//     off from the rest of the text.  For colors available, type 'colors'.

int CanReceive(object ob)
{
    if ( creatorp(ob) )
        write( "%^BOLD%^BLUE%^房间告诉你：%^BOLD%^GREEN%^你是一个创造者！%^BOLD%^BLUE%^（这是来自主文件的消息。）%^RESET%^\n");
    return 1;
}

void init()
{
    ::init();
    add_action("aa_pull","pull");
}

//  We're going to use the variable 'myvar' in the middle of a write() funciton.  As
//   you'll notice below, the text you are writing has to be in the " ".  Then we
//   separate the text by putting in: " + myvar + ".  This adds the myvar variable
//   to the text output whenever a player pulls the lever.  Try it and see.


mixed aa_pull(string str)
{
    if (str!="lever")
        return notify_fail("拉什么？\n");
    myvar ++;
    write("你拉动了拉杆，'myvar'的值现在是 " + myvar + "\n");
    say(this_player()->GetName() + "拉动了拉杆！\n");
    return 1;
}
