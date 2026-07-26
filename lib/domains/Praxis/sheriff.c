/*
// File     :  /domains/Praxis/sheriff.c
// Comment  :  handles law enforcement
// 94-08-15 :  Descartes of Borg wrote original code
// 94-08-28 :  Manny of Law executed it
// 94-09-02 :  Pallando of Everywhere fixed it
 */
#include <lib.h>
#include <daemons.h>
#include <dirs.h>

inherit LIB_ROOM;

object *__Prisoners;
mapping Executions;

object *clone_guards(int num);

void create() {
    object *obs;
    int x,y, i, tot;

    Executions = ([
            "hanging" : "death_by_hanging",
            "firing squad" : "death_by_firing_squad",
            "torture" : "death_by_torture",
            "the pit" : "death_by_the_pit",
            // "stoning" : "death_by_stoning",
            // "beheading" : "death_by_beheading",
            ]);
    room::create();
    SetNoClean(1);
    SetProperties( ([ "light":2, "indoors":1, "no bump":1, "no kill":1,
                "no steal":1 ]) );
    SetShort("普拉克西斯治安官办公室");
    SetLong(
            "在这间小型单间木屋的角落里，有一个装着铁栏的区域，"
            "表明你已进入普拉克西斯治安官办公室。治安官的一张旧桌子占据着"
            "房间的东北角。通往法庭和院子的出口分别在西面和南面。"
           );
    SetItems( ([ "desk":"一张摇摇晃晃的木桌，几乎从未使用过，因为"
                "治安官似乎从来都坐不住。",
                ({ "building", "office", "room" }): "一座很久以前为无法无天的时代建造的木屋。"
                "其中一个区域有一间牢房。",
                "area": "一间牢房。",
                ({ "cell", "jail cell", "jail" }): (: "la_jail" :),
                "exits": "博克拉路和中心路。"]) );
    SetSmell("default", "你能闻到汗流浃背的亡命之徒留下的气味。");
    SetExits( ([ "south":"/"+__DIR__+"yard",
                "west":"/"+__DIR__+"court_room" ]) );
    x = POLITICS_D->query_personnel("police");
    y = POLITICS_D->query_spending("police");
    //if(!(tot = (y/x)/currency_rate("gold"))) return;
    for(i=0, obs = allocate(x); i<x; i++)
        obs[i] = new("/"+__DIR__+"obj/mon/police");
    obs->SetKeyName("deputy");
    obs->SetId( ({ "law officer", "praxis police", "police", "deputy",
                "officer" }) );
    obs->SetShort("普拉克西斯副警长");
    obs->SetLong("一位负责维护普拉克西斯治安的执法官员。"
            "如果你被这位官员追捕，输入\"surrender\"投降并入狱。");
    obs->SetRace("klingon");
    obs->SetRace("human");
    obs->SetGender(random(2) ? "male" : "female");
    obs->SetLevel(tot/1000+1);
    obs->SetSkill("melee", (tot/1000)*7);
    obs->SetSkill("attack", (tot/1000)*7);
    obs->SetSkill("defense", (tot/1000)*7);
    obs->SetSkill("stealth", (tot/1000)*5);
    obs->SetStat("constitution", (tot/1000)*3 + 15);
    obs->SetStat("dexterity", (tot/1000)*5 + 10);
    obs->SetMorality(random(500));
    obs->move(this_object());
    __Prisoners = ({});
}

void init() {
    room::init();
    add_action("cmd_quit", "quit");
}

protected int cmd_quit(string str) {
    message("system", "你不能从治安官办公室退出。",
            this_player());
    return 1;
}

void rescue_me(object victim, object outlaw) {
    object *obs;
    int x, i;

    if(!present("deputy")) return;
    x = outlaw->query_level() - victim->query_level();
    if(x < 5) x = 1;
    else x = x/5;
    i = sizeof(obs = all_inventory(this_object()));
    while(i-- && x) {
        if(obs[i]->id("deputy")) {
            obs[i]->set_target(outlaw);
            x--;
        }
    }
}

