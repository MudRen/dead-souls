#include <lib.h>
#include <daemons.h>
#include <position.h>

inherit LIB_SENTIENT;
inherit LIB_DONATE;

protected void create() {
    sentient::create();
    SetKeyName("beggar");
    SetId(({"beggar"}));
    SetAdjectives(({"dirty"}));
    SetShort("一个肮脏的乞丐");
    SetLong("这个乞丐的外表中有一种奇特的高贵气质。他看起来肯定不像一直就是个乞丐。");
    SetCanBite(0);
    SetWimpy(90);
    SetPacifist(1);
    SetInventory(([
                "/domains/town/obj/map" : 1,
                ]));
    SetLevel(1);
    SetAutoStand(0);
    SetRace("human");
    SetGender("male");
    SetConsultResponses( ([
                "map" : "这是让你知道怎么到处走的。",
                ({ "levels", "leveling", "level" }) : "我不懂那些东西。"+
                "去冒险者公会问德克吧。"
                ]) );
    SetPosition(POSITION_SITTING);
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
    SetAction(5, ({
                "!say 'Bree-yark'在地精语中是'我们投降'的意思。",
                "!say 向教堂捐款有时会给你额外奖励，但如果你超过5级就不要从慈善箱里拿了！那会扣经验值！",
                "!say 布兰迪是个好姑娘，她的秘密菜单里有镇上最纯正的香料棒。",
                "!say 我听说秘密洞穴就在森林正北方。",
                "!say 有一次我看到森林中间有东西在发光。",
                "!say 别去惹炎魔。说真的。",
                "!say 你见过兽人或矮人游泳吗？那可不好看。",
                "!say 你有没有想过那些兽人是不是有充分的理由一直这么暴躁？",
                "!say 你不必加入法师公会就能从赫克默那里学一些法术，但加入公会会有帮助。",
                "!say 如果你想成为一名战士，我听说你需要找到一个叫'星门'的东西，然后'拨号塔'。"+
                " 谁能想得出*那个*啊？",
                "!say 如果你能找人复活你的尸体，"+
                    "你就不会受到死亡惩罚。但要记住复活和复生是有区别的！",
                "!say 如果你不会僵尸的语言，你就无法控制它。",
                "!say 我听说北方堡垒有一个语言老师，收钱教学而不是消耗训练点数。",
                "!say 飞行或隐形时旅行要小心。那真的很消耗体力！",
                "!say 升级会提升你的技能，所以如果可以的话，在升级前先加入一个公会。",
                "!say 如果你达到条件后没有自动升级，去找德克让他帮你升级。",
                "!say 雅乌特亚人是一个来自另一个世界的骄傲猎人种族，拥有强大的魔法。祈祷你永远不会遇到他们。",
                "!say 喝醉了有助于更快恢复，但醉酒打架可不是好主意！",
                "!say 喝咖啡能让你清醒一些。",
                "!say 肚子里有食物和水能帮助你更快恢复。",
                "!say 如果你在房间里看不到你确信应该在那里的物品，也许你需要一个光源。"
    }));
}

//Fix courtesy of  Jonez
string GetLong(string str){
    return sentient::GetLong(str);
}

int GiveMap(object ob){
    object map;
    if(ob && present(ob->GetKeyName(),environment(this_object()))
            && !this_object()->GetInCombat() &&
            member_array(ob->GetRace(),RACES_D->GetRaces(1)) != -1 &&
            !creatorp(ob) &&
            !stringp(ob->CanManipulate()) ){
        if(ob->GetGender() == "male"){
            eventForce("say 拿着这个，兄弟。愿它对你有用。");
        }
        else if(ob->GetGender() == "female"){
            eventForce("say 拿着这个，姐妹。愿它对你有用。");
        }
        else eventForce("say 给，你可能需要这个");
        eventForce("give my first map to "+ob->GetKeyName());
    }
    if(map = present("map",this_object())) {
        map->eventDestruct(); 
        eventForce("shrug");
    }
    return 1;
}

int SayHi(object ob){
    if(this_object() && ob &&
            present(ob->GetKeyName(),environment(this_object()))
            && !this_object()->GetInCombat() &&
            member_array(ob->GetRace(),RACES_D->GetRaces(1)) != -1)
        eventForce("say 你好，"+ob->GetName());
    return 1;
}

void init(){
    ::init();

    call_out((: SayHi, this_player() :), 1);

    if(!present("town map",this_player())){
        new("/domains/town/obj/map")->eventMove(this_object());
        call_out((: GiveMap, this_player() :), 4);
    }
    //if(!present("cold virus",this_object())){
    //    new("/domains/town/obj/cold")->eventInfect(this_object());
    //}
}
