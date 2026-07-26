#include <lib.h>
#include <objects.h>
#include <post.h>
#include "/lib/include/post_office.h"

inherit LIB_ROOM;

protected void create(){
    room::create();
    SetTown("campus");
    SetClimate("indoors");
    SetAmbientLight(40);
    SetShort("校园邮件室");
    SetLong("这是一间小办公室，里面有一排排信箱和各种其他邮政用具。柜台后面的墙上有一块告示牌，概述了如何给其他用户寄信的说明。");
    SetItems( ([
                ({"box","boxes","mailboxes","mailbox"}) : "为LPC大学居民准备的一排排信箱。",
                "sign" : "墙上的一块告示牌，描述如何寄送邮件。",
                ({"wall","walls"}) : "灰色油漆的机构墙壁，就像你在邮局看到的那种。",
                "implements" : "墨水、纸张等。",
                "instructions" : "试试阅读它们。",
                "counter" : "人们写信时用来倚靠的柜台。" ]) );
    SetExits( ([ 
                ]) );
    SetProperty("no attack", 1);
}
void init(){
    ::init();
    add_action("instr","read");
}
int instr(string str){
    if(str=="instructions"||str=="sign"){
        write("要给某人寄信，请输入 mail <收件人名字>。\n"+
                "输入主题行。\n"+
                "输入你的消息内容。\n"+
                "完成后，在空白行输入一个句号（.）。\n"+
                "按 x，然后按 s 发送。完成了！\n");
        return 1;
    }
}
mixed CanMail(object who, string args) {
    if( who && !interactive(who) ) return 0;
    //Normally only people from this town should be able to
    //do mail stuff here, but this is a newbie area, and
    //it's a little too confusing to newcomers not to be able
    //to send mail from a post office.
    //if( GetTown() != who->GetTown() )
    //    return "Any mail you might have will be at your home post office.";
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
    if( !ob || (living(ob) && !interactive(ob)) ) return 0;
    else return room::CanReceive(ob);
}
int eventReleaseObject() {
    object ob;

    if(!ob) return 0;
    if( !(ob = previous_object()) ) return room::eventReleaseObject();
    if( !room::eventReleaseObject() ) return 0;
    if( (ob = present(POSTAL_ID, ob)) ) ob->eventDestruct();
    return 1;
}
