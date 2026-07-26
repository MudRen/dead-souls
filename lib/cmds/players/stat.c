/*    /cmds/creator/stat.c
 *    from the Dead Souls LPC Library
 *    a command to view something's stats
 *    created by Descartes of Borg 950409
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

string gargs;

mixed cmd(string args) {
    string *lines, *arr, *limbs;
    object ob, *candidates;
    string tmp1, tmp2, gold;
    int i, x, y, cols, dbt;

    if( args == "" || !args || args == "me" ) ob = this_player();
    else if(args && !creatorp(this_player())) {
        write("你只能查看自己的状态。");
        return 1;
    }
    if(!environment(this_player())){
        write("你没有环境。状态是你最不用担心的事情。");
        return 1;
    }
    gargs = args;
    candidates = filter(get_livings(environment(this_player())),
            (: answers_to(gargs, $1) :) );
    if(!ob && sizeof(candidates)) ob = candidates[0];
    else if( !ob && !(ob = present(args, environment(this_player()))) )
        if( !(ob = find_player(convert_name(args))) &&
                !(ob = find_living(lower_case(args))) &&
                !(ob = find_object(args)) )
            return capitalize(args) + " is nowhere to be found.";
    if(!living(ob)) return capitalize(args) + " 不是活物。";
    cols = (this_player()->GetScreen())[0];
    tmp1 = ob->GetCapName() + " 又名 " + ob->GetShort() +
        "，等级 " + ob->GetLevel() + " " + ob->GetGender();
    if( !(tmp2 = ob->GetRace()) ) tmp2 = "blob";
    tmp1 += " " + tmp2;
    if( !(tmp2 = ob->GetClass())  || !stringp(tmp2)) tmp2 = "drifter";
    tmp1 += " " + capitalize(tmp2);
    if( tmp2 = ob->GetSpouse() )
        tmp1 += " (配偶: " + tmp2 + ")";
    lines = ({ center(tmp1, cols) });
    if( ob->GetUndead() ) tmp1 = "%^BOLD%^RED%^不死%^RESET%^";
    else tmp1 = "%^BOLD%^GREEN%^存活%^RESET%^";
    if( ob->GetSleeping() ) tmp1 += " / 睡眠中";
    else tmp1 += " / 清醒";
    if( ob->GetParalyzed() ) tmp1 += " / 麻痹";
    lines += ({ center(tmp1, cols), "" });
    lines += ({ center("生命: " +ob->GetHealthPoints() + "/"+
                ob->GetMaxHealthPoints() + "   魔法: " +
                ob->GetMagicPoints() + "/" +
                ob->GetMaxMagicPoints() + "   体力: " +
                ob->GetStaminaPoints() + "/" +
                to_int(ob->GetMaxStaminaPoints()) + "   负重: " +
                ob->GetCarriedMass() + "/" +
                ob->GetMaxCarry(), cols) });
    lines += ({ center("食物: " + ob->GetFood() + "    " +
                "饮水: " + ob->GetDrink() + "    " +
                "酒精: " + ob->GetAlcohol() + "    " +
                "咖啡因: " + ob->GetCaffeine() + "    " +
                "毒素: " + ob->GetPoison() + "    ", cols) });
    lines += ({ "\n" }) ;
    if(dbt = ob->GetExperienceDebt()) {
        lines += ({ center("训练点数: " + ob->GetTrainingPoints() +
                    "    " +
                    "任务点数: "+ ob->GetQuestPoints(),cols)
                });
        lines += ({ center("经验值: " + ob->GetExperiencePoints() +
                    "    " +
                    "经验债务: "+ dbt,cols)
                });
    } else {
        lines += ({ center("训练点数: " + ob->GetTrainingPoints() +
                    "    " +
                    "任务点数: "+ ob->GetQuestPoints() +
                    "    " +
                    "经验值: "+ ob->GetExperiencePoints(),cols)
                });
    }
    lines += ({ "", "肢体:" });
    limbs = ob->GetWieldingLimbs();
    if(ob && !ob->GetGhost()) arr = map(sort_array(ob->GetLimbs(), 1),
            (: sprintf("%:-14s%s (%d) %d/%d", $1,
                       ((member_array($1, $(limbs)) == -1) ? " " : "*"),
                       ($(ob))->GetLimbClass($1),
                       ($(ob))->GetHealthPoints($1),
                       ($(ob))->GetMaxHealthPoints($1)) :));
    i = sizeof(arr);
    while(i--) if( (y = strlen(arr[i])) > x ) x = y;
    x = cols/(x+2);
    lines += explode(format_page2(arr, x), "\n") + ({ "", "技能:" });
    arr = map(sort_array(ob->GetSkills(), 1),
            function(string skill, object who) {
            mapping mp = who->GetSkill(skill);
            int x, max;
            x = to_int(percent(mp["points"],
                    who->GetMaxSkillPoints(skill, mp["level"])));
            max = who->GetMaxSkillLevel(skill);
            if( max < mp["level"] ) max = mp["level"];
            return sprintf("%:-18s (%d) %:2d%% - %d/%d",
                skill, mp["class"], x, mp["level"], max);
            }, ob);
    i = sizeof(arr);
    while(i--) if( (y = strlen(arr[i])) > x ) x = y;
    x = cols/(x+2);
    lines += explode(format_page2(arr, x), "\n") + ({ "", "属性:" });
    arr = map(sort_array(ob->GetStats(), 1),
            (: sprintf("%:-12s (%d) %d/%d", $1,
                       ($(ob))->GetStatClass($1),
                       ($(ob))->GetStatLevel($1),
                       ($(ob))->GetBaseStatLevel($1)) :));
    i = sizeof(arr);
    x = 0;
    while(i--) if( (y = strlen(arr[i])) > x ) x = y;
    x =cols/(x+2);
    lines += explode(format_page2(arr, x), "\n");
    if(sizeof(ECONOMY_D->__QueryCurrencies())){
        if(valid_currency("gold")) gold = "gold";
        else gold = ECONOMY_D->__QueryCurrencies()[0];
        lines += ({ "", ob->GetName()+" 已积累净资产 " +
                ( ob->GetNetWorth(gold) ) + " "+gold+"。"});
        arr = filter( map(ob->GetCurrencies(),
                    (: ($(ob))->GetCurrency($1) &&
                     sprintf("%d %s", ($(ob))->GetCurrency($1), $1) :)),
                (: $1 :));
        lines += ({ "持有金钱: "+implode(arr, ", ") });
    }
    this_player()->eventPage(lines, "system");
    return 1;
}

string GetHelp(){
    string ret = "用法: stat";
    if(creatorp(this_player())) ret += " [生物]";
    ret += "\n\n显示生物的统计信息。\n"+
        "参考: score, status, env.";
    return ret;
}