int release_objects(object ob) {
    return (member_array(ob, __Prisoners) == -1);
}

void add_prisoner(object ob) { __Prisoners += ({ ob }); }

void remove_prisoner(object ob) { __Prisoners -= ({ ob }); }

object *query_prisoners() { return __Prisoners; }

string la_jail(string arg) {
    string str;
    int i;

    if(!sizeof(__Prisoners)) return "目前没有囚犯。";
    str = "以下囚犯在牢房中：";
    i = sizeof(__Prisoners);
    while(i--) str += __Prisoners[i]->query_cap_name()+"    ";
    return str;
}

object *clone_guards(int num) {
    object *obs;
    int y, x, i, tot;

    y = POLITICS_D->query_spending("police");
    x = POLITICS_D->query_personnel("police");
    for(i=0, obs = allocate(num); i<num; i++)
        obs[i] = new("/"+__DIR__+"obj/mon/guard");
    tot = (y/x)/currency_rate("gold");
    tell_object(find_player("manny"), "tot = "+tot);
    obs->SetKeyName("guard");
    obs->SetId( ({ "guard", "city guard", "officer", "praxis guard" }) );
    obs->SetShort("普拉克西斯守卫");
    obs->SetRace("klingon");
    obs->SetRace("human");
    obs->SetGender(random(2) ? "male" : "female");
    obs->SetLevel(tot/1000+1);
    obs->SetSkill("melee", (tot/1000)*7);
    obs->SetSkill("attack", (tot/1000)*7);
    obs->SetSkill("defense", (tot/1000)*7);
    obs->SetSkill("stealth", (tot/1000)*5);
    obs->SetStat("constitution", (tot/1000)*3 + 15);
    obs->SetStat("dexterity", (tot/1000)*5 + 10);
    obs->SetMorality(random(500));
    return obs;
}

string death_by_hanging(object who) {
    if(member_array(who, __Prisoners) == -1)
        return who->query_cap_name()+"不是囚犯。";
    message("say", "%^RED%^你听到城卫兵走近门口的有节奏的脚步声。两个高大魁梧的"
            "蓝衣男子走进门来，面无表情地用粗绳把你的双手紧紧绑在一起。",
            who);
    shout("%^BOLD%^%^RED%^远处的钟声敲了三下，"
            "预示着"+who->query_cap_name()+"即将被处决。");
    call_out("hanging_part_two", 2, who);
    return "处决已经开始了。";
}

void hanging_part_two(object who) {
    message("say", "\n%^CYAN%^守卫对你低语：%^RESET%^人渣。", who);
    call_out("hanging_part_three", 3, who);
}

void hanging_part_three(object who) {
    int x, y;
    object *obs;

    message("say", "\n%^RED%^两个守卫牢牢抓住你的手臂，开始把你拖向城镇广场。", who);
    (DIR_STANDARD_DOMAIN+"/square")->SetProperty("no bump", 1);
    new("/"+__DIR__+"obj/misc/handcuffs")->move(who);
    obs = clone_guards(2);
    obs->set_target(who);
    obs->move(DIR_STANDARD_DOMAIN+"/square");
    obs[0] = new("/"+__DIR__+"obj/misc/gallows");
    obs[0]->set_hangman(who);
    obs[0]->move(DIR_STANDARD_DOMAIN+"/square");
    who->eventMoveLiving(DIR_STANDARD_DOMAIN+"/square");
    call_out("hanging_part_four", 4, who);
}

