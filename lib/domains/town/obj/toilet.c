#include <lib.h>

inherit LIB_CHAIR;

protected void create() {
    chair::create();
    SetKeyName("mansion commode");
    SetId( ({ "toilet","commode","bowl","can" }) );
    SetAdjectives( ({ "porcelain","white" }) );
    SetShort("一个马桶");
    SetLong("这是一件常见的室内管道设施。");
    SetMass(2000);
    SetBaseCost("silver",15);
    SetMaxSitters(1);
}

void init(){
    ::init();
    add_action("flush","flush");
}

int flush(string str){
    if(!str || str == "" ||str == "toilet"){
        write("ba-WHOOSH!");
        say(this_player()->GetName()+" flushes the toilet. ba-WHOOSH!");
        return 1;
    }
    else return 0;
}

mixed CanGet(object ob) { return "The toilet does not budge.";}
