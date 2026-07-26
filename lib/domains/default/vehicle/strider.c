#include <lib.h>

inherit LIB_VEHICLE;

string ReadInstructions(){
    string ret = "要移动，使用 \"drive\" 命令，例如：drive east\n"+
        "要让机甲用它的机械臂做某事，使用以下语法：\n"+
        "direct mech to get boulder\n"+
        "direct mech to kill orc\n\n";
    if(environment(this_player()) == this_object()){
        return ret;
    }
    else return "你在这里无法阅读任何东西。";
}

protected void create() {
    vehicle::create();
    SetKeyName("strider");
    SetId(({"landstrider","walker","scout","columbu","mech"}));
    SetAdjectives(({"landstrider","walker","scout","columbu","strider","class"}));
    SetShort("一个步行者机甲");
    SetLong("这是一个 Columbu class scout vehicle consisting of a human-sized transparent ball turret mounted on two large birdlike legs with two robotic arms on each side for manipulation and combat。 Though technically a \"scout\" class mech， it is two meters tall and ballistic plated， and not to be trifled with by meat-based creatures。");
    SetVehicleInterior("这是一个 highly advanced military mechanized reconaissance vehicle 的内部。这里有一些你可以阅读的说明。");
    AddItem("instructions","关于这个机甲操作的一些文档。");
    AddItem(({"landstrider","walker","scout","columbu","mech","here"}),
            "这是一个 highly advanced military mechanized reconaissance vehicle 的内部。这里有一些你可以阅读的说明。");
    SetRead("instructions", (: ReadInstructions :));
    SetRace("strider");
    SetClass("fighter");
    SetLevel(10);
    SetMelee(1);
    SetMount(1);
    SetMountStyle("driven");
    SetVisibleRiders(0);
    SetOpacity(0);
    SetNoClean(1);
    SetPacifist(0);
    SetNoCondition(1);
}

void init(){
    ::init();
    add_action("DirectMech","direct");
}

mixed DirectMech(string str){
    string what, cmd;
    int i = sscanf(str,"%s to %s",what, cmd);
    if(i != 2) i = sscanf(str,"%s %s",what, cmd);
    if(i != 2 || !answers_to(what,this_object())) return 0;
    if(environment(this_player()) == this_object()){
        write("你将命令输入机甲。");
        call_out("eventForce", 2, cmd);
        return 1;
    }
}
