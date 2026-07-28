#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

int ringfound;
string SearchCrap(){
    string result;
    if(!ringfound){
        result="你在那堆恶心的垃圾中翻找，发现了一枚漂亮的金戒指。";
        say(this_player()->GetName()+"在碎屑堆中翻找，似乎找到了有价值的东西。");
        if(!new("/domains/campus/armor/ring")->eventMove(this_player()))
            new("/domains/campus/armor/ring")->eventMove(environment(this_object()));
        ringfound=1;
        return result; 
    }

    result="你在那堆恶心的垃圾中翻找，什么也没发现。";
    say(this_player()->GetName()+"翻了翻碎屑堆，什么也没找到。");
    return result; 
}
void create(){
    ::create();
    SetKeyName("debris");
    SetId( ({"pile","debris","crap","crud"}) );
    SetAdjectives( ({"disgusting","pile of","smelly"}) );
    SetShort("一堆碎屑");
    SetLong("这是一堆臭烘烘、令人恶心的污物，是从这里流淌的污水中积累起来的。");
    SetMass(20);
    SetDollarCost(0);
    SetVendorType(VT_TREASURE);
    SetSearch( (: SearchCrap :) );
    ringfound=0;

}
mixed CanGet(object ob) { return "这堆碎屑根本搬不动。";}
string GetItemCondition() { return "";}
void init(){
    ::init();
}
