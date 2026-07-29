#include <lib.h>
#include <daemons.h>
#include <message_class.h>

#ifndef DISABLE_IMC2
#define DISABLE_IMC2 0
#endif

inherit LIB_ROOM;

int imud_enabled = 0;
string gname;
string *ulist = ({});
mapping umap = ([]);

void validate(){
    if(!this_player() || !archp(this_player())){
        error("No.");
    }
}

int ReceiveObs(object ob){
    string bname = base_name(ob);
    umap[bname] = (umap[bname] + 1);
    return 0;
}

string ReadScreen(){
    string ret = "Top loaded objects:\n";
    int hbs, hbs2, rooms, npcs, meminf;
    mixed *foo = ({});
    object *floods = ({});
    validate();
    floods = objects( (: (base_name($1) == LIB_FLOW || inherits(LIB_FLOW, $1))
                && clonep($1) :) );
    ulist = ({});
    umap = ([]);
    if(sizeof(objects()) < 8192){
        foo = objects( (: ReceiveObs($1) :) );
        ulist = ({});
        foreach(mixed key, mixed val in umap){
            reset_eval_cost();
            ulist += ({ ({ val, key }) });
        }
        ulist = sort_array(ulist, -1)[0..9];
        if(sizeof(ulist)){
            foreach(mixed element in ulist){
                ret += element[1]+" "+element[0]+"\n";
            }
        }
    }
    else {
        ret += "Too many objects to sort.\n";
    }
    rooms = sizeof(objects( (: inherits(LIB_ROOM, $1) :) ) );
    npcs = sizeof(objects( (: inherits(LIB_NPC, $1) && clonep($1):) ) );
    hbs = sizeof(filter( heart_beats(), (: !living($1) :) ));
    hbs2 = sizeof(filter( heart_beats(), (: !living($1) &&
                    !inherits(LIB_ROOM, $1) :) ));
    ret += "\nTotal number of loaded objects: "+sizeof(objects())+"\n";
    ret += "Loaded rooms: "+rooms+"\n";
    ret += "Cloned NPC's: "+npcs+"\n\n";
    ret += "Total number of connected users: "+sizeof(users())+"\n";
    ret += "Pending callouts: "+sizeof(call_out_info())+"\n";
    ret += "File descriptors in use: "+
        (sizeof(explode(dump_file_descriptors(),"\n"))-3)+"\n";
    ret += "Nonlivings with heartbeats: "+hbs+", !rooms: "+hbs2+"\n";
    ret += "Flood objects: "+sizeof(floods)+"\n";
    if(true()){
        string tmp;
        meminf = memory_info()/1000000;
        if(!meminf) tmp = "less than 1 meg";
        else tmp = meminf+" megs";
        if(meminf){
            ret += "Memory in use (allocated memory will be higher): "+
                tmp+"\n";
        }
    }
    return ret;
}

string eventReadScreen(){
    validate();
    return unguarded( (: ReadScreen :) );
}

mixed eventReadPrintout(){
    return read_file("/doc/old/the_beginning.txt");
}

void SetImud(int i){
    if(!i) i = 0;
    imud_enabled = i;
}

int GetImud(){
    return imud_enabled;
}

string SignRead(){
    string ret = "";

    if(!INTERMUD_D->GetEnabled()){
        ret += "\"I3 connection: %^B_BLACK%^%^BOLD%^WHITE%^DISABLED%^RESET%^, ";
    }
    else if(INTERMUD_D->GetConnectedStatus())
        ret += "\"I3 connection: %^BOLD%^GREEN%^ONLINE%^RESET%^, ";
    else ret +=  "\"I3 connection: %^BOLD%^RED%^OFFLINE%^RESET%^, ";

    switch (IMC2_D->getonline()) {
        case 1:
            ret += "IMC2: %^BOLD%^GREEN%^ONLINE%^RESET%^\"";
            break;
        case 2:
            if(!IMC2_D->GetEnabled()){
                ret += "IMC2: %^B_BLACK%^%^BOLD%^WHITE%^DISABLED%^RESET%^\"";
            }
            else {
                ret += "IMC2: %^BOLD%^YELLOW%^WAITING FOR ACCEPTANCE%^RESET%^\"";
            }
            break;
        case 3:
            ret += "IMC2: %^BOLD%^RED%^OFFLINE: CONNECT ERROR%^RESET%^\"";
            break;
        case 4:
            ret += "IMC2: %^BOLD%^RED%^OFFLINE: HUB DOWN%^RESET%^\"";
            break;
        case 5:
            ret += "IMC2: %^BOLD%^RED%^OFFLINE: BANNED%^RESET%^\"";
            break;
        default:
            ret += "IMC2: %^BOLD%^RED%^OFFLINE%^RESET%^\"";
            break;
    }
    return ret;
}

string LongDesc(){
    string desc = "这是一个由某种白色闪亮材料构成的抛光无菌房间。"+
        "墙上有一个显示屏，旁边有一个控制面板。"+
        "面板上挂着一条长长的打印输出。"+
        "\n网络故障排除室在下面。";
    desc += "\n墙上的标志写着："+SignRead();
    return desc;
}

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("管理员房间");
    SetLong( LongDesc() );
    SetItems( ([ ({"wall","walls"}) : "墙壁似乎由某种先进的聚合物构成。它们极其干净且高度抛光。",
                "room" : "这看起来可能是MUD的控制室。",
                //({"screen","viewscreen"}) : "This is a display screen of some sort.",
                ({"screen","viewscreen"}) : (: eventReadScreen :) ,
                ({"printout"}) : (: eventReadPrintout :) ,
                ({"sign"}) : "一个你可以阅读的标志。",
                ({"panel","control panel"}): "这似乎是MUD的主控制面板。"+
                "它包含一系列令人眼花缭乱的键盘，但控制面板最显著的特征"+
                "是其中心的一块金属板，形状像人手。",
                ({"camera","hal","HAL"}) : "这是安装在墙内的摄像机的矩形面板。"+
                "矩形的上端是一个压印标签。下端是镜头，"+
                "中心有一个发光的红灯。",
                ({"label","stamped label"}) : "一个压印的金属标签。标签上写着：'HAL 9000'。",
                ({"plate","metallic plate","identification plate"}) : "这似乎是一种"+
                    "识别板，设计用于容纳人手。",
                    "portal" : "通往另一个地方的传送门。"]) );
    SetExits( ([
                "north" : "/domains/default/room/wiz_hall",
                "down" : "/secure/room/network.c",
                ]) );
    SetEnters( ([
                ]) );
    SetProperties(([
                "no peer" : 1,
                ]));
    SetRead("screen", (: eventReadScreen :) );
    SetRead("printout", (: eventReadPrintout :) );
    SetRead("sign", (: SignRead :) );

    SetListen("default", "你能隐约听到墙壁传来的低沉嗡嗡声。");
    SetListen( ({"wall","walls"}), "你听到低沉的脉动声，仿佛来自机器。");
    SetInventory( ([
                "/secure/obj/arch_board" : 1,
                ]) );
    SetCoordinates("-2,2,0");
}
int CanReceive(object ob) {
    if( !archp(ob)  && base_name(ob) != "/secure/obj/arch_board"){
        message("info","管理员房间仅供管理员使用，抱歉。",ob);
        return 0;
    }
    return 1;
}
void init(){
    ::init();
}
