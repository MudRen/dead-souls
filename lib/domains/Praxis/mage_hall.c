#include <lib.h>
#include ROOMS_H
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
        message("my_action", "You have not yet voted for your class leader.  Please do so now.", this_player());
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
    SetProperty("no attack",1);
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "法师树内殿");
    SetLong(
            "欢迎来到法师树的核心！\n"
            "法师们来这里提升他们对魔法艺术的知识。"
            "可用的命令有 <cost>、<advance>、<list (编号)>、"
            "<improve 属性>、<train 技能 数量> 和 <roll stats>。"
            "穿过被闪烁的%^BLUE%^蓝色%^RESET%^光芒守护的楼梯"
            "是树的入口。"
            "<help skills> 将列出所有技能的完整名称。");
    SetExits( 
            (["up" : "/domains/Praxis/mage_join",
             "council" : "/domains/Praxis/council_hall",
             "east" : "/domains/Praxis/mage_vote",
             "down" : "/domains/Praxis/roots",
             "stairs" : "/domains/Praxis/trunk"]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetNoClean(1);
    ob->SetId( ({ "board", "crystal board", "bulletin board"}) );
    ob->set_board_id("mage_board");
    ob->set_max_posts(25);
    ob->set_edit_ok(MAGE_COUNCIL);
    ob->move("/domains/Praxis/mage_hall");
    ob->SetShort( "法师水晶布告板");
    ob->SetLong(
            "这是一块巨大的水晶板，法师们有能力将他们关于法师职业的想法"
            "注入其中。\n");
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

int roll(string str) {
    if(str != "stats") {
        notify_fail("Correct syntax: <roll stats>\n");
        return 0;
    }
    //ROOM_SETTER->do_rolls();
    return 1;
}

string get_male(int lev) {
    string *male_title_str;

    if(!male_title_str) male_title_str = allocate(20);
    male_title_str[19]      ="the new high mortal mage";
    male_title_str[18]      ="the high mage warlock";
    male_title_str[17]      ="the master warlock";
    male_title_str[16]      ="the elder warlock";
    male_title_str[15]      ="the warlock";
    male_title_str[14]      ="the lesser warlock";
    male_title_str[13]      ="the master mage";
    male_title_str[12]      ="the elder mage";
    male_title_str[11]      ="the mage";
    male_title_str[10]      ="the low mage";
    male_title_str[9]	="the grand high enchanter";
    male_title_str[8]	="the high enchanter";
    male_title_str[7]	="the enchanter";
    male_title_str[6]	="the low enchanter";
    male_title_str[5]	="the grand master conjurer";
    male_title_str[4]	="the master conjurer";
    male_title_str[3]	="the conjurer";
    male_title_str[2]	="the apprentice conjurer";
    male_title_str[1]	="the inexperienced magic user";
    male_title_str[0]	="the novice mage";
    return male_title_str[lev-1];
}

string get_female(int lev) {
    string *female_title;

    female_title = ({
            "the new high mortal mage",
            "the high mage witch",
            "the master witch",
            "the elder witch",
            "the witch",
            "the lesser witch",
            "the master mage",
            "the elder mage",
            "the mage",
            "the low mage",
            "the grand high enchantress",
            "the high enchantress",
            "the enchantress",
            "the low enchantress",
            "the grand master conjuress",
            "the master conjuress",
            "the conjuress",
            "the apprentice conjuress",
            "the inexperienced magic user",
            "the novice mage"
    });
    if(lev>20) lev = 20;
    return female_title[20-lev];
}

int advance() { return ADVANCE_D->advance(); }

int train(string str) {
    string which, which_tmp;
    int amount;

    if(!str) {
        notify_fail("正确语法：<train 技能 数量>\n");
        return 0;
    }
    if(sscanf(str, "%s %s %d", which, which_tmp, amount) == 3) which = which +" "+ which_tmp;
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
    if(!str) {
        notify_fail("提升什么？\n");
        return 0;
    }
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
        case "intelligence": return ADVANCE_D->get_stat_cost(1, lev); break;
        case "constitution": return ADVANCE_D->get_stat_cost(1, lev); break;
        case "wisdom": return ADVANCE_D->get_stat_cost(1, lev); break;
        default: return ADVANCE_D->get_stat_cost(2, lev); break;
    }
}

int cost(string str) {
    int bing;

    write("升级、训练和提升的费用：\n");
    bing = ADVANCE_D->get_exp( this_player()->query_level() + 1 );
    if(bing < 1) write("等级：\t\t升级不需要花费。");
    else write("等级：\t\t"+bing+"\n");
    write("\n技能：你通过花费你想要的经验值来训练。\n");
    write("\n");
    write("strength:\t\t" + get_cost("strength",
                this_player()->query_base_stats("strength")) +
            "\t\tconstitution:\t\t" + get_cost("constitution",
                this_player()->query_base_stats("constitution")) );
    write("intelligence:\t\t" + get_cost("intelligence",
                this_player()->query_base_stats("intelligence")) +
            "\t\tdexterity:\t\t" + get_cost("dexterity",
                this_player()->query_base_stats("dexterity")) );
    write("wisdom:\t\t" + get_cost("wisdom",
                this_player()->query_base_stats("wisdom")) +
            "\t\tcharisma:\t\t" + get_cost("charisma",
                this_player()->query_base_stats("charisma")) );
    return 1;
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

