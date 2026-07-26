#include <lib.h>
#include <boobytraps.h>

inherit LIB_BOOBYTRAP_SHADOW;

varargs mixed SpringTrap(mixed arg1, mixed arg2){
    write("你被毒针陷阱刺中了！");
    say(this_player()->GetCapName()+"被毒针陷阱刺中了！");
    this_player()->AddPoison(10);
    return boobytrap_shadow::SpringTrap(arg1, arg2);
}

void create(){
    SetTrapType(BOOBYTRAP_ALL);
}
