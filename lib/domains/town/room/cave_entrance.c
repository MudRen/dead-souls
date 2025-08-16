#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

int initialized = 0;
int CheckQuest(object ob);

void create() {
    room::create();
    SetAmbientLight(5);
    SetShort("黑暗洞穴");
    SetLong("这是悬崖底部的一个小洞穴。北墙上有一扇石门。墙上写着一些文字。");
    SetExits( ([
                "out" : "/domains/town/virtual/forest/-4,25",
                "south" : "/domains/town/virtual/forest/-4,25",
                "north" : "/domains/town/room/cave1.c",
                ]) );
    SetItems(([
                ({ "writing", "writing on the wall","scrawl" }) : "你可以阅读的粗糙文字", 
                ({ "wall" }) : "这个洞穴里的岩石表面.",
                ]) );
    SetRead(({ "writing", "writing on the wall" })  
            , "朋友，拨打校园实验室" );
    SetDoor("north", "/domains/town/doors/stone.c");
}

void init(){
    ::init();
    CheckQuest(this_player());
    if(!initialized){
        object door = present("stone door",this_object());
        if(!door) return;
        door->SetItems( ([
                    ({"inscription"}) : "Words in the language of the elves.",
                    ]) );
        SetInventory(([
                    "/domains/town/obj/stargate3" : 1,
                    ]));
        SetClimate("indoors");
        door->SetRead( ([
                    ({"inscription"}) : "说，朋友，然后进入。",
                    "default" : "尝试：阅读门上的铭文"
                    ]) );
        door->SetLanguage("Edhellen");
        initialized = 1;
    }
}

varargs mixed eventHearTalk(object who, object target, int cls, string verb,
        string msg, string lang) {
    int decoded = 0;
    object door = present("stone door",this_object());
    if(door) door = door->GetDoor();
    if(door && door->GetClosed() && lower_case(lang) == "edhellen"
            && who->GetLanguageLevel(lang) > 50 && 
            grepp(lower_case(msg),"friend"))
        decoded = 1;
    room::eventHearTalk(who,target,cls,verb,msg,lang);
    if(decoded){
        eventPrint("伴随着巨大的轰鸣声，石门隆隆打开！");
        door->SetClosed(0);
    }
    return 1;
}

int CheckQuest(object ob){
    string *quests;
    quests = ob->GetQuests();
    if(!ob->GetQuest("Cave Finding Quest")){
        ob->AddQuest("Cave Explorer I","Cave Finding Quest");
        write("%^BOLD%^%^RED%^\n\n恭喜！\n%^RESET%^");
        write("%^BOLD%^%^RED%^你已经解决了失落洞穴的任务。你获得了3个任务点数和2500经验点数。干得好！\n\n%^RESET%^");
        say(this_player()->GetName()+"解决了新手任务2。");
        ob->AddQuestPoints(3);
        ob->AddExperiencePoints(2500);
        return 1;
    }
    return 1;
}

