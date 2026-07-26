#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;
int ds;

string LongDesc(){
    string desc = "不朽者们来这里相互交流他们正在建造的世界。默认起始房间在北边。拱门房间在南边。"+
        (!(ds) ? "要访问Dead Souls测试和开发MUD，请前往楼上附属区。" : "")+
        "测试实验室设施在东边。";
    desc += "\n一个指示牌上写着："+load_object(ROOM_ARCH)->SignRead();
    return desc;
}

protected void create() {
    object ob;
    room::create();
    if(mud_name() == "Dead Souls"){
        ds = 1;
    }
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("创造者大厅");
    SetLong( LongDesc() );
    SetProperty("no attack", 1);
    SetProperty("nopeer",1);
    ob = new("/lib/bboard");
    ob->SetKeyName("chalkboard");
    ob->SetId( ({ "board", "chalkboard", "dusty board", "dusty chalkboard" }) );
    ob->set_board_id("immortal_board");
    ob->set_max_posts(30);
    ob->SetShort("一个布满灰尘的黑板");
    ob->eventMove(this_object());
    SetInventory(([
                "/domains/default/npc/tree" : ({ 10, 1 }),
                "/domains/default/obj/chest" : 1 ]));
    SetItems( ([
                ({"sign"}) : "一个你可以阅读的指示牌。",
                ]) );
    SetExits( ([
                "south" : "/secure/room/arch",
                "north" : "/domains/default/room/start",
                "east" : "/domains/default/room/wiz_corr1",
                "up" : "/domains/default/room/wiz_hall2.c",
                ]) );
    SetRead("sign", (: load_object(ROOM_ARCH)->SignRead() :) );
}

int CanReceive(object sneak) {
    object *living_stack = get_livings(sneak);
    if(!living_stack || !arrayp(living_stack)) living_stack = ({ sneak });
    foreach(object ob in living_stack){
        if(living(ob) && !creatorp(ob) &&
                base_name(ob) != "/domains/default/npc/tree" &&
                base_name(ob) != "/secure/npc/arch_wraith" &&
                base_name(ob) != "/domains/default/npc/drone3" &&
                base_name(ob) != "/secure/obj/floodmapper" &&
                !member_group(ob,"TEST")) {
            message("info","仅限创造者工作人员使用，抱歉。", ob);
            return 0;
        }
    }
    return ::CanReceive(sneak);
}

int eventReceiveObject(object ob){
    string race = ob->GetRace();
    int ret = ::eventReceiveObject(ob);
    if(!ret) return 0;
    if(race && race == "orc"){
        ob->eventPrint("欢迎来到我们包容的大厅，骄傲的兽人！");
    }
    if(ob->GetInvis()){
        tell_room(this_object(), capitalize(ob->GetKeyName())+
                " enters invisibly.", ({ ob }) );
        ob->eventPrint("%^BOLD%^%^RED%^你的隐形进入已被通报。%^RESET%^");
    }
    return ret;
}

int eventReleaseObject(object ob){
    int ret = ::eventReleaseObject(ob);
    if(!ret) return 0;
    if(ob->GetInvis()){
        tell_room(this_object(), capitalize(ob->GetKeyName())+
                " exits invisibly.", ({ ob }) );
        ob->eventPrint("%^BOLD%^%^RED%^你的隐形离开已被通报。%^RESET%^");
    }
    return ret;
}

void init(){
    ::init();
}
