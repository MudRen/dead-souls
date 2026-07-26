#include <lib.h>
#include <medium.h>

inherit LIB_LIMB;

int stank;

protected void create(){
    limb::create();
}

void init(){
    ::init();
    if(environment() && environment()->GetMedium() == MEDIUM_LAND) stank = 1;
}

int eventDecay(){
    if( !environment() ){
        CallOut = -1;
        Destruct();
        return 0;
    }
    switch(Count){
        case 10:
            if(stank)
                message("smell", "The "+Limb+" rapidly corrodes.", environment());
            SetShort("正在腐蚀的" + Limb + "残余");
            break;
        case 20:
            if(stank)
                message("smell", "An acrid chemical odor fills the area.",
                        environment());
            SetShort("一些腐蚀的化学物质");
            break;
        case 30:
            CallOut = -1;
            Destruct();
            return 0;
    }
    Count++;
    return Count;
}

void SetLimb(string limb, string owner, string race){
    SetKeyName(limb);
    SetId( ({ "limb", Limb = limb }) );
    Owner = owner;
    Race = race;
    Count = 1;
    SetShort("一段正在融化的" + possessive_noun(Race) + " " + Limb);
    SetLong("这个肢体正在快速腐蚀，分解成化学成分。");
}
