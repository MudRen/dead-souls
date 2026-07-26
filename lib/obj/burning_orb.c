/*    /obj/burning_orb.c
 *    From Dead Souls LPMud
 *    Created by Descartes of Borg 961103
 *    Version: @(#) burning_orb.c 1.1@(#)
 *    Last modified: 96/11/03
 */

#include <lib.h>
#include <vendor_types.h>

inherit LIB_TORCH;

protected void create() {
    torch::create();
    SetKeyName("burning orb");
    SetVendorType(VT_MAGIC);
    SetId("orb");
    SetAdjectives("burning", "flaming");
    SetShort("燃烧的宝珠");
    SetLong("一个触碰时不会灼伤你的燃烧宝珠。你可以用它点燃其他东西或火把。");
    SetRadiantLight(5);
    SetMinHeat(10);
    SetFuelRequired(1);
    SetMaxFuel(50);
    SetFuelAmount(50);
    SetRefuelable(0);
    SetMass(5);
    SetValue(2);
    SetBurntValue(1);
    SetDestroyOnSell(1);
    if( clonep() ) {
        eventBurn();
    }
}
