/*    /domains/Ylsrim/room/bazaar.c
 *    From the Dead Souls Mud Library
 *    An example of a simple room
 *    created by Descartes of Borg 950928
 */

#include <lib.h>

inherit LIB_ROOM;

int ReadSign() {
    this_player()->more("/domains/town/txt/warning_sign.txt");
    return 1;
}

protected void create() {
    object ob; // this will be used to create dummy items

    // setup the stuff you inherit
    room::create();
    // set the town, as native Ylsrimites can do special things in Ylsrim
    SetTown("Ylsrim");
    // the climate in Ylsrim is arid because it is a desert town
    SetClimate("arid");
    // the is the amount of light the street lamps make at night
    SetAmbientLight(30);
    // the obvious exits tell people how to leave the room
    // set the sounds people hear
    SetListen("商贩们正在恳求你来看看他们的商品。");
    // set the short description... should not be capitalized
    SetShort("伊尔斯利姆中心集市");
    // this is the description people see at day
    SetDayLong("出售各种商品的店铺和商贩挤满了伊尔斯利姆的中心集市。"
            "当地村民和异域旅行者在你身边穿梭，寻找便宜货，"
            "甚至有些时候是在找麻烦。"
            "卡利德路从你北边由西向东穿过伊尔斯利姆，"
            "防具店和武器店分列集市两侧。集市向南延伸。"
            "\n%^RED%^这里有一块告示牌，你可以阅读。%^RESET%^");
    SetSkyDomain("town");
    // this is the description people see at night
    SetNightLong("虽然伊尔斯利姆的大部分区域此刻都很安静，"
            "中心集市上仍然挤满了做生意的人，尽管大多数店铺已经关门。"
            "卡利德路就在北边，已经打烊的防具店和武器店分列集市两侧。"
            "集市向南延伸。"
            "\n%^RED%^这里有一块告示牌，你可以阅读。%^RESET%^");
    // set up dummy items... the first few are simple
    AddItem(({ "villager", "traveller" }),
            "村民们和旅行者们都在外面寻找好买卖。");
    AddItem(({ "sign"}), "一块告示牌。要阅读它，请输入 'read sign'。");
    AddItem(({ "road" }), "这条路从西边的大沙漠穿过伊尔斯利姆，通往东边更肥沃的土地。", ({ "kaliid" }));
    // people need to enter the armory, so we need to do something special
    // first create an armory dummy item
    SetRead("sign", (: ReadSign :) );
    ob = new(LIB_DUMMY, ({ "armory", "shop" }),
            function(string str) {
            if( query_night() ) {
            return "已经关门了。";
            }
            else {
            return "正在营业。";
            }
            }, ({ "armor" }));
    // set it so when people 'enter armory', they move to the armory
    ob->SetEnter("/domains/Ylsrim/room/"+ "armory");
    // now add it as an item
    AddItem(ob);
    // do the same stuff for the weaponry
    ob = new(LIB_DUMMY, ({ "weaponry", "shop" }),
            function(string str) {
            if( query_night() ) {
            return "已经关门了。";
            }
            else {
            return "正在营业。";
            }
            }, ({ "weapon" }));
    ob->SetEnter("/domains/Ylsrim/room/"+ "weaponry");
    AddItem(ob);
    // set the directional exits
    SetExits( ([ "north" : "/domains/Ylsrim/room/"+ "kaliid4",
                "south" : "/domains/Ylsrim/room/"+ "s_bazaar" ]) );
}
void init(){
    ::init();
}
