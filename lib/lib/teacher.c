/*    /lib/teacher.c
 *    from the Dead Souls  Library
 *    created 960320 by Blitz@Dead Souls
 *    Version: @(#) teacher.c 1.3@(#)
 *    Last modified: 96/10/28
 */

#include <lib.h>
#include <daemons.h>
#include "include/teacher.h"

inherit LIB_SENTIENT;

private string* TeachingLanguages;
private mapping Students;
private int commercial = 0;
private int AllLangs = 0;
private int teaching_fee = 50;
private string local_currency = "silver";

int SetAllLanguages(int i){
    if(!i) AllLangs = 0;
    else AllLangs = 1;
    return AllLangs;
}

int GetAllLanguages(){
    return AllLangs;
}

int GetCommercial(){
    return commercial;
}

int SetCommercial(int i){
    if(i){
        commercial = i;
        if(!teaching_fee) teaching_fee = 50;
    }
    else commercial = 0;
    return commercial;
}

string GetLocalCurrency(){
    return local_currency;
}

string SetLocalCurrency(string str){
    local_currency = str;
    return local_currency;
}

int GetTeachingFee(){
    return teaching_fee;
}

int SetTeachingFee(int i){
    if(i){
        teaching_fee = i;
        commercial = 1;
    }
    else {
        teaching_fee = 0;
        commercial = 0;
    }
    return teaching_fee;
}

/**** driver applies ****/

protected void create(){
    sentient::create();
    TeachingLanguages = ({});
    Students = ([]);
    SetNoClean(1);
    SetCommandResponses( ([
                "teach" : (: eventTeachLanguage :),
                "teach" : (: eventTeachLanguage :),
                "default" : (: eventHelp :),
                "help" : (: eventHelp :),
                ]) );
    SetRequestResponses( ([
                "default" : (: eventHelp :),
                "help" : (: eventHelp :),
                ]) );
}

protected void init(){
    string str;
    sentient::init();
    if( !living(this_player()) ) return;
    str = this_player()->GetKeyName();
    if( Students[str] ){
        eventForce("speak 你需要重新开始学习，"+this_player()->GetName());
        map_delete(Students, str);
    }
}

/**** data manipulation ****/

mixed AddTeachingLanguages(string *args){
    string *tmp_array = ({});
    if( !args )
        error("Bad argument 1 to AddTeachingLanguages.");
    foreach(string lang in args){
        tmp_array += ({ capitalize(lower_case(lang)) });
    }
    return (TeachingLanguages = distinct_array(TeachingLanguages + tmp_array));
}

mixed RemoveTeachingLanguages(string *args...){
    if( !args || !arrayp(args) )
        error("Bad argument 1 to RemoveTeachingLanguages.");
    TeachingLanguages -= args;
    return TeachingLanguages;
}

string* GetTeachingLanguages(){ return copy(TeachingLanguages); }

string Expertise(){
    string tmp, expertises;
    if(!sizeof(GetTeachingLanguages())) return "none";
    else if(sizeof(GetTeachingLanguages()) == 1){
        return GetTeachingLanguages()[0];
    }
    expertises = implode(GetTeachingLanguages(), ", ");
    if(sizeof(GetTeachingLanguages()) == 2){
        expertises = replace_string(expertises,", "," and ");
    }
    else if(sizeof(GetTeachingLanguages()) > 2){
        tmp = last_string_element(expertises,",");
        expertises = replace_string(expertises, tmp, " and"+tmp);
    }
    return expertises;
}

mapping GetStudents(){ return copy(Students); }

/**** high-level events ****/

int eventHelp(object who, string unused){
    eventForce("speak 我不太确定你在问什么，" + who->GetName() + "。");
    if(sizeof( GetTeachingLanguages() )){
        eventForce("speak 我擅长的领域涵盖" +
                Expertise() + "。");
        eventForce("speak 如果你有训练点数，可以\"ask "+GetKeyName()+" to teach "
                "<语言>\"。");
    }
    return 1;
}

int eventTeachLanguage(object who, string verb, string language){
    if( !who || environment(who) != environment() ){
        return 0;
    }
    if( !sizeof(language) || !sizeof(verb) ) return eventHelp(who, 0);
    if( verb == "teach" ){

        language = capitalize(language);

        if( Students[ who->GetKeyName() ] ){
            eventForce("speak 我已经在教你了！");
            return 0;
        }
        if( !GetAllLanguages() &&
                member_array(language, this_object()->GetTeachingLanguages()) == -1 ){
            eventForce("speak 我对"+capitalize(language)+"语一无所知。");
            return 0;
        }
        if( !commercial && this_player()->GetTrainingPoints() < 1 ){
            eventForce("speak 你需要更多训练点数。");
            return 0;
        }
        if(commercial && this_player()->GetCurrency(GetLocalCurrency()) < teaching_fee){
            eventForce("speak 我每节课收"+teaching_fee+" "+GetLocalCurrency()+"。你似乎没有足够数量的正确货币。");
            return 0;
        }
        Students[ who->GetKeyName() ] = language;
        eventStart(who, language);
        call_out((: ContinueTeaching, who, language, 0 :), TEACHING_WAIT);
        return 1;
    }
    return 1;
}

nosave int ContinueTeaching(object who, string language, int x){
    language = capitalize(language);
    if( !who || !Students[who->GetKeyName()] ) return 0;
    if( !present(who, environment()) ||
            member_array(who, this_object()->GetEnemies()) != -1){
        map_delete(Students, who->GetKeyName());
        return 0;
    }
    if( x > 4 ){
        map_delete(Students, who->GetKeyName());
        eventComplete(who, language);
        who->AddLanguagePoints(language,5+((who->GetStatLevel("intelligence")/10)*2)+random(10));
        if(!commercial) who->AddTrainingPoints(-1);
        else who->AddCurrency(GetLocalCurrency(),-teaching_fee);
        return 1;
    } else {
        eventContinue(who, language, ++x);
        call_out((: ContinueTeaching, who, language, x :), TEACHING_WAIT);
        return 1;
    }
}

/**** message handling events ****/

/*  The three following events are purely *aesthetic*,
 *  Hopefully prolific coders will override them for
 *  more interesting teaching techniques. :)
 */

int eventStart(object who, string language){
    who->eventPrint(GetName() + " 开始教你"
            + language + "语。");
    environment()->eventPrint(GetName() + " 开始教" +
            who->GetName() + "...", who);
    return 1;
}

int eventContinue(object who, string language, int x){
    who->eventPrint("你专心聆听着" + GetName()
            + possessive(this_object())
            + "关于" + language + "的论述。");
    return 1;
}

int eventComplete(object who, string language){
    who->eventPrint("你觉得自己在" + language + "方面略有进步。");
    eventForce("speak 目前我能教你的就这些了，" +
            who->GetName() + "。");
    return 1;
}
