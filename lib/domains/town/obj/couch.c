#include <lib.h>
#include <props.h>

inherit LIB_BED;
inherit LIB_SMELL;

protected void create() {
    ::create();
    SetKeyName("beat up couch");
    SetId( ({ "couch","sofa","recliner" }) );
    SetAdjectives( ({ "beat up","beat-up","old" }) );
    SetShort("一张破旧的沙发");
    SetLong("这是一张破旧、磨损且肮脏的沙发，那种你在廉价家具店才能看到的款式。");
    SetMass(500);
    SetBaseCost("silver",15);
    SetMaxSitters(2);
    SetMaxLiers(1);
    SetSmell( ([
                "default" : "It smells dirty and gross. There's a "
                "faint whiff of dog urine."
                ]) );
}

void init(){
    ::init();
}
