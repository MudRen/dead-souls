/*    /verbs/players/speak.c
 *    from the Dead Souls Mud Library
 *    speak
 *    speak STR
 *    speak in WRD STR
 */

#include <lib.h>
#include <talk_type.h>
#include "include/speak.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("speak");
    SetRules("","in WRD","in WRD STR","STR");
}

mixed can_speak() { return "说什么？用什么语言？"; }

mixed can_speak_in_wrd(string str) {
    mixed ret = this_player()->CanSpeak(0, TALK_LOCAL, "foo", str);
    if(intp(ret)) {
        write("你现在使用"+capitalize(lower_case(str))+"语交谈。");
        return 1;
    }
    else return ret;
}

mixed can_speak_str(string str) {
    string lang;

    if( !str ) return 0;
    if( strlen(str) > 3 && str[0..2] == "in " ) return 0;
    lang = this_player()->GetDefaultLanguage() || 
        this_player()->GetNativeLanguage();
    if(this_player()->GetPolyglot()) return 100;
    return this_player()->CanSpeak(0, TALK_LOCAL, str, lang);
}

mixed can_speak_in_wrd_str(string lang, string str) {
    if( !lang || !str ) return 0;
    if( !environment(this_player()) ) return "你现在不在任何地方。";
    if(this_player()->GetPolyglot()) return 100;
    return this_player()->CanSpeak(0, TALK_LOCAL, str, lang);
}

mixed do_speak() { return 1; }

mixed do_speak_in_wrd(string str) { 
    this_player()->SetDefaultLanguage(str);
    return 1;
}

mixed do_speak_str(string str) {
    string lang;
    lang = this_player()->GetDefaultLanguage() ||
        this_player()->GetNativeLanguage();
    return do_speak_in_wrd_str(lang, str);
}

mixed do_speak_in_wrd_str(string lang, string str) {
    if( str[<1] != '.' && str[<1] != '?' && str[<1] != '!' )
        str = capitalize(str) + ".";
    else str = capitalize(str);
    return this_player()->eventSpeak(0, TALK_LOCAL, str, lang);
}

string GetHelp(string str) {
    return ("用法：speak <消息>\n"
            "      speak in <语言> [消息]\n\n"
            "向与你同房间的所有人发送指定的消息。如果你是化身，你可以通过 "
            "\"message\" 命令自定义消息的显示方式。如果你没有指定语言，"
            "将使用你的默认语言。\n"
            "要将默认语言切换为母语以外的语言：\n"
            "speak in FOO\n"
            "另见：message, say, shout, speak, tell");
}

