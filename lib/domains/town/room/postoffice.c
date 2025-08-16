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
    SetShort("城镇邮局");
    SetLong("这是一个小办公室，里面排列着邮箱和各种其他邮政用具。柜台后面的墙上有一个标牌，概述了如何给其他用户发送邮件的说明。要塞之路在东边。");
    SetItems( ([ 
                ({"box","boxes","mailboxes","mailbox"}) : "为边境居民准备的邮箱排列。",
                "sign" : "这是墙上描述如何发送消息的标志。",
                ({"wall","walls"}) : "你会在邮局里看到的那种灰色的机构墙壁。",
                "implements" : "墨水、纸张等。",
                "instructions" : "试着阅读它们。",
                "counter" : "人们写消息时用来倚靠的柜台。" ]) );
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
        write("要给某人发送邮件，输入 mail <此人的名字>。\n"+
                "输入主题行。\n"+
                "输入你的消息。\n"+
                "完成后，在空白行输入一个句点(.)。\n"+
                "输入 x，然后输入 s 发送。你就完成了！\n");
        return 1;
    }
}
mixed CanMail(object who, string args) {
    if( !interactive(who) ) return 0;
    if( GetTown() != who->GetTown() )
        return "你可能有的任何邮件都会在你的家乡邮局。";
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
