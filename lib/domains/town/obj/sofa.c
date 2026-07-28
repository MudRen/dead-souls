#include <lib.h>

inherit LIB_BED;

protected void create() {
    ::create();
    SetKeyName("sofa");
    SetId("sofa");
    SetAdjectives( ({ "black", "small", "tasteful", "upholstered" }) );
    SetShort("一张沙发");
    SetLong("这是一张小型毛绒沙发，装饰雅致，配有柔软的天鹅绒面料。");
    SetMass(1500);
    SetDollarCost(15);
    SetMaxSitters(2);
}

mixed CanGet(object ob) { return "沙发纹丝不动。";}

void init(){
    ::init();
}
