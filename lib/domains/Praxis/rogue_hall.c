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
    SetProperty("no attack",1);
    SetProperty("light", 1);
    SetProperty("indoors", 1);
    SetShort( "盗贼藏身处核心");
    SetLong(
            "欢迎来到盗贼藏身处！\n"
            "盗贼们来这里磨练他们邪恶的技能。\n"
            "可用的命令有 <cost>、<advance>、<list (编号)>、"
            "<train 技能 数量>、<improve 属性> 和 <roll stats>。"
            "穿过被闪烁的%^BLUE%^蓝色%^RESET%^光芒守护的楼梯向上"
            "是堡垒的入口。<help skills> 将列出所有技能的完整名称。");
    SetExits( 
            (["up" : "/domains/Praxis/rogue_join",
             "council" : "/domains/Praxis/council_hall",
             "east" : "/domains/Praxis/rogue_vote"]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board", "rogue board" }) );
    ob->set_board_id("rogue_board");
    ob->set_max_posts(25);
    ob->set_edit_ok(ROGUE_COUNCIL);
    ob->move("/domains/Praxis/rogue_hall");
    ob->SetShort( "盗贼邪恶阴谋布告板");
    ob->SetLong( "在这块腐烂的木板上，盗贼们发布悬赏、"
            "卑鄙行为和其他邪恶阴谋，供其他盗贼查看。\n");
    //    new("/realms/grumpy/rogue/obj/box.c")->move(this_object());
}

void init() {
    ::init();
    add_action("cost","cost");
    add_action("murder", "murder");
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
    switch(lev) {
        case 1:  return "the rascal";                break;
        case 2:  return "the little thug";           break;
        case 3:  return "the petty thief";           break;
        case 4:  return "the lurking swindler";      break;
        case 5:  return "the minor rogue";           break;
        case 6:  return "the creeping cutpurse";     break;
        case 7:  return "the nasty thug";            break;
        case 8:  return "the lurking criminal";      break;
        case 9:  return "the devious bandit";        break;
        case 10: return "the fearsome rogue";        break;
        case 11: return "the deceiving fiend";       break;
        case 12: return "the rich swindler";         break;
        case 13: return "the accomplished rogue";    break;
        case 14: return "the corrupt pick-pocket";   break;
        case 15: return "the cunning thief";         break;
        case 16: return "the spiteful con-artist";   break;
        case 17: return "the deceitful backstabber"; break;
        case 18: return "the perpetual thief";       break;
        case 19: return "the grand master rogue";    break;
        case 20: return "the high mortal rogue";     break;
        default: return ""; break;
    }
}

string get_female(int lev) {
    switch(lev) {
        case 8: return "the lesser murderess"; break;
        default: return get_male(lev); break;
    }
}

int advance() { return ADVANCE_D->advance(); }

int train(string str) {
    string which, which_tmp;
    int amount;

    if(sscanf(str, "%s %s %d", which, which_tmp, amount) ==3) which = which + " "+ which_tmp;
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
        case "intelligence": return ADVANCE_D->get_stat_cost(1, lev); break;
        case "dexterity": return ADVANCE_D->get_stat_cost(1, lev); break;
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

int murder() {
    if(this_player()->query_skill("murder")) return 0;
    this_player()->add_skill("murder", 3, 100);
    write("完成。\n");
    return 1;
}

