#include <lib.h>
#include <dirs.h>
#include <virtual.h>
#include <position.h>

inherit LIB_VIRT_LAND;

nosave private int XPosition, YPosition;

int max_north = 4999;
int max_south = 4989;
int max_east = 5015;
int max_west = 5005;

varargs void SetLongAndItems(int x, int y, int z);

varargs int LimitTravel(int requested, int maximum, int lessthan){
    if(lessthan && requested < maximum) return maximum;
    else if(lessthan && requested > maximum) return requested;
    else if(requested > maximum) return maximum;
    else return requested;
}

#if 0
int PreExit(mixed arg1, mixed arg2){
    object ob = this_player();
    if(!ob) return 0;
    if(ob->GetPosition() != POSITION_FLYING){
        write("你不在飞行状态！");
        return 0;
    }
    return 1;
}
#endif

varargs protected void create(int x, int y) {
    string n, s, e, w;
    string ne, nw, se, sw;
    string fly;

    SetNoReplace(1);
    virt_land::create();
    XPosition = x;
    YPosition = y;
    SetClimate("temperate");
    SetAmbientLight(30);
    SetLongAndItems(x, y);
    SetShort("一片平坦的平原");
    if( x == max_east ) e = "arena/" + (x) + "," + y;
    else e = "arena/" + (x+1) + "," + y;
    if( x == max_west ) w = "arena/" + (x) + "," + y;
    else w = "arena/" + (x-1) + "," + y;
    if( y == max_north ) n = "arena/" + x + "," + (y);
    else n = "arena/" + x + "," + (y+1);
    if( y == max_south ) s = "arena/" + x+ "," + (y);
    else s = "arena/" + x + "," + (y-1);
    //fly = "sky/" + x + "," + y + "," + 1;

    nw = "arena/" + LimitTravel(x - 1, max_west, 1) + "," + LimitTravel(y+1, max_north);
    ne = "arena/" + LimitTravel(x + 1, max_east) + "," + LimitTravel(y+1, max_north);
    sw = "arena/" + LimitTravel(x - 1, max_west, 1) + "," + LimitTravel(y-1, max_south, 1);
    se = "arena/" + LimitTravel(x + 1, max_east) + "," + LimitTravel(y-1, max_south, 1);

    //SetFlyRoom(__DIR__+fly);
    SetSkyDomain("town");

    SetGoMessage("你不能往那个方向走。");
    if( n ) AddExit("north", __DIR__ + n);
    if( s ) AddExit("south", __DIR__ + s);
    if( e ) AddExit("east", __DIR__ + e);
    if( w ) AddExit("west", __DIR__ + w);
    if( ne ) AddExit("northeast", __DIR__ + ne);
    if( nw ) AddExit("northwest", __DIR__ + nw);
    if( se ) AddExit("southeast", __DIR__ + se);
    if( sw ) AddExit("southwest", __DIR__ + sw);

    //AddExit("up", __DIR__ + "sky/"+x+","+y+",1", (: PreExit :) );
    //AddExit("up", __DIR__ + "sky/"+x+","+y+",1", (: PreExit :) );

    if(y == max_south){
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
    if(x == 5005 && y == 4999){
        RemoveExit("west");
        AddExit("west","/domains/default/room/wiz_corr_east3");
        AddItem("sign" , "这是一块插在地上的告示牌。");
        SetRead( ({"sign"}) , "巫师实验室在西边。");
    }
}

varargs void SetLongAndItems(int x, int y, int z) {
    mapping inv, items;
    string str;
    ::SetLongAndItems(x, y, z);

    inv = ([]);
    str = "你身处一片广阔的平坦平原上，四周被石墙环绕，"
        "形成了一个用于重武器和骑马作战的大型竞技场。";
    if(query_night()) str += " 夜空中的星星在头顶闪烁。";
    if(x == max_west && y != max_north) str += " 石墙阻止了继续向西前进。";
    if(x == max_east) str += " 石墙阻止了继续向东前进。";
    if(y == max_south ) str += " 石墙阻止了继续向南前进。";
    if(y == max_north) str += " 石墙阻止了继续向北前进。";
    if(x == max_west && y == max_north) str += "\n%^GREEN%^这里有一块可以阅读的告示牌。%^RESET%^";

    SetItems( ([ "arena" : "一个充满暴力死亡和巨大毁灭的地方。",
                ]) );

    if(y == max_north) {
        AddItem( ({ "rock wall","wall","stone wall"}),
                "这堵巨大的石墙阻止了继续向北前进。" );
    }
    else if(y == max_south) {
        AddItem( ({ "rock wall","wall","stone wall"}),
                "这堵巨大的石墙阻止了继续向南前进。" );
    }

    if(x == max_east) {
        AddItem( ({ "rock wall","wall","stone wall"}),
                "这堵巨大的石墙阻止了继续向东前进。" );
    }
    if(x == max_west) {
        AddItem( ({ "rock wall","wall","stone wall"}),
                "这堵巨大的石墙阻止了继续向西前进。" );
    }
    AddItem( ({ "walls","rock walls","stone walls" }),
            "巨大的围墙构成了这片杀戮之地的边界。" );
    SetLong(str);
    SetDayLight(30);
    SetNightLight(30);
}
