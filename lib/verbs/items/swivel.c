#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("swivel");
    SetRules("","OBJ", "WRD OBJ", "STR on OBJ");
    SetSynonyms("spin");
    SetErrorMessage("旋转什么？或者旋转什么在什么上？");
    SetHelp("语法：<swivel 物品>\n"
            "        <swivel 物品 on 物品>\n\n"
            "允许你旋转一个物品，或者旋转物品上的某个东西。"
            "例如，你可能想\"旋转万向节\"，或者简单地\"在椅子上旋转\"。\n\n"
            "同义词：spin");
}

mixed can_swivel(){
    return 1;
}

mixed can_swivel_obj(){
    return this_player()->CanManipulate();
}

mixed can_swivel_wrd_obj(){
    return this_player()->CanManipulate();
}

mixed can_swivel_str_on_obj(){
    return this_player()->CanManipulate();
}

mixed do_swivel(){
    object furn = this_player()->GetProperty("furniture_object");
    if(furn && objectp(furn)){
        return furn->eventSwivel(this_player());
    }
    write("你来回旋转。");
    say(this_player()->GetCapName()+" 来回旋转。");
    return 1;
}

mixed do_swivel_obj(object target){
    return target->eventSwivel(this_player());
}

mixed do_swivel_wrd_obj(string wrd, object target){
    return target->eventSwivel(this_player());
}

varargs mixed do_swivel_str_on_obj(string thing, object target){
    return target->eventSwivel(this_player(), remove_article(lower_case(thing)));
}
