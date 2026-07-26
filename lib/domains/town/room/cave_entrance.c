#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

int initialized = 0;
int CheckQuest(object ob);

void create() {
    room::create();
    SetAmbientLight(5);
    SetShort("黑暗洞穴");
    SetLong("这是悬崖底部的一个小洞穴。北墙上嵌着一扇石门。墙上潦草地写着一些文字。");
    SetExits( ([
                "out" : "/domains/town/virtual/forest/-4,25",
                "south" : "/domains/town/virtual/forest/-4,25",
                "north" : "/domains/town/room/cave1.c",
                ]) );
    SetItems(([
                ({ "writing", "writing on the wall","scrawl" }) : "你可以阅读的粗略涂鸦",
                ({ "wall" }) : "洞穴中粗糙的岩石表面。",
                ]) );
    SetRead(({ "writing", "writing on the wall" })  
            , "Friend, dial campus lab" );
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
                    ({"inscription"}) : "Speak, friend, and enter.",
                    "default" : "Try: read inscription on door"
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
        eventPrint("With a great roar, the stone door rumbles open!");
        door->SetClosed(0);
    }
    return 1;
}

int CheckQuest(object ob){
    string *quests;
    quests = ob->GetQuests();
    if(!ob->GetQuest("Cave Finding Quest")){
        ob->AddQuest("Cave Explorer I","Cave Finding Quest");
        write("%^BOLD%^%^RED%^\n\nCONGRATULATIONS!\n%^RESET%^");
        write("%^BOLD%^%^RED%^You have solved the quest of the "+
                "Lost Cave. You have "+
                "earned 3 quest points, and 2500 experience "+
                "points. Nice job!\n\n%^RESET%^");
        say(this_player()->GetName()+" solves newbie quest 2.");
        ob->AddQuestPoints(3);
        ob->AddExperiencePoints(2500);
        return 1;
    }
    return 1;
}

