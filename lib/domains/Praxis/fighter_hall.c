#include <lib.h>
#include <council.h>
#include <daemons.h>
#include ROOMS_H

inherit LIB_ROOM;

string get_new_title(object tp);
string get_male(int lev);
string get_female(int lev);
string previous_title(object tp);
int get_cost(string which, int lev);

int CanReceive(object ob) {
    if(!VOTING_D->is_time_to_vote())
        return ::CanReceive(ob);
    if(VOTING_D->query_voted(this_player()->query_name(),this_player()->query_class()))
        return ::CanReceive(ob);
    if(creatorp(this_player()) || this_player()->query_level() < 2)
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
    SetProperties( (["no attack": 1, "no castle":1,"light":2,"indoors":1]) );
    SetShort( "战士内殿");
    SetLong(
            "欢迎来到战士大厅内殿！\n"
            "战士们来这里学习战斗艺术。"
            "你身处一个看起来像大型训练厅的地方。地上铺着大垫子，"
            "墙上挂着各种形状和形式的武器。"
            "在这个强大的大厅里，战士可以<advance>、<cost>、"
            "<list (编号)>、<improve 属性>、<train 技能 数量> 和 <roll stats>。"
            "穿过被闪烁的%^BLUE%^蓝色%^RESET%^光芒守护的楼梯是大厅的入口。");
    SetExits( ([ 
                "council" : "/domains/Praxis/council_hall",
                "east" : "/domains/Praxis/fighter_vote",
                "down" : "/domains/Praxis/fighter_join",
                ]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board", "bulletin board", "glory board" }) );
    ob->set_board_id("fighter_board");
    ob->set_edit_ok(FIGHTER_COUNCIL);
    ob->set_max_posts(50);
    ob->move("/domains/Praxis/fighter_hall");
    ob->SetShort( "战士荣耀布告板");
    ob->SetLong(
            "我们世界的战士们在这里发布他们辉煌冒险的故事，"
            "以及关于外面危险的信息。\n");
    //new("/realms/grumpy/fighter/obj/box.c")->move(this_object());
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
    //ROOM_SETTER->do_rolls();
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
    male_title_str[19]      ="the legend";
    male_title_str[18]      ="the wise old master of combat";
    male_title_str[17]      ="the old veteran";
    male_title_str[16]      ="the battle hardened veteran";
    male_title_str[15]      ="is death incarnate";
    male_title_str[14]      ="the war-monger";
    male_title_str[13]     = "the great gladiator";
    male_title_str[12]      ="the experienced gladiator";
    male_title_str[11]      ="the gladiator";
    male_title_str[10]      ="the great champion";
    male_title_str[9]       ="the champion";
    male_title_str[8]       ="the experienced fighter";
    male_title_str[7]       ="the employed fighter";
    male_title_str[6]       ="the fighter for hire";
    male_title_str[5]       ="the rookie fighter";
    male_title_str[4]       ="the amateur fighter";
    male_title_str[3]       ="the experienced squire";
    male_title_str[2]       ="the gung-ho squire";
    male_title_str[1]       ="the timid squire";
    male_title_str[0]       ="the page";
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
    string adj;
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
    adj = (str == "strength" ? "stronger" : (str == "intelligence" ? "more intelligent" :
                (str == "wisdom" ? "wiser" : (str == "dexterity" ? "more nimble" :
                                              (str == "constitution" ? "sturdier" : "more attractive")))));
    if(str == "strength") adj = "更强壮了";
    else if(str == "intelligence") adj = "更聪明了";
    else if(str == "wisdom") adj = "更睿智了";
    else if(str == "dexterity") adj = "更敏捷了";
    else if(str == "constitution") adj = "更健壮了";
    else adj = "更有魅力了";
    message("my_action", sprintf("你看起来%s。", adj), this_player());
    message("other_action", sprintf("%s看起来%s",
                this_player()->query_cap_name(), adj), environment(this_player()),
            ({ this_player() }));
    return 1;
}

int get_cost(string stat, int lev) {
    switch(stat) {
        case "strength": return ADVANCE_D->get_stat_cost(1, lev); break;
        case "constitution": return ADVANCE_D->get_stat_cost(1, lev); break;
        case "dexterity": return ADVANCE_D->get_stat_cost(1, lev); break;
        default: return ADVANCE_D->get_stat_cost(2, lev); break;
    }
}

int cost(string str) {
    int bing;

    write("升级、训练和提升的费用：\n");
    bing = ADVANCE_D->get_exp( this_player()->query_level() + 1 );
    if(bing < 1) write("等级：\t\t升级不需要花费。");
    else write("等级：\t\t"+bing+"\n");
    write("技能：你通过花费你想要的经验值来训练。");
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
