#include <lib.h>
#include <props.h>

inherit LIB_BED;
inherit LIB_SMELL;

protected void create() {
    ::create();
    SetKeyName("beat up couch");
    SetId( ({ "couch","sofa","recliner" }) );
    SetAdjectives( ({ "beat up","beat-up","old" }) );
    SetShort("一个破旧的旧沙发");
    SetLong("这是一个破旧、磨损且肮脏的沙发， the kind one might expect in a university dorm room。");
    SetMass(3000);
    SetBaseCost("silver",15);
    SetMaxSitters(2);
    SetMaxLiers(1);

    SetSmell( ([
                "default" : "闻起来又脏又恶心。有一股淡淡的狗尿味。"
                ]) );
}
