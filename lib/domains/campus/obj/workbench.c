#include <lib.h>

inherit LIB_TABLE;

void create() {
    ::create();
    SetKeyName("workbench");
    SetAdjectives( ({"work", "simple", "flat"}) );
    SetId( ({"table", "workbench", "bench"}) );
    SetShort("工作台");
    SetLong("一个用于分析材料的简单平面。");
    SetMaxCarry(5000);
    SetInventory(([
                "/domains/town/armor/rocketpack" : 1,
                "/domains/default/obj/generator" : 1,
                "/domains/default/obj/module_cloak" : 1,
                "/domains/default/armor/wristcomp" : 1,
                "/domains/default/obj/vial_blue" : 1,
                "/domains/town/armor/breather" : 1,
                ]));
    SetPreventGet("The workbench does not budge.");
    SetBaseCost("silver",1);
}

void init(){
    ::init();
}
