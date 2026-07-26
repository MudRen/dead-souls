#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <localtime.h>
inherit LIB_ARMOR;

string l_time;
string l_time,tzone;
protected void create(){
    armor::create();
    SetKeyName("pocket watch");
    SetId(({"watch","pocketwatch","pocket watch","timepiece"}));
    SetShort("金怀表");
    SetLong("这是一块装饰精美、雕刻精致的金怀表。它散发着近乎超现实的深金色光泽。它静静地滴答作响，看起来你可以通过查看手表来获取准确时间。");
    SetMass(10);
    SetDollarCost(1);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,1);
    SetProtection(KNIFE,1);
    SetArmorType(A_AMULET);
}
void init(){
    ::init();
    add_action("check_time","check");
    add_action("pre_check","time");
}
int pre_check(string str){
    if(!str){
        this_object()->check_time("time");
        return 1;
    }
}
int check_time(string str){
    if(str=="time" || str=="watch"){
        if(present("pocket watch",this_player())){
            tzone="/daemon/timezone"->GetTZ();
            l_time="/daemon/current_time"->GetCurrentTime(tzone);
            write("看了看怀表，你发现现在是"+l_time+"。\n");
            say(this_player()->GetName()+" checks "+possessive(this_player())+
                    " pocket watch.\n");
            return 1;
        }
        write("你从这里看不清表盘。\n");
        return 1;
    }
}