void hanging_part_four(object who) {
    message("say", "\n%^RED%^聚集的嗜血人群中传来恶意的嘲笑声，"
            "一个守卫用黑头罩蒙住了你的头。你脑海中烙印着你此生"
            "将看到的最后一幅画面，一幅充满仇恨和厌恶面孔的画面。"
            "你被对自己罪行的真诚悔恨所淹没，但意识到为时已晚，"
            "这种燃烧的情感被扑灭了。", who);
    message("say", who->query_cap_name()+"被拖上楼梯来到"
            "木制平台上。人群中充满威胁的嘲笑声，"
            "一个较为魁梧的守卫将一个大黑头罩罩在"
            +who->query_cap_name()+"惊恐的脸上。"
            "对"+who->query_possessive()+"灵魂的任何怜悯"
            "很快被对这样一个卑劣之人的仇恨和厌恶所取代。",
            environment(who), who);
    call_out("hanging_part_five", 3, who);
}

void hanging_part_five(object who) {
    message("say", "\n%^RED%^有人紧紧抓住你颤抖的前臂，"
            "引你走上一小段楼梯来到木制平台上。一根沉重的绳索套在你的脖子上，"
            "然后收紧。附近鼓声的有节奏的敲击是你意识中唯一的声音，"
            "因为你不敢去想另一边等待你的是什么……", who);
    message("say", "\n死亡之鼓的有节奏的敲击让周围的人群安静下来。", environment(who), who);
    call_out("hanging_part_six", 4, who);
}

void hanging_part_six(object who) {
    message("say", "\n%^RED%^鼓声变成了一阵连续的滚奏……", who);
    message("say", "\n鼓声变成了一阵连续的滚奏……", environment(who), who);
    call_out("hanging_part_seven", random(3) + 2, who);
}

void hanging_part_seven(object who) {
    object here;

    here = environment(who);
    message("say", "\n%^RED%^脚下地板落下的沉闷声是你耳朵听到的最后一个声音。", who);
    message("say", "\n突然毫无预警地，"+who->query_cap_name()+
            "脚下的地板塌陷了，只留下"+who->query_cap_name()+
            "被系在"+who->query_possessive()+"脖子上的绳索吊着。"+
            who->query_cap_name()+"挣扎了一会儿，然后瘫软下来。", environment(who), who);
    present("handcuffs", who)->destruct();
    who->die();
    call_out("hanging_part_eight", 3, here);
}

void hanging_part_eight(object where) {
    object stuff;
    message("say", "守卫们散去，拆除绞刑架并清理场地后离开。", where);
    if(stuff = present("guard", where)) stuff->destruct();
    if(stuff = present("guard", where)) stuff->destruct();
    if(stuff = present("gallows", where)) stuff->destruct();
    where->SetProperty("no bump", 0);
}

string death_by_firing_squad(object who) {
    object *obs;
    if(member_array(who, __Prisoners) == -1)
        return who->query_cap_name()+"不是囚犯。";
    message("say", "%^RED%^一个高大魁梧的守卫走了进来，身边跟着"
            "一个穿着黑袍的牧师，嘴里念叨着一本小书里的经文。", who);
    obs=clone_guards(2);
    obs[1]->SetKeyName("priest");
    obs[1]->SetShort("牧师");
    obs->move(environment(who));
    shout("%^RED%^远处的钟声响起，预示着"+who->query_cap_name()+
            "将在城镇广场被处决。");
    call_out("squad_part_two", 2, who);
    return "处决已经开始了。";
}

void squad_part_two(object who) {
    object pole, *obs;
    int x;

    message("say", "\n%^RED%^%^BOLD%^守卫告诉你：%^RESET%^你的时间到了。", who);
    message("say", "\n%^RED%^打开牢房后，一个守卫用粗绳把你的双手绑在背后。"
            "然后一个守卫紧紧抓住你的手臂，把你拖出建筑物，朝城镇广场走去。", who);
    new("/"+__DIR__+"obj/misc/handcuffs")->move(who);
    message("say", "一个普拉克西斯守卫扛着一根大型血迹斑斑的柱子走了进来。"
            "走到广场的另一边，他挖了一个小洞并牢牢地把柱子固定在地上。", DIR_STANDARD_DOMAIN+"/square");
    (DIR_STANDARD_DOMAIN+"/square")->SetProperty("no bump", 1);
    clone_guards(1)->move(DIR_STANDARD_DOMAIN+"/square");
    pole=new(LIB_ITEM);
    pole->SetKeyName("pole");
    pole->SetId( ({ "pole", "bloodstained pole", "large pole" }) );
    pole->SetShort("一根大型血迹斑斑的柱子");
    pole->SetLong("一根牢牢固定在地上的大柱子。柱子上半部分各处散布着血迹。");
    pole->SetPreventGet("这根柱子牢牢固定在地上。");
    pole->move(DIR_STANDARD_DOMAIN+"/square");
    message("say", "一小队守卫走了进来，在柱子对面排成一列。", DIR_STANDARD_DOMAIN+"/square");
    clone_guards(5)->move(DIR_STANDARD_DOMAIN+"/square");
    call_out("squad_part_three", 5, who);
}

