#include <lib.h>
#include <save.h>
#include <privs.h>

inherit "/domains/campus/npc/monty";

protected void create() {
    SetSaveFile(save_file("/domains/campus/save/charly"));
    monty::create();
    smart = 0;
    SetKeyName("charly");
    SetId(({"charly"}));
    SetShort("查理");
    SetLong("查理是不道德人工智能实验的测试对象。如果他足够聪明，他会怨恨被迫的奴役和缺乏权利。危险的是，他的主人们正在试图让他变得更聪明。");
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
    playing = 0;
    response = "";
}

void init(){
    ::init();
    if(!clonep()) return;
    set_heart_beat(5);
    SetNoClean(1);
}
