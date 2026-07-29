/*    /lib/talk.c
 *    from the Dead Souls  Object Library
 *    handles general yapping
 *    created by Descartes of Borg 951118
 *    Version: @(#) talk.c 1.5@(#)
 *    Last Modified: 96/10/08
 */

#include <talk_type.h>
#include <commands.h>
#include <daemons.h>
#include <message_class.h>
#include "include/talk.h"
#define MAX_TELL_HIST_SIZE  50

private mixed TalkHist = ([]);
private string SpeakColor = "CYAN%^";

int GetPolyglot();

int direct_ask_liv_str(){ return 1; }

int direct_ask_liv_to_str(){ return 1; }

int direct_ask_liv_for_str(){ return 1; }

int direct_ask_liv_about_str(){ return 1; }

int direct_request_str_from_liv(){ return 1; }

int direct_say_to_liv(){ return 1; }

int direct_say_to_liv_str(){ return 1; }

int direct_whisper_to_liv(){ return 1; }

int direct_whisper_in_wrd_to_liv(){ return 1; }

int direct_whisper_to_liv_str(){ return 1; }

int direct_whisper_in_wrd_to_liv_str(){ return 1; }

int direct_whisper_to_liv_in_wrd_str(){ return 1; }

string SetSpeakColor(string str){
    if(!str) str = "foo";
    switch(str){
        case "red" : SpeakColor = upper_case(str)+"%^";break;
        case "green" : SpeakColor = upper_case(str)+"%^";break;
        case "orange" : SpeakColor = upper_case(str)+"%^";break;
        case "yellow" : SpeakColor = upper_case(str)+"%^";break;
        case "blue" : SpeakColor = upper_case(str)+"%^";break;
        case "magenta" : SpeakColor = upper_case(str)+"%^";break;
        case "black" : SpeakColor = upper_case(str)+"%^";break;
        case "white" : SpeakColor = upper_case(str)+"%^";break;
        case "b_red" : SpeakColor += upper_case(str)+"%^";break;
        case "b_green" : SpeakColor += upper_case(str)+"%^";break;
        case "b_orange" : SpeakColor += upper_case(str)+"%^";break;
        case "b_yellow" : SpeakColor += upper_case(str)+"%^";break;
        case "b_blue" : SpeakColor += upper_case(str)+"%^";break;
        case "b_magenta" : SpeakColor += upper_case(str)+"%^";break;
        case "b_black" : SpeakColor += upper_case(str)+"%^";break;
        case "b_white" : SpeakColor += upper_case(str)+"%^";break;
        case "b_cyan" : SpeakColor += upper_case(str)+"%^";break;
        case "flash" : SpeakColor += upper_case(str)+"%^";break;
        default : SpeakColor = "CYAN%^";break;
    }
    return SpeakColor;
}

string GetSpeakColor(){ return SpeakColor; }

int eventTellHist(string str){
    string pob = base_name(previous_object());
    string stack = implode(call_stack(2)," ");
    string tz = this_object()->GetProperty("timezone");
    if(!tz || !valid_timezone(tz)) tz = query_tz();
    if(!TalkHist) TalkHist = ([]);
    if(!TalkHist["tell"]) TalkHist["tell"] = ({});
    if(pob != SERVICES_D && pob != CMD_TELL &&
            pob != IMC2_D && pob != INSTANCES_D &&
            stack != "eventTellHist eventHearTalk eventSpeak cmd cmdAll <function>" &&
            stack != "eventTellHist eventHearTalk eventSpeak cmd cmd cmdAll <function>"){
        return 0;
    }
    if(sizeof(TalkHist["tell"]) > MAX_TELL_HIST_SIZE){
        TalkHist["tell"] -= ({ TalkHist["tell"][0] });
    }
    TalkHist["tell"] += ({ timestamp(tz)+" "+str });
    return 1;
}

string* GetTellHistory(){
    if(!TalkHist) TalkHist = ([]);
    if(!TalkHist["tell"]) TalkHist["tell"] = ({});
    if(this_object() != this_player() && !archp(this_player()))
        return ({});
    return copy(TalkHist["tell"]);
}

int eventTalkHist(string str, string type){
    string pob = base_name(previous_object());
    string stack = implode(call_stack(2)," ");
    string tz = this_object()->GetProperty("timezone");
    if(!tz || !valid_timezone(tz)) tz = query_tz();
    if(!TalkHist) TalkHist = ([]);
    if(!TalkHist[type]) TalkHist[type] = ({});
    if(sizeof(TalkHist[type]) > MAX_TELL_HIST_SIZE){
        TalkHist[type] -= ({ TalkHist[type][0] });
    }
    TalkHist[type] += ({ timestamp(tz)+" "+str });
    return 1;
}

