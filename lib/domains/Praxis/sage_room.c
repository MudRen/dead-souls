//  /d/standard/sage_room
//  by Valodin
//  This is where you can learn new languages and fix old ones

#include <lib.h>
#include <daemons.h>
#include <clock.h>

//  This is how many experience points == one second
#define SEC_TO_EXP  3

inherit "/lib/std/room";

#define OLD_LANGUAGES ({ "elvish", "giantish", "orcish", "artrellian", "mischief", "sensuous", "hobbitish", "pseudo-speak", "gnomish" })

mapping queue;

void create() {
    ::create();
    queue = ([]);
    SetProperty("light", 3);
    SetProperty("indoors", 1);
    SetProperty("no steal", 1);
    SetProperty("no attack", 1);
    SetProperty("no magic", 1);
    SetShort( "贤者之室");
    SetLong( "这间烟雾缭绕的房间墙壁上挂满了来自遥远土地的装饰品。"
            "在一团巨大的烟雾中央坐着一位白发矮小的老人。"
            "他看起来非常睿智。这里有关于如何说不同语言的书籍。");
    SetItems(
            ([({"sage", "man", "old man"}) : "贤者是一位矮小、"
             "满脸皱纹的老人。但他看起来非常睿智。",
             ({"walls", "trappings"}) : "墙上覆盖着用多种语言书写的"
             "奇怪文字，但在贤者烟斗冒出的烟雾中几乎看不清楚。",
             "pipe" : "贤者在抽着这个小水烟斗。"
             "缕缕烟雾让你想起了那个人的胡须。",
             ({"book", "books"}) : "翻阅书籍时，你决定应该学习一门新语言。"]) );
    AddExit("south", "/domains/Praxis/w_boc_la2", (: "leave_the_room" :) );
}

void init() {
    ::init();
    add_action("ask_sage", "ask");
    add_action("study_lang", "study");
}

int remove_old_lang(object ob) {
    string *langs;
    int i, szl;

    if(!function_exists("query_all_languages", ob))
        return 0;
    langs = ob->query_all_languages();
    for(i = 0, szl = sizeof(langs); i < szl; i++)
        if(member_array(langs[i], OLD_LANGUAGES) != -1)
            ob->remove_language(langs[i]);
    return 1;
}

int fix_languages() {
    write("贤者专注地注视着你。");
    if(!remove_old_lang(this_player()))
    {
        write("贤者说：你需要新的身体，我才能帮助你的心智。");
        return 1;
    }
    //LANG_D->init_languages(this_player());
    write("贤者说：你已经被治愈了，我的" +
            ((this_player()->query_gender() == "male") ? "孩子" :
             "孩子") + "。");
    return 1;
}

int ask_sage(string str)
{
    string trash;

    notify_fail("问谁，问什么？\n");
    if(!str)
        return 0;
    if(sscanf(str, "sage%s", trash, trash) == 1)
        notify_fail("你想问贤者什么？\n");
    if(sscanf(str, "sage%sfix%s", trash, trash) == 2)
    {
        return fix_languages();
    }
    return 0;
}

int able_to_study(int amount)
{
    int exp;

    exp = this_player()->query_exp();
    if((exp - amount) < 
            ADVANCE_D->get_exp(this_player()->query_level()))
        return 0;
    else
        return 1;
}

int coclean(mixed *element, object ob)
{
    if(element[0] != ob)
        return 0;
    else
        return 1;
}

void clean_call_outs(object ob)
{
    mixed *all_callouts;
    int i, acsz;

    all_callouts = call_out_info();
    all_callouts = filter_array(all_callouts, "coclean", this_object(), 
            this_object());
    for(i = 0, acsz = sizeof(all_callouts); i < acsz; i++)
        remove_call_out(all_callouts[i][1]);
    for(i = 0, acsz = sizeof(all_callouts); i < acsz; i++)
        if(all_callouts[i][3] != ob)
            call_out(all_callouts[i][1], all_callouts[i][2], all_callouts[i][3]);
}

