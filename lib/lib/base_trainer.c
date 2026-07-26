/*    /lib/trainer.c
 *    from the Dead Souls  Library
 *    created 960320 by Blitz@Dead Souls
 *    Version: @(#) trainer.c 1.3@(#)
 *    Last modified: 96/10/28
 */

#include <lib.h>
#include <daemons.h>
#include "include/trainer.h"

private string* TrainingSkills;
private mapping Students;
int NoSpells = 0;
private nosave object me;

/**** driver applies ****/

void create(){
    me = this_object();;
    TrainingSkills = ({});
    Students = ([]);
    me->SetNoClean(1);
    me->SetCommandResponses( ([
                "train" : (: eventTrain :),
                "teach" : (: eventTrain :),
                "default" : (: eventHelp :),
                "help" : (: eventHelp :),
                ]) );
    me->SetRequestResponses( ([
                "help" : (: eventHelp :),
                ]) );
}

protected void init(){
    string str;
    if( !living(this_player()) ) return;
    str = this_player()->GetKeyName();
    if( Students[str] ){
        me->eventForce("speak 你需要重新开始学习，"+
                this_player()->GetName());
        map_delete(Students, str);
    }
}

int SetNoSpells(int i){
    if(i) NoSpells = 1;
    else NoSpells = 0;
    return NoSpells;
}

int GetNoSpells(){
    return NoSpells;
}

/**** data manipulation ****/

mixed AddTrainingSkills(string *args){
    if( !args )
        error("Bad argument 1 to AddTrainingSkills.");
    return (TrainingSkills = distinct_array(TrainingSkills + args));
}

mixed RemoveTrainingSkills(string *args){
    if( !args || !arrayp(args) )
        error("Bad argument 1 to RemoveTrainingSkills.");
    TrainingSkills -= args;
    return TrainingSkills;
}

string* GetTrainingSkills(){ return copy(TrainingSkills); }

string Expertise(){
    string tmp, expertises;
    string expertises2 = "";
    mapping spellbook = me->GetSpellBook();

    if(!sizeof(GetTrainingSkills())) return "none";
    else if(sizeof(GetTrainingSkills()) == 1){
        return GetTrainingSkills()[0];
    }
    expertises = implode(GetTrainingSkills(), ", ");
    if(sizeof(GetTrainingSkills()) == 2){
        expertises = replace_string(expertises,", "," and ");
    }
    else if(sizeof(GetTrainingSkills()) > 2){
        tmp = last_string_element(expertises,",");
        expertises = replace_string(expertises, tmp, " and"+tmp);
    }

    if(sizeof(spellbook) && !GetNoSpells()){
        expertises2 = implode(keys(spellbook), ", ");
        if(sizeof(spellbook) == 1) expertises2 = replace_string(expertises2,", ",".");
        else if(sizeof(spellbook) == 2){
            expertises2 = replace_string(expertises2,", "," and ",1);
            expertises2 = replace_string(expertises2,", ",".");
        }
        else {
            tmp = last_string_element(expertises2,",");
            expertises2 = replace_string(expertises2,tmp," and"+tmp);
        }
        expertises2 = "。至于法术，我可以教你 "+expertises2;
    }

    return expertises + expertises2;
}

mapping GetStudents(){ return copy(Students); }

/**** high-level events ****/

int eventHelp(object who, string unused){
    if(who) me->eventForce("speak 我不太确定你在问什么，" +
            who->GetName() + "。");
    if(sizeof( GetTrainingSkills() )){
        me->eventForce("speak 我的训练专长领域包括 " +
                Expertise() + "。");
        me->eventForce("speak 如果你有训练点数，可以 \"ask "+me->GetKeyName()+" to train "
                "<技能名>\"。");
        if(sizeof(me->GetSpellBook()) && !GetNoSpells()){
            me->eventForce("speak 你也可以 \"ask "+me->GetKeyName()+
                    " to teach <法术名>\"。");
        }
    }
    return 1;
}