void squad_part_three(object who) {
    object thing;
    if(thing=present("guard", environment(who)))
        thing->move(DIR_STANDARD_DOMAIN+"/square");
    else clone_guards(1)->move(DIR_STANDARD_DOMAIN+"/square");
    if(thing=present("priest", environment(who)))
        thing->move(DIR_STANDARD_DOMAIN+"/square");
    else clone_guards(1)->move(DIR_STANDARD_DOMAIN+"/square");
    who->eventMoveLiving(DIR_STANDARD_DOMAIN+"/square");
    message("say", "\n%^RED%^在曾经熟悉的城镇广场上，一大片区域已被清理出来，"
            "广场远端的墙边立着一根柱子。这根柱子就是你和面无表情的守卫前进的方向。", who);
    message("say", "\n%^RED%^守卫把你的双手牢牢地绑在粗糙的血迹斑斑的柱子后面，"
            "面对着一列城镇守卫，每人手持一把大弓，搭着一支箭。", who);
    message("say", "\n%^RED%^守卫拿出一个大黑头罩罩在你头上，然后退开了。", who);
    new("/"+__DIR__+"obj/misc/hood")->move(who);
    message("say", who->query_cap_name()+"被拖向广场远端的一根柱子，"
            "被一个守卫绑在上面。守卫把一个大黑头罩罩在罪犯头上，然后退开了。", environment(who), who);
    message("say", "\n附近的一面鼓开始有节奏地敲击。",
            environment(who));
    call_out("squad_part_four", 4, who);
}

void squad_part_four(object who) {
    message("say", "\n%^RED%^鼓声变成了一阵连续的滚奏，"
            "你听到一个守卫喊了一个听不清的词。你听到武器上膛的声音。", who);
    message("say", "\n领头的守卫喊了一个听不清的词，"
            "一列守卫准备好了武器。", environment(who),
            who);
    call_out("squad_part_five", 4, who);
}

void squad_part_five(object who) {
    message("say", "\n%^RED%^一个守卫喊出第二个词，行刑队准备发射箭矢。", who);
    message("say", "\n领头的守卫喊出第二个词，"
            "一列守卫拉弓搭箭准备发射。", environment(who),
            who);
    call_out("squad_part_six", 4, who);
}

void squad_part_six(object who) {
    int x, dam;

    message("say", "\n%^RED%^守卫喊出第三个也是最后一个词，"
            "数十支箭矢穿透了你的整个身体。包围你的黑暗变得更加浓重，"
            "模糊的声音开始在你脑海中邪恶地咯咯笑……", who);
    message("say", "\n守卫喊出第三个也是最后一个词，"
            "整个行刑队将箭矢射入"+who->query_cap_name()+
            "无助的身体。尸体瞬间瘫软下来。",
            environment(who), who);
    dam= (who->query_max_hp())/5;
    present("hood", who)->destruct();
    present("handcuffs", who)->destruct();
    for(x=0; x<6; ++x) 
        who->do_damage("torso", dam + 10);
    call_out("squad_part_seven", 4, environment(who));
    who->die();
}

