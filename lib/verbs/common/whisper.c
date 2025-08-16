/*    /verbs/common/whisper.c
 *    from the Dead Souls  Object Library
 *    whisper
 *    whisper to LIV STR
 *    created by Descartes of Borg 951118
 */

#include <lib.h>
#include <talk_type.h>
#include "include/whisper.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("whisper");
    SetRules("to LIV", "in WRD", "in WRD to LIV", "to LIV STR",
            "to LIV in WRD STR", "in WRD to LIV STR");
    SetErrorMessage("对谁耳语什么？");
    SetHelp("语法：whisper to <生物> <消息>\n"
            "        whisper to <生物> in <语言> <消息>\n"
            "        whisper in <语言> to <生物> <消息>\n\n"
            "私下向目标人物发送消息，使用你指定的语言，有很小几率被其他人偷听到。"
            "如果你没有指定语言，将使用你的母语。\n"
            "另见：say, shout, speak, tell, yell");
}

mixed can_whisper_to_liv(object target) {
    return "你想耳语什么？";
}

mixed can_whisper_in_wrd(string lang) {
    return "用" + lang + "耳语给谁？";
}

mixed can_whisper_in_wrd_to_liv(string wrd, object ob) {
    return "你想耳语什么内容？";
}

mixed can_whisper_to_liv_str(object targ, string str) {
    string lang;

    lang = this_player()->GetNativeLanguage() || "english";
    return can_whisper_to_liv_in_wrd_str(targ, lang, str);
}

mixed can_whisper_in_wrd_to_liv_str(string lang, object targ, string str) {
    return can_whisper_to_liv_in_wrd_str(targ, lang, str);
}

mixed can_whisper_to_liv_in_wrd_str(object targ, string lang, string str) {
    return this_player()->CanSpeak(targ, TALK_SEMI_PRIVATE, str, lang);
}

mixed do_whisper() { return 1; }

mixed do_whisper_to_liv(object ob) { return 1; }

mixed do_whisper_in_wrd(string wrd) { return 1; }

mixed do_whisper_in_wrd_to_liv(string str, object ob) { return 1; }

mixed do_whisper_to_liv_str(object targ, string str) {
    string lang = this_player()->GetDefaultLanguage() ||
        this_player()->GetNativeLanguage();
    return do_whisper_to_liv_in_wrd_str(targ, lang, str);
}

mixed do_whisper_in_wrd_to_liv_str(string lang, object targ, string str) {
    return do_whisper_to_liv_in_wrd_str(targ, lang, str);
}

mixed do_whisper_to_liv_in_wrd_str(object targ, string lang, string str) {
    if( sizeof(str) > 1){
        if( str[<1] != '?' && str[<1] != '!' && str[<1] != '.' )
            str = capitalize(str) + ".";
        else str = capitalize(str);
    }
    return this_player()->eventSpeak(targ, TALK_SEMI_PRIVATE, str,lang);
}
