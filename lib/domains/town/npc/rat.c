#include <lib.h>

inherit LIB_SENTIENT;

int CheckRat(mixed val){
    string *allowed_races = ({ "orc", "half-orc", "rodent" });
    if(!val) return 0;
    if(!objectp(val)) return 0;
    if(member_array(val->GetRace(), allowed_races) != -1) return 0;
    return 1;
}

protected void create() {
    sentient::create();
    SetKeyName("rat");
    SetMaxHealthPoints(10);
    SetAdjectives( ({"mangy", "little", "dirty"}) );
    SetId( ({"rat"}) );
    SetShort("一只老鼠");
    SetLong("一只邋遢的小脏老鼠。");
    SetLevel(1);
    SetRace("rodent");
    SetGender("male");
    SetClass("fighter");
    SetEncounter( (: CheckRat :) );
    SetMessage("come","$N窜了进来。");
    SetMessage("leave","$N窜向$D。");
    SetAction(5, ({
                "老鼠吱吱叫着。", "你听到老鼠四处乱窜的声音。",
                "一只邋遢的小老鼠蹭过你的腿。",
                "你听到细小的咀嚼声。"}));
}
void init(){
    ::init();
}
