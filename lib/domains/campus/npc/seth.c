#include <lib.h>

inherit LIB_SENTIENT;

int give_it(string str);
protected void create() {
    sentient::create();
    SetKeyName("Dr. Seth Brundle");
    SetId(({"seth","brundle","Dr. Brundle","Seth","Brundle","seth brundle", "Seth Brundle"}));
    SetShort("塞斯·布伦德尔博士");
    SetLong("布伦德尔博士是一位身材高大、瘦削的科学家，肤色橄榄色，有着深邃的黑眼睛。他似乎非常不安，正在努力工作。他看起来衣衫不整、精神紧张、非常焦虑。");
    SetInventory(([
                "/domains/campus/obj/omni" : 1,
                "/domains/campus/obj/labkey" : 1,
                ]));
    SetLevel(5);
    SetUnique(1);
    SetRace("human");
    SetGender("male");
    AddCommandResponse("give", (: give_it :));
    AddCommandResponse("omni", (: give_it :) );
    SetAction(25, ({
                "塞斯·布伦德尔紧张地用手捋了捋头发。",
                "布伦德尔博士抽搐了一下。", "塞斯·布伦德尔博士在思考。",
                "塞斯在思考。", "塞斯·布伦德尔博士仔细地思考着。",
                "塞斯·布伦德尔博士说，\"没有万能遥控器你就回不来了。\"",
                "塞斯·布伦德尔博士紧张地盯着传送门。"}));
}
void reset(){
    if(!present("omni",this_object())){
        new("/domains/campus/obj/omni")->eventMove(this_object());
        return;
    }
}
int give_it(string str){
    if(!present("omni",this_object())){
        this_object()->eventForce("say 恐怕我没有什么东西可以给你");
        this_object()->eventForce("ponder");
        return 1;
    }
    if(!present("omni",this_player())){
        write("布伦德尔博士怀疑地看了你一眼。\n");
        say("布伦德尔博士怀疑地看了"+this_player()->GetName()+"一眼。\n");
        this_object()->eventForce("give first omni to "+lower_case(this_player()->GetName()) );
        this_object()->eventForce("say 尽量别死掉，"+this_player()->GetName());
        this_object()->eventForce("sigh");
        return 1;
    }
    this_object()->eventForce("snort");
    this_object()->eventForce("say 你已经有一个了，"+this_player()->GetName());
    return 1;
}
void init(){
    ::init();
}
