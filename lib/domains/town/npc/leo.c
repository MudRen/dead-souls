#include <lib.h>

inherit LIB_SENTIENT;

int give_it(string str);
int WieldStaff(){
    if(!present("staff",this_object())){
        new("/domains/town/weap/leostaff")->eventMove(this_object());
        tell_room(environment(),"里奥拍了拍手，一根大"+
                "木杖凭空出现。");
        this_object()->eventForce("wield staff");
        this_object()->eventForce("say 你这可怜的傻瓜！");
    }
    return 1;
}

protected void create() {
    sentient::create();
    SetKeyName("leo");
    SetId(({"archwizard","wizard"}));
    SetAdjectives(({"portly","the portly","wizard","archwizard"}));
    SetShort("肥胖的大巫师里奥");
    SetLong("里奥是一位身材魁梧、面容友善的巫师，"+
            "留着大胡子，有一个大肚子。他看起来很忙，"+
            "有些心事重重。");
    SetInventory(([
                "/domains/town/armor/wizard_hat" : "wear hat",
                "/domains/town/armor/robe" : "wear robe",
                "/domains/town/obj/pipe" : 1,
                ]));
    SetLevel(300);
    SetUnique(1);
    SetRace("human");
    SetGender("male");
    SetClass("mage");
    SetSkill("multi-hand", 9);
    SetAction(25, ({
                "里奥若有所思地挠了挠胡子。",
                "里奥似乎在努力回忆什么。", "里奥沉思着。",
                "里奥思考着。", "里奥仔细思考着。",
                "里奥说：\"我到底把屠兽者之剑放哪了？\"",
                "里奥说：\"我只希望那些讨厌的兽人没有找到它。\"",
                "里奥说：\"我只是没时间去和那些兽人战斗。\""
                }));
    SetCombatAction(100, (: WieldStaff :));
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
    SetCustomXP(10);
}

int CompleteQuest(object ob){
    string *quests;
    object sword = present("orcslayer", this_object());
    quests = ob->GetQuests();
    if(!ob->GetQuest("Orc Slayer Quest")){
        ob->AddQuest("the Orc Slayer","Orc Slayer Quest");
        eventForce("say 你已经完成了屠兽者任务。恭喜你！");
        eventForce("say 我 hereby 授予你7点任务点数和2000点经验值！");
        ob->AddQuestPoints(7);
        ob->AddExperiencePoints(2000);
        if(sword) sword->eventDestruct();
        reload("/domains/town/room/valley",0,1);
        reload("/domains/town/room/orc_fortress",0,1);
        reload("/domains/town/room/orc_temple",0,1);
    }
    return 1;
}

int eventReceiveObject(object foo) {
    int ret;
    object ob, player;
    ob = previous_object();
    player = this_player();

    if( !ob || !(ret = ::eventReceiveObject(foo)) ) return 0;
    if(base_name(ob) == "/domains/town/weap/orcslayer"){
        this_object()->DisableActions(1);
        call_out("CompleteQuest", 0, player);
        call_out("EnableActions", 300, 1);
    }
    return ret;
}

void init(){
    ::init();
}
