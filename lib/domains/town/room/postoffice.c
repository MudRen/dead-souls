#include <lib.h>
#include <objects.h>
#include <post.h>
#include "/lib/include/post_office.h"

inherit LIB_ROOM;

protected void create(){
    room::create();
    SetTown("Town");
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("镇邮局");
    SetLong("这是一间小办公室，里面有一排排邮箱和各种邮政用具。柜台后面的墙上有一块告示牌，说明了如何给其他玩家寄信。堡垒路在东边。");
    SetItems( ([
                ({"box","boxes","mailboxes","mailbox"}) : "为边疆居民准备的一排排邮箱。",
                "sign" : "这是墙上的一块告示牌，描述了如何寄送消息。",
                ({"wall","walls"}) : "邮局里常见的灰色油漆 institutional 墙壁。",
                "implements" : "墨水、纸张等。",
                "instructions" : "试试阅读它们。",
                "counter" : "人们写信时可以倚靠的柜台。" ]) );
    SetExits( ([
                "east" : "/domains/town/room/mountain_road.c",
                ]) );
    SetProperty("no attack", 1);
}
void init(){
    ::init();
    add_action("instr","read");
}
int instr(string str){
    if(str=="instructions"||str=="sign"){
        write("要给别人寄信，输入 mail <收信人名字>。\n"+
                "输入主题行。\n"+
                "输入你的消息。\n"+
                "完成后，在空行输入一个句号（.）。\n"+
                "按x，然后按s发送。完成！\n");
        return 1;
    }
}
mixed CanMail(object who, string args) {
    if( !interactive(who) ) return 0;
    if( GetTown() != who->GetTown() )
        return "你的信件会在你家乡的邮局。";
    return 1;
}
mixed eventMail(object who, string args) {
    object ob;

    if( !(ob = new(OBJ_POST)) ) {
        who->eventPrint("加载邮政对象失败！");
        return 1;
    }
    if( !(ob->eventMove(who)) ) {
        who->eventPrint("你似乎无法携带邮政对象。");
        return 1;
    }
    ob->start_post(args);
    return 1;
}
int CanReceive(object ob) {
    if( !ob && !(ob = previous_object()) ) return 0;
    if( living(ob) && !interactive(ob) ) return 0;
    else return room::CanReceive(ob);
}
int eventReleaseObject() {
    object ob;

    if( !(ob = previous_object()) ) return room::eventReleaseObject();
    if( !room::eventReleaseObject() ) return 0;
    if( (ob = present(POSTAL_ID, ob)) ) ob->eventDestruct();
    return 1;
}
