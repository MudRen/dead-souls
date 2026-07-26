#include <lib.h>
#include <vendor_types.h>

inherit LIB_STORAGE;
inherit LIB_PRESS;
inherit LIB_INSTALL;
inherit LIB_ACTIVATE;

string oportal = "/secure/obj/portal_orange";
string bportal = "/secure/obj/portal_blue";

varargs mixed CheckOrange(int ob){
    object o, *tmp;
    int orange = sizeof(tmp=filter(deep_inventory(this_object()),
                (: base_name($1) == "/domains/default/obj/vial_orange" :) ) );
    if(orange) o = tmp[0];
    if(ob) return o;
    return orange;
}

varargs mixed CheckBlue(int ob){
    object b, *tmp;
    int blue = sizeof(tmp=filter(deep_inventory(this_object()),
                (: base_name($1) == "/domains/default/obj/vial_blue" :) ) );
    if(blue) b = tmp[0];
    if(ob) return b;
    return blue;
}

string ExaOrange(){
    string ret = "一个橙色按钮。 ";
    if(CheckOrange()) ret += "它在发光。";
    else ret += "它是 darkened。";
    return ret;
}

string ExaBlue(){
    string ret = "一个蓝色按钮。 ";
    if(CheckBlue()) ret += "它在发光。";
    else ret += "它是 darkened。";
    return ret;
}  

mixed PressOrange(mixed args...){
    int orange = CheckOrange();
    if(orange){
        orange = new(oportal)->eventMove(environment(this_player()));
    }
    if(orange){
        write("你按下按钮， with a deep thumping sound an orange portal appears。");
        say(this_player()->GetName()+"按下了"+possessive(this_player())+"传送门生成器上的按钮， with a deep thumping sound an orange portal appears。");
    }  
    else {
        write("Click。");
        say(this_player()->GetName()+"按下了"+possessive(this_player())+"传送门生成器上的按钮。");
    }
    return 1;
}

mixed PressBlue(mixed args...){
    int blue = CheckBlue();
    if(blue){
        blue = new(bportal)->eventMove(environment(this_player()));
    }
    if(blue){
        write("你按下按钮， with a deep thumping sound a blue portal appears。");
        say(this_player()->GetName()+"按下了"+possessive(this_player())+"传送门生成器上的按钮， with a deep thumping sound a blue portal appears。");
    }
    else {
        write("Click。");
        say(this_player()->GetName()+"按下了"+possessive(this_player())+"传送门生成器上的按钮。");
    }
    return 1;
}

string ReadLabel(){
    string ret = "";
    ret += "GCM Heavy Industries Portal Generator Mk I\n\n";
    ret += "* Please read this beard to know act According to carry on!\n";
    ret += "* no portaling through between same room allowed Interdicted!\n";
    ret += "* Please the human user to be sign release form the organs!\n";
    ret += "* If you are stolen, call the police at once!\n";
    ret += "* values of "+sprintf("%c",223)+" may give rise to dom!\n";
    return ret;
}

string ReadScribbles(){
    string ret = "";
    ret += "this technology was stolen by GCM and they don't understand it. ";
    ret += "NOBODY HAS EVER RETURNED FROM USING PORTALS IN THE SAME ROOM! ";
    ret += "and whatever you do, stay away from th\n";
    return ret;
}

void create(){
    ::create();
    SetKeyName("GCM Portal Generator Mk I");
    SetId( ({"generator", "device", "generator mk i","generator mark i"}) );
    SetAdjectives( ({"sleek","mk i","futuristic","portal","gcm"}) );
    SetShort("一个传送门生成器");
    SetLong("这是一个 sleek, futuristic device with orange and blue buttons。它有一个 printed label you can read， and it looks like someone has scribbled some markings on it as well。");
    SetMass(100);
    SetBaseCost("silver",5000);
    SetVendorType(VT_TREASURE);
    SetItems( ([
                ({"label","printed label"}) : "一个你可以阅读的印刷标签。",
                ({"markings","scribbles","scribbled markings"}) : "你可以阅读的 markings， apparently scribbled in haste。",
                ({ "button", "buttons" }) : "传送门生成器有两个按钮，一个橙色，一个蓝色。",
                ({ "orange button" }) : (: ExaOrange :),
                ({ "blue button" }) : (: ExaBlue :),
                ]) );
    SetReads( ([
                "default" : "试试 'read label on generator'",
                ({"label","printed label"}) : (: ReadLabel :),
                ({"markings","scribbles","scribbled markings"}) : (: ReadScribbles :),
                ]) );
    SetPress( ([
                "default" : "试试 'push blue button on generator'",
                ({ "button", "buttons" }) : "你必须按其中一个。",
                ({"orange button"}) : (: PressOrange :),
                ({"blue button"}) : (: PressBlue :),
                ]) );
    SetMaxCarry(200);
    SetUnique(1);
}

varargs mixed eventInstall(object what, object where){
    write("传送门生成器无法安装在任何地方");
    return 1;
}

mixed CanPutInto(object who, object item){
    return "这是一个传送门生成器。可以在里面安装东西。";
}

mixed CanGetFrom(object who, object item){
    return "这是一个传送门生成器。可以从里面卸载东西。";
}

int CanReceive(object ob){
    if(base_name(ob) == "/domains/default/obj/vial_blue"){
        if(CheckBlue()){
            write("它不合适。");
            return 0;
        }
        else return 1;
    }
    if(base_name(ob) == "/domains/default/obj/vial_orange"){
        if(CheckOrange()){
            write("它不合适。");
            return 0;
        }
        else return 1;
    }
    write("那不属于那里。");
    return 0;
}

int eventTurnOn(){
    write("试试 'push orange button on generator'");
    return 1;
}

void init(){
    ::init();
}