string* GetTalkHistory(string type){
    if(!type) type = "say";
    if(!TalkHist) TalkHist = ([]);
    if(!TalkHist[type]) TalkHist[type] = ({});
    if(this_object() != this_player() && !archp(this_player()))
        return ({});
    return copy(TalkHist[type]);
}

string* GetTalkHistTypes(){
    if(!TalkHist) TalkHist = ([]);
    return keys(TalkHist);
}

varargs mixed CanSpeak(object target, string verb, string msg, string lang){
    if(!this_player()->CanBreathe()){
        return "你连呼吸都做不到。";
    }
    if( lang && (!this_object()->GetPolyglot() && (!GetLanguageLevel(lang) || !GetLanguageName(lang)) ) )
        return "你不会说那种语言！";
    if( target ){
        if( target == this_object() )
            return "你真的想自言自语吗？";
        if( userp(target) && !interactive(target) )
            return target->GetName() + " 已断线。";
        if( target->GetBlocked("tell") )
            return target->GetName() + " 正在屏蔽所有私聊。";
    }
    return 1;
}

varargs mixed eventHearTalk(object who, object target, int cls, string verb,
        string msg, string lang){
    string tmp;
    object *riders = this_object()->GetRiders() - ({ who });

    if(riders && sizeof(riders))
        riders->eventHearTalk(who, target, cls, verb, (msg ||0), (lang ||0));

    if( lang && !newbiep() && !GetPolyglot() ) msg = translate(msg, GetLanguageLevel(lang));
    switch(cls){
        case TALK_PRIVATE:
            if( target != this_object() ) return 0;
            if( verb == "reply" )
                tmp = "%^BOLD%^RED%^" + who->GetName() +
                    " 回复,%^RESET%^ \"" + msg + "%^RESET%^\"";
            else tmp = "%^BOLD%^RED%^" + who->GetName() +
                " 告诉你,%^RESET%^ \"" + msg + "%^RESET%^\"";
            if(target->GetMuffed() && member_array(who->GetKeyName(),target->GetMuffed()) == -1){
                eventTellHist(tmp);
                this_object()->eventPrint(tmp, MSG_CONV);
            }
            break;

        case TALK_SEMI_PRIVATE:
            if( target != this_object() ) return 0;
            tmp = "%^BOLD%^" + SpeakColor + who->GetName() + " 用" +
                capitalize(lang) + "语对你低语,%^RESET%^ \"" + msg + "%^RESET%^\"";
            this_object()->eventPrint(tmp, MSG_CONV);
            eventTalkHist(tmp, "whisper");
            break;

        case TALK_LOCAL:
            if( target ){
                if( target != this_object() ){
                    if( msg[<1] == '?' ) tmp = target->GetName();
                    else tmp = "对 " + target->GetName();
                    if( lang ) tmp += " 用" + capitalize(lang) + "语";
                }
                else {
                    if( msg[<1] == '?' ) tmp = "你";
                    else tmp = "对你";
                    if( lang ) tmp += " 用" + capitalize(lang) + "语";
                }
                tmp = who->GetName() + " " + tmp +
                    "说,%^BOLD%^CYAN%^ \"" + msg + "%^RESET%^\"";
                eventTalkHist(tmp, "say");
                this_object()->eventPrint(tmp, MSG_CONV);
            }
            else if( verb == "yell" ){
                tmp = "%^BOLD%^GREEN%^你听到远处一个" + who->GetGender()
                    + " " + who->GetRace() + " 用" + capitalize(lang) +
                    "语大喊,%^RESET%^ \"" + msg + "%^RESET%^\"";
                eventTalkHist(tmp, "yell");
                this_object()->eventPrint(tmp, MSG_CONV);
            }
            else {
                if( lang ) tmp = " 用" + capitalize(lang) + "语说";
                else tmp = " 说";
                tmp = who->GetName() + tmp + ", \"";
                tmp = tmp + "%^BOLD%^" + SpeakColor + msg + "%^RESET%^\"";
                this_object()->eventPrint(tmp, MSG_CONV);
                eventTalkHist(tmp, verb);
            }
            break;

        case TALK_AREA:
            tmp = "%^BOLD%^GREEN%^" + who->GetName() + " 用" +
                capitalize(lang) + "语大喊,%^RESET%^ \"" + msg + "%^RESET%^\"";
            eventTalkHist(tmp, "yell");
            this_object()->eventPrint(tmp, MSG_CONV);
            break;

        case TALK_WORLD:
            tmp = "%^BOLD%^BLUE%^" + who->GetName() + " 用" +
                capitalize(lang) + "语 shouts,%^RESET%^ \"" + msg + "%^RESET%^\"";
            eventTalkHist(tmp, "shout");
            this_object()->eventPrint(tmp, MSG_CONV);
            break;

        default:
            return 0;
    }
    this_object()->eventTalkRespond(who, target, cls, msg, lang);
    return 1;
}

