#include <lib.h>
#include "ex.h"

inherit PAPAROOM;

void create()
{
    ::create();
    SetAmbientLight(30);
    SetShort( "子文件示例" );
    SetLong("这是一个属性继承自另一个房间的示例房间。\n<look more> 查看更多信息。"
    );

    //Note:  When we set the "exits" in this room we
    //       over-write the "exits" we inherited from PAPAROOM
    // There's a way to just add an exit to the list, but exits
    // are primarily unique to each room, so this method is fine.
    SetExits( ([
        "west" : EXPATH + "exroom2",
        "east" : EXPATH + "exroom2b"
      ]));

    SetItems( ([
        "more" : @EndText
-------------------------------------------------------------------
看看CanReceive函数。
你看到 ::CanReceive(ob) 这一行了吗？
:: 表示"我所继承的文件"。
所以，我们调用（使用）exroom2.c中编写的CanReceive()函数，
然后执行我们自己的操作。

当一个对象进入这个房间（玩家、碗、剑等）时，
它就成为了变量 'ob'。

我们将变量 'ob' 传递给exroom2.c中的CanReceive()函数。

然后我们检查ob是否是玩家或创造者。（输入：man userp）
如果是，就给该对象发送一条消息。
-------------------------------------------------------------------
EndText,
      ]));

    /*   See the way I did the SetItems again for 'more'.  This is one
         way to do it.  Another way to do it is to use a (: functional :)
         like I did for the lever.  Take a look, however, at this comment
         that you are reading.  If you'll notice, I've done it a little
         differently to show you a way to comment out several lines all
         at once.  The original method that I used was to put // in front
         of the line that I wanted to comment out.  If you have several
         lines like we have here, then you'll want to begin your comment
         like you see here and end it like below.  This is how I will
         be doing large comments in future examples.
     */


}

int CanReceive(object ob)
{
    ::CanReceive();
    if ( userp(ob) )
        write("%^MAGENTA%^房间告诉你：%^BOLD%^GREEN%^你是玩家，无论是否是创造者！%^MAGENTA%^（这是来自本房间的消息）%^RESET%^\n");
    return 1;
}

void init()
{
    ::init();
}
