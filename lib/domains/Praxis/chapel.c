#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperties( ([ "light" : 2, "indoors" : 1, "no attack" : 1, "no steal" : 1 ]) );
    SetExits( 
            (["south" : "/domains/Praxis/monastery"]) );
    SetShort("小教堂");
    SetLong( 
            sprintf("%s的小教堂庄严肃穆且古老，有着彩色玻璃窗和深色橡木长椅。"
                "大多数婚礼仪式都在这里举行。输入<help marriage>获取"
                "关于婚礼的信息。", mud_name()) );
    SetItems(
            (["pews" : "古老的橡木座椅，被无数个世纪以来坐过的人们的臀部染成深色。",
             "windows" : "窗户呈现了亡者之魂历史上的重要事件，其中多幅画面相当血腥。",
             "ceremony" : "只有当你向上滚动时才可以看到仪式。"]) );
}
void init(){
    ::init();
}
