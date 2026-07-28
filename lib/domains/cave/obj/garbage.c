#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

int searched;

string SearchCrap(){
    string result;
    if(!searched){
        if(!random(1000)){
            result="你在那堆恶心的垃圾中翻找，发现了一枚漂亮的金戒指。";
            say(this_player()->GetName()+"在垃圾堆中翻找，似乎找到了有价值的东西。");
            if(!new("/domains/campus/armor/ring")->eventMove(this_player()))
                new("/domains/campus/armor/ring")->eventMove(environment(this_object()));
            searched=1;
            return result; 
        }
    }

    result="你在那堆恶心的垃圾中翻找，什么也没发现。";
    say(this_player()->GetName()+"翻了翻垃圾堆，什么也没找到。");
    searched=1;
    return result; 
}

void create(){
    ::create();
    SetKeyName("garbage");
    SetId( ({"pile","debris","crap","crud"}) );
    SetAdjectives( ({"disgusting","pile of","smelly"}) );
    SetShort("一堆垃圾");
    SetLong("这是一堆又臭又恶心的垃圾。");
    SetMass(2000);
    SetDollarCost(0);
    SetSearch( (: SearchCrap :) );
    SetNoCondition(1);
    SetPreventGet("这堆垃圾根本搬不动。");
}

void init(){
    ::init();
}
