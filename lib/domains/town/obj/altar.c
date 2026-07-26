#include <lib.h>
#include <props.h>

inherit LIB_BED;
inherit LIB_SMELL;

protected void create() {
    bed::create();
    SetKeyName("altar");
    SetId( ({ "altar","platform","pedestal" }) );
    SetAdjectives( ({ "orcish", "simple","stone" }) );
    SetShort("一个滴血的简朴石祭坛");
    SetLong("这是一个仪式用的兽人祭坛，兽人们在这里用俘虏的鲜血祭拜他们的黑暗之神。");
    SetItems( ([
                ({"blood","dried blood","tissue","rotting tissue"}) : ""+
                "This appears to be the accumulated detritus of "+
                "numerous sacrifices.",
                ]) );
    SetPreventGet("The altar is dug into the floor and does not move.");
    SetInventory(([
                "/domains/town/weap/boobytrap_dagger" : 1,
                "/domains/town/armor/boobytrap_ring" : 1,
                ]));
    SetMass(3000);
    SetBaseCost("silver",15);
    SetMaxSitters(2);
    SetMaxLiers(1);
    SetMaxCarry(5000);
    SetSmell( ([ "default" : "The altar is nauseatingly rank."]) );
}

void init(){
    bed::init();
}
