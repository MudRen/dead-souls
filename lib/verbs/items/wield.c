/*    /verbs/items/wield.c
 *    From the Dead Souls Mud Library
 *    The command to allow people to wield weapons
 *    Created by Descartes of Borg 951018
 *    Version: @(#) wield.c 1.2@(#)
 *    Last modified: 97/01/01
 */

#include <lib.h>

inherit LIB_VERB;

string* GetFreeLimbs(object who) {
    string* limbs = who->GetWieldingLimbs();

    limbs = filter(limbs, (: !$(who)->GetWielded($1) :));
    return limbs;
}

protected void create() {
    verb::create();
    SetVerb("wield");
    SetRules("OBS", "OBS in STR", "OBS with STR");
    SetErrorMessage("装备什么？也许你想指定用哪个肢体？");
    SetHelp(
            "用法：wield all\n"
            "      wield <武器>\n"
            "      wield <武器> in <肢体>\n"
            "      wield <武器> with <肢体>\n"
            "\n"
            "此命令将你指定的武器装备到你指定的肢体上。\n\n"
            "注意，肢体可以是单个肢体，也可以是用逗号或 \"and\" 分隔的肢体列表，"
            "这取决于装备武器需要多少个肢体。例如：\n"
            "\twield the rusty sword with my right hand and left hand\n"
            "\twield the artrell sword with first hand, second hand, and "
            "third hand\n"
            "\n"
            "另见：wear");
}

mixed can_wield_obj() {
    if( !sizeof(this_player()->GetWieldingLimbs()) ) {
        return "你没有可以装备武器的肢体！";
    }
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return 1;
}

mixed can_wield_obj_word_str() {
    return can_wield_obj();
}

mixed do_wield_obj(object ob) {
    string* limbs = GetFreeLimbs(this_player());
    int hands = ob->GetHands();

    if(ob->GetEquipped())
        return write("你已经装备了它！");

    if( hands < sizeof(limbs) ) {
        limbs = limbs[0..(hands-1)];
    }
    else if( hands > sizeof(limbs) ) {
        return write("你没有足够的肢体来装备！");
    }
    return ob->eventEquip(this_player(), limbs);
}

mixed do_wield_obj_word_str(object ob, string word, string str) {
    return ob->eventEquip(this_player(), explode_list(str));
}

mixed do_wield_obs(mixed* targs) {
    object* obs;

    if( !sizeof(targs) ) {
        this_player()->eventPrint("没有这样的东西可以装备。");
        return 1;
    }
    obs = filter(targs, (: objectp :));
    if( !sizeof(obs) ) {
        mapping messages = unique_mapping(targs, (: $1 :));

        foreach(string msg in keys(messages)) {
            this_player()->eventPrint(msg);
        }
        return 1;
    }
    foreach(object item in obs) {
        string* limbs = GetFreeLimbs(this_player());
        int hands = item->GetHands();

        if( sizeof(limbs) < hands ) {
            this_player()->eventPrint("你没有足够的肢体来装备" +
                    item->GetDefiniteShort() + "。");
        }
        else {
            mixed tmp;

            if( hands < sizeof(limbs) ) {
                limbs = limbs[0..(hands-1)];
            }
            tmp = item->CanEquip(this_player(), limbs);
            if( tmp != 1 ) {
                if( !tmp ) {
                    this_player()->eventPrint("你无法装备" +
                            item->GetDefiniteShort() + "。");
                }
                else {
                    this_player()->eventPrint(tmp);
                }
            }
            else {
                item->eventEquip(this_player(), limbs);
            }
        }
    }
    return 1;
}
