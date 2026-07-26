#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

int searched;

string SearchCrap(){
    string result;
    result="You rummage through the disgusting pile "+
        "and find nothing.";
    say(this_player()->GetName()+" searches a pile of debris "+
            "with no results.");

    if(!random(10)){
        object germ = new("/domains/cave/obj/ecoli");
        if(germ) germ->eventInfect(this_player());
    }

    searched=1;
    return result; 
}

void create(){
    ::create();
    SetKeyName("waste");
    SetId( ({"pile","debris","crap","crud"}) );
    SetAdjectives( ({"waste","biological","disgusting","pile of","smelly"}) );
    SetShort("一堆废物");
    SetLong("这是一堆又臭又恶心的生物废物。");
    SetMass(2000);
    SetDollarCost(0);
    SetSearch( (: SearchCrap :) );
    SetNoCondition(1);
    SetPreventGet("The pile of debris isn't at all portable.");
}

void init(){
    ::init();
}
