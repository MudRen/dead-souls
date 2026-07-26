#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperties( ([
                "light":2,
                "indoors":1
                ]) );
    SetShort("审批室");
    SetLong("这是审批团队的会议室。在这个房间里，"
            "问题、建议和新的审批变更可以发布在布告板上，"
            "以便每个人都能了解最新动态。楼上是不朽者大厅。");
    SetExits( ([
                "up": __DIR__ "adv_inner"
                ]) );
}
void reset() {
    ::reset();
    //if(!present("approval board")) 
    //new( __DIR__ "obj/misc/app_board")->move(this_object());
}
void init(){
    ::init();
}
