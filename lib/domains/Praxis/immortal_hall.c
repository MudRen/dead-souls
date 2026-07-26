#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 1);
    SetProperty("indoors", 1);
    SetProperty("no castle", 1);
    SetShort( "不朽者大厅");
    SetLong(
            "欢迎来到不朽者大厅！\n"
            "高级凡人来这里寻找导师，引导他们进入不朽世界。"
            "凡人来这里证明他们有资格成为高级凡人。"
            "一段螺旋楼梯从地窖向上延伸。");
    SetExits( 
            (["up" : "/domains/Praxis/stairs"]) );
    SetProperty("no castle", 1);
}

void reset() {
    ::reset();
    if(!present("unity")) 
        new("/domains/Praxis/obj/mon/unity")->move(this_object());
}
void init(){
    ::init();
}
