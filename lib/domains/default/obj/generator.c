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
    else ret += "它是暗淡的。";
    return ret;
}

string ExaBlue(){
    string ret = "一个蓝色按钮。 ";
    if(CheckBlue()) ret += "它在发光。";
    else ret += "它是暗淡的。";
    return ret;
}  

mixed PressOrange(mixed args...){
    int orange = CheckOrange();
    if(orange){
        orange = new(oportal)->eventMove(environment(this_player()));
    }
    if(orange){
        write("你按下按钮，伴随着低沉的撞击声，一个橙色传送门出现了。");
        say(this_player()->GetName()+"按下了"+possessive(this_player())+"传送门生成器上的按钮，伴随着低沉的撞击声，一个橙色传送门出现了。");
    }
    else {
        write("咔哒。");
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
        write("你按下按钮，伴随着低沉的撞击声，一个蓝色传送门出现了。");
        say(this_player()->GetName()+"按下了"+possessive(this_player())+"传送门生成器上的按钮，伴随着低沉的撞击声，一个蓝色传送门出现了。");
    }
    else {
        write("咔哒。");
        say(this_player()->GetName()+"按下了"+possessive(this_player())+"传送门生成器上的按钮。");
    }
    return 1;
}

string ReadLabel(){
    string ret = "";
    ret += "GCM重工业传送门生成器 Mk I\n\n";
    ret += "* 请阅读此说明以了解操作方法！\n";
    ret += "* 禁止在同一房间之间传送！\n";
    ret += "* 请人类用户签署器官释放表！\n";
    ret += "* 如果你被偷了，请立即报警！\n";
    ret += "* "+sprintf("%c",223)+"的值可能会导致毁灭！\n";
    return ret;
}

string ReadScribbles(){
    string ret = "";
    ret += "这项技术被GCM偷走了，他们并不理解它。 ";
    ret += "从来没有人从在同一房间使用传送门中回来过！ ";
    ret += "无论你做什么，远离那\n";
    return ret;
}

void create(){
    ::create();
    SetKeyName("GCM Portal Generator Mk I");
    SetId( ({"generator", "device", "generator mk i","generator mark i"}) );
    SetAdjectives( ({"sleek","mk i","futuristic","portal","gcm"}) );
    SetShort("一个传送门生成器");
    SetLong("这是一个造型流畅的未来主义设备，上面有橙色和蓝色的按钮。它有一个可以阅读的印刷标签，看起来有人还在上面匆忙地涂写了一些标记。");
    SetMass(100);
    SetBaseCost("silver",5000);
    SetVendorType(VT_TREASURE);
    SetItems( ([
                ({"label","printed label"}) : "一个你可以阅读的印刷标签。",
                ({"markings","scribbles","scribbled markings"}) : "你可以阅读的标记，看起来是匆忙涂写的。",
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
