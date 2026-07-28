#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_PRESS;
inherit "/lib/events/manipulate";

int MoveRug();
int PushRug();
void create(){
    ::create();
    SetKeyName("persian rug");
    SetId( ({"rug"}) );
    SetAdjectives( ({"persian","ornamental"}) );
    SetShort("一块波斯地毯");
    SetLong("这是一块美丽的、图案精美的波斯地毯。它的颜色非常鲜艳。");
    SetMass(100);
    SetBaseCost("silver",500);
    SetManipulate( ([ "default" : (: MoveRug :) ]) );
    SetPress( ([ "default" : (: PushRug :) ]) );
    SetVendorType(VT_TREASURE);
}
mixed CanGet(object ob) { return "地毯似乎固定在地上。";}
int MoveRug(){
    send_messages("move", "$agent_name $agent_verb动了动波斯地毯。",
            this_player(), 0, environment(this_player()));
    environment(this_object())->RevealDoor();
    return 1;
}
int PushRug(){
    send_messages("move", "$agent_name $agent_verb动了动波斯地毯。",
            this_player(), 0, environment(this_player()));
    environment(this_object())->RevealDoor();
    return 1;
}
void init(){
    ::init();
}
