#include <lib.h>
#include "ex.h"

inherit LIB_ROOM;
int pre_north();
int post_south();
int post_north();

void create()
{
    ::create();
    SetAmbientLight(30);
    SetShort( "出口前/后触发及添加/删除出口示例" );
    SetLong(@EndText
北边有一扇带门铃的门，南边是一面空白的墙。
-------------------------------------------------------------
这是一个演示出口前触发和出口后触发的示例房间。
它还展示了如何添加和删除房间的出口，以及在玩家身上
使用临时变量。

这里有一个可以拉动和推入的拉杆，还有一个可以按的铃。
拉动拉杆：创建一个向南的出口。
推入拉杆：删除向南的出口。
按铃：允许你向北走。
当你向南走后，向南的出口会消失。
-------------------------------------------------------------
EndText
    );

    SetExits( ([  
      ]));

    AddExit( "north", EXPATH + "exroom5", (: pre_north :));    

}

void init()
{
    ::init();
    add_action("aa_pull","pull");
    add_action("aa_push","push");
    add_action("aa_ring","ring");
}


int aa_pull(string str)
{
    if (str!="lever" && str!="lever out")
    {
        write( "拉什么？\n" );
        return 1;
    }
    /*  Now, we can find out if the lever has been already pulled
        in one of two ways. 
        Method one: we test to see if the exit to the south is open.
        Since pulling the lever does this, and the only way to
        create that exit is pulling the lever -- this is a valid method.

        Method two: we use a variable and change it's value when the lever
        is pushed or pulled.  Since we have a method that works without
        using an additional variable, that is the method I'll pick here.
        It will also show you how to query for an exit.

Note:  GetExits() returns a mapping for all the exits in a room
GetExit("dir") returns the value for that specific direction.
if there is NOT an exit in that direction it will return UNDEFINED
and can be detected using the ! operator. (! means 'not') 
conversely, if GetExit("dir") is true, then there IS an exit
to that direction.  Got it?  Good.
     */

    if ( GetExit("south") )
    {
        write("拉杆已经被拉出来了！\n");
        return 1;
    }

    /*  If you don't know by now, this_player() indicates the player doing the actions
        So when I do this_player()->GetName() it gives me the name of the player
        who is doing the actions and allows me to tell the room who it is.
     */

    write( "你拉动了拉杆，南墙上出现了一道隐形的裂缝。一扇门滑开了，露出了一个之前未被发现的出口。" );
    say(this_player()->GetName() + "拉动了拉杆，南边出现了一个出口。\n");

    //  AddExit() functions add an exit to the room.  Here, we added an exit and
    //  set up a (: functional :) to do close up the exit when they leave.

    AddExit( "south", EXPATH + "exroom3", (: post_south :) );
    SetObviousExits("north, south");
    return 1;
}


int aa_push(string str)
{
    if (str!="lever" && str!="lever in")
    {
        write( "推什么？\n" );
        return 1;
    }

    /*  Since there's more then one way for the exit to dissappear (see the post-exit
        function for south) and there may be more then one player wandering the halls
        we don't want to assume that 'this' player pushed the lever.  So we wouldn't
        say "You've already pushed the lever."
     */

    if ( ! GetExit("south") )
    {
        write( "拉杆已经被推到底了。\n");
        return 1;
    }
    write( "你推入拉杆，一扇看不见的门在南墙上滑动关闭。墙壁现在看起来坚固而不可穿透。" );
    say(this_player()->GetName() + "推入了拉杆，南边的出口关闭了。\n");

    //  Now we remove the exit that was added earlier.

    RemoveExit("south");
    SetObviousExits("n");
    return 1;
}


int aa_ring(string str)
{
    if (str!="bell" && str!="doorbell" && str!="door bell")
    {
        write( "按什么？\n" );
        return 1;
    }
    //if we only want to let them ring it once, we can check for the
    //temp var here.  This version will let them ring it many times.
    write("叮咚！\n你按了门铃！你现在可以向北走了。\n");
    say("叮咚！门铃响了。\n");
    this_player()->SetProperty("rung_bell", 1);
    return 1;
}


/* CODING STYLE 101
   Personally, I always put my post/pre exit functions right after create and 
   before the reset() or init() functions.  This makes them easy to find.
   Since they're MENTIONED in the create() I like to keep 'em close at hand.
   For the same reason I usually follow my init() with any add_actions that
   I've created.  I also preface my functions with an indicator saying what
   their purpose is.  I've chosen aa_ for add_actions an pe_ for pre or post
   exit functions.  OR i use pre_ or post_ when i have both going on.  This
   may not seem like a big deal in a little file, but when the file gets 
   huge, it helps to glance at a function and go: ah ha! this is a post_exit
   function.  or ah ha! this is an add_action or similarly: ah ha! this is
   not any specialized function so I must be calling it for some other reason.
   The order you write them in is a personal decision.  Just keep your
   create() function first on the list.
 */

//A return 0 in a pre-exit will prevent you from going that dir.
//A return 1 will allow you to go that dir.


int pre_north()
{
    if( !this_player()->GetProperty("rung_bell") )
    {
        write("请先按门铃！\n");
        return 0;  
    }
    //  Now that the pre_north() function has done what it needs to do, we 
    //   will call the post_north() function here
    post_north();
    return 1;
}


int post_north()
{
    //might as well delete it, it's served its purpose.
    this_player()->RemoveProperty("rung_bell");
    return 1;
}


//We're going to delete the exit AFTER the player walks through
//  Because doing it in a pre_exit would be tatamount to slamming
//  a door in their face.  You wouldn't want to do that... would you?  :P


int post_south()
{
    write("你听到一声响动，发现墙壁已经神秘地关闭了。\n");
    say("你听到一声响动，发现墙壁已经神秘地关闭了。\n");
    this_player()->eventMoveLiving("/domains/examples/room/exroom3", "south", this_player()->GetName()+" enters.");
    RemoveExit("south");
    SetObviousExits("n");
}
