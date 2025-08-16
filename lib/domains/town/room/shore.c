#include <lib.h>
#include <daemons.h>

inherit LIB_FISHING;

int ActionFunction(){
    object *cres, dude;
    if(!sizeof(get_livings(this_object()))) return 0;
    //The next line identifies creators in the room
    cres = filter(get_livings(this_object()), (: creatorp($1) :) );
    //The next line picks a living being here at random
    dude = get_random_living(this_object());
    if(!dude) return 0;
    if((RACES_D->GetNonMeatRace(dude->GetRace()))) return 0;
    //The next line makes that person sigh. Note that since
    //creators normally can't be forced by non-privileged objects,
    //only npc's and players will be affected.
    dude->eventForce("sigh");
    //The next line tells any creators present the identitiy of the
    //target of the previous action.
    if(!sizeof(cres)) return 0;
    //The action below is commented out because it confused people.
    //basically it tells creators about this function.
    //cres->eventPrint("%^YELLOW%^The ActionFunction activates. Dude is: "+
    //  identify(dude)+".%^RESET%^");
    return 1;
}

varargs string readSign() {
    string ret = "警告！兽人、矮人和其他一些种族不能"+
        "游泳！如果你跳进海里你会下沉并淹死！";
    return ret;
}

int ActionFunction2(){
    object *cres, dude;
    if(!sizeof(get_livings(this_object()))) return 0;
    cres = filter(get_livings(this_object()), (: creatorp($1) :) );
    dude = get_random_living(this_object());
    if(!dude) return 0;
    if((RACES_D->GetNonMeatRace(dude->GetRace()))) return 0;
    dude->eventForce("ponder");
    if(!sizeof(cres)) return 0;
    //The action below is commented out because it confused people.
    //basically it tells creators about this function.
    //cres->eventPrint("%^GREEN%^ActionFunction2 activates. Dude is: "+
    //  identify(dude)+".%^RESET%^");
    return 1;
}

protected void create() {
    fishing::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("海岸边缘");
    SetNightLong("你在海岸上，在小镇的最东端。一条路向西通向镇中心。一片大海延伸到东方的地平线。一个孤独的路灯照亮了这个区域。\n%^GREEN%^这里有一个标牌你可以阅读。%^RESET%^");
    SetDayLong("你在海岸上，在小镇的最东端。一条路向西通向镇中心。一片大海延伸到东方的地平线。\n%^GREEN%^这里有一个标牌你可以阅读。%^RESET%^");
    SetItems( ([
                "sign":"地上的一个标牌。要阅读它，请使用'read sign'命令。",
                "ground":"当地的地表。"
                "horizon":"天空与大海相爱的地方。"
                "town":"西边的人口中心。"
                "road":"向西通向小镇。"
                ]) );
    SetExits( ([
                "west" : "/domains/town/room/vill_road4",
                "south" : "/domains/town/room/docks.c",
                ]) );
    SetRead("sign", (: readSign :) );
    //SetFrequency determines how often the room checks 
    //whether it should perform an action. If it is set
    //at 1, it checks approximately every second. The
    //default is 5.
    SetFrequency(5);
    //The first argument of SetAction is a number, indicating from
    //one to 100 the percentage of likelihood an event will occur.
    //The second argument is an array that contains strings,
    //functions, or both. Every time an action is triggered, an
    //element is picked from the array at random. If it is a string,
    //that string is displayed to the living things in the room.
    //If it is a function, that function is evaluated.
    SetAction(2, ({"一阵凉爽的微风从东边吹来，"
                "带来了大海清新的咸味。",
                (: ActionFunction :) }) );
    SetChance(90);
    SetFish( ([
                "/domains/town/meals/shark" : 1,
                "/domains/town/meals/herring" : 10,
                ]) );
    //This is a function that allows for a set of actions
    //with different trigger frequencies.
    SetActionsMap( ([ 
                "柔和的微风冷却着你的额头。" : 5,
                "你短暂地听到远处海鸥的叫声。" : 7,
                (: ActionFunction2 :) : 2,
                ]) );
    SetInventory( ([
                "/domains/town/obj/seawater" : 1,
                ]) );
    AddItem(new("/domains/town/obj/lamp"));
    SetSkyDomain("town");
}
void init(){
    ::init();
}
