#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_QUEST;

void create(){
    item::create();
    quest::create();
    SetKeyName("generic quest object");
    SetId( ({"thing","item","thang","dingus", "object"}) );
    SetAdjectives( ({"generic","sample","template","quest"}) );
    SetShort("普通任务物品");
    SetLong("这是一个古老时代的遗物，为了兼容性而存在。");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetQuestPoints(1);
}
void init(){
    ::init();
}
