//	shovel.c created by Descartes 921004
//	it digs in rooms that look for shovels when digging is done

#include <lib.h>

inherit LIB_ITEM;

void init() {
    ::init();
    add_action("dig", "dig");
}

void create() {
    ::create();
    SetId( ({ "shovel" }) );
    SetKeyName("shovel");
    SetShort( "一把铲子");
    SetLong( "你也许能在合适的土壤里用它来挖掘。");
    SetMass(100);    SetValue( 18);

}

int dig(string str) {
    notify_fail("铲子无法处理这里的土壤。\n");
    return 0;
}
