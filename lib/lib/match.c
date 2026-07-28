/*    /lib/match.c
 *    from the Dead Souls Object Library
 *    an object which can be self-induced to burn
 *    created by Descartes of Borg 960512
 */

#include <lib.h>
#include "include/match.h"

inherit LIB_TORCH;

private int StrikeChance = 50;

mixed direct_strike_obj(){
    if( environment() != this_player() ) return "#You don't have that!";
    if( GetBurning() ) return "它已经点燃了！";
    return 1;
}

mixed eventStrike(object who){
    if( !GetFuelAmount() || StrikeChance < random(100) || !eventBurn(who) ){
        who->eventPrint("你划了划" + GetShort() + "，但什么也没发生。");
        environment(who)->eventPrint(who->GetName() + " 划了划" +
                GetShort() + "，但什么也没发生。",
                who);
        return 1;
    }
    who->eventPrint("你划了划" + GetShort() + "，它点燃了！");
    environment(who)->eventPrint(who->GetName() + " 划了划" +
            GetShort() + "，它点燃了！", who);
    return 1;
}

int GetStrikeChance(){
    return StrikeChance;
}

protected int SetStrikeChance(int x){
    return (StrikeChance = x);
}
