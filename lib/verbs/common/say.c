/*    /verbs/common/say.c
 *    from the Dead Souls  Object Library
 *    say
 *    sat to LIV
 *    say STR
 *    say to LIV STR
 *    created by Descartes of Borg 951118
 */

#include <lib.h>
#include <talk_type.h>
#include "include/say.h"

inherit LIB_VERB;

protected void create() {
    ::create();
    SetVerb("say");
    SetRules("","to LIV STR","STR");
}

mixed can_say_to_liv(object ob) {
    if( !ob ) return 0;
    return "你想对"+ ob->GetName() + "说什么？";
}

mixed can_say_to_liv_str(object targ, string str) {
    string lang = this_player()->GetDefaultLanguage() || 
        this_player()->GetNativeLanguage();
    return this_player()->CanSpeak(targ, TALK_LOCAL, str, lang);
}

mixed can_say(mixed args...) {
    return 1;
}

mixed can_say_str(string str) {
    string lang = this_player()->GetDefaultLanguage() ||
        this_player()->GetNativeLanguage();
    if( !str ) return 0;
    return this_player()->CanSpeak(0, TALK_LOCAL, str, lang);
}

mixed do_say(mixed args...){
    write("说什么？");
    return "说什么？";

mixed do_say_to_liv(object ob) { return 1; }

mixed do_say_to_liv_str(object targ, string str) {
    string lang = this_player()->GetDefaultLanguage() ||
        this_player()->GetNativeLanguage();
    return this_player()->eventSpeak(targ, TALK_LOCAL, str, lang);
}

mixed do_say_str(string str) { return do_say_to_liv_str(0, str); }

string GetHelp(string str) {
    return ("语法：say <消息>\n"
            "        say to <生物> <消息>\n\n"
            "发送一个房间里的所有人都能看到的消息。如果你"
            "指定了目标，目标人物会被显示为消息的目标。\n"
            "另见：shout, speak, reply, tell, whisper");
}
