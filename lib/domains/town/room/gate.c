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
            present("gate guard",this_object())->eventForce("say 你现在太大了，无法从我身边溜过去。你不能再进入公馆了。");
            return 0;
        }
    }
    if((newbiep(this_player()) || this_player()->GetLevel() <= maxnoob)
            && guard && living(guard)){
        tell_object(this_player(),"你是个如此的新手，门卫甚至没注意到你从他身边溜过去。");
        tell_room(this_object(),this_player()->GetName()+" 偷偷溜过门卫。",({ this_player() }) );
    }
    return 1;
}	

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("公馆大门");
    SetLong("你站在一座大型美丽公馆的大门前，公馆位于南边。前柱子上的科林斯柱头表明了居住在这里的人物的财富和重要性。茂密的常春藤缠绕着大门和环绕庄园的砖墙。");
    SetItems( ([
                "gate" : "一个漂亮的锻铁入口控制点。",
                ({"estate", "mansion"}) : "公馆的庭地在南边。",
                ({"capital","capitals","corinthian capital","corinthian capitals"}) :
                "这些是支撑公馆前悬垂物的柱子顶部。精美详细的茛苕叶雕刻使它们被区分为科林斯式。",
                ({"overhang","front overhang"}) : "公馆前由柱子支撑的华丽而不必要的结构。",
                ({"pillar","pillars","column","columns"}) : "支撑公馆前悬垂物的承重结构。",
                ({"ivy","lush ivy"}) : "常春藤植物的藤蔓在墙壁和大门上来回缠绕，如此茂密以至于几乎将它们遮蔽。",
                ({"wall","walls"}) : "防止随意进入的建筑特征。它们由砖块制成，看起来古老而坚固。",
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
