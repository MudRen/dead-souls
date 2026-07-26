/*  /verbs/players/score.c
 *  from the Dead Souls Library
 *  Displays a list of score and related info
 *  created by Blitz@Dead Souls
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;
inherit LIB_HELP;

varargs mixed eventScore();

protected void create() {
    daemon::create();
    SetNoClean(1);
    SetHelp("用法: score\n\n"
            "显示你的角色信息。\n"
            "参考: stat, status, env");
}

nosave string *FoodDegree =
({ "饿死了！", "非常饿。",
 "有点饿。", "不太饿。",
 "感觉饱了。", "很饱。" });

nosave string *DrunkDegree =
({ "清醒", "微醺", "醉了", "烂醉",
 "醉得不省人事", "醉得一塌糊涂" });

nosave string *DrinkDegree =
({ "口渴极了", "非常渴", "很渴", "渴",
 "有点渴", "不渴" });

mixed cmd(string arg) {
    eventScore(arg);
    return 1;
}

varargs mixed eventScore(string arg) {
    string *str;
    int birth, age, x, y, z, qp, xp, dbt;
    string *tmp;
    mapping lev;
    object who;
    string prn, haben, be, poss;
    string past, qual, cnj;

    if(!arg || !creatorp(this_player()) || !(who = find_player(arg))){
        who = this_player();
        haben = "have";
        be = "are";
        poss = "your";
        prn = "you";
        past = "were";
        qual = "qualify";
        cnj = "";
    }

    else {
        haben = "has";
        be = "is";
        poss = possessive(who);
        prn = nominative(who);
        past = "was";
        qual = "qualifies";
        cnj = "s";
    }
    str  = ({ who->GetShort() + " (" +
        who->GetMoralityDescription() + ")." });
    str += ({ sprintf("等级 %d %s%s %s.",
                who->GetLevel(),
                ( who->GetUndead() ? "不死 " : ""),
                capitalize(who->GetRace() || "nothing"),
                capitalize(who->GetClass() || "commoner")) });
    str += ({ "出生地是 "+who->GetTown()+"，信仰 "+
                (who->GetReligion() || "agnostic") + "。" });
    str += ({ sprintf("完成了 %s 个任务，拥有 %s 个头衔。"+
                "（%d 任务点数）",
                consolidate(sizeof(who->GetQuests()),
                    "one quest"),
                consolidate(sizeof(who->GetTitles()),
                    "one title"), who->GetQuestPoints() ) });
    birth = who->GetBirth();
    age = ( query_year(time()) - query_year(birth) );
    str += ({ sprintf("出生于第 %d 年 %s 月 %d%s 日。"
                "（%d 岁）", query_year(birth), query_month(birth),
                query_date(birth), ordinal(query_date(birth)), age) });
    if( x = who->GetTrainingPoints() < 1 ) {
        y = who->GetLevel() + 1 + (x / -4);
        str += ({ "在等级 " + y + " 时将获得训练点数。" });
    }
    else str += ({ "拥有 " + consolidate(
                who->GetTrainingPoints(),
                "one training point") + "训练点数。" });
    if( who->GetWimpy() )
        str += ({ "感觉很胆怯。" }); else
            str += ({ "感觉很勇敢。" });
    if( who->GetPoison() > 0 )
        str += ({ "中毒了。" });
    x = who->GetFood() / 17;
    if( x > sizeof(FoodDegree) - 1 ) x = (sizeof(FoodDegree) - 1);
    y = who->GetDrink() / 17;
    if( y > sizeof(DrinkDegree) - 1 ) y = (sizeof(DrinkDegree) - 1);
    z = who->GetAlcohol();
    if(z) z = (z/17) + 1;
    if( z > sizeof(DrunkDegree) - 1 ) z = (sizeof(DrunkDegree) - 1);
    str += ({ FoodDegree[x] });
    str += ({ sprintf("%s，%s。", DrinkDegree[y], DrunkDegree[z]) });
    x = who->GetCustomStats();

    tmp = ({});
    qp = who->GetQuestPoints();
    xp = who->GetExperiencePoints();
    dbt = who->GetExperienceDebt();
    lev = PLAYERS_D->GetLevelList()[(who->GetLevel()) + 1];

    if(dbt){
        str += ({ "有 "+dbt+" 点经验值债务。" });
    }

    if(lev){
        if(REQUIRE_QUESTING){
            qp = lev["qp"] - qp;
            if(qp > 0) tmp += ({"还需要 "+comma(qp)+" 任务点数才能升级。"});
        }

        xp = lev["xp"] - xp;
        if(xp > 0) tmp += ({"还需要 "+comma(xp)+" 经验点数才能升级。"});
        if(!sizeof(tmp)) tmp += ({"满足升级条件。"});
        str += tmp;
    }

    if(x){
        str += ({ "\n还有 "+x+" 点定制点数。输入: help customize" });
    }
    this_player()->eventPage(str, "info");
    return 1;
}
