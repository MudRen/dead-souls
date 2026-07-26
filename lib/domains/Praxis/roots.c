inherit "/lib/std/room";

void create() {
    object pedestal, box;
    object for_test_only;

    ::create();
    SetShort("在树根之间");
    SetLong(
            "在这里，在传说中的法师树巨大钟乳石般的根部之间，一个大房间"
            "被挖掘出来。所有的水分都被魔法引导到根部，所以这里的空气非常干燥。"
            "除了树本身（偶尔还有法师），没有生命敢打扰这里的寂静。"
            "房间中央，一个小基座从地面突出，而在北墙附近，一个捐款箱"
            "提醒你对职业的财务责任。东边的小楼梯通往法师树的核心。");
    SetProperties( (["light"     : 2, 
                "indoors"   : 1 ,
                "no castle" : 1]) );
    SetItems( ([
                "room"       :  (: this_object(), "print_long" :),
                "tree"       : "你在树根之间。",
                "north wall" : "树的北墙附近有一个捐款箱",
                "wall"       : "树的北墙附近有一个捐款箱",
                "roots"      : "这些巨大的根部为庞大的法师树提供养分。"
                "根据传说，根部直达世界的核心，"
                "有效地使法师树像地球一样永久存在。",
                "stairway"   : "楼梯是从根部雕刻出来的。看起来不太坚固，"
                "但当你踏上去时你就放心了，"
                "因为楼梯分享了树本身的无限稳定性。"]) );
    SetExits( (["up" : "/domains/Praxis/mage_hall"]) );
    //box = new("/realms/nialson/mages/donation");
    //box->move(this_object());
    pedestal = new("/domains/Praxis/obj/misc/pedestal");
    pedestal->move(this_object());
#if 0
    for_test_only = new("/domains/Praxis/obj/magic/ball");
    for_test_only->move(this_object());
#endif
}

void print_long() {
    write (this_object()->GetLong());
}
void init(){
    ::init();
}
