/*    /verbs/common/ask.c
 *    from the Dead Souls Object Library
 *    created by Blitz@Dead Souls
 */

#include <lib.h>
#include <talk_type.h>
#include "include/ask.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("ask");
    SetRules("LIV STR", "STR", "LIV to STR", "LIV for STR", "LIV about STR");
    SetErrorMessage("问什么？或者让谁做什么？");
    SetHelp("用法：ask <生物> <某事>\n"
            "      ask <某事>\n"
            "      ask <生物> about <某事>\n"
            "      ask <生物> to <做某事>\n"
            "      ask <生物> for <某物>\n\n"
            "当你用特定问题询问目标时，一些NPC和某些无生命的物品会做出回应。\n"
            "另见：reply, say, shout, speak, tell, whisper, yell");
}

mixed can_ask_liv_to_str(string str) { return 1; }

mixed can_ask_liv_for_str(string str) { return 1; }

mixed can_ask_liv_about_str(string str) { return 1; }

mixed can_ask_liv_str(string str) {
    string tmp;

    if( !str ) {
        str = "";
    }
    if( sscanf(str, "to %s", tmp) ) return 1;
    else if( sscanf(str, "for %s", tmp) ) return 1;
    else return this_player()->CanSpeak(/* ob */0, TALK_LOCAL, str);
}

mixed can_ask_str(string str) {
    return this_player()->CanSpeak(0, TALK_LOCAL, str);;
}

mixed do_ask_liv_to_str(object ob, string str) {
    string lang = this_player()->GetDefaultLanguage();
    //string pre = "In " + lang + ", ";
    string pre = "";
    int lvl;
    string msg = translate(str, lvl=(this_player()->GetLanguageLevel(lang)));
    if(lvl < 50) pre += "用糟糕的"+lang+"，";
    else if(lvl < 60) pre += "用很差的"+lang+"，";
    else if(lvl < 75) pre += "用生硬的"+lang+"，";
    else if(lvl < 99) pre += "用不太流利的"+lang+"，";
    else pre += "用"+lang+"，";
    msg = translate(msg, ob->GetLanguageLevel(lang));
    message("my_action", pre + "你请求"+ob->GetName()+"去做"+str+"。",
            this_player() );
    message("other_action", pre + this_player()->GetName()+"请求"
            "你去做"+msg+"。", ob);
    message("other_action", pre + this_player()->GetName()+"请求"+
            ob->GetName()+"做某事。",
            environment(ob), ({ ob, this_player() }) );
    ob->eventAsk(this_player(), str);
    return 1;
}

mixed do_ask_liv_for_str(object ob, string str) {
    string lang = this_player()->GetDefaultLanguage();
    string pre = "用" + lang + "，";
    string msg = translate(str, this_player()->GetLanguageLevel(lang));
    msg = translate(msg, ob->GetLanguageLevel(lang));
    message("my_action", pre + "你向"+ob->GetName()+"索要"+str+"。",
            this_player() );
    message("other_action", pre + this_player()->GetName()+"向"+
            ob->GetName()+"索要某物。",
            environment(ob), ({ ob, this_player() }) );
    if( !(ob->eventRequest(this_player(), str)) )
        message("other_action", pre + this_player()->GetName()+"向"
                "你索要"+msg+"。", ob);
    return 1;
}

mixed do_ask_liv_about_str(object ob, string str) {
    string lang = this_player()->GetDefaultLanguage();
    string pre = "用" + lang + "，";
    string msg = translate(str, this_player()->GetLanguageLevel(lang));
    msg = translate(msg, ob->GetLanguageLevel(lang));
    message("my_action", pre + "你向"+ob->GetName()+"询问关于"+str+"的事。",
            this_player() );
    message("other_action", pre + this_player()->GetName()+"向"+
            ob->GetName()+"询问某事。",
            environment(ob), ({ ob, this_player() }) );
    if( !(ob->eventConsult(this_player(), str)) )
        message("other_action", pre + this_player()->GetName()+"向"
                "你询问关于"+msg+"的事。", ob);
    return 1;
}

mixed do_ask_liv_str(object ob, string str) {
    mixed tmp;
    if( sscanf(str, "to %s", tmp) ) return do_ask_liv_to_str(ob, tmp);
    if( sscanf(str, "for %s", tmp) ) return do_ask_liv_for_str(ob, tmp);
    if( sscanf(str, "about %s", tmp) ) return do_ask_liv_about_str(ob, tmp);
    if( str[<1] != '?' ) str = capitalize(str) + "?";
    else str = capitalize(str);
    return this_player()->eventSpeak(ob, TALK_LOCAL, str);
}

mixed do_ask_str(string str) {
    if( str[<1] != '?' ) str = capitalize(str) + "?";
    else str = capitalize(str);
    return this_player()->eventSpeak(0, TALK_LOCAL, str);
    return 1;
}
