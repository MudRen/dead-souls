/*    /verbs/items/wear.c
 *    From the Dead Souls Mud Library
 *    Allows a player to wear armor
 *    Created by Descartes of Borg 951020
 *    Version: @(#) wear.c 1.2@(#)
 *    Last modified: 97/01/01
 */

#include <lib.h>
#include <armor_types.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("wear");
    SetRules("OBS", "OBJ on STR");
    SetErrorMessage("穿戴什么？如有疑问，请指定要穿戴的肢体。");
    SetHelp("用法：wear <护甲>\n"
            "      wear <护甲> on <肢体>\n\n"
            "允许你穿上一件衣服。有些衣服可以穿戴在不同的位置，因此需要你指定穿戴的位置。"
            "例如，盾牌可以戴在右手或左手上。所以你可以输入 \"wear shield on right hand\"。\n\n"
            "另见：wield");
}

mixed can_wear_obj() {
    if( this_player()->GetParalyzed() ) {
        return "You cannot do anything.";
    }
    return this_player()->CanManipulate();
}

mixed can_wear_obj_on_str(string str) {
    return can_wear_obj();
}

mixed do_wear_obj(object ob) {
    return ob->eventEquip(this_player(), ob->GetRestrictLimbs());
}

mixed do_wear_obj_on_str(object ob, string str) {
    return ob->eventEquip(this_player(),
            ({ remove_article(lower_case(str)) }));
}

mixed do_wear_obs(object* armors) {
    object* obs;

    if( !sizeof(armors) ) {
        this_player()->eventPrint("There is no such thing to be worn.");
        return 1;
    }
    obs = filter(armors, (: objectp :));
    if( !sizeof(obs) ) {
        mixed* ua;

        ua = unique_array(armors, (: $1 :));
        foreach(string* list in ua) {
            this_player()->eventPrint(list[0]);
        }
        return 1;
    }
    foreach(object armor in obs) {
        do_wear_obj(armor);
    }
    return 1;
}
