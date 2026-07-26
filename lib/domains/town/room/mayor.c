#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("town");
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("镇长办公室");
    SetLong("这是镇长相当狭小的办公室。尽管有些杂乱，但似乎很适合镇长的工作风格和习惯。");
    SetProperties (([
                "no attack":1, 
                "no bump":1, 
                "no steal":0, 
                "no magic":0, 
                "no paralyze":0, 
                "no teleport":0]));
    SetItems(([  
                "clutter" : "There are papers and folders everywhere, but the stacks and piles seem somehow a well-organized mess." ,
                ({"mess","stack","stacks","pile","piles","papers","paper","folder","folders"}) : "Evidence of a busy man and strangely-organized mind."]));
    SetExits( ([ 
                "down" : "/domains/town/room/thall",
                ]) );
    SetInventory(([  "/domains/town/npc/mayor" : ({60, 1})]));
}
void init() {
    ::init();
    SetSmell(([]));
    SetListen(([]));
}
