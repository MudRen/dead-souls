#include <lib.h>
inherit LIB_ROOM;

void AddStuff(){
    object ob;
    ob = new("/lib/bboard");
    ob->SetKeyName("chalkboard");
    ob->SetId( ({ "board", "chalkboard","bulletin board","visitor's board"}));
    ob->set_board_id("visitor_board");
    ob->set_max_posts(30);
    ob->SetShort("访客留言板");
    ob->SetLong("这是访客留言板。学生和访客通过它互相发布关于LPC大学的消息、评论和问题，也可以向LPC大学的创建者提问。创建者偶尔也会发布提示、建议和线索。要发布消息，请输入：post <消息名称>。写完后，在空行输入一个句号，然后在冒号提示符(:)处输入小写x并回车。\n");
    ob->eventMove(this_object());
    ob->SetNoClean(0);
}
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(40);
    SetShort("学生休息室");
    SetLong("这是LPC大学新主楼的学生休息室。目前这里相当空旷，因为大楼仍处于建设初期。你看到地板上有一些标记，指示着未来家具的摆放位置。主走廊在北边，南墙上有一扇窗户俯瞰着校园。");
    SetItems(([
                ({"here","room","lounge"}) : "这里似乎是要作为学生休息室。",
                "building" : "你在新主楼，LPC大学的主行政楼。",
                ({"mark","marks"}) : "一些粉笔标记和胶带指示着家具的摆放位置。",
                ({"floor","ground"}) : "标准的米白色油毡瓷砖地板，以防笨拙的学生打算在这里吃东西。",
                ({"corridor","hall"}) : "新主楼一楼的主走廊。",
                "window" : "南墙上的一扇窗户，俯瞰着校园。奇怪的是，窗外似乎什么都没有……没有校园，没有灯光，没有星星……什么都没有。就好像行政楼悬浮在真空中一样。",
                "campus" : "它似乎奇怪地消失了。",
                ({"wall","south wall"}) : "一扇有窗户的墙。"]));
    SetExits( ([
                "north" : "/domains/campus/room/corridor2.c",
                ]) );
    SetInventory(([
                "/domains/campus/obj/locker" : 1,
                ]));
    SetProperty("no attack", 1);
    AddStuff();
}
void init(){
    ::init();
}
