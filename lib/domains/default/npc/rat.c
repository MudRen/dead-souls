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
    SetAdjectives( ({"mangy", "little", "dirty"}) );
    SetId( ({"rat"}) );
    SetShort("一只老鼠");
    SetLong("一只邋遢的小脏老鼠。");
    SetLevel(3);
    SetMaxHealthPoints(50);
    SetRace("rodent");
    SetGender("male");
    SetClass("fighter");
    SetWanderSpeed(1);
    SetEncounter( (: CheckRat :) );
    SetMessage("come","$N scurries in.");
    SetMessage("leave","$N scurries $D.");
    SetAction(5, ({
                "老鼠吱吱叫。", "你听到老鼠在四处乱窜。",
                "一只邋遢的小老鼠蹭到了你的腿。",
                "你听到微小的咀嚼声。"}));
}
void init(){
    ::init();
}
