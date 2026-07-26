#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetExits( 
            (["west" : "/domains/Praxis/east_road2",
             "east" : "/domains/Praxis/cemetery/grave_yard2"]) );
    SetShort("墓地入口");
    SetLong(
            "你站在一座古老、几乎被遗忘的墓地大门之间。"
            "这里的空气非常静止，异常安静。你感到不安，回头看了看。"
            "不知为何，再也没有人来这里了。东边你可以看到一块墓碑。");
    SetItems(
            (["headstone" : "墓碑太远了，看不清上面的字。",
             "gates" : "这些门是古董。再也没有人制作这样的门了。"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
} 
