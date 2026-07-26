#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperties( ([ "no castle" : 1,"light" : 2, "indoors" : 1]) );
    SetShort("一间茅草屋顶的房子");
    SetLong(
            "这间小小的茅草屋已经矗立了很多年。"
            "它是一位年老、名誉扫地的骑士的住所。房子非常简陋，"
            "没有任何装饰或家具。骑士相当贫穷，除了几件微薄的"
            "物品外什么也买不起。一扇粗糙的木门通往南边的房间，"
            "向北则回到太阳巷。");
    SetItems(
            (["thatch" : "开始受到天气和疏于维护的影响。",
             "house" : "非常不起眼。",
             "furnishing" : "什么都没有。",
             "decoration" : "完全没有。",
             "door" : (: this_object(), "look_at_door" :) ]) );
    SetExits( ([ 
                "north" : "/domains/Praxis/sun1",
                ]) );
    SetDoor("/domains/Praxis/locked", "south");
    //present("knight")->eventForce("close door");
    //present("knight")->eventForce("lock door with key");
}

void reset() {
    object mon, key;

    ::reset();
    if(!present("knight")) {
        mon = new("/domains/Praxis/obj/mon/knight");
        mon->move(this_object());
        new("/domains/Praxis/obj/armour/helm")->move(mon);
        mon->command("wear helm");
        key = new(LIB_ITEM);
        key->SetKeyName("key");
        key->SetId( ({ "key", "honor key" }) );
        key->SetShort( "一把木钥匙");
        key->SetLong("这把木钥匙非常粗糙。"
                "看起来不会通往什么重要的地方。");
        key->SetValue(15);
        key->SetMass(40);
        key->move(mon);
    }
    if(query_reset_number() != 1) {
        //present("knight")->eventForce("close door");
        //present("knight")->eventForce("lock door with key");
    }
}

void look_at_door() {
    write("这是一扇门。");
}
void init(){
    ::init();
}