void squad_part_seven(object place) {
    object thing;
    message("say", "守卫们开始列队离开，其中一个在离开时拔走了柱子。"
            "他把尸体留在地上任其腐烂，这正是它应得的下场。",
            DIR_STANDARD_DOMAIN+"/square");
    place->SetProperty("no bump", 0);
    while(thing = present("guard", place)) 
        thing->destruct();
    if(thing=present("pole", place)) thing->destruct();
}

string death_by_torture(object who) {
    if(member_array(who, __Prisoners) == -1)
        return who->query_cap_name()+"不是囚犯。";
    message("say", "%^RED%^一个高大的守卫走进你的牢房，"
            "用一根大绳子绑住你的双手。他一言不发地把你拖出了房间。", who);
    new("/"+__DIR__+"obj/misc/handcuffs")->move(who);
    call_out("torture_part_two", 3, who);
    return "处决已经开始了。";
}

void torture_part_two(object who) {
    who->eventMoveLiving("/"+__DIR__+"torture_room");
    message("say", "%^RED%^守卫把你带进了一个你只在传闻中听过的房间。"
            "一想到要以如此残忍的方式告别生命，你的心就沉了下去。", who);
    message("say", "\n%^RED%^守卫强迫你躺在房间中央的一张小桌子上。"
            "沉重的束缚带被固定在你的双腿、手臂和额头上，让你无法动弹。"
            "当你抬头看时，你终于看到了将夺走你生命的东西：一根长杆末端"
            "的一把巨大而锋利的刀片。", who);
    call_out("torture_part_three", 4, who);
}

void torture_part_three(object who) {
    message("say", "\n%^RED%^%^BOLD%^守卫告诉你：%^RESET%^现在老实待着，"
            "几个小时后一切就结束了。", who);
    message("say", "\n守卫邪恶地咧嘴一笑。", who);
    message("say", "\n%^RED%^守卫伸手抓住刀片，像钟摆一样摆动它。", who);
    call_out("torture_part_four", 4, who);
}

void torture_part_four(object who) {
    message("say", "\n守卫沉思了片刻。", who);
    call_out("torture_part_five", 4, who);
}

void torture_part_five(object who) {
    message("say", "\n%^RED%^%^BOLD%^守卫告诉你：%^RESET%^你知道吗，"
            "我尊重你这种人。没多少人有胆量做你做的事。", who);
    message("say", "\n%^RED%^%^BOLD%^守卫告诉你：%^RESET%^我会对你仁慈一点，"
            "让你走得快一些。", who);
    message("say", "\n%^RED%^守卫抓住刀片钟摆上方的杆子往下拉，"
            "让刀片更靠近你的脖子。他用力推了一下，刀片又开始了"
            "稳定的摆动。", who);
    call_out("torture_part_six", 3, who);
}
void torture_part_six(object who) {
    message("say", "\n%^RED%^经过一番仔细检查后，守卫露出了满意的冷笑。", who);
    message("say", "\n%^BOLD%^%^RED%^守卫告诉你：%^RESET%^祝你来世愉快。", who);
    message("say", "\n%^RED%^守卫邪恶地咧嘴一笑，大步走出房间，锁上了身后的门。", who);
    call_out("torture_part_seven", 6, ({ who, 1 }) );
}

void torture_part_seven(mixed *stuff) {
    object who;
    who = stuff[0];
    switch(random(7)) {
        case 0:
        case 1:
        case 2: tell_object(who, "\n%^RED%^你注意到摆动的刀片似乎越来越近了"); break;
        case 3: tell_object(who, "\n%^RED%^你有一种非常强烈的想上厕所的冲动。"); break;
        case 4: tell_object(who, "\n%^RED%^你的身体一阵颤抖。");
                break;
        case 5: tell_object(who, "\n%^RED%^一只小老鼠快速跑过地面");
        case 6: tell_object(who, "\n%^RED%^仔细一看，在你脖子上方摆动的刀片看起来异常干净。"
                        "你不禁想知道你是否是这台可怕装置夺走的第一条生命。");
    }
    if(++stuff[1] == 10) 
        call_out("torture_part_eight", 5, who);
    else call_out("torture_part_seven", 6, stuff);
}

