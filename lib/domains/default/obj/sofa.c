#include <lib.h>

inherit LIB_BED;

protected void create() {
    ::create();
    SetKeyName("sofa");
    SetId("sofa");
    SetAdjectives( ({ "black", "small", "tasteful", "upholstered" }) );
    SetShort("一个沙发");
    SetLong("这是一个小型、 plush sofa tastefully upholstered in black。它 appears designed for sitting on。");
    SetMass(1500);
    SetDollarCost(15);
    SetMaxSitters(2);
}
mixed CanGet(object ob) { return "这个沙发纹丝不动。";}
void init(){
    ::init();
}
