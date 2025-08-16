/*    /verbs/common/shout.c
 *    from the Dead Souls  Object Library
 *    shout
 *    shout 
 *    let it all out
 *    created by Descartes of Borg 951119
 */

#include <lib.h>
#include <talk_type.h>
#include "include/shout.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("shout");
    SetRules("","in WRD STR","STR");
}

mixed can_shout() { return "喊什么？"; }

mixed can_shout_str(string str) {
    string lang;
    if( !str ) return 0;
    if(this_player()->GetGaggedType("local")) return 0;
    lang = this_player()->GetDefaultLanguage() || 
        this_player()->GetNativeLanguage();
    return can_shout_in_wrd_str(lang, str);
}

mixed can_shout_in_wrd_str(string lang, string str) {
    if( !lang || !str ) return 0;
    if( !creatorp(this_player()) && this_player()->GetStaminaPoints()<100 )
        return "你太累了，无法大喊。";
    if( strlen(str) > 250 ) return "要喊的内容太多了！";
    return this_player()->CanSpeak(0, TALK_WORLD, str, lang);
}

mixed do_shout() { return 1; }

mixed do_shout_str(string str) {
    string lang;
    lang = this_player()->GetDefaultLanguage() || 
        this_player()->GetNativeLanguage();
    return do_shout_in_wrd_str(lang, str);
}

mixed do_shout_in_wrd_str(string lang, string str) {
    int cost = -100;
    if(this_player()->GetPlayerPaused()) cost = -300;
    if( str[<1] != '!' && str[<1] != '?' && str[<1] != '.' )
        str = capitalize(str) + ".";
    else str = capitalize(str);
    this_player()->AddStaminaPoints(cost);
    return this_player()->eventSpeak(0, TALK_WORLD, str, lang);
}

string GetHelp(string str) {
    return ("语法：shout <消息>\n"
            "        shout in <语言> <消息>\n\n"
            "向" + mud_name() + "上的所有玩家发送消息。如果你没有"
            "指定语言，将使用你的母语。滥用大喊是违反"
            + mud_name() + "规则的行为。\n"
            "另见：reply, say, speak, tell, whisper, yell");
}
