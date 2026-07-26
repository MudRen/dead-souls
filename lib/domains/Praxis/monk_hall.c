#include <lib.h>
#include <council.h>
#include <daemons.h>

inherit LIB_ROOM;

string get_new_title(object tp);
string get_male(int lev);
string get_female(int lev);
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
        message("my_action", "你还没有投票选举职业领袖。请现在就去投票。", this_player());
        call_out("move_me", 5, this_player());
    }
    return ::CanReceive(ob);
}

void move_me(object ob) {
    ob->eventMoveLiving("/domains/Praxis/"+ob->query_class()+"_vote");
    return;
}


void create() {
    object ob, box;

    ::create();
    SetProperty("no attack",1);
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetProperty("no castle", 1);
    SetShort( "僧侣大厅内");
    SetLong(
            "欢迎来到永恒圣洁修道院。\n"
            "所有僧侣都来这里提升生命和学习。"
            "可用的命令有 <cost>、<advance>、<list (编号)>、"
            "<improve 属性>、<train 技能 数量> 和 <roll stats>。"
            "穿过被闪烁的%^BLUE%^蓝色%^RESET%^光芒守护的通道向西"
            "是修道院的入口。输入 <help skills> 可以获得技能的完整名称列表。");
    SetExits( 
            (["west" : "/domains/Praxis/monk_join",
             "council" : "/domains/Praxis/council_hall",
             "east" : "/domains/Praxis/monk_vote"]) );

    ob = new(LIB_BOARD);
    ob->SetKeyName("tableau");
    ob->SetId( ({ "holy tableau", "tableau", "monk tableau", "board" }) );
    ob->set_board_id("monk_board");
    ob->set_max_posts(25);
    ob->set_edit_ok(MONK_COUNCIL);
    ob->move("/domains/Praxis/monk_hall");
    ob->SetShort( "僧侣圣板");
    ob->SetLong( "僧侣们在上面记录想法的圣板。\n");
    //box = new("/realms/nialson/monks/donation");
    //box->move(this_object());
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
    if(str != "stats") return 0;
    call_other("/domains/Praxis/setter", "do_rolls");
    return 1;
}

string get_new_title(object tp)
{
    int lev;
    string gen, title;

    lev = this_player()->query_level();
    gen = this_player()->query_gender();
    if(this_player()->query_guild()) {
        if(present(tp->query_guild()+"_ob", tp)) {
            title = present(tp->query_guild()+"_ob", tp)->query_title(tp);
            title += " $N";
        }
        else title = "$N";
    }
    else title = "$N";
    if(gen == "male") title += " "+get_male(lev);
    else title += " "+get_female(lev);
    return title;
}

string get_male(int lev) {
    string *male_title_str;

    if(!male_title_str) male_title_str = allocate(20);
    male_title_str[19]      ="the angel";
    male_title_str[18]      ="the prophet";
    male_title_str[17]      ="the saint";
    male_title_str[16]      ="the doctor of divinity";
    male_title_str[15]      ="the devil-dodger";
    male_title_str[14]      ="the pope";
    male_title_str[13]      ="the holy father";
    male_title_str[12]      ="the cardinal priest";
    male_title_str[11]      ="the spiritual father";
    male_title_str[10]      ="the great missionary";
    male_title_str[9]       ="the missionary";
    male_title_str[8]       ="the promoter of the faith";
    male_title_str[7]       ="the high priest";
    male_title_str[6]       ="the priest";
    male_title_str[5]       ="the born again priest";
    male_title_str[4]       ="the evangelist";
    male_title_str[3]       ="the preacher";
    male_title_str[2]       ="the servant of God";
    male_title_str[1]       ="the bible reader";
    male_title_str[0]       ="the choir boy";
    return male_title_str[lev-1];
}

string get_female(int lev) {
    string *fem_title_str;

    if(!fem_title_str) fem_title_str = allocate(20);
    fem_title_str[19]       ="the angel";
    fem_title_str[18]       ="the prophet";
    fem_title_str[17]       ="the saint";
    fem_title_str[16]       ="the doctor of divinity";
    fem_title_str[15]       ="the devil-dodger";
    fem_title_str[14]       ="the pope";
    fem_title_str[13]       ="the mother superior";
    fem_title_str[12]       ="her reverance";
    fem_title_str[11]       ="the cardinal priestess";
    fem_title_str[10]       ="the spiritual mother";
    fem_title_str[9]        ="the great missionary";
    fem_title_str[8]        ="the missionary";
    fem_title_str[7]        ="the promoter of the faith";
    fem_title_str[6]        ="the high priestess";
    fem_title_str[5]        ="the priestess";
    fem_title_str[4]        ="the born again priestess";
    fem_title_str[3]        ="the evangelist";
    fem_title_str[2]        ="the preacheress";
    fem_title_str[1]        ="the sevant of God";
    fem_title_str[0]        ="the choir girl";
    return fem_title_str[lev-1];
}

int advance() { return ADVANCE_D->advance(); }

int train(string str) {
    string which, which_tmp;
    int amount;

    if(!str) {
        notify_fail("训练什么？\n");
        return 0;
    }
    if(sscanf(str, "%s %s %d", which, which_tmp, amount) == 3) which = which + " " + which_tmp;
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
    message("Nmy_action", "你感觉更加", this_player());
    message("Nother_action", this_player()->query_cap_name()+
            "看起来更加", this_object(), ({ this_player() }) );
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
        case "dexterity": return ADVANCE_D->get_stat_cost(1, lev); break;
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
    write("技能：你通过花费你想要的经验值来训练。\n");
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
        if(x <1) {
            notify_fail("没有这个任务。\n");
            return 0;
        }
        "/domains/Praxis/quest_room"->list_quests(this_player(), x);
    }
    return 1;
}

