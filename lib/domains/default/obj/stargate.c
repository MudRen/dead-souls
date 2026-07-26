#include <lib.h>
#include <daemons.h>
#include "/lib/include/stargate.h"

inherit LIB_STARGATE;

int ReadScreen();

void create() 
{
    ::create();
    SetOrigin("stargate lab", "/domains/default/room/stargate_lab");
    SetRead(([ ({ "screen" }) : (: ReadScreen :) ]) );
    SetItems(([ ({ "screen" }) : "一个显示星门网络状态的计算机屏幕" ]) );
}

void init()
{
    ::init();
}

int ReadScreen()
{
    write("星门网络状态\n");
    write("-----------------------\n");
    write("\n");

}
