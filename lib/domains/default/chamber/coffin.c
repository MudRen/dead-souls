#include <lib.h>
#include <position.h>

inherit LIB_CHAMBER;

protected void create() {
    chamber::create();
    SetKeyName("coffin");
    SetId(({"box"}));
    SetAdjectives(({"pine", "simple"}));
    SetShort("一口棺材");
    SetLong("这是一个简单的松木盒子，用于存放死者的遗体。");
    SetRace("vehicle");
    SetPosition(POSITION_NULL);
    SetMelee(0);
    SetNoClean(1);
    SetMount(1);
    SetMountStyle("driven");
    SetVisibleRiders(0);
    SetOpacity(100);
    SetMaxHealthPoints(20);
    SetMaxCarry(30000);
}

void init(){
    ::init();
}

int eventMove(mixed foo){
    int ret;
    ret = ::eventMove(foo);
    return ret;
}
