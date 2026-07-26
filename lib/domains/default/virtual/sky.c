#include <lib.h>
#include <dirs.h>
#include <virtual.h>

inherit LIB_VIRT_SKY;

nosave private int XPosition, YPosition, ZPosition;

varargs void SetLongAndItems(int x, int y, int z);

varargs int LimitTravel(int requested, int maximum, int lessthan){
    if(lessthan && requested < maximum) return maximum;
    else if(lessthan && requested > maximum) return requested;
    else if(requested > maximum) return maximum;
    else return requested;
}

varargs protected void create(int x, int y, int z) {
    string n, s, e, w, u, d;
    string ne, nw, se, sw;

    int max_north = 10;
    int max_south = 1;
    int max_east = 10;
    int max_west = 1;
    int max_up = 10;
    int max_down = 0;

    SetNoReplace(1);
    virt_sky::create();
    XPosition = x;
    YPosition = y;
    ZPosition = z;
    SetClimate("temperate");
    SetAmbientLight(30);
    SetLongAndItems(x, y, z);
    SetShort("平坦平原上空的天空");
    if( x == max_east ) e = "sky/" + (x) + "," + y + "," + z;
    else e = "sky/" + (x+1) + "," + y + "," + z;
    if( x == max_west ) w = "sky/" + (x) + "," + y + "," + z;
    else w = "sky/" + (x-1) + "," + y + "," + z;
    if( y == max_north ) n = "sky/" + x + "," + (y) + "," + z;
    else n = "sky/" + x + "," + (y+1) + "," + z;
    if( y == max_south ) s = "sky/" + x+ "," + (y) + "," + z;
    else s = "sky/" + x + "," + (y-1) + "," + z;
    if( z == max_up ) u = "sky/" + x + "," + y + "," + (z);
    else u = "sky/" + x + "," + y + "," + (z+1);
    if( z == max_down ) d = "sky/" + x+ "," + (y) + "," + z;
    else d = "sky/" + x + "," + y + "," + (z-1);

    nw = "sky/" + LimitTravel(x - 1, max_west, 1) + "," + LimitTravel(y+1, max_north)+ "," + z;
    ne = "sky/" + LimitTravel(x + 1, max_east) + "," + LimitTravel(y+1, max_north)+ "," + z;
    sw = "sky/" + LimitTravel(x - 1, max_west, 1) + "," + LimitTravel(y-1, max_south, 1)+ "," + z;
    se = "sky/" + LimitTravel(x + 1, max_east) + "," + LimitTravel(y-1, max_south, 1)+ "," + z;

    SetGoMessage("你不能往那个方向走。");

    if( n ) AddExit("north", __DIR__ + n);
    if( s ) AddExit("south", __DIR__ + s);
    if( e ) AddExit("east", __DIR__ + e);
    if( w ) AddExit("west", __DIR__ + w);
    if( u ) AddExit("up", __DIR__ + u);
    if( d ) AddExit("down", __DIR__ + d);
    if( ne ) AddExit("northeast", __DIR__ + ne);
    if( nw ) AddExit("northwest", __DIR__ + nw);
    if( se ) AddExit("southeast", __DIR__ + se);
    if( sw ) AddExit("southwest", __DIR__ + sw);

    if(z == 1){
        RemoveExit("down");
        AddExit("down", __DIR__ + "arena/" + x + "," + y);
    }

#if 1
    if(y == 1){
        RemoveExit("south");
        RemoveExit("southeast");
        RemoveExit("southwest");
    }
    else if(y == 10){
        RemoveExit("north");
        RemoveExit("northeast");
        RemoveExit("northwest");
    }
    if(x == 1){
        RemoveExit("west");
        RemoveExit("northwest");
        RemoveExit("southwest");
    }
    if(x == 10){
        RemoveExit("east");
        RemoveExit("northeast");
        RemoveExit("southeast");
    }
#endif
}

varargs void SetLongAndItems(int x, int y, int z) {
    mapping inv, items;
    string str;
    ::SetLongAndItems(x, y, z);

    inv = ([]);
    str = "你身处一片广阔平坦平原的上空，四周被石墙环绕，"
        "形成了一个用于重武器和骑马作战的大型竞技场。";
    if(query_night()) str += " 夜空中的星星在头顶闪烁。";
    if(x == 1) str += " 石墙阻止了继续向西前进。";
    if(x == 10) str += " 石墙阻止了继续向东前进。";
    if(y == 1) str += " 石墙阻止了继续向南前进。";
    if(y == 10) str += " 石墙阻止了继续向北前进。";
    if(x == 5 && y == 1) str += "\n%^GREEN%^这里有一块可以阅读的告示牌。%^RESET%^";

    SetItems( ([ "arena" : "一个充满暴力死亡和巨大毁灭的地方。",
                ]) );

    if(y == 10) {
        AddItem( ({ "rock wall","wall","stone wall"}),
                "这堵巨大的石墙阻止了继续向北前进。" );
    }
    else if(y == 1) {
        AddItem( ({ "rock wall","wall","stone wall"}),
                "这堵巨大的石墙阻止了继续向南前进。" );
    }

    if(x == 10) {
        AddItem( ({ "rock wall","wall","stone wall"}),
                "这堵巨大的石墙阻止了继续向东前进。" );
    }
    if(x == 1) {
        AddItem( ({ "rock wall","wall","stone wall"}),
                "这堵巨大的石墙阻止了继续向西前进。" );
    }
    AddItem( ({ "walls","rock walls","stone walls" }),
            "巨大的围墙构成了这片杀戮之地的边界。" );
    SetLong(str);
    SetDayLight(30);
    SetNightLight(30);
}
