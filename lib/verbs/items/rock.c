#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("rock");
    SetRules("","OBJ", "WRD OBJ", "STR on OBJ");
    SetErrorMessage("摇摆什么？或者摇摆什么在什么上？");
    SetHelp("语法：<rock 物品>\n"
            "        <rock 物品 on 物品>\n\n"
            "允许你摇摆一个物品，或者摇摆物品上的某个东西。"
            "例如，你可能想\"摇摆光环\"，或者简单地\"在摇椅上摇摆\"。\n\n"
            "");
}

mixed can_rock(){
    return 1;
}

mixed can_rock_obj(){
    return this_player()->CanManipulate();
}

mixed can_rock_wrd_obj(){
    return this_player()->CanManipulate();
}

mixed can_rock_str_on_obj(){
    return this_player()->CanManipulate();
}

mixed do_rock(){
    object furn = this_player()->GetProperty("furniture_object");
    if(furn && objectp(furn)){
        return furn->eventRock(this_player());
    }
    write("你前后摇摆。");
    say(this_player()->GetCapName()+" 前后摇摆。");
    return 1;
}

mixed do_rock_obj(object target){
    return target->eventRock(this_player());
}

mixed do_rock_wrd_obj(string wrd, object target){
    return target->eventRock(this_player());
}

varargs mixed do_rock_str_on_obj(string thing, object target){
    return target->eventRock(this_player(), remove_article(lower_case(thing)));
}
