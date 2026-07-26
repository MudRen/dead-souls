#include <lib.h>

inherit LIB_DUMMY; 
inherit LIB_MANIPULATE;
inherit LIB_PRESS; 

int hidden;

int MoveThePainting();
int PushThePainting();
int OpenSesame();
string ShowDali();

protected void create() {
    dummy::create();
    SetKeyName("wall");
    SetId("wall");
    SetAdjectives("bedroom");
    SetShort("一堵卧室墙");
    SetLong("这是一堵典型而华丽的卧室墙，上面挂着一幅画。");
    SetItems( ([
                ({"painting","beautiful painting"}) :  (: ShowDali :),
                ]) );
    SetManipulate( ([
                ({"painting","beautiful painting"}) : (: MoveThePainting :)
                ]) );
    SetPress( ([
                ({"painting","beautiful painting"}) : (: PushThePainting :)
                ]) );
    hidden = 1;
}

void init(){
    add_action("GetPainting","get");
}

int GetPainting(string str){
    write("它似乎牢牢地固定在墙上。");
    return 1;
}

int MoveThePainting(){
    send_messages("move", "$agent_name $agent_verb the painting on the wall.",
            this_player(), 0, environment(this_player()));
    if(hidden == 1) {
        OpenSesame();
    }
    return 1;
}

int PushThePainting(){
    send_messages("push", "$agent_name $agent_verb the painting on the wall.",
            this_player(), 0, environment(this_player()));
    if(hidden == 1) {
        OpenSesame();
    }
    return 1;
}

string ShowDali(){
    string ret;
    ret = "一幅美丽的复制品：\n";
    ret += read_file("/domains/town/txt/pot.txt");
    return ret;
}

int OpenSesame(){
    write("你发现了一条秘密通道！");
    say(this_player()->GetName()+"发现了一条秘密通道！");
    AddItem(({"secret passageway","passageway"}) , "一条你可以进入的秘密通道。");
    hidden = 0;
    environment()->OpenPassage();
    return 1;
}
