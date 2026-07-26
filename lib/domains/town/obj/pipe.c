#include <lib.h>
#include <vendor_types.h>
inherit LIB_PIPE;

void create(){
    ::create();
    SetKeyName("magic pipe");
    SetId( ({"sigpipe","magical pipe","pipe of insight"}) );
    SetAdjectives( ({"magic","magical","kalinash's", "sig", "smoking"}) );
    SetShort("一支魔法烟斗");
    SetLong("这是一支漂亮的象牙烟斗。有一些魔法附着在上面。");
    SetMass(5);
    SetBaseCost("silver", 300);
    SetVendorType(VT_TREASURE);
    SetRadiantLight(1);
    SetMaxFuel(300);
    SetItems( ([
                "inscription" : "烟斗上的一段铭文，你可以阅读。",
                ]) );
    SetRead( ([
                "default" : "试试：read inscription on pipe",
                "inscription" : "卡利纳什的洞察之烟斗",
                ]) );
    SetLanguage("common");
    SetFuelAmount(50);
    SetRefuelable(1);
    SetFuelType("smokable material");
}

void init(){
    ::init();
}

varargs mixed eventLight(object who, object tool){
    SetBaseCost("silver", 1);
    return ::eventLight(who, tool);
}

mixed eventSmoke(object who, object what){
    if(!GetLit()){
        write("它没有点燃！");
        return 1;
    }
    write("你抽了一口"+remove_article(GetShort())+"。");
    say(who->GetName()+"抽了一口"+possessive(who)
            +remove_article(GetShort())+"。");
    if((((time() - GetLastPuff()) > 10) && random(100) < 25) ||
            creatorp(this_player())){
        object bonus = new(LIB_BONUS);
        object *kbonuses = filter(all_inventory(this_player()),
                (: stringp($1->GetBonusName()) && 
                 $1->GetBonusName() == "kpipe_bonus" :) );
        if(sizeof(kbonuses) > 9) return bonus->eventDestruct();
        bonus->SetBonusName("kpipe_bonus");
        bonus->SetStats( ([ 
                    "intelligence" : 1,
                    "wisdom" : 1,
                    "strength" : -1,
                    "durability" : -1,
                    ]) );
        bonus->SetBonusDuration(300);
        if(bonus->eventMove(who)){
            write("你感觉自己对这个世界有了更深的理解。");
        }
    }    
    lastpuff = time();
    eventDecreaseFuel(1);
    if( !GetFuelAmount() ) eventBurnOut();
    return 1;
}

int eventBreak(){
    return 0;
}
