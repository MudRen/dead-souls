#include <lib.h>
#include ROOMS_H
#include "ex.h"

//  The #include "ex.h" is used in each of these files to remember
//    the defines for EXPATH and other variables we have defined
//    that all of these files use.  It would be tedious to have to
//    put the #define EXPATH in every file, so we put it into one
//    and include it as a reference for each file that needs it.
//    Consider it a library card.  The books that are in the library
//    (the #define's) are referenced every time you see EXPATH.

inherit LIB_ROOM;

//   I'm defining a global variable here called once to be used later
//     in the file.  A global variable is something that can be used
//      by any function in this room.  There are also local variables
//     that can be defined only in the variable using it.

int once;

//   I'm also defing a function lever_pulled() that will be called later.
mixed lever_pulled();

void create()
{
    ::create();
    SetAmbientLight(30);
    SetShort( "拉杆示例" );
    SetLong("这是一个使用简单add_action来改变描述的示例房间。这里有一个可以拉动的拉杆。"
           );

    SetExits( ([
                "north" : EXPATH + "exroom2",
                "south" : EXPATH + "entrance",
                ]));

    //   Here, take a look at how I set the lever item.  It is different
    //     that you saw in the entrance room.  What I am doing here is
    //     calling a functional.  When the player types 'look lever', it
    //     will call the functional (: lever_pulled :) that we defined above.
    //     I'll explain later in this file.

    SetItems( ([
                "lever" : ((: lever_pulled :))
                ]) );

}

//  In the init() function, I am setting our global variable 'once' to 0.  This
//    is used to reset the lever back when the room resets or the mud reboots.
//    so the next player who comes in to pull the lever, they can.
//    In the init() function, we also define the actions that can be done in the
//    room.  In this case, we need a pull action to 'pull lever'.  Whenever a player
//    types pull, it will call the function aa_pull().

void init()
{
    ::init();
    add_action("aa_pull","pull");
    once = 0;
}

//   This is the function that is called when a player types pull as mentioned above.
//      First, we need to check and see if they are pulling the correct thing.  the
//      string str is defining a local variable that will be used in this function.
//      Next, we have if( str != "lever").  That is saying if I type 'pull finger',
//      it will write 'Pull what?'.  The \n symbol means a carriage return or 'enter'
//      to go to the next line.

mixed aa_pull(string str)
{
    if ( str != "lever")
    {
        write( "拉什么？\n" );
        return 1;
    }

    //   Here we are going to check if the lever has been pulled.  If it has, 
    //     it's going to tell the player that and exit the aa_pull() function.
    //     this is done by the return 1; that you see here.

    if( once ==1 )
    {
        write( "拉杆已经被拉过了。" );
        return 1;
    }

    //  If the lever has not been pulled, this part starts.  As you'll notice, we
    //    set once = 1 to indicate that the lever has been pulled.

    write("你拉动了拉杆！\n");
    say(this_player()->GetName() + "拉动了拉杆！\n");
    once=1;
    return 1;
}

//   I told you I'd explain what the functional (: lever_pulled :) was for.
//     Below, it checks to see if the lever has been pulled.  if( !once )
//     says, if once is equal to 0 (not pulled) it returns and says the lever
//     has not been pulled.  If once is not equal to 0, then it means that it
//     has been pulled and returns a different message.

mixed lever_pulled()
{
    if( !once )
        return "拉杆嵌在墙里。也许你可以拉动它。";
    return "拉杆已经被拉过了。你来晚了！";
}
