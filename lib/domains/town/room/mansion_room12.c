#include <lib.h>
inherit LIB_ROOM;

int CheckQuest(object ob);
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("秘密地下室");
    SetLong("你在公馆下方的秘密地下室里。");
    SetExits( ([
                "up" : "/domains/town/room/mansion_room9"
                ]) );
    SetObviousExits("up");
    SetInventory( ([
                "/domains/town/obj/chest2" : 1,
                ]) );
    SetDoor("up", "/domains/town/doors/trapdoor");
}
void init(){
    ::init();
    CheckQuest(this_player());
}
int CheckQuest(object ob){
    string *quests;
    quests = ob->GetQuests();
    if(!ob->GetQuest("Newbie Mansion Chamber Quest")){
        ob->AddQuest("隐藏地下室发现者","Newbie Mansion Chamber Quest");
        write("%^BOLD%^%^RED%^\n\n祝贺你！\n%^RESET%^");
        write("%^BOLD%^%^RED%^你解决了公馆隐藏地下室的秘密任务。你获得了"
                "2点任务点数和1500点经验值。干得好！\n\n%^RESET%^");
        say(this_player()->GetName()+" 完成了新手任务1。");
        ob->AddQuestPoints(2);
        ob->AddExperiencePoints(1500);
        return 1;
    }
    return 1;
}
