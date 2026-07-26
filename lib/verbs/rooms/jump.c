/*    /verbs/rooms/jump.c
 *    from the Dead Souls Mud Library
 *    jump in OBJ
 *    jump into OBJ
 *    jump off OBJ
 *    jump off of OBJ
 *    jump from OBJ
 *    jump through OBJ
 *    jump across OBJ
 *    jump over OBJ
 *    jump onto OBJ
 *    jump on OBJ
 *    go ahead and jump
 *    might as well jump
 *    created by Descartes of Borg 960117
 */

#include <lib.h>
#include <jump.h>
#include "include/jump.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("jump");
    SetRules("in OBJ", "into OBJ", "off OBJ", "off of OBJ", "from OBJ",
            "through OBJ", "across OBJ", "over OBJ", "onto OBJ", "on OBJ"); 
    SetSynonyms("leap");
    SetErrorMessage("从哪里跳、跳进哪里、跳过什么、跳到什么上或跳穿什么？");
    SetHelp("用法：jump into <地点>\n"
            "      jump off <地点>\n"
            "      jump through <物品>\n"
            "      jump over <物品>\n"
            "      jump on <物品>\n\n"
            "这六种不同的语法实际上代表三种非常不同的运动类型。因此它们通常用于不同的情况。"
            "但它们都允许你跳跃。\n"
            "同义词：leap\n"
            "另见：enter, go");
}

mixed can_jump_word_obj(){
    if(!stringp(hobbled(this_player()))){
        return "你的伤势阻碍了那个动作。";
    }
    return 1;
}

mixed can_jump_word_word_obj(){
    if(!stringp(hobbled(this_player()))){
        return "你的伤势阻碍了那个动作。";
    }
    return 1;
}

varargs mixed do_jump_in_obj(object ob, mixed *args...){
    return do_jump_into_obj(ob, args...);
}

varargs mixed do_jump_into_obj(object ob, mixed *args...){
    string id;
    id = remove_article(lower_case(args[0]));
    return ob->eventJump(this_player(), id, JUMP_INTO);
}

varargs mixed do_jump_off_obj(object ob, mixed *args...){
    return do_jump_from_obj(ob, args...);
}

varargs mixed do_jump_off_of(object ob, mixed *args...){
    return do_jump_off_of_obj(ob, args...);
}

varargs mixed do_jump_from_obj(object ob, mixed *args...){
    string id;
    id = remove_article(lower_case(args[0]));
    return ob->eventJump(this_player(), id, JUMP_FROM);
}

varargs mixed do_jump_through_obj(object ob, mixed *args...){
    string id;
    id = remove_article(lower_case(args[0]));
    return ob->eventJump(this_player(), id, JUMP_THROUGH);
}

varargs mixed do_jump_across_obj(object ob, mixed *args...){
    return do_jump_over_obj(ob, args...);
}

varargs mixed do_jump_over_obj(object ob, mixed *args...){
    string id;
    id = remove_article(lower_case(args[0]));
    return ob->eventJump(this_player(), id, JUMP_OVER);
}

varargs mixed do_jump_onto_obj(object ob, mixed *args...){
    return do_jump_on_obj(ob, args...);
}

varargs mixed do_jump_on_obj(object ob, mixed *args...){
    string id;
    id = remove_article(lower_case(args[0]));
    return ob->eventJump(this_player(), id, JUMP_ON);
}    
