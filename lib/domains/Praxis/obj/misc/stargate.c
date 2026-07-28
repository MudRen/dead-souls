#include <lib.h>
#include <daemons.h>
#include "/lib/include/stargate.h"

inherit LIB_STARGATE;

int ReadScreen();

void create() 
{
    ::create();
    SetOrigin("praxis", "/domains/Praxis/square");
    SetRead(([ ({ "screen" }) : (: ReadScreen :) ]) );
    SetItems(([ ({ "screen" }) : "一个显示星门网络状态的电脑屏幕"]) );
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
