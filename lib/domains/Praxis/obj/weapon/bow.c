//  /domains/Praxis/obj/weapon/bow.c
//  Short bow used in executions.
//  For the Nightmare mortal law system.
//  Created by Manny@Nightmare 940906

#include <lib.h>

inherit LIB_ITEM;

create() {
    ::create();
    SetKeyName("bow");
    SetId( ({ "bow", "short bow" }) );
    SetShort("短弓");
    SetLong("一把小弓。");
    SetMass(10);
    SetClass(2);
    SetValue(10);
}

void init() {
    ::init();
    if(environment(this_object())->query_name() != "guard") {
        write("短弓在你手中碎裂了。");
        destruct();
    }
}

