#include <lib.h>
#include <dirs.h>
#include <virtual.h>

inherit LIB_VIRT_LAND;

nosave private int XPosition, YPosition, found;
nosave string lupus;
int max_north = 25;
int max_south = 1;
int max_east = -3;
int max_west = -28;


varargs void SetLongAndItems(int x, int y, int z);

varargs int LimitTravel(int requested, int maximum, int lessthan){
    if(lessthan && requested < maximum) return maximum;
    else if(lessthan && requested > maximum) return requested;
    else if(requested > maximum) return maximum;
    else return requested;
}

mixed SearchFun(object who, string str){
    object ob;
    if( found || !(ob = new("/domains/Ylsrim/etc/pole")))
        return "你没有发现任何有趣的东西。";
    found = 1;
    eventPrint(who->GetName() + "在废弃的营地中发现了一根鱼竿。", who);
    if( !(ob->eventMove(this_player())) ) {
        ob->eventMove(this_object());
    }
    return "你发现了一根鱼竿！";
}

varargs protected void create(int x, int y) {
    string n, s, e, w;
    string ne, nw, se, sw;
    string fly;

    SetNoReplace(1);
    virt_land::create();
    /* Without the virtual exemption, virts with npc's
     * wind up being perpetual motion NPC factories.
     */
    SetExemptVirtual(1);
    XPosition = x;
    YPosition = y;
    SetClimate("temperate");
    SetAmbientLight(30);
    SetLongAndItems(x, y);
    SetShort("茂密的森林");
    if( x == max_east ) e = "forest/" + (x) + "," + y;
    else e = "forest/" + (x+1) + "," + y;
    if( x == max_west ) w = "forest/" + (x) + "," + y;
    else w = "forest/" + (x-1) + "," + y;
    if( y == max_north ) n = "forest/" + x + "," + (y);
    else n = "forest/" + x + "," + (y+1);
    if( y == max_south ) s = "forest/" + x+ "," + (y);
    else s = "forest/" + x + "," + (y-1);
    fly = "sky/" + x + "," + y + "," + 1;

    nw = "forest/" + LimitTravel(x - 1, max_west, 1) + "," + LimitTravel(y+1, max_north);
    ne = "forest/" + LimitTravel(x + 1, max_east) + "," + LimitTravel(y+1, max_north);
    sw = "forest/" + LimitTravel(x - 1, max_west, 1) + "," + LimitTravel(y-1, max_south, 1);
    se = "forest/" + LimitTravel(x + 1, max_east) + "," + LimitTravel(y-1, max_south, 1);

    SetFlyRoom(__DIR__+fly);

    SetGoMessage("你无法朝那个方向前进。");
    if( n ) AddExit("north", __DIR__ + n);
    if( s ) AddExit("south", __DIR__ + s);
    if( e ) AddExit("east", __DIR__ + e);
    if( w ) AddExit("west", __DIR__ + w);
    if( ne ) AddExit("northeast", __DIR__ + ne);
    if( nw ) AddExit("northwest", __DIR__ + nw);
    if( se ) AddExit("southeast", __DIR__ + se);
    if( sw ) AddExit("southwest", __DIR__ + sw);

    if(x == -4 && y == 1){
        RemoveExit("south");
        RemoveExit("west");
        AddExit("south","/domains/town/room/forest_path1");
        RemoveExit("southeast");
        RemoveExit("southwest");

    }
    else if(y == max_south){
        RemoveExit("south");
        RemoveExit("southeast");
        RemoveExit("southwest");
    }
    if(y == max_north){
        RemoveExit("north");
        RemoveExit("northeast");
        RemoveExit("northwest");
    }
    if(x == max_west){
        RemoveExit("west");
        RemoveExit("northwest");
        RemoveExit("southwest");
    }
    if(x == max_east){
        RemoveExit("east");
        RemoveExit("northeast");
        RemoveExit("southeast");
    }
}

