#include <lib.h>
inherit LIB_ROOM;

int maxnoob = MAX_NEWBIE_LEVEL;

int PreExit(){
    object guard = present("gate guard",this_object());
    if(!MAX_NEWBIE_LEVEL) maxnoob = 3;
    if(((MAX_NEWBIE_LEVEL && !newbiep(this_player())) || 
                this_player()->GetLevel() > maxnoob) &&
            (!this_player()->GetInvis() && !creatorp(this_player()) &&
             !present("testchar badge",this_player()))){
        if(guard && living(guard)){
            present("gate guard",this_object())->eventForce("say 你现在太大了，别想从我这溜过去。你不能再去庄园了。");
            return 0;
        }
    }
    if((newbiep(this_player()) || this_player()->GetLevel() <= maxnoob)
            && guard && living(guard)){
        tell_object(this_player(),"你太新手了，城门守卫甚至没注意到你溜了过去。");
        tell_room(this_object(),this_player()->GetName()+"悄悄溜过了城门守卫。",({ this_player() }) );
    }
    return 1;
}	

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("庄园大门");
    SetLong("你正站在一座宏伟美丽庄园的大门北边，庄园矗立在南边。前柱上的科林斯柱头彰显着居住于此之人的财富与地位。茂盛的常春藤缠绕着大门和环绕庄园的砖墙。");
    SetItems( ([
                "gate" : "一道漂亮的锻铁入口关卡。",
                ({"estate", "mansion"}) : "南边是庄园的领地。",
                ({"capital","capitals","corinthian capital","corinthian capitals"}) :
                "这些是支撑庄园前廊悬挑的柱头。精美的莨苕叶雕刻使其具有科林斯风格。",
                ({"overhang","front overhang"}) : "庄园前方由柱子支撑的华丽而不必要的建筑结构。",
                ({"pillar","pillars","column","columns"}) : "支撑庄园前廊悬挑的承重结构。",
                ({"ivy","lush ivy"}) : "常春藤的藤蔓沿着墙壁和大门蔓延，茂密得几乎将它们遮蔽。",
                ({"wall","walls"}) : "防止随意进入的建筑结构。它们由砖块砌成，看起来古老而坚固。",
                ]) );
    SetSkyDomain("town");
    SetExits( ([
                "north" : "/domains/town/room/road2.c",
                ]) );
    SetInventory(([
                "/domains/town/npc/mp" : ({ 3600, 1 }),
                ]));
    AddExit("south", "/domains/town/room/mansion_ext", (: PreExit :));
    AddItem(new("/domains/town/obj/lamp"));
    SetProperty("no attack", 1);
}
void init(){
    ::init();
}