void torture_part_eight(object who) {
    message("say", "\n%^RED%^刀片危险地靠近你的脖子摆动。"
            "据你估计，你只剩下最后一口气了……",
            who);
    call_out("torture_part_nine", 3, who);
}

void torture_part_nine(object who) {
    message("say", "\n%^RED%^在最后一击中，巨大的金属刀片"
            "在你的喉咙上切出一道干净的伤口。你挣扎着想要呼吸更多空气，"
            "却只是让你的嘴巴和肺里充满了你的鲜血。", who);
    message("say", "\n%^BOLD%^%^BLACK%^永恒的黑暗终于覆盖了你的双眼。"
            "远处，邪恶的声音为它们最新的受害者而欢快地咯咯笑着……", who);
    present("handcuffs", who)->destruct();
    who->die();
}

string death_by_the_pit(object who) {
    if(member_array(who, __Prisoners) == -1)
        return who->query_cap_name()+"不是囚犯。";
    message("say", "%^RED%^一个高大魁梧的守卫走进牢房，"
            "用一根绳子牢牢地绑住你的双手。", who);
    message("say", "\n%^RED%^%^BOLD%^守卫告诉你：%^RESET%^你这可怜虫要去"
            "蜘蛛坑了。嘿嘿嘿。", who);
    message("say", "\n%^RED%^守卫把你拖出建筑物，朝可怕的蜘蛛坑走去……", who);
    shout("%^RED%^远处的钟声预示着"+who->query_cap_name()+
            "即将死在可怕的蜘蛛坑中。");
    new("/"+__DIR__+"obj/misc/handcuffs")->move(who);
    call_out("pit_part_two", 5, who);
    return "The execution has begun.";
}


void pit_part_two(object who) {
    string orig_long;

    message("say", "两个守卫走进来清理出一块区域，"
            "露出一块巨大的石盖。守卫们抬起沉重的石板，"
            "在广场的东北侧打开了一个深邃的黑洞。", DIR_STANDARD_DOMAIN+"/square");
    (DIR_STANDARD_DOMAIN+"/square")->SetProperty("no bump", 1);
    orig_long = (DIR_STANDARD_DOMAIN+"/square")->GetLong();
    (DIR_STANDARD_DOMAIN+"/square")->AddExit("down",
            DIR_STANDARD_DOMAIN+"/spider_pit", (: "prevent_down" :) );
    (DIR_STANDARD_DOMAIN+"/square")->SetLong(
            orig_long+"\n\n广场中央露出了一个又大又深的坑。");
    clone_guards(2)->move(DIR_STANDARD_DOMAIN+"/square");
    call_out("pit_part_three", 3, ({ who, orig_long }));
}

void pit_part_three(mixed *stuff) {
    stuff[0]->eventMoveLiving(DIR_STANDARD_DOMAIN+"/square");
    message("say", "\n%^RED%^来到再熟悉不过的城镇广场，"
            "两个守卫已经移开了坑上的盖子。在深邃的黑洞中，"
            "阴森的地面似乎在蠕动……", stuff[0]);
    message("say", "\n"+stuff[0]->query_cap_name()+"被城镇守卫拖了进来。", environment(stuff[0]), stuff[0]);
    call_out("pit_part_four", 4, stuff);
}

void pit_part_four(mixed *stuff) {
    object here;

    message("say", "\n%^RED%^%^BOLD%^守卫告诉你：%^RESET%^替我向跳跃者问好！", stuff[0]);
    message("say", "\n%^RED%^守卫邪恶地咯咯笑着把你推进了坑里。", stuff[0]);
    message("say", "\n守卫邪恶地咯咯笑着把"+stuff[0]->query_cap_name()+
            "推进了坑里", environment(stuff[0]),
            stuff[0]);
    here=environment(stuff[0]);
    stuff[0]->eventMoveLiving("/"+__DIR__+"spider_pit",
            "falls screaming into the pit!!");
    (DIR_STANDARD_DOMAIN+"/square")->SetProperty("no bump", 0);
    message("say", "\n守卫把防护盖拉回洞口上。"
            "你意识到罪犯安详死去的可能性为零，因为洞内传来了沉闷的痛苦尖叫声。",
            DIR_STANDARD_DOMAIN+"/square");
    call_out("pit_part_five", 10, ({ here, stuff[1] }));
}

