/*    /verbs/items/throw.c
 *    from the NIghtmare IVr2 Object Library
 *    created by Descartes of Borg 951029
 *    Version: @(#) throw.c 1.3@(#)
 *    Last modified: 96/10/20
 */

#include <lib.h>
#include <rounds.h>

inherit LIB_VERB;

mixed do_throw_obj_word_obj(object what, string word, object where);
void eventThrow(object who, object what, object where);

protected void create() {
    verb::create();
    SetVerb("throw");
    SetSynonyms("toss");
    SetRules("OBJ", "OBJ at OBJ", "OBJ into OBJ");
    SetErrorMessage("投掷什么？");
    SetHelp("语法：<throw 物品>\n"
            "        <throw 物品 at 物品>\n"
            "        <throw 物品 into 物品>\n\n"
            "允许你投掷一个物品。有些物品你也可以"
            "用来攻击性地投掷。其他地方可能只是"
            "允许你把物品扔进去，比如把装备"
            "扔给深渊里的朋友。\n"
            "注意，向某人投掷武器会引发"
            "战斗。\n\n"
            "同义词：toss");
}

mixed can_throw_obj() {
    if( this_player()->GetParalyzed() ) {
        return "你无法做任何事情。";
    }
    if(intp(check_light())) return this_player()->CanManipulate();
    else return check_light();
}

mixed can_throw_obj_word_obj() {
    return can_throw_obj();
}

mixed do_throw_obj(object ob) {
    return do_throw_obj_word_obj(ob, 0, 0);
}

mixed do_throw_obj_word_obj(object what, string word, object where) {
    object enemy;
    object env = environment(this_player());
    if( where && living(where) && what->GetClass() > 1 ) {
        enemy = where;
    }
    else {
        enemy = 0;
    }
    if(env && env->GetProperty("no attack")){
        write("一股神秘的力量阻止了你的恶意行为。");
        return 1;
    }
    if( this_player()->GetInCombat() || enemy ) {
        this_player()->eventPrint("你准备投掷" +
                what->GetShort() + "。");
        this_player()->SetAttack(enemy, (: eventThrow, this_player(), what,
                    where :), (enemy ? ROUND_WEAPON :
                        ROUND_OTHER));
        return 1;
    }
    eventThrow(this_player(), what, where);
    return 1;
}

void eventThrow(object who, object what, object where) {

    if( !who ) {
        return;
    }
    if( !what || environment(what) != who ) {
        who->eventPrint("你已经没有东西可以投掷了。");
        return;
    }
    what->eventThrow(who, where);
}
