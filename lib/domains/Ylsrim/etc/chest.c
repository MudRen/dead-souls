/*    /domains/Ylsrim/etc/chest.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 951028
 */

#include <lib.h>

inherit LIB_STORAGE;

protected void create() {
    storage::create();
    SetKeyName("chest");
    SetId( ({ "chest" }) );
    SetAdjectives( ({ "wooden" }) );
    SetShort("一个木箱");
    SetLong("这个箱子是用远离伊尔斯利姆的古老森林的木材制成的。"
            "触摸它你能感受到它的年代久远。");
    SetMass(1200);
    SetValue(300);
    SetInventory( ([ DIR_STANDARD_DOMAIN "/etc/shovel" : -10,
                DIR_STANDARD_DOMAIN "/etc/heal_scroll" : 1 ]) );
    SetCanClose(1);
    SetClosed(1);
    SetMaxCarry(2000);
}