varargs void SetLongAndItems(int x, int y, int z) {
    mapping inv, items;
    string str;
    ::SetLongAndItems(x, y, z);

    inv = ([]);
    str = "你在一片广阔的森林中。树木和茂密的植被从四面八方逼近，"
        "看起来几乎令人感到威胁。"
        "没有路径标记你的方向。";
    if(query_night()) str += "夜空中的星星透过头顶茂密的树冠几乎看不见。";
    else str+= "阳光艰难地穿透树冠，使森林变得凉爽而黑暗。";
    if(x == max_east) str+= " 一条从北向南奔流的河流使向东的旅行变得不可能。"
            "河的对岸是一个巨大的斜坡，看起来上面有一条通往北方高原的道路。";
    if(y == max_north) str+= " 一道陡峭的悬崖在此处北方耸立，使向北进入山区的旅行变得不可能。";
    if(x == max_west) str += " 森林在西方密不可穿。";
    if(y == max_south) str += " 森林在南方密不可穿。";
    if(x == -4 && y == 1) str += "\n%^GREEN%^这里有一个你可以阅读的路牌。%^RESET%^";
    if(x == -4 && y == 25) str += "\n%^GREEN%^悬崖壁上有一个洞穴入口。%^RESET%^";
    if(x == -3 && y == 25) str += "\n%^GREEN%^悬崖壁上有一个洞穴入口。%^RESET%^";
    SetItems( ([ "forest" : "它是如此广阔。",
                ({"woods","trees","vegetation","plants"}) : "茂密、阴森且压抑，"
                "这些似乎增添了一种危险和幽闭恐惧的气氛。",
                "no path" : "你观察到了它的缺失。",
                ({"mountain","mountains"}): "从这里可以隐约看到北方伟大山脉的雪峰。",
                "cliff" : "在北方，一道高耸的悬崖从森林中拔地而起。",
                ({"canopy","forest canopy","heavy forest canopy"}) : "这里树木的巨大枝干"
                "和厚重的树叶形成了森林树冠，几乎像一个天花板，很少有光线能穿透。",
                ]) );
    if(y == max_north) {
        AddItem( ({ "river", "stream", "great river"}),
                "这条狭窄但湍急的河流构成了向东旅行的不可逾越的障碍。" );
        AddItem( ({ "slope","road","plateau"}), "看起来那是"
                "堡垒之路，高高在斜坡上，向北通往边境要塞。");
    }
    if(x == -4 && y == 25) {
        AddItem(({"cave","opening","entrance","cave entrance"}) ,
                "这是悬崖壁上一个相当可怕的开口，向北通入地下。");
        AddEnter("cave","/domains/town/room/cave_entrance");
        RemoveExit("north");
        RemoveExit("northeast");
        RemoveExit("northwest");
    }

    if(x == -3 && y == 25) {
        AddItem(({"cave","opening","entrance","cave entrance"}) ,
                "这是悬崖壁上一个黑暗的开口，向北通入地下。");
        AddEnter("cave","/domains/amigara/room/cave");
        RemoveExit("north");
        RemoveExit("northeast");
        RemoveExit("northwest");
    }

    if(x == -4 && y == 1) {
        if(random(99) > 95) lupus = "Bad Wolf!";
        else lupus = "Straight on! Beware th";
        AddItem("sign" , "这是一个匆忙书写的路牌，插在地上。");
        SetRead( ({"sign"}) , lupus);
    }
    if( !random(50) ){
        str += "  烧焦的木头、散落的石头和树枝，以及其他废弃营地的痕迹散落一地。";
        AddItem( ({ "twigs", "sticks", "kindling", "wood", "burnt wood" }) ,
                "虽然早已烧成灰烬，但散落的引火物和烧焦的木头"
                "作为曾经路过此地的旅行者的记忆依然存在");
        if( random(2) ){
            SetSearch( (: SearchFun :) );
        }
    }
    else if( !random(10) )
        SetSmell("default", "你闻到了远处篝火的味道。");
    if( !random(55) )
        inv["/domains/town/npc/forest_orc"] = random(2)+1;
    if( !random(45) )
        inv["/domains/town/npc/bear"] = 1;
    if( !random(15) )
        inv["/domains/town/npc/deer"] = 1;
    if( !random(65) )
        inv["/domains/town/npc/gecko"] = 1;
    if( !random(35) )
        inv["/domains/town/npc/newt"] = 1;
    if( !random(75) )
        inv["/domains/town/npc/spider"] = 1;

    else if( !random(14) )
        SetListen("default", "你听到了远处的声音。");
    SetLong(str);
    SetDayLight(25);
    SetNightLight(0);
    SetInventory(inv);
}
