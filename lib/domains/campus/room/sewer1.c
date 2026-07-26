#include <lib.h>
#include <damage_types.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(10);
    SetShort("下水道");
    SetLong("你在下水道系统恶臭的地下隧道里。这里的空气相当污浊，墙壁通风口周期性地喷出蒸汽，使这里非常闷热潮湿。一英尺高的深色液体覆盖着隧道底部，沿着隧道从东向西流淌。");
    SetItems( ([ ({"tunnel","tunnels"}) : "你在下水道隧道里。这里污浊、黑暗、炎热。",
                ({"sewer","sewer system"}) : "虽然明显维护良好且是现代建筑，但这仍然是下水道隧道，对人类的舒适度很不友好。",
                ({"steam","vent","vents","wall-mounted vents"}): "显然附近有工业机械通过墙壁上的通风口排出热蒸汽。",
                "air" : "空气中弥漫着腐烂废物的恶臭。",
                ({"wall","walls"}) : "下水道隧道的墙壁由混凝土建造，看起来坚固耐用。",
                ({"stream","liquid","stream of liquid","dark liquid"}) : "不管这是什么东西，水不是它的主要成分。它是某种恶臭的液体废物，沿着隧道底部流动。",
                ({"sewage","waste","garbage"}) : "看来隧道底部的液体是垃圾和废物处理的结果。液态的垃圾从这里向西流动。",
                ]) );
    SetSmell( ([ "default" : "污水和废物的恶臭弥漫在这里。"]) );
    SetListen("default","你听到滴水的微弱回声。");
    SetExits( ([ "west" : "/domains/campus/room/sewer.c",
                "east" : "/domains/campus/room/sewer2.c"
                ]) );
    set_heart_beat(10);
}
int SteamBlast(){
    object *temparr,*stuff,*lstuff;
    int i;
    stuff=all_inventory();
    lstuff = ({});
    for(i=0;i<sizeof(stuff);i++){
        temparr= ({ stuff[i] });
        if(living(stuff[i]) && !sizeof(lstuff)) lstuff = ({stuff[i]});
        if(living(stuff[i]) && sizeof(lstuff) > 0 && member_array(stuff[i],lstuff) == -1) lstuff += ({stuff[i]});
    }
    for(i=0;i<sizeof(lstuff);i++){
        if(sizeof(lstuff) > 0 && !creatorp(lstuff[i]) ) 
            lstuff[i]->eventReceiveDamage(HEAT, 7,random(30)+10, "torso");

    }
    tell_room(this_object(), "你被一股滚烫的蒸汽击中了！");
    return 1;
}
void heart_beat(){
    if(random(10) == 1) SteamBlast();
    return;
}
void init(){
    ::init();
}
