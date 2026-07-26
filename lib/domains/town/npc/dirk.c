#include <lib.h>
#include <daemons.h>
#ifndef REQUIRE_QUESTING
#define REQUIRE_QUESTING 1
#endif

inherit LIB_SENTIENT;

int hint;

int AdvanceDude(mixed arg);
mapping advancement, Levels;
int TalkFunc(){
    string thing1, thing2, thing3, thing4, thing5;

    thing1 = "胆怯逃跑并不丢人。留得青山在，不怕没柴烧。死亡会带走宝贵的经验值。";
    thing2 = "我希望能再见到达芙妮公主。";
    thing3 = "不要醉酒打架。";
    thing4 = "向赫克默学习法术是个好主意。";
    thing5 = "食物、饮料和咖啡因有助于恢复健康和体力。";

    switch(hint){
        case 0 : eventForce("say "+thing1);break;
        case 1 : eventForce("say "+thing2);break;
        case 2 : eventForce("say "+thing3);break;
        case 3 : eventForce("say "+thing4);break;
        case 4 : eventForce("say "+thing5);break;
        default :  eventForce("smile");
    }

    if(hint == 4) hint = 0;
    else hint++;
    return 1;
}

protected void create() {
    int i;
    sentient::create();
    Levels = PLAYERS_D->GetLevelList();
    advancement = ([]);
    SetKeyName("dirk");
    SetId(({"dirk"}));
    SetShort("疲惫的德克");
    SetLong("20年来，勇敢的德克一直在试图击败邪恶的火龙辛吉，几乎没有休息。"+
            "如今他只想休息放松，于是接受了镇上冒险者公会会长的职位。"+
            "如果你觉得自己够格，就\"ask dirk to advance\"。");
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
    SetInventory(([
                "/domains/town/armor/collar" : "wear collar",
                ]));
    SetLevel(15);
    SetRace("human");
    SetGender("male");
    //SetAction(5, (: TalkFunc :));
    AddTalkResponse("hello", "嗨！向我请教提示吧！");
    AddTalkResponse("hi", "嗨！向我请教提示吧！");
    SetCommandResponses( ([ 
                "advance": (: AdvanceDude :) 
                ]) );
    SetRequestResponses( ([
                ({ "a hint", "hints", "a clue", "clues", "a tip", "tips" }) : 
                (: TalkFunc :),
                ]) );
    SetConsultResponses( ([
                ({ "level", "levels", "leveling", "advancement", "advancing" }) :
                "要升级，先去外面获取一些经验，然后回来"+
                "让我帮你晋升。某些级别你可能需要"+
                "任务点数才能升级，不仅仅是经验。",
                ({ "xp", "XP", "experience" }) : "你可以通过"+
                "杀死怪物或完成一些任务来获得经验值。"+
                "有时完成一些你甚至不知道会奖励点数的任务也能获得经验值。"+
                "不过一般来说，战斗胜利才会获得经验奖励。",
                ({ "points" }) : "这是用来追踪你进度的方式。我"+
                "关心的点数类型是经验值和任务点数。",
                ({ "quests", "quest", "quest points" }) : "任务是你可以"+
                "尝试完成的使命，完成任务通常会奖励你"+
                "任务点数。你需要任务点数才能升级到"+
                "某个级别以上。",
                ]) );
    for(i=0;i<21;i++){
        advancement[i] = Levels[i];
    }
}

void init(){
    ::init();
}

int AdvanceDude(mixed arg){
    int level,xp,qp;
    int desired_level,required_xp,required_qp;
    mixed *statlist;
    mapping this_stat;
    int statclass, statlevel, i;

    statlist = this_player()->GetStats();

    if(this_player()->GetKeyName() == "guest"){
        this_object()->eventForce("say 我不给临时玩家升级。");
        return 1;
    }

    if(!level = this_player()->GetLevel()){
        this_object()->eventForce("say 你把我搞糊涂了。");
        return 1;
    }

    if(level > 19){
        this_object()->eventForce("say 哇哦，大"+
                "家伙。超过20级的晋升是"+
                "超人类长老公会的权限。"+
                "抱歉我帮不了你。");
        return 1;
    }

    xp = this_player()->GetExperiencePoints();
    if(!qp = this_player()->GetQuestPoints()) qp = 0;
    desired_level = level+1;
    required_xp = advancement[desired_level]["xp"];
    if(!required_qp = advancement[desired_level]["qp"]) required_qp = 0;
    if(!REQUIRE_QUESTING) required_qp = 0;
    this_object()->eventForce("say 第"+desired_level+"级"+
            "，头衔为\""+advancement[desired_level]["title"]+"\""+
            "，需要"+required_xp+"点经验值和"+
            required_qp+"点任务点数。");

    if( xp > required_xp-1 && qp > required_qp-1){
        this_object()->eventForce("say 恭喜你！"+
                "你已晋升到第"+desired_level+"级，"+
                "获得了称号"+this_player()->GetName()+" "+
                advancement[desired_level]["title"]+"。");

        this_player()->ChangeLevel(desired_level);
        this_player()->AddTrainingPoints(desired_level);
        this_player()->AddTitle(advancement[desired_level]["title"]);
        this_player()->RemoveTitle(advancement[desired_level-1]["title"]);

        this_player()->save_player(this_player()->GetKeyName());

        if(level == MAX_NEWBIE_LEVEL){
            write("\n德克举起手，严厉地指向你。\n");
            say("\n德克举起手，严厉地指向"+
                    this_player()->GetName()+"。\n");
            this_object()->eventForce("say "+this_player()->GetName()+"，"+
                    "你不再是新手了。从现在起，你在黑暗中需要"+
                    "光源才能看见。从现在起，你将"+
                    "无法理解你没有学过的语言。你"+
                    "赢得了这次晋升，现在作为一名真正的冒险者面对未来。");
        }

        return 1;
    }

    else this_object()->eventForce("say 抱歉，"+
            this_player()->GetName()+"，你还没有"+
            "满足第"+desired_level+"级的所有要求。"+
            "请在满足条件后再来试试。");
    return 0;
}

string GetLevelTitle(int level){
    if(!level) level = 1;
    return advancement[level]["title"];
}

int DiamondReaction(){
    eventForce("say 达芙妮公主的钻石！天哪！");
    eventForce("say 能把它给我吗？");
    return 1;
}

varargs int eventPrint(string msg, mixed arg2, mixed arg3){
    if(grepp(msg,"fabled Princess Daphne diamond")){
        call_out( (: DiamondReaction :), 0 );
    }
    return ::eventPrint(msg, arg2, arg3);
}

int CompleteQuest(object ob){
    string *quests;
    object gem = present("diamond", this_object());
    quests = ob->GetQuests();
    if(!ob->GetQuest("Princess Diamond Quest")){
        ob->AddQuest("the Gemfinder","Princess Diamond Quest");
        eventForce("say 你已经完成了公主钻石任务。"+
                "恭喜你！");
        eventForce("say 我 hereby 授予你10点任务点数！");
        ob->AddQuestPoints(10);
        if(gem) gem->eventMove("/domains/campus/room/bookstore2");
    }
    return 1;
}

int eventReceiveObject() {
    object ob, player;
    ob = previous_object();
    player = this_player();

    if( !ob || !::eventReceiveObject() ) return 0;
    if(base_name(ob) == "/domains/campus/obj/diamond"){
        call_out("CompleteQuest", 0, player);
    }
    return 1;
}

