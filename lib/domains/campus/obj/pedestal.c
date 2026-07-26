#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_PRESS;

int PushTheButton();
string color,gagnant,my_door,other_door,removed_door;
void create(){
    ::create();
    SetKeyName("button pedestal");
    SetId( ({"pedestal","altar"}) );
    SetAdjectives( ({"cylindrical","round","waist-high"}) );
    SetShort("带红色按钮的基座");
    SetLong("这是一个圆柱形基座，大约齐腰高，由神秘材料制成。上面有一个按钮。");
    SetItems( ([
                ({"button","red button"})  : "一个红色按钮。"
                ]) );
    SetMass(20);
    SetDollarCost(10);
    SetVendorType(VT_TREASURE);
    SetPress( ([
                ({"button","red button"}) : (: PushTheButton :)
                ]) );
}
mixed CanGet(object ob) { return "这个基座纹丝不动。";}
int ResetGame(){
    object *objects;
    object *contents;
    string prize;
    prize = "/domains/campus/armor/silverring";
    objects = ({});
    objects+=({ load_object("/domains/campus/room/red_room") });
    objects+=({ load_object("/domains/campus/room/green_room") });
    objects+=({ load_object("/domains/campus/room/blue_room") });

    objects = ({ load_object("/domains/campus/doors/red_door") });
    objects +=({ load_object("/domains/campus/doors/green_door") });
    objects +=({ load_object("/domains/campus/doors/blue_door") });

    foreach(object ding in objects){
        if(ding) ding->SetClosed(1);
        if(ding) ding->SetLocked(1);
    }

    if(sscanf(gagnant,"%s door",color)>0){
        string where;
        where="/domains/campus/room/"+color+"_room";
        //new(prize)->eventMove(load_object(where));
    }
}
int PushTheButton(){
    int genrand;
    gagnant = "";
    genrand = random(3);
    send_messages("press", "$agent_name $agent_verb the button.",
            this_player(), 0, environment(this_player()));
    if(genrand == 0) gagnant = "red door";
    if(genrand == 1) gagnant = "green door";
    if(genrand == 2) gagnant = "blue door";
#if 0
    tell_room(environment(),"A voice from the pedestal says: "
            "PRECOG: genrand is: "+genrand);
    tell_room(environment(),"A voice from the pedestal says: "
            "PRECOG: gagnant is: "+gagnant+".\n"
            "PRECOG: genrand modulus is: "+genrand);
#endif
    remove_action("doStay","stay");
    remove_action("doSwitch","switch");
    add_action("choose","choose");
    tell_room(environment(),"基座发出声音说："
            "你现在必须从这三扇门中选择一扇。"
            "其中一扇后面有奖品。另外两扇后面什么都没有。"
            "例如要选择红门，请输入：choose red door");
    ResetGame();
    return 1;
}
void init(){
    ::init();
    if(gagnant != "" && my_door !=""){
        add_action("doStay","stay");
        add_action("doSwitch","switch");
    }
    if(gagnant != "" && my_door == ""){
        add_action("choose","choose");
    }
}
int choose(string str){
    if(!str || str == ""){
        tell_room(environment(),"基座发出声音说：请试着选择一扇门，好吗？");
    }
    else if(str == "door"){
        tell_room(environment(),"基座发出声音说：你需要说得更具体一些。");
    }
    else if(str == "red door" || str == "blue door" ||str == "green door"){
        tell_room(environment(),"基座发出声音说：你选择了"+str+"。");
        this_object()->MontyMagic(str);
    }
    else {
        tell_room(environment(),"基座发出声音说：我不明白你的意思。");
    }
    reap_dummies();
    reap_other("/domains/campus/armor/silverring");
    return 1;
}
int MontyMagic(string str){
    int genrand,which;
    string *choices;
    choices = ({});
    if(str != "red door") choices += ({ "red door" });
    if(str != "green door") choices += ({ "green door" });
    if(str != "blue door") choices += ({ "blue door" });
    genrand = random(2);
    if(choices[1] == gagnant) which = 0;
    else if(choices[0] == gagnant) which = 1;
    else which = genrand;
    removed_door = choices[which];
    choices -= ({ choices[which] });
    other_door = choices[0];
    my_door = str;
    choices += ({ str });
    if(sscanf(removed_door,"%s door",color)>0) color = color;
    load_object("/domains/campus/doors/"+color+"_door")->SetLocked(0);
    load_object("/domains/campus/doors/"+color+"_door")->SetClosed(0);
    tell_room(environment(),"基座发出声音说："
            "我已经打开了"+removed_door+"！\n"
            "你可以进入"+color+"房间看看里面是空的。\n"
            "只剩下"+choices[0]+"和"+choices[1]+"了。\n\n"
            "你想换到"+other_door+"吗？\n"
            "还是你想留在"+str+"？\n\n"
            "要换，请输入：switch\n"
            "要留下，请输入：stay");
    remove_action("choose","choose");
    add_action("doStay","stay");
    add_action("doSwitch","switch");
    return 1;

}
int CheckWin(string str){
    if(sscanf(str,"%s door",color)>0) color = color;
    if(str == gagnant) {
        this_object()->WinFun();
        return 1;
    }
    load_object("/domains/campus/doors/"+color+"_door")->SetLocked(0);
    load_object("/domains/campus/doors/"+color+"_door")->SetClosed(0);
    tell_room(environment(),"基座发出声音说："
            "你输了！！！\n"
            "你可以进入"+color+"房间去领取你的大奖——什么都没有。哈哈哈！");
    return 1;
}
int doStay(){
    tell_room(environment(),"基座发出声音说：哦，多么忠诚！");
    remove_action("doStay","stay");
    remove_action("doSwitch","switch");
    CheckWin(my_door);
    return 1;
}
int doSwitch(){
    tell_room(environment(),"基座发出声音说：你真是反复无常！");
    remove_action("doStay","stay");
    remove_action("doSwitch","switch");
    my_door = other_door;
    CheckWin(my_door);
    return 1;
}
int WinFun(){
    load_object("/domains/campus/doors/"+color+"_door")->SetLocked(0);
    load_object("/domains/campus/doors/"+color+"_door")->SetClosed(0);
    tell_room(environment(),"基座发出声音说："
            "你赢了，恭喜！\n"
            "你可以进入"+color+"房间领取你的奖品。\n\n"
            "按下基座上的按钮可以重置游戏。");
    return 1;
}
