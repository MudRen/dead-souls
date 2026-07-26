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
        write("To mail someone, type mail <person's name here>.\n"+
                "Enter a subject line.\n"+
                "Enter your message.\n"+
                "Once you've finished, enter a period (.) on a blank line.\n"+
                "Hit x, then s to send it. You're done!\n");
        return 1;
    }
}
mixed CanMail(object who, string args) {
    if( !interactive(who) ) return 0;
    if( GetTown() != who->GetTown() )
        return "Any mail you might have will be at your home post office.";
    return 1;
}
mixed eventMail(object who, string args) {
    object ob;

    if( !(ob = new(OBJ_POST)) ) {
        who->eventPrint("Failed to load postal object!");
        return 1;
    }
    if( !(ob->eventMove(who)) ) {
        who->eventPrint("You can't seem to carry the postal object.");
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
