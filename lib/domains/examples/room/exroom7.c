#include <lib.h>
#include "ex.h"

inherit LIB_ROOM;

int once;
int is_pulled();

void create()
{
    ::create();
    SetAmbientLight(30);
    SetShort( "双动词单动作示例" );
    SetLong(@EndText
这个房间演示了如何使用两个动词来执行同一个动作。
这里有一条链子。你可以拉它或猛拉它。

注意：看看我们如何改变链子的描述？
在任务完成后删除"任务提示"是很重要的。
然后在任务准备好时再把它们放回来。
EndText
    );

    //  Here is another functional to point to the is_pulled()
    //   function.  This is a very useful tool.

    SetItems( ([
        "chain" : (: is_pulled :),
      ]));

    SetExits( ([
        "south" : EXPATH + "exroom6",
      ]));
}

/*  Here you'll see that we have two add_actions.  We have 'pull' and
    'yank'.  If the player uses either verb when pulling the chain
    the aa_chain() function is called.
 */

void init()
{
    ::init();
    add_action("aa_chain","pull");
    add_action("aa_chain","yank");
}

/* This is the first reset() function that we've seen so I'd like
   to take a moment to explain it.  The reset() function allows
   an object to do self-maintenance.  After every reset interval
   (whose exact length is determined on a mud by mud basis, but
   averages around every 2 hours), reset() is called in every
   object that currently exists.  Here, we use the reset()
   function to return the variable 'once' back to 0 to allow the
   chain to be pulled again after reset occurs.
 */

void reset()
{
    ::reset();
    once=0;
}

/* query_verb() tells you what the player typed */
mixed aa_chain (string str)
{
    string averb=query_verb();
    if (str!="chain")
        return notify_fail(capitalize(averb)+ "什么？\n");
    if (once)
        return notify_fail("这条链子已经被拉过了。\n");

    //   We're returning the averb variable that was defined and set
    //     above in a message to the player and the room.  Then, we
    //     set the 'once' variable to show that the chain has been pulled.
    write("你拉动了链子！\n");
    say(this_player()->GetName() + "拉动了链子！\n");
    once=1;    
    return 1;
}

//  This is the functional that was called to show the current state
//    of the chain.  Pulled or not pulled.
string is_pulled()
{
    if( once )
        return "你看到一条普通的链子。\n";
    else
        return "这里有一条链子，等着被拉动。\n";
}
