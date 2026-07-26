#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
int polefound;
string SearchCrap(){
    string result;
    object *livings;
    livings = get_livings(environment(this_object()));
    foreach(object living in livings){
        if(living->GetRace() == "troll" && !interactive(living)) {
            write("巨魔分散了你的注意力！");
            return " ";
        }
    }
    if(!polefound){
        result="在石头堆里翻找，你发现了一根藏在下面的鱼竿。";
        say(this_player()->GetName()+"在石头堆里翻找，似乎发现了什么有价值的东西。");
        new("/domains/town/obj/pole")->eventMove(environment(this_player()));
        polefound=1;
        return result; 
    }

    result="你在石头堆里翻找，什么也没发现。";
    say(this_player()->GetName()+"在石头堆里翻找，没有结果。");
    return result; 
}


void create(){
    ::create();
    SetKeyName("rocks");
    SetId( ({"pile","rocks","crap","bunch"}) );
    SetAdjectives( ({"pile of"}) );
    SetShort("一堆石头");
    SetLong("这是一堆石头。");
    SetMass(200);
    SetDollarCost(0);
    SetNoCondition(1);
    SetVendorType(VT_TREASURE);
    SetSearch( (: SearchCrap :) );
    polefound=0;
    SetItems( ([
                ({"rock","rocks"}) : "一堆石头。",
                ]) );

}

mixed CanGet(object ob) { return "这堆石头根本搬不动。";}
