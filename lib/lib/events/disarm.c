#include <lib.h>

mixed direct_boobytrap_obj_with_obj(){
    return 1;
}

mixed indirect_boobytrap_obj_with_obj(){
    object env = environment();
    if(!env || env != this_player()){
        return "#你没有那个东西！";
    }
    return 1;
}

mixed direct_disarm_obj(){
    if(sizeof(this_object()->FoundTraps())) return 1;
    return 0;
}

varargs mixed eventDisarm(mixed arg){
    int disarm_score = 0;
    int failure = 0;
    int wisdom_score = this_player()->GetStat("wisdom")["level"];
    mapping Traps = this_object()->FoundTraps();
    object trap = keys(Traps)[0];
    write("你开始尝试解除陷阱。");
    say(this_player()->GetCapName()+"开始尝试解除陷阱。");

    disarm_score += this_player()->GetStat("luck")["level"];
    disarm_score += this_player()->GetStat("intelligence")["level"];
    disarm_score += this_player()->GetStat("coordination")["level"];

    if(disarm_score > Traps[trap]["level"]) return trap->eventDisarm(this_player());

    failure = (Traps[trap]["level"] - disarm_score);

    if( failure > this_player()->GetStat("luck")["level"]){
        return trap->SpringTrap(this_player());
    }

    if(failure < wisdom_score){
        write("你解除陷阱失败了。");
    }

    if(failure > (wisdom_score + 100)){
        write("你成功解除了陷阱！");
    }
    return 1;
}
