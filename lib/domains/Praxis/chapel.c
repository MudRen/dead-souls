#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperties( ([ "light" : 2, "indoors" : 1, "no attack" : 1, "no steal" : 1 ]) );
    SetExits( 
            (["south" : "/domains/Praxis/monastery"]) );
    SetShort("小教堂");
    SetLong(
            sprintf("%s小教堂庄严而古老，有彩色玻璃窗和深色橡木长椅。"
                "大多数婚礼仪式都在这里举行。"
                "输入 <help marriage> 获取婚礼信息。", mud_name()) );
    SetItems(
            (["pews" : "古老的橡木座椅，因无数年代的坐卧而变得暗沉。",
             "windows" : "窗户展示了泥潭历史的精彩瞬间，其中很多都很血腥。",
             "ceremony" : "仪式只有在你回滚时才能看到。"]) );
}
void init(){
    ::init();
}
