#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("治疗室");
    SetLong("这里是治疗师克莱皮乌斯的工作室。他在此为顾客进行医疗处置。角落里的一张桌子上堆满了笔记和书籍。接待和等候区在东边。");
    SetItems( ([
                "desk" : "这是克莱皮乌斯处理文书和研究的地方。",
                ({"notes","books","notes and books"}) : "这些是医生桌子上的物品。",
                "corner" : "桌子所在的位置。"
                ]) );
    SetExits( ([ 
                "east" : "/domains/town/room/healer",
                ]) );
    SetRead( ({"notes","books","notes and books"}) , "That belongs to Clepius and it's private." ); 
    SetProperty("no attack", 1);
    SetInventory(([
                "/domains/town/obj/bbucket" :1,
                "/domains/town/npc/clepius" : ({60, 1})
                ]) );
    SetProperty("busy",0);

}
int CanReceive(object ob) {
    if(playerp(ob) && !creatorp(ob) && GetProperty("busy") == 1){
        message("info","The doctor is with a patient right now. Please "+
                "wait until you are called.",ob);
        return 0;
    }
    return 1;
}
void init(){
    ::init();
}
