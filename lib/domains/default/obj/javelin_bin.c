#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("bin");
    SetAdjectives( ({"tall", "metal", "javelin","spear"}) );
    SetId( ({"javelin bin"}) );
    SetShort="a tall metal bin";
    SetLong("这个 tall container is meant to hold javelins。");
    SetInventory(([
                "/domains/town/weap/javelin" : ({ 1200, 10 }),
                ]));
    SetNoCondition(1);
    SetCanClose(0);
    SetMass(274);
    SetBaseCost("silver",1);
    SetMaxCarry(3500);
    SetNoClean(1);
}

void init(){
    ::init();
}

mixed CanGet(object ob) { return "这个箱子纹丝不动。";}

int CanReceive(object ob) {
    if(!answers_to("javelin",ob)) {
        write("这是一个仅用于标枪的箱子。");
        return 0;
    }
    else return 1;
}
