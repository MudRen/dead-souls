#include <lib.h>

inherit LIB_ROOM;

nosave private int __EntryAllowed, __PartyTime;

int query_party_time();
int x;

void create() {
    room::create();
    SetProperties( ([ "light":2, "indoors":1, "no attack":1,
                "no teleport":1, "no steal":1, "no magic":1 ]) );
    SetShort("%^MAGENTA%^%^BOLD%^在火山中%^RESET%^");
    SetLong(
            "你站在一个宽阔的圆形平台上，四面八方都被%^RED%^冒泡的岩浆%^RESET%^包围。"
            "平台漂浮在岩浆池上方安全距离处，但足够近，"
            "让你能感受到岩浆有时向上喷涌时的热量。"
            "平台装饰着%^MAGENTA%^漂浮的光芒"
            "%^RESET%^，%^BLUE%^色彩和%^ORANGE%^大小各异。%^RESET%^"
            "放着茶点的桌子也放置在平台边缘附近。");
    SetItems(
            ([
             ({"platform", "wide platform", "circular platform"}) :
             "平台漂浮在岩浆池上方安全距离处，但足够近，"
             "让你能感受到岩浆有时向上喷涌时的热量。"
             "平台装饰着%^MAGENTA%^漂浮的光芒"
             "%^RESET%^，%^BLUE%^色彩和%^ORANGE%^大小各异。%^RESET%^"
             "放着茶点的桌子也放置在平台边缘附近。",
             ({"sides", "side", "edges", "edge"}) :
             "平台四面八方都被%^RED%^冒泡的岩浆%^RESET%^包围。",

             ({"pool", "pool of lava", "lava", "bubbling lava"}) :
             (:this_object(), "look_lava":),

             ({"lights", "light", "floating lights", "floating light"}) :
             (:this_object(), "look_lights":),
             ({"tables", "table"}) :
             "桌子上摆满了各种美味的茶点。"
             "装着各种可能组合饮品的瓶子沿着桌子摆放。"
             "事实上，你现在就想给自己倒一杯冰凉的饮料。"
             "你直觉到 pour <饮品名> 会为你提供一杯你最喜欢的冰凉饮料。",
                 ({"treats", "treat"}) : (:this_object(), "look_treat":)
                                           ]) );
    SetExits( ([ "square" : "/domains/Praxis/square" ]) );
}

void init() {
    room::init();
    add_action("cmd_pour", "pour");
}

void start_party(string msg) {
    if(base_name(previous_object()) != "/cmds/mortal/_mudparty") return;
    if(query_party_time()) return;
    message("shout", sprintf("来自%s的派对公告：%s派对正在"
                "举行以庆祝%s！", this_player()->query_cap_name(),
                mud_name(), msg), users());
    message("shout", "你有2分钟时间输入\"mudparty join\"来加入派对！", users());
    __EntryAllowed = 1;
    __PartyTime = 1;
    call_out("deny_entry", 120);
}

protected void deny_entry() { __EntryAllowed = 0; }

int query_party_time() { return __PartyTime; }

int query_entry_allowed() { return __EntryAllowed; }

string look_lava(string unused)
{
    x=random(3)+1;

    if(x==1)
    {
        message("info",
                "%^RED%^一股壮观的岩浆喷泉喷向空中，在撞击平台之前分开，"
                "让你免于必死的命运。%^RESET%^",
                environment(this_player()));
    }

    if(x==2)
    {
        message("info",
                "%^RED%^一股火焰从岩浆中喷出，将房间笼罩在红色光芒中。%^RESET%^", environment(this_player()));
    }

    if(x==3)
    {
        message("info",
                "%^RED%^%^BOLD%^一大股岩浆从平台下方涌出，平台随之晃动。%^RESET%^",
                environment(this_player()));
    }

    if(x==4)
    {
        message("info",
                "%^MAGENTA%^岩浆的颜色从%^RED%^红色%^MAGENTA%^变成了紫色。%^RESET%^",
                environment(this_player()));
    }

    return("岩浆不断变化和冒泡。你可以看到大块的岩石漂浮在其中。");
}


string look_lights(string unused)
{
    x=random(3)+1;

    if(x==1)
    {
        return(
                "一个美丽的%^YELLOW%^黄色%^RESET%^球体漂浮到你附近，在你身上投下欢快的光芒。");
    }

    if(x==2)
    {
        return(
                "一个美丽的%^BLUE%^蓝色%^RESET%^球体漂浮到你附近，在你身上投下柔和的光芒。");
    }

    if(x==3)
    {
        return(
                "一个美丽的%^MAGENTA%^紫色%^RESET%^球体漂浮到你附近，在你身上投下紫色的光芒。");
    }

    if(x==4)
    {
        return(
                "一个美丽的%^RED%^红色%^RESET%^球体漂浮到你附近，在你身上投下玫瑰色的光芒。");
    }
}


int look_treat()
{
    message("other_action",
            this_player()->query_cap_name()+"在看了一遍桌子上的茶点后，"
            "开始吃喝起来。",
            environment(this_player()), this_player());
    message("my_action",
            "看着面前琳琅满目的茶点，你决定尝试所有的东西！"
            "潘趣酒、饼干、肉类..应有尽有！", this_player());
    return 1;
}

int cmd_pour(string str) {
    object ob;
    string *words;

    //    if(!str) return notify_fail("Pour what?\n");
    //    if(this_player()->query_mp() < 10)
    //      return notify_fail("You are too weak for that!\n");
    //    words = explode(str, " ");
    //    if(words[0] == "A" || words[0] == "An") words[0] = lower_case(words[0]);
    //    ob = new(DRINK);
    //    ob->SetKeyName(words[sizeof(words)-1]);
    //    ob->SetMass(75);
    //    ob->SetId(explode(strip_colours(str), " "));
    //   if(sizeof(words) > 2)
    //      SetAdjectives(words[0..sizeof(words)-2]);
    //    ob->SetShort(implode(words, " "));
    //    ob->SetLong("A nice drink created by "+
    //      this_player()->query_cap_name()+".");
    //    ob->SetStrength(random(30)+2);
    //    ob->set_drink("$N drink $O.",
    //      "$N drinks $O poured by "+this_player()->query_cap_name()+".");
    //    this_player()->add_hp(-2);
    //    if(ob->move(this_player())) {
    //        message("my_action", "You cannot carry that!", this_player());
    //        ob->destruct();
    //        return 1;
    //    }
    //    message("my_action", "You pour "+implode(words, " ")+".", this_player());
    //    message("other_action", sprintf("%s pours %s.",
    //      this_player()->query_cap_name(), implode(words, " ")),
    //      this_object(), ({ this_player() }));
    return 1;
}
