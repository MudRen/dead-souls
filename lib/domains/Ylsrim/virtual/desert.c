/*    /domains/Ylsrim/virtual/desert.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960302
 */

#include <lib.h>
#include <dirs.h>
#include <virtual.h>

inherit LIB_VIRT_LAND;

nosave private int XPosition, YPosition;

varargs void SetLongAndItems(int x, int y, int z);

varargs protected void create(int x, int y) {
    string n, s, e, w;

    SetNoReplace(1);
    virt_land::create();
    XPosition = x;
    YPosition = y;
    SetClimate("arid");
    SetAmbientLight(30);
    SetLongAndItems();
    SetShort(x == 25 ? "沙漠边缘" : "沙漠深处");
    if( x == 25 ) e = "desert/" + random(25) + "," + y;
    else e = "desert/" + (x+1) + "," + y;
    if( x == 1 ) w = "desert/" + random(25) + "," + y;
    else w = "desert/" + (x-1) + "," + y;
    if( y == 25 ) n = "desert/" + x + "," + random(25);
    else n = "desert/" + x + "," + (y+1);
    if( y == 1 ) s = "desert/" + x+ "," + random(25);
    else s = "desert/" + x + "," + (y-1);
    SetGoMessage("沙丘太高了，你无法从那个方向通过。");
    if( n ) AddExit("north", __DIR__ + n);
    if( s ) AddExit("south", __DIR__ + s);
    if( e ) AddExit("east", __DIR__ + e);
    if( w ) AddExit("west", __DIR__ + w);
    if(x == 7 && y == 7){
        RemoveExit("east");
        AddExit("east","/domains/Ylsrim/room/sand_room");
    }
}

varargs void SetLongAndItems(int x, int y, int z) {
    mapping inv, items;
    string str;
    ::SetLongAndItems(x, y, z);

    inv = ([]);
    str = "你身处一片广袤沙漠的中心。无尽沙海的空旷像弯刀一样割裂着你的士气。"
        "没有路径标记你的方向。";
    SetItems( ([ "desert" : "沙漠如此辽阔。" ]) );
    if( !random(50) ) {
        str += "  烧焦的木头、散落的岩石和树枝，以及其他废弃营地的痕迹散落各处。";
        AddItem( ({ "twigs", "sticks", "kindling", "wood", "burnt wood" }) ,
                "虽然早已烧成灰烬，散落的柴火和烧焦的木头"
                "作为曾经经过这里的旅行者的记忆躺在那里");
        if( random(2) ) {
            string thing;

            foreach(thing in ({ "twigs", "sticks", "kindling", "wood" }))
                SetSearch(thing, function(object who, string str) {
                        object ob;
                        string thing2;

                        if( !(ob = new("/domains/Ylsrim"+ "/etc/pole")) )
                        return 0;
                        who->eventPrint("你找到了一根钓鱼竿！");
                        eventPrint(who->GetName() + "在废弃营地中找到了一根钓鱼竿。", who);
                        foreach(thing2 in ({ "twigs", "sticks", "kindling", "wood"}))
                        RemoveSearch(thing2);
                        if( !(ob->eventMove(this_player())) ) {
                        who->eventPrint("你掉了鱼竿！");
                        eventPrint(who->GetName() + "掉了鱼竿。", who);
                        ob->eventMove(this_object());
                        }
                        return;
                        });
        }
    }
    else if( !random(10) )
        SetSmell("default", "你闻到了远处篝火的味道。");
    if( !random(25) )
        inv["/domains/Ylsrim"+ "/npc/traveller"] = random(3) + 1;
    else if( !random(4) )
        SetListen("default", "你听到远处有低语声。");
    SetLong(str);
    SetInventory(inv);
}