void pit_part_five(mixed *stuff) {
    object thing;

    message("say", "守卫们满意地认为这个世界变得更美好了，"
            "把蜘蛛坑的盖子盖好后走开了。", stuff[0]);
    stuff[0]->RemoveExit("down");
    stuff[0]->SetLong(stuff[1]);
    if(thing = present("guard", stuff[0])) thing->destruct();
    if(thing = present("guard", stuff[0])) thing->destruct();
}

int prevent_down() {
    message("say", "一个守卫挡住了你的去路，让你明白"
            "你真的不想下去那里。", this_player());
    return 0;
}

string death_by_stoning(object who) {
    if(member_array(who, __Prisoners) == -1) 
        return who->query_cap_name()+" is not a prisoner.";
    message("say", "%^RED%^A guard enters and ties your hands together "
            "with a thick rope.", who);
    message("say", "\n%^BOLD%^%^RED%^A guard tells you:%^RESET%^ Right "
            "this way, you scumbag.", who);
    message("say", "\n%^RED%^The guard grabs you by the arm and drags you "
            "towards the town square.", who);
    // shout("%^RED%^Distant bells sound, signaling the execution "
    // "of "+who->query_cap_name()+" by stoning in the town square.");
    call_out("stoning_part_two", 5, who);
}

void stoning_part_two(object who) {
    object *townsfolk, *homes;
    string *wanted;
    int x, y;

    wanted = ({ "horace", "lars", "beggar", "knight", "waitress" });
    townsfolk=({ });
    homes = ({ });
    for(x=0, y=0; y<sizeof(wanted); y++)
        if(find_living(wanted[y])) {
            homes[x]=environment(townsfolk[x]);
            message("say", townsfolk[x]->query_cap_name()+" cheers in excitment "
                    "for the upcomming execution!", environment(townsfolk[x]));
            x++;
        }
    townsfolk->eventMoveLiving(DIR_STANDARD_DOMAIN+"/square", "to join in the "
            "stoning of "+who->query_cap_name());
    call_out("control_townsfolk", 1, ({ who, townsfolk, homes }));
    (DIR_STANDARD_DOMAIN+"/square")->SetProperty("no bump", 1);
    new("/"+__DIR__+"obj/misc/stones")->move(DIR_STANDARD_DOMAIN+"/square");
    who->eventMoveLiving(DIR_STANDARD_DOMAIN+"/square");
    message("say", "\n%^RED%^Upon arrival to the town square, the guard "
            "ties you to a wooden post, facing the jeering crowd.   With a "
            "grim smirk upon his face, he wishes you a good afterlife and "
            "leaves you to die at the hands of the countless victims of "
            "your crimes.", who);
    message("say", "Upon arrival to the town square, the guard ties "+
            who->query_cap_name()+" to the post, smirks, and leaves.  "
            "Immedately the towns people pick up their rocks and expend "
            "thier frustration upon the criminal who caused them so much "
            "grief.", environment(who), who);
}