int eventTrain(object who, string verb, string skill){
    mixed *langs;
    int ok;
    if( !who || environment(who) != environment() ){
        return 0;
    }
    langs = this_object()->GetLanguages();
    foreach(string lang in langs){
        if(who->GetLanguageLevel(lang) >= 95){
            ok = 1;
            me->SetDefaultLanguage(lang);
            break;
        }
    }
    if(!ok){
        write("你必须精通 "+me->GetName()+
                " 的一种语言才能理解"+possessive(me)+
                "的训练。");
        return 1;
    }
    if( !sizeof(skill) || !sizeof(verb) ) return eventHelp(who, 0);
    if(first(skill, 3) == "in ") skill = replace_string(skill,"in ","",1);
    if(first(skill, 6) == "me in ") skill = replace_string(skill,"me in ","",1);

    if( verb == "teach"){
        object ob = SPELLS_D->GetSpell(skill);

        if(!sizeof(me->GetSpellBook()) || me->GetNoSpells()){
            me->eventForce("speak 我不能教法术。我只训练技能。");
            me->eventHelp();
            return 0;
        }
        if(!ob){
            me->eventForce("speak 我从没听说过那样的法术。");
            return 0;
        }

        if( !who->eventLearnSpell(skill) ){
            me->eventForce("speak 你还没有准备好学习那个法术！");
            return 0;
        }

        who->eventPrint(me->GetName() + " 触碰了你的额头，传授给你 " +
                skill + " 的知识。");
        environment()->eventPrint(me->GetName() + " 触碰了 " +
                possessive_noun(who) +
                " 的额头，传授给 " +
                objective(who) + " " +
                skill + " 的知识。", who);
        return 1;
    }

    if(skill) skill = lower_case(skill);

    if( Students[ who->GetKeyName() ] ){
        me->eventForce("speak 我已经在训练你了！");
        return 0;
    }
    if( member_array(skill, me->GetTrainingSkills()) == -1 ){
        me->eventHelp();
        return 0;
    }
    if( member_array(skill,
                this_player()->GetSkills() ) == -1 ){
        me->eventForce("speak 你看起来不像是擅长 " +
                skill + " 的人！");
        me->eventForce("speak 我不能训练你一个你完全不会的技能。你可能需要加入一个能让你学习这个技能的公会或职业。");
        return 0;
    }
    if( this_player()->GetTrainingPoints() < 1 ){
        me->eventForce("speak 你需要更多的训练点数！");
        return 0;
    }
    Students[ who->GetKeyName() ] = skill;
    eventStart(who, skill);
    call_out((: ContinueTraining, who, skill, 0 :), TRAINING_WAIT);
    return 1;
}

nosave int ContinueTraining(object who, string skill, int x){
    if( !who || !Students[who->GetKeyName()] ) return 0;
    if( !present(who, environment()) ||
            member_array(who, this_object()->GetEnemies()) != -1){
        map_delete(Students, who->GetKeyName());
        return 0;
    }
    if( x > 4 ){
        map_delete(Students, who->GetKeyName());
        eventComplete(who, skill);
        who->eventTrain(skill, 1);
        return 1;
    } else {
        eventContinue(who, skill, ++x);
        call_out((: ContinueTraining, who, skill, x :), TRAINING_WAIT);
        return 1;
    }
}

/**** message handling events ****/

/*  The three following events are purely *aesthetic*,
 *  Hopefully prolific coders will override them for
 *  more interesting training techniques. :)
 */

int eventStart(object who, string skill){
    who->eventPrint(me->GetName() + " 开始教你 " +
            skill + " 技能。");
    environment()->eventPrint(me->GetName() + " 开始教导 " +
            who->GetName() + "……", who);
    return 1;
}

int eventContinue(object who, string skill, int x){
    who->eventPrint("你专注地听着 " + me->GetName()
            + " 继续讲解 " + possessive(me)
            + " 关于 " + skill + " 的论述。");
    return 1;
}

int eventComplete(object who, string skill){
    who->eventPrint("你对 " + skill + " 的掌握更加熟练了。");
    me->eventForce("speak 我现在能教你的都教了，" +
            who->GetName() + "。");
    return 1;
}
