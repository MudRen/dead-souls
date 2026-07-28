/*    /domains/Ylsrim/npc/leader.c
 *    from the Dead Souls Object Library
 *    class leader inheritable
 *    created by Descartes of Borg 951115
 *    Version: @(#) leader.c 1.5@(#)
 *    Last modified: 96/11/24
 */

#include <lib.h>
#include <daemons.h>
#include <message_class.h>
#include "include/leader.h"

inherit LIB_SENTIENT;

int eventTeachPlayer(object who, string spell);

protected void create(){
    sentient::create();
}

mixed eventAsk(object who, string str){
    string cmd, args;
    mixed tmp;
    string lang, prof, orig = str;

    lang = who->GetDefaultLanguage();
    prof = who->GetLanguageLevel(lang);
    str = translate(str, prof);
    prof = this_object()->GetLanguageLevel(lang);
    str = translate(str, prof);

    if( (tmp = sentient::eventAsk(who, orig)) == 1 ) return 1;
    if( !str || str == "" ){
        eventForce("speak 让我描述什么？描述" +
                (GetClass() || "东西") + "吗？");
        return 1;
    }
    if( sscanf(str, "%s %s", cmd, args) != 2 ){
        cmd = str;
        args = 0;
    }
    switch(cmd){
        case "describe": case "preview": case "explain":
            eventPreview(who, args);
            break;

        case "convert":
            eventConvert(who, args);
            break;

        case "join": case "become": case "be":
            eventJoin(who, args);
            break;

        case "teach":
            eventTeachPlayer(who, args);
            break;

        default:
            eventForce("speak 我不太明白你的意思");
            if( who->GetClass() ){
                eventForce("speak 你是想让我教你一个法术吗？");
            }
            else {
                eventForce("speak 你是想让我描述" +
                        pluralize((GetClass()||"东西")) + "吗？");
            }
            break;
    }
    return 1;
}

void eventConvert(object who, string args){
    if( GetSkillLevel("faith") < 1 ){
        eventForce("speak 我不做 conversions");
        return;
    }
    if( !args || args == "" ){
        eventForce("speak 转化谁？");
        return;
    }
    if( args != "me" ){
        object ob;

        ob = present(args, environment());
        if( !ob ){
            eventForce("speak 我没看到那种东西在这里");
            return;
        }
        if( !living(ob) ){
            eventForce("laugh");
            eventForce("speak 你还想让我崇拜一块奶酪吗？");
            return;
        }
        if( ob != who ){
            eventForce("speak " + ob->GetName() + " 必须自愿请求"
                    "转化。");
            return;
        }
    }
    who->SetProperty("converting", GetReligion(1));
    eventForce("speak 我试试看，希望我的信仰没有辜负我");
    call_out((: eventForce("convert " + ($(who))->GetKeyName()) :), 1);
}

void eventPreview(object who, string args){
    if( args ) args = remove_article(lower_case(args));
    if( args && args != "" && args != (""+GetClass()) ){
        if( args[0..<2] != GetClass() ){
            eventForce("speak 你想让我描述什么？");
            return;
        }
    }
    who->eventPage(DIR_CLASS_HELP "/" + GetClass(), MSG_HELP);
}

void eventJoin(object who, string args){
    string myclass = (GetClass() || "thing");
    if( !args || args == "" ){
        eventForce("speak 你是想成为" +
                add_article(myclass) + "吗？");
        return;
    }
    args = remove_article(lower_case(args));
    if( args != myclass && args[0..<2] != myclass && 
            args != pluralize(myclass) ){
        eventForce("speak 你想让我把你变成什么？");
        eventForce("speak 人们只要求我加入" +
                pluralize(myclass) + "。");
        return;
    }
    if( who->ClassMember(myclass) ){
        eventForce("speak 你已经是" + add_article(myclass) + "了");
        return;
    }
    if( who->GetClass() == who->SetClass(GetClass()) ){
        eventForce("speak 你无法成为" + add_article(GetClass()) + "！");
        eventForce("attack " + who->GetKeyName());
        return;
    }
    if( !(who->GetReligion()) && GetReligion() )
        who->SetReligion(GetReligion(0), GetReligion(1));
    environment()->eventPrint(GetName() + " 使 " + who->GetName() +
            " 成为了" + add_article(GetClass()) + "。",
            ({ who, this_object() }));
    eventForce("speak 欢迎新的" + GetClass() + "！");
    eventForce("speak 在这座殿堂里，你将找到庇护。");
    eventForce(GetClass() + " " + who->GetName() +
            " 刚刚加入了我们的行列！");
    who->SetShort("foo");  /* reset title */
    return;
}

int eventPreAttack(object ob){
    if( member_array(ob, GetEnemies()) > -1 ) return sentient::eventPreAttack(ob);
    eventForce(GetClass() + " " + pluralize((GetClass() || "市民")) + "！我们的家园正被" + ob->GetName() + "侵袭！");
    return sentient::eventPreAttack(ob);
}

int eventTeachPlayer(object who, string spell){
    object ob = SPELLS_D->GetSpell(spell);

    if( ob ){
        foreach(string skill in ob->GetSkills()){
            if( GetSkillLevel(skill) < ob->GetRequiredSkill(skill) ){
                eventForce("speak 我不懂" + spell + "。");
                return 1;
            }
        }
        if( !who->eventLearnSpell(spell) ){
            eventForce("speak 你还没有准备好学习那个法术！");
            return 1;
        }
        who->eventPrint(GetName() + " 触碰了你的额头，赐予了你"
                + spell + "的知识。");
        environment()->eventPrint(GetName() + " 触碰了" +
                possessive_noun(who) +
                " 额头，赐予了" +
                objective(who) + spell + "的知识。", who);
        return 1;
    }
    else {
        eventForce("speak 我从未听说过那种法术");
        return 1;
    }
}