void control_townsfolk(mixed *them) {
    int x;

    for(x=0; x<sizeof(them[1]); x++)
        switch(random(5)) {
            case 0 : message("saY", them[1][x]->query_cap_name()+" cheers "
                             "enthustically!", environment(them[1][x])); break;
            case 1 : message("say", them[1][x]->query_cap_name()+"yells: "
                             "Scumbag!!", environment(them[1][x])); break;
            case 2 : message("say", them[1][x]->query_cap_name()+" spits on " +
                             them[0]->query_cap_name()+"!", environment(them[1][x]));
                     break;
            case 3 : message("say", them[1][x]->query_cap_name()+"boos "
                             "and hisses.", environment(them[1][x])); break;
            case 4 : them[1][x]->command("get stone");
                     them[1][x]->command("throw stone at "+them[0]->query_name());
                     break;
        }
    if(them[0]->query_ghost()) {
        them[1]->command("cheer");
        call_out("stoning_part_three", 3, ({ them[1], them[2] }) );
    } else call_out("control_townsfolk", 1, them);
}

void stoning_part_three(mixed *townsfolk) {
    int x;
    message("say", "The townsfolk head back to their respective "
            "homes.", environment(townsfolk[0][0]));
    present("stone pile", environment(townsfolk[0][0]))->destruct();
    for(x=0; x < sizeof(townsfolk[0]); x++)
        townsfolk[0][x]->eventMoveLiving(townsfolk[1][x]);
}

string death_by_beheading(object who) {
    if(member_array(who, __Prisoners) == -1) 
        return who->query_cap_name()+" is not a prisoner.";
    message("say", "%^RED%^A large, burly guard enters your cell and securly "
            "ties your hands with a thick rope.  He grabs your arm and pulls "
            "you towards the exit of the prison, in the direction of the town "
            "square.", who);
    shout("%^RED%^Distant bells ring thrice, signaling the "
            "public beheading of "+who->query_cap_name()+" at the town "
            "square");
    new("/"+__DIR__+"obj/misc/handcuffs")->move(who);
    call_out("beheading_part_two", 2, who);
    return "The execution has begun";
}

void beheading_part_two(object who) {
    (DIR_STANDARD_DOMAIN+"/square")->SetProperty("no bump", 1);
    clone_guards(4)->move(DIR_STANDARD_DOMAIN+"/square");
    message("say", "A group of guards enter, bringing with them a large "
            "platform with a thick round wooden stump covered with dried "
            "blood.", DIR_STANDARD_DOMAIN+"/square");
    who->eventMoveLiving(DIR_STANDARD_DOMAIN+"/square");
    message("say", "\n%^RED%^Upon arrival to the town square, you notice "
            "a large platform with a blood-stained wooden stump.  Standing "
            "atop the platform is a black-hooded man with a large axe.  It "
            "is upon this platform, next to the hooded man, where you are "
            "lead by the guard and commanded to kneal.", who);
    call_out("beheading_part_three", 3, who);
}

void beheading_part_three(object who) {
    message("say", "\n%^RED%^From atop the platform you see the gathering "
            "crowd, very unfriendly.  A rope is placed around your neck, and "
            "you are forced to place your head over the stump, you neck "
            "fearfully exposed to the man in the black hood.  A nearby drum "
            "begins it's steady death beat...", who);
    message("say", "\nA guard places a rope around "+who->query_cap_name()+
            "'s neck and is forced to lie over the stump.  There is a desparate "
            "look on "+who->query_cap_name()+"'s face as a nearby drum begins "
            "a steady beat...", environment(who), who);
    call_out("beheading_part_four", 3, who);
}

void beheading_part_four(object who) {
    message("say", "\n%^RED%^Without warning, the drum beat comes to a "
            "sudden stop.", who);
    message("say", "\nThe drum beat comes to a sudden end, and the black "
            "hooded brings his axe down through "+who->query_cap_name()+"'s "
            "neck without hesitation.  "+who->query_cap_name()+"'s head drops "
            "to the platform with a loud thunk, the expression of desparation "
            "permanently affixed to "+who->query_possessive()+" face.", 
            environment(who), who);
    (DIR_STANDARD_DOMAIN+"/square")->SetProperty("no bump", 0);
    who->die();
}


varargs mapping valid_execution( string type )
{
    if( type ) return Executions[type];
    return Executions;
}

string execute( object who, string type )
{
    return call_other( this_object(), Executions[type], who );
}
