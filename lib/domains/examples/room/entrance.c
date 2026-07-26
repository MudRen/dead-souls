#include <lib.h>
#include ROOMS_H
#include "ex.h"

inherit LIB_ROOM;


void create() {
    room::create();
    SetAmbientLight(30);
    SetShort( "示例大厅入口" );
    SetLong(
            "|-----------------------------------------------------------------------------|\n\n"+
            "  你在一个宽敞空旷的房间里。这里没什么东西可供观察——目前只有\n"
            "地板、天花板和墙壁。北面的开口通向令人惊叹的示例大厅。描述顶部\n"
            "的那条线是一个非常有用的工具，用于保持所有描述和消息的标准宽度。\n\n"
            "  示例大厅中有许多房间可供浏览。每个房间只展示一两种不同类型的功能。\n"
            "例如，展示如何使用出口前触发函数。当然，你可能会将许多这些功能\n"
            "组合到一个房间中。房间文件可能会变得很长很复杂，但当你理解了\n"
            "各个部分，就很容易理解整体了。别忘了在每个房间中使用\n"
            "%^BOLD%^GREEN%^'more here'%^RESET%^。大多数房间都有注释中的解释。\n\n"
            "  最后要说的是，大多数功能都很简单。这些都是非常基础的示例。"
           );

    SetExits( ([  
                "north"   : EXPATH + "exroom1",
                "south" : START
                ]));

    //  What follows is a short tutorial on item descriptions.

    // A mapping is a special type of variable -- a list. 
    //   It has a 'key' and a 'value' which are tied together.
    //   When you query a key it returns the value.
    //   Each key must be unique.

    // The SetItems in rooms is a mapping where the key & value are
    //   both strings.

    // This: ([ ]) means what is inside is a mapping.

    // SetItems( ([ ])  ); means you're putting an entire
    //   mapping into the SetItems.  This is how we put items into
    //   various rooms.  We're manipulating the entire mapping
    //   as a whole.  You'll notice for the walls, there is an
    //   array to allow a player to do 'look wall' and 'look walls'
    //   and get the same description.  This is a very useful method.

    SetItems( ([
                "floor" : "地板很脏。",
                "ceiling" : "天花板很高。",
                ({ "wall", "walls" }) : "墙壁目前没什么特别的。",
                ]) );

    // The room code also allows us to manipulate individual 'keys' of the
    //   SetItems mapping:
    //   AddItem( "bird" , "A small robin sits  passageway you can enter.");
    //   would be a way to put the description for bird into the SetItems mapping.

    // With any mapping, when you set a value for a key that already exists 
    //   the mapping replaces the old one with the new; if that key does 
    //   not yet exist it will add it in.

    // So, when you see the ([ ]) it means you are plunking in a group of
    //   key/value pairs into the mapping.

    // Finally, if you do SetItems( ([ ]) );  it is going to replace
    //   the entire SetItems mapping with what is in the ([ ]).
    //   If you do AddItem(); it will ADD the new mapping to  
    //   the existing SetItems mapping.  

    // To illustrate you need to call the test1() function in this room.
    //   To do that, do the following:
    //   > call here->test1()

}

void test1()
{
    write("现在看看这个房间");
    SetItems( ([
                "north wall" : "北墙上有一个出口。",
                "east wall" : "东墙被漆成了蓝色。",
                "south wall" : "南墙被漆成了黄色。",
                "west wall" : "西墙被漆成了绿色。",
                "wall" : "哪面墙？北墙、南墙、东墙还是西墙？",
                "walls" : "哪面墙？北墙、南墙、东墙还是西墙？"
                ]) );

    // In this example, when overwriting the SetItems mapping, you are
    //   not able to use arrays at this time.  That is the reason that
    //   'wall' and 'walls' is not listed as you first saw.  Keep this
    //   in mind when overwriting existing mappings.  As you'll also
    //   notice, as mentioned above, you can no longer look at the floor
    //   or the ceiling since the whole SetItems mapping has been replaced.

    // Now let's add one description to the list.
    AddItem( "statue", "这里有一座巫师的雕像。" );

    return;
}
