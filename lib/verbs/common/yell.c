/*    /verbs/common/yell.c
 *    from the Dead Souls  Object Library
 *    yell
 *    yell in WRD STR
 *    yell STR
 *    created by Descartes of Borg 951119
 */

#include <lib.h>
#include <talk_type.h>
#include "include/yell.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("yell");
    SetRules("","in WRD STR","STR");
}

mixed can_yell() { return "喊叫什么？"; }

mixed can_yell_str(string str) {
    string lang;

    if( !str ) return 0;
    lang = this_player()->GetDefaultLanguage() || 
        this_player()->GetNativeLanguage();
    return can_yell_in_wrd_str(lang, str);
}

mixed can_yell_in_wrd_str(string lang, string str) {
    if( !lang || !str ) return 0;
    return this_player()->CanSpeak(0, TALK_AREA, str, lang);
}

mixed do_yell() { return 1; }

mixed do_yell_str(string str) {
    string lang;

    lang = this_player()->GetDefaultLanguage() || 
        this_player()->GetNativeLanguage();
    return do_yell_in_wrd_str(lang, str);
}

mixed do_yell_in_wrd_str(string lang, string str) {
    if( str[<1] != '!' && str[<1] != '?' && str[<1] != '.' )
        str = capitalize(str) + ".";
    else str = capitalize(str);
    return this_player()->eventSpeak(0, TALK_AREA, str, lang);
}

string GetHelp(string str) {
    return ("用法：yell <消息>\n"
            "      yell in <语言> <消息>\n\n"
            "向你周围区域发送消息。如果你没有指定语言，将使用你的母语。\n"
            "另见：reply, say, shout, speak, tell, whisper");
}