int convert_time(string str)
{
    string *times;
    int ret, i, j, tln;

    times = explode(str, " ");
    ret = 0;
    tln = sizeof(times) / 2;
    for(i = 0; i < tln; i++)
    {
        j = to_int(times[2 * i]);
        switch(times[2 * i + 1])
        {
            case "seconds":
            case "second":
                j = j * SECOND;
                break;
            case "minutes":
            case "minute":
                j = j * MINUTE;
                break;
            case "hours":
            case "hour":
                j = j * HOUR;
                break;
            case "days":
            case "day":
                j = j * DAY;
                break;
            case "week":
            case "weeks":
                j = j * WEEK;
                break;
            case "month":
            case "months":
                j = j * MONTH;
                break;
            case "year":
            case "years":
                j = j * YEAR;
                break;
            default:
                return 0;
        }
        ret += j;
    }
    return ret;
}

int study_lang(string str)
{
    string lang, timestr;
    int nmtimespan;

    if(!str)
    {
        write("学习哪种语言，学多长时间？");
        return 1;
    }

    if(queue[this_player()])
    {
        write("贤者说：我不能同时教你两种语言，我的" +
                ((this_player()->query_gender() == "male") ? "孩子。" :
                 "孩子。"));
        return 1;
    }

    if(!function_exists("learn_language", this_player()))
    {
        write("贤者说：抱歉，我的" +
                ((this_player()->query_gender() == "male") ? "孩子" :
                 "孩子") + "，但我无法在你现在的身体状态下教你。");
        return 1;
    }
    if((sscanf(str, "%s for %s", lang, timestr) != 2) || (lang == "") ||
            (timestr == "") || !(nmtimespan = convert_time(timestr)))
    {
        write("学习哪种语言，学多长时间？");
        return 1;
    }

    lang = lower_case(lang);

    if(nmtimespan <= 0)
    {
        write("贤者厌恶地对你摇了摇头。");
        return 1;
    }
    if(nmtimespan > DAY)
    {
        write("你觉得在那之前你早就饿了、厌烦了。");
        return 1;
    }

    if(!able_to_study(SEC_TO_EXP * nmtimespan))
    {
        write("贤者说：抱歉，我的" +
                ((this_player()->query_gender() == "male") ? "孩子" :
                 "孩子") + "，但你的经验不足以学习那么长时间。");
        return 1;
    }

    write("你开始学习" + capitalize(lang) + "。你必须留在这里"
            "学习直到时间结束才能学会这门语言。");
    queue[this_player()] = ({ lang, (SEC_TO_EXP * nmtimespan) });
    call_out("advance_em", nmtimespan, this_player());

    //if(member_array(lang, (LANG_D->all_languages())) == -1)
    //{
    // write("The sage says: " + capitalize(lang) + " is an uncommon language.  "
    //	  "If you did not mean to study it, then you should leave now, my " +
    //	  ((this_player()->query_gender() == "male") ? "son." :
    //	   "daughter."));
    //   return 1;
    //}
    return 1;
}

int leave_the_room()
{
    if(queue[this_player()])
    {
        write("你决定放弃学习，去做其他事情。");
        map_delete(queue, this_player());
        clean_call_outs(this_player());
    }
    return 1;
}

void advance_em(mixed arg)
{
    object ob;
    string lang;
    int exp;

    ob = (object)arg;
    if(!ob || (environment(ob) != this_object()))
    {
        if(ob)
            if(queue[ob])
                map_delete(queue,ob);
        return;
    }

    if(!queue[ob])
        return;

    lang = queue[ob][0];
    exp = queue[ob][1];
    ob->add_exp(-exp);
    ob->learn_language(lang, exp);
    write("你完成了" + capitalize(lang) + "的学习。");
    map_delete(queue, ob);
}
