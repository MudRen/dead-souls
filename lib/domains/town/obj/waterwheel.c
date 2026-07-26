#include <lib.h>
#include <vendor_types.h>

inherit LIB_ITEM;
inherit LIB_TURN;

nosave int turned = 0;
object Turner;

void create(){
    ::create();
    SetKeyName("waterwheel");
    SetId( ({"wheel"}) );
    SetAdjectives( ({"water", "large","metal","iron"}) );
    SetShort("一个嵌入基岩的大铁轮");
    SetLong("这是一个嵌入基岩的铁轮。");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetInvis(0);
    SetPreventGet("它牢牢地嵌在基岩里。");
    SetNoCondition(1);
    set_heart_beat(1);
    SetUnique(1);
}

void init(){
    ::init();
}

varargs mixed CanTurn(object who, object what){
    if(turned){
        return "#轮子转不动了。";
    }
    else return 1;
}

int eventTurn(object who){
    object pipe, env = environment();
    if(env) pipe = present("water pipe", env);
    if(!who) who = this_player();
    if(!turned){
        if(pipe){
            write("你转动了轮子。");
            say(who->GetName()+"转动了轮子。");
            if(!pipe->GetFlowing()){
                tell_room(env,"水开始从管道中流出。");
            }
            pipe->openpipe(1);
            turned = 1;
            Turner = who;
        }
        else {
            write("轮子松动地转了转，没有明显效果。");
            say(who->GetName()+"转动了轮子，没有明显效果。");
        }
    }
    else {
        write("什么也没发生。");
        say(who->GetName()+"试图转动轮子。什么也没发生。");
    }
    return 1;
}

object GetTurner(){
    return Turner;
}
