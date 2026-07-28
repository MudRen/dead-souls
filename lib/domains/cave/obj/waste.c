#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

int searched;

string SearchCrap(){
    string result;
    result="你在那堆恶心的废物中翻找，什么也没发现。";
    say(this_player()->GetName()+"翻了一堆废物，什么也没找到。");

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
    SetPreventGet("这堆废物根本搬不动。");
}

void init(){
    ::init();
}
