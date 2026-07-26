#include <lib.h>
#include ROOMS_H
inherit LIB_ROOM;

object *ejected_players = ({});

string ReadSign();

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(50);
    SetShort("会议室");
    SetLong("这是虚拟校区的临时会议室。房间装饰精美，配有雕刻华丽的红木镶板和金箔饰边。豪华的地毯和柔和的灯光使这间会议室成为一个非常舒适、令人放松的环境。主走廊在北边。\n%^GREEN%^这里有一块你可以阅读的告示牌。%^RESET%^");
    SetItems(([
                ({"panels","paneling","wall","walls","mahogany","wood"}) : "墙壁镶嵌着深色红木。木材上雕刻着精美的图案。这种工艺一定花费不菲。",
                ({"room","conference room","ad hoc conference room"}) : "这是一间设备齐全、舒适的会议室。",
                ({"carving","carvings","design","designs","craftmanship"}) : "雕刻大多是抽象形状，细节丰富、紧密交织，几乎在你眼前蠕动。",
                ({"leaf","gold-leaf trim","trim","gold leaf trim"}) : "墙壁踢脚线和门框上的饰边是美丽的金箔设计。",
                ({"floor","carpet","carpeting","luxurious carpeting"}) : "地毯厚实，呈深栗色。",
                ({"lighting","lights","moody lighting"}) : "这里的照明是间接和漫射的，给一切带来温暖的光芒。",
                "environment" : "确实非常舒适。",
                "sign" : "试试：read sign",
                ]));
    SetExits( (["north" : "/domains/campus/room/corridor4",
                ]));
    SetInventory((["/domains/campus/obj/podium" : 1,
                "/secure/npc/cambot" : 1
                ]));
    SetRead( ([
                "sign" :  (: ReadSign :)
                ]) );
    SetProperty("no attack", 1);
    SetProperty("meeting room", 1);
    SetNoClean(1);
}
int CanReceive(object ob) {
    if(ob && interactive(ob) && !environment(ob)){
        write("You are whisked to the main start point.");
        ob->eventMoveLiving(ROOM_START);
        return 0;
    }
    if(member_array(ob, ejected_players) != -1) {
        write("You have been ejected from the meeting room and may not return.");
        return 0;
    }
    return ::CanReceive(ob);
}

void init(){
    ::init();
}

object *AddEjected(object punk){
    if(member_array(punk, ejected_players) == -1){
        write(capitalize(punk->GetKeyName())+" has been added to the ejected list.");
        ejected_players += ({ punk });
    }
    else write(capitalize(punk->GetKeyName())+" is already on the ejected list.");
    return ejected_players;
}

object *GetEjected(){
    return ejected_players;
}

object *RemoveEjected(object punk){
    if(member_array(punk, ejected_players) != -1){
        write(capitalize(punk->GetKeyName())+" has been removed from the ejected list.");
        ejected_players -= ({ punk });
    }
    else write(capitalize(punk->GetKeyName())+" is not on the ejected list.");
    return ejected_players;
}

string ReadSign(){
    string ret = "这是一个用于有序管理会议的特殊房间。它使用特殊的讲台来管理发言，并阻止接收频道消息。在某些情况下还阻止传送进入。如果你在这里参加会议，请尽量保持礼貌，避免打扰他人。你是自愿来的，所以如果你感到无聊，请随意安静离开。这个房间的一些有用命令：\n";
    ret += "raise ：表示你希望发言。\n";
    ret += "agenda ：显示当前议程。\n\n";
    ret += "记住！频道和一些命令如 \"call\" 可能";
    ret += "在这里不起作用！";
    return ret;
}

int eventDestruct(){
    if( !(master()->valid_apply(({ "ASSIST" }))) )
        error("Illegal attempt to destroy object: "+get_stack()+" "+identify(previous_object(-1)));
    else return ::eventDestruct();
}