mixed eventTalkRespond(object who, object targ, int cls, string msg, string lang){
    return true(who,targ,cls,msg,lang);
}

varargs mixed eventSpeak(object target, int cls, string msg, string lang){
    string verb, tmp;
    int cols;
    object env;

    if( living(environment()) ){
        object *riders = environment()->GetRiders();
        if(riders && sizeof(riders) ){
            if(member_array(this_object(),riders) != -1){
                if(environment()->GetVisibleRiders())
                    env = environment(environment());
            }
        }
    }

    if(!env) env = environment();

    if( lang && !GetPolyglot() ){
        msg = translate(msg, GetLanguageLevel(lang));
        lang = GetLanguageName(lang);
    }
    cols = GetScreen()[0];
    if( msg[<1] != '?' && msg[<1] != '!' && msg[<1] != '.' )
        msg = capitalize(msg) + ".";
    else msg = capitalize(msg);
    switch( cls ){
        case TALK_PRIVATE:
            tmp = "%^BOLD%^RED%^你对" + target->GetName() +
                ",%^RESET%^ \"" + msg + "%^RESET%^\"";
            this_object()->eventPrint(tmp, MSG_CONV);
            target->eventHearTalk(this_object(), target, cls, "tell", msg);
            eventTellHist(tmp);
            return 1;

        case TALK_SEMI_PRIVATE:
            if( !target ) tmp = "%^BOLD%^CYAN%^你用" + capitalize(lang) + "语低语,%^RESET%^ \"" + msg + "%^RESET%^\"";
            else tmp = "%^BOLD%^CYAN%^你用" + capitalize(lang) + "语对" +
                target->GetName() + "低语,%^RESET%^ \"" + msg + "%^RESET%^\"";
            eventTalkHist(tmp, "whisper");
            this_object()->eventPrint(tmp, MSG_CONV);
            env->eventHearTalk(this_object(), target, cls, "whisper",
                    msg, lang);
            return 1;

        case TALK_LOCAL:
            if( msg[<1] == '?' ) verb = GetMessage("ask") || "问";
            else if( msg[<1] == '!' ) verb = GetMessage("exclaim") || "喊道";
            else {
                verb = GetMessage("say") || "说";
                if ((msg[<1] >= 'a' && msg[<1] <= 'z') ||
                        (msg[<1] >= 'A' && msg[<1] <= 'Z')) msg = msg + ".";
            }
            if( target && msg[<1] == '?' ){
                tmp = "你" + verb + " " + target->GetName();
                if( lang ) tmp = tmp + " 用" + capitalize(lang) + "语";
            }
            else if( target ){
                tmp = "你对 " + target->GetName() + " " + verb;
                if( lang ) tmp = tmp + " 用" + capitalize(lang) + "语";
            }
            else {
                tmp = "你" + verb;
                if( lang ) tmp = tmp + " 用" + capitalize(lang) + "语";
            }
            tmp = tmp + ", \"%^BOLD%^" + SpeakColor + msg + "%^RESET%^\"";
            eventTalkHist(tmp, "say");
            this_object()->eventPrint(tmp, MSG_CONV);
            env->eventHearTalk(this_object(), target, cls, verb, msg,
                    lang);
            return 1;

        case TALK_AREA:
            tmp = "%^BOLD%^GREEN%^你用" + capitalize(lang) + "语大喊,%^RESET%^ \"" +
                msg + "%^RESET%^\"";
            eventTalkHist(tmp, "yell");
            this_object()->eventPrint(tmp, MSG_CONV);
            env->eventHearTalk(this_object(), target, cls, "yell", msg,
                    lang);
            break;

        case TALK_WORLD:
            tmp = "%^BOLD%^BLUE%^你用" + capitalize(lang) + "语 shouts,%^RESET%^ \"" +
                msg + "%^RESET%^\"";
            eventTalkHist(tmp, "shout");
            this_object()->eventPrint(tmp, MSG_CONV);
            INSTANCES_D->eventSendShout(msg, lang);
            (users() - ({ this_object() }))->eventHearTalk(this_object(), target,
                    cls,"shout", msg, lang);
            return 1;

        default:
            return 0;
    }
}
