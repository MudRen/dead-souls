/*    /domains/Ylsrim/npc/fighter.c
 *    From the Dead Souls Mud Library
 *    An example class leader
 *    Created by Lassondra@Dead Souls
 */

#include <lib.h>
inherit LIB_TRAINER;

nosave string save_file = save_file("/domains/Ylsrim/save/roshd");
nosave string quest_object = "/domains/town/armor/orc_helmet";
string *ok_join = ({});

int JoinGuild(object ob, string verb, string what);
int TeachFeat(object who, string verb, string feat);
int AllowPass(object who, object what){
    if(who->GetClass() == "fighter") return 1;
    return ::AllowPass(who, what);
}

int CheckVisitor(object who){
    eventForce("say 只有战士才被允许进入那里！");
    return 1;
}

protected void create() {
    trainer::create();
    RestoreObject(save_file);
    if(!ok_join) ok_join = ({});
    SetKeyName("roshd burlyneck");
    SetId("roshd", "roshd burlyneck");
    SetShort("罗什德·布尔尼克，战士大师");
    SetLong("罗什德·布尔尼克是战士们的导师。他体型巨大，身高远超七英尺。"
            "长长的棕色头发飘在身后，他的二头肌大得需要好几掌才能合围。"
            "罗什德的盔甲磨损严重，沾满泥土，仿佛刚从战场上归来。"
            "罗什德为新成员传授战斗之道。"
            "如果你选择成为战士，请 \"ask roshd to join\"。"
            "\n\n尽管他忠于公会，罗什德也会训练有资质的外人战斗技能。"
            "例如：\"ask roshd to train blunt defense\"");
    SetRace("orc");
    SetClass("fighter");
    SetLevel(45);
    SetGender("male");
    SetMorality(-400);
    SetProperty("no bump", 1);
    SetGuard("north", (: CheckVisitor :));
    //SetLanguage("Common", 100);
    //SetDefaultLanguage("Common");
    SetNoSpells(1);
    AddTrainingSkills(({"multi-weapon","multi-hand","blunt attack","blunt defense","blade attack","blade defense","knife attack","knife defense"}));
    // stick him on the fighter line
    if( clonep() ) {
        AddChannel("fighter");
    }
    SetCommandResponses( ([
                "train" : (: eventTrain :),
                "teach" : (: eventTrain :),
                "default" : (: eventHelp :),
                "help" : (: eventHelp :),
                "join" : (: JoinGuild :),
                ]) );
    AddRequestResponses( ([
                "help" : (: eventHelp :),
                ]) );
}

int JoinGuild(object ob, string verb, string what){
    string keyname = ob->GetKeyName();
    string name = ob->GetName();
    if(ob->GetClass() == "fighter") {
        eventForce("say 你已经加入了，天才。");
        return 1;
    }
    eventForce("say 嗯……想加入我们的公会，是吗？");

    if(member_array(keyname, ok_join) == -1){
        eventForce("say 首先你必须证明自己的价值。把那个自封的兽人萨满偷走的骷髅头盔带给我，"
                "我就认可你有资格加入我们的大家庭。在此之前，你不能加入战士公会。");
        return 1;
    }
    if(ob->GetClass() == "explorer" || !ob->GetClass()){
        eventForce("say 很好，"+ob->GetName()+"。");
        ob->ChangeClass("fighter");
        eventForce("say 欢迎加入战士公会！你现在可以接受特殊技能训练，"
                "让你成为一名优秀而受人尊敬的肉盾！");
        eventForce("laugh");
        eventForce("say 武器训练来找我。近战技能，也就是徒手搏斗，"
                "去找北边房间的武术训练师。");
        return 1;
    }
    eventForce("say 抱歉，看起来你已经选择了你的专业。作为公会会长公会的成员，"
            "我不能将你从"+capitalize(ob->GetClass())+"公会中移除。");
    return 1;
}

int CompleteQuest2(object ob){
    string *quests;
    object hat = present_file("/domains/town/armor/orc_helmet", this_object());
    quests = ob->GetQuests();
    if(!ob->GetQuest("Orc Master Quest")){
        ob->AddQuest("the Orc Master","Orc Master Quest");
        eventForce("say 你已经完成了兽人大师任务。恭喜！");
        eventForce("say 我 hereby 授予你 7 任务点数和 2000 经验值！");
        ob->AddQuestPoints(7);
        ob->AddExperiencePoints(2000);
        if(hat) hat->eventDestruct();
        reload("/domains/town/room/valley",0,1);
        reload("/domains/town/room/orc_fortress",0,1);
        reload("/domains/town/room/orc_temple",0,1);
    }
    return 1;
}

int eventReceiveObject(object foo){
    int ret;
    object ob, player;
    ob = previous_object();
    player = this_player();

    if( !ob || !(ret = ::eventReceiveObject(foo)) ) return 0;
    if(base_name(ob) == quest_object){
        call_out("EnableJoin", 0, player, ob);
    }
    if(base_name(ob) == "/domains/cave/obj/letter" && interactive(player)){
        call_out("CompleteQuest", 0, player);
    }
    return ret;
}

mixed EnableJoin(object player, object thing){
    string uname = thing->GetUniqueId();
    string name, keyname;
    if(!player) return 0;
    keyname = player->GetKeyName();
    if(member_array(keyname, ok_join) == -1){
        name = lower_case(player->GetName());
        ok_join += ({ keyname });
        SaveObject(save_file,1);
        if(name != keyname) keyname = capitalize(name);
        if(sizeof(present_file(quest_object, this_object(), 1)) > 1){
            eventForce("say 不错。不过我现在已经够用了，所以还给你吧。");
            eventForce("give "+uname+" to "+player->GetKeyName());
        }
        else {
            eventForce("say 谢谢，"+keyname+"。这正是我想要的。");
            eventForce("wear "+uname);
        }
        if(player->GetClass() != "fighter"){
            eventForce("say 如果你愿意，现在可以请求加入战士公会了：ask roshd to join");
        }
        call_out("CompleteQuest2", 0, player);
    }
    else {
        eventForce("say 我想我们已经讨论过这个了。");
        eventForce("give "+uname+" to "+player->GetKeyName());
    }
    return 1;
}

int CompleteQuest(object ob){
    string *quests;
    object letter = present("kletter", this_object());
    quests = ob->GetQuests();
    if(!ob->GetQuest("A Soldier's Lament")){
        ob->AddQuest("the Postman","A Soldier's Lament");
        eventForce("read letter");
        eventForce("cry");
        eventForce("say 无论你是怎么得到这封信的，我都感谢你，卡萨特卡也感谢你。");
        eventForce("say 我 hereby 授予你 5 任务点数和 800 经验值。");
        ob->AddQuestPoints(5);
        ob->AddExperiencePoints(800);
        if(letter) letter->eventDestruct();
        reload("/domains/cave/room/kurogane",0,1);
    }
    return 1;
}

void init(){
    ::init();
}


