#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("治疗室");
    SetLong("这是治疗师克勒庇乌斯的工作室。"
            "这里就是他为顾客进行医疗程序的地方。"
            "角落里的书桌上堆满了笔记和书籍。"
            "接待和等候区在东边。");
    SetItems( ([
                "desk" : "这是克勒庇乌斯处理文书工作和研究的地方。",
                ({"notes","books","notes and books"}) : "这些是医生书桌上的内容。",
                "corner" : "书桌所在的位置。"
                ]) );
    SetExits( ([ 
                "east" : "/domains/town/room/healer",
                ]) );
    SetRead( ({"notes","books","notes and books"}) , "这是克勒庇乌斯的私人物品，请勿翻阅。" ); 
    SetProperty("no attack", 1);
    SetInventory(([
                "/domains/town/obj/bbucket" :1,
                "/domains/town/npc/clepius" : ({60, 1})
                ]) );
    SetProperty("busy",0);

}
int CanReceive(object ob) {
    if(playerp(ob) && !creatorp(ob) && GetProperty("busy") == 1){
        message("info","医生正在给病人看病。请"+
                "等待叫号。",ob);
        return 0;
    }
    return 1;
}
void init(){
    ::init();
}
