#include <lib.h>
#include <council.h>
#include <daemons.h>

inherit LIB_ROOM;

string get_new_title(object tp);
string get_male(int lev);
string get_female(int lev);
string previous_title(object tp);
int get_cost(string which, int lev);

int CanReceive(object ob) {
    if(!VOTING_D->is_time_to_vote())
        return ::CanReceive(ob);
    if(creatorp(this_player()) || this_player()->query_level() < 2)
        return ::CanReceive(ob);
    if(VOTING_D->query_voted(this_player()->query_name(),
                this_player()->query_class()))
        return ::CanReceive(ob);
    else {
        message("my_action", "你还没有投票选举你的职业领袖。请现在就去投票。", this_player());
        call_out("move_me", 5, this_player());
    }
    return ::CanReceive(ob);
}

void move_me(object who) {
    who->eventMoveLiving("/domains/Praxis/"+who->query_class()+"_vote");
    return;
}

void create() {
    object ob;

    ::create();
    SetProperties(([ "no attack":1, "no castle" :1, "light":2, "indoors":1]));
    SetShort("卡塔安中央密室");
    SetLong(
            "欢迎来到卡塔安中央密室！\n"
            "你发现自己身处一个非常黑暗潮湿的洞穴。影子在洞穴的"
            "石壁上舞动，空气中弥漫着邪恶的气息。卡塔安们来这里"
            "提升战斗和魔法技艺。"
            "可用的命令有 <cost>、<advance>、<list(编号)>、"
            "<improve 属性>、<train 技能 数量> 和 <roll>。"
            "穿过被闪烁的%^BLUE%^蓝色%^RESET%^光芒守护的洞口向下"
            "是主大厅的入口。"
            "<help skills> 将列出所有技能的完整名称。");
    SetExits( ([ 
                "up" : "/domains/Praxis/kataan_join",
                "council" : "/domains/Praxis/council_hall",
                "east" : "/domains/Praxis/kataan_vote",
                ]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board", "bulletin board", "board of despair" }) );
    ob->set_board_id("kataan_board");
    ob->set_edit_ok(KATAAN_COUNCIL);
    ob->set_max_posts(25);
    ob->move("/domains/Praxis/kataan_hall");
    ob->SetShort( "卡塔安绝望布告板");
    ob->SetLong(
            "我们世界的卡塔安们在这里发布背叛故事和恶魔传说，供所有人查看。\n");
}

void init() {
    ::init();
    add_action("cost","cost");
    add_action("roll","roll");
    add_action("train", "train");
    add_action("improve", "improve");
    add_action("advance","advance");
    add_action("list","list");
}

int roll() { call_other("/domains/Praxis/setter", "do_rolls"); return 1; }

string get_new_title(object tp)
{
    int lev;
    string gen, title;

    lev = this_player()->query_level();
    gen = this_player()->query_gender();
    if(this_player()->query_guild()) {
        if(present(tp->query_guild()+"_ob", tp)) {
            if(lev > 19) title = "High mortal";
            else title = present(tp->query_guild()+"_ob", tp)->query_title(tp);
            title += " $N";
        }
        else {
            if(lev > 19) title = "High mortal $N";
            else title = "$N";
        }
    }
    else {
        if(lev > 20) title = "High mortal $N";
        else title = "$N";
    }
    if(lev > 20) title += previous_title(tp);
    else if(gen == "male") title += " "+get_male(lev);
    else title += " "+get_female(lev);
    return title;
}

string get_male(int lev) {
    string *male_title_str;

    if(!male_title_str) male_title_str = allocate(20);
    male_title_str[19]      ="the supreme high kataan of doom";
    male_title_str[18]      ="the supreme kataan of doom";
    male_title_str[17]      ="the high kataan of doom";
    male_title_str[16]      ="the kataan of doom";
    male_title_str[15]      ="the javelin of death";
    male_title_str[14]      ="the warmage of evil";
    male_title_str[13]      ="the lesser kataan";
    male_title_str[12]      ="the great shaman of the underrealms";
    male_title_str[11]      ="the shaman of the underrealms";
    male_title_str[10]      ="the demonic warmage";
    male_title_str[9]       ="the evil warmage";
    male_title_str[8]       ="the warmage";
    male_title_str[7]       ="the archer of kataan";
    male_title_str[6]       ="the shamanic follower of kataan";
    male_title_str[5]       ="the bolt thrower";
    male_title_str[4]       ="the bolt tosser";
    male_title_str[3]       ="the rock thrower";
    male_title_str[2]       ="the rock tosser";
    male_title_str[1]       ="the pebble thrower";
    male_title_str[0]       ="the pebble tosser";
    return male_title_str[lev-1];
}

string get_female(int lev) {
    return get_male(lev);
}

int advance() { return ADVANCE_D->advance(); }

int train(string str) {
    string which, which_tmp;
    int amount;

    if(!str) {
        notify_fail("正确语法：<train 技能 数量>\n");
        return 0;
    }
    if(sscanf(str, "%s %s %d", which, which_tmp, amount) == 3) which = which+ " "+ which_tmp;
    else if(sscanf(str, "%s %d", which, amount) !=2) {
        notify_fail("正确语法：<train 技能 数量>\n");
        return 0;
    }
    which = lower_case(which);
    if(!this_player()->skill_exists(which)) {
        notify_fail("没有这个技能。\n");
        return 0;
    }
    return ADVANCE_D->train_player(this_player(), which, amount);
}

int improve(string str) {
    string *stats;
    int stat_cost;

    stats = ({ "strength", "intelligence", "wisdom", "dexterity", "constitution", "charisma" });
    str = lower_case(str);
    if(member_array(str, stats) == -1) {
        notify_fail("你没有这个属性。\n");
        return 0;
    }
    stat_cost = get_cost(str, this_player()->query_base_stats(str));
    if( this_player()->query_exp()-stat_cost < ADVANCE_D->get_exp( this_player()->query_level() ) ) {
        notify_fail("你的经验不足以以那种方式提升自己。\n");
        return 0;
    }
    this_player()->SetStat(str, this_player()->query_base_stats(str) + 1);
    this_player()->add_exp(-stat_cost);
    write("你感觉更加");
    say(this_player()->query_cap_name()+"看起来更加");
    if(str == "strength") tell_room(this_object(), "强壮了。\n");
    else if(str == "intelligence") tell_room(this_object(), "聪明了。\n");
    else if(str == "wisdom") tell_room(this_object(), "睿智了。\n");
    else if(str == "dexterity") tell_room(this_object(), "敏捷了。\n");
    else if(str == "constitution") tell_room(this_object(), "健壮了。\n");
    else tell_room(this_object(), "有魅力了。\n");
    return 1;
}

int get_cost(string stat, int lev) {
    switch(stat) {
        case "strength": return ADVANCE_D->get_stat_cost(1, lev); break;
        case "intelligence": return ADVANCE_D->get_stat_cost(1, lev); break;
        case "charisma": return ADVANCE_D->get_stat_cost(1, lev); break;
        default: return ADVANCE_D->get_stat_cost(2, lev); break;
    }
}

int cost(string str) {
    int bing;

    write("升级、训练和提升的费用：\n");
    bing = ADVANCE_D->get_exp( this_player()->query_level() + 1 );
    if(bing < 1) write("等级：\t\t升级不需要花费。");
    else write("等级：\t\t"+bing+"\n");
    write("技能：你通过花费你想要的经验值来训练。\n");
    write("力量：\t\t" + get_cost("strength",
                this_player()->query_base_stats("strength")) +
            "\t\t体质：\t\t" + get_cost("constitution",
                this_player()->query_base_stats("constitution")) );
    write("智力：\t\t" + get_cost("intelligence",
                this_player()->query_base_stats("intelligence")) +
            "\t\t敏捷：\t\t" + get_cost("dexterity",
                this_player()->query_base_stats("dexterity")) );
    write("智慧：\t\t" + get_cost("wisdom",
                this_player()->query_base_stats("wisdom")) +
            "\t\t魅力：\t\t" + get_cost("charisma",
                this_player()->query_base_stats("charisma")) );
    return 1;
}

string previous_title(object tp) {
    string pre, post, str;

    str = tp->getenv("TITLE");
    sscanf(str, "%s $N %s", pre, post);
    return post;
}

int list(string str) {
    int x;

    if(!str) "/domains/Praxis/quest_room"->list_quests(this_player(), 0);
    else {
        if(sscanf(str, "%d", x) != 1) {
            notify_fail("你必须给出想要列出的任务编号。\n");
            return 0;
        }
        if(x<1) {
            notify_fail("没有这个任务。\n");
            return 0;
        }
        "/domains/Praxis/quest_room"->list_quests(this_player(), x);
    }
    return 1;
}
