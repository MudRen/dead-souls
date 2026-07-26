/*    /d/standard/obj/mon/receptionist.c
 *    from Nightmare IV
 *    receptionist for the Nightmare Inn
 *    created by Descartes of Borgie and Lassondra of Sunshine@Nightmare 940424
 */

#include <lib.h>

inherit LIB_NPC;

#define ROOMS ([\
101: ([ "name": "regular", "cost":8 ]),\
        102: ([ "name": "regular", "cost":8 ]),\
        103:([ "name":"regular", "cost":8 ]),\
        104:([ "name":"regular", "cost":8 ]),\
        105:(["name":"deluxe", "cost":12 ]),\
        106:(["name":"deluxe", "cost":12 ]),\
        107:([ "name":"deluxe", "cost":12]),\
        108:(["name":"deluxe", "cost":12]),\
        109:(["name":"honeymoon suite", "cost":20]),\
        110:(["name":"honeymoon suite", "cost":20]),\
        ])

void create() {
    npc::create();
    SetKeyName( "linfield");
    SetId( ({ "linfield", "receptionist" }) );
    SetShort( "林菲尔德，接待员" );
    SetLong( "林菲尔德是噩梦旅馆的庄重接待员。"
            "他高高地站在柜台后面，等待着为下一位客人服务。"
            "他穿着深色裤子和西装外套，白色衬衫，"
            "系着蓝红条纹的领结。");
    SetLevel(15);
    SetGender( "male" );
    SetRace( "human" );
    SetHealthPoints(700);
    SetClass( "mage" );
    SetSkill( "magic attack", 60);
    SetSkill( "melee", 70);
    SetCurrency( "gold", 50);
}

void init() {
    npc::init();
    add_action("cmd_rent", "rent");
    add_action("cmd_list", "list");
}

int cmd_list(string str) {
    write( "%^GREEN%^   -=       噩梦旅馆    =-%^RESET%^");
    write( "\n");
    write( "%^GREEN%^     有3种类型的房间。%^RESET%^");
    write( "%^GREEN%^     普通房：%^RESET%^"+currency_value(ROOMS[101]["cost"], "gold") );
    write( "%^GREEN%^     豪华房：%^RESET%^" +currency_value(ROOMS[106]["cost"], "gold") );
    write( "%^GREEN%^     蜜月套房：%^RESET%^" +currency_value(ROOMS[109]["cost"], "gold") );
    write( "%^GREEN%^     要租房，请输入 <rent '房间类型(如deluxe)'>%^RESET%^");
    return 1;
}

int cmd_rent(string str) {
    object ob;
    int *arr;
    int cost, i, x;

    if(str != "regular" && str != "deluxe" && str != "honeymoon suite")
        return notify_fail("租什么类型的房间？\n");
    i = sizeof(arr = keys(ROOMS));
    x = -1;
    while(i--) {
        if(ROOMS[arr[i]]["name"] == str &&
                !(environment(this_object())->query_occupied(arr[i]))) {
            x = arr[i];
            break;
        }
    }
    if(x == -1)
        return notify_fail("目前没有这样的房间可用。\n");
    cost = currency_value(ROOMS[x]["cost"], "gold");
    if(cost > this_player()->query_money("gold")) {
        this_object()->eventForce("speak 你没有足够的钱租那些房间！");
        return 1;
    }
    this_player()->AddCurrency(-cost, "gold");
    environment(this_object())->set_occupied(x);
    message("my_action", sprintf("你租了噩梦旅馆的%d号房间。",
                x), this_player());
    message("other_action", sprintf("%s在噩梦旅馆租了一间房。",
                this_player()->query_cap_name()), environment(this_object()),
            ({ this_player() }) );
    ob = new(LIB_ITEM);
    ob->SetKeyName("hotel key");
    ob->SetShort("一把旅馆钥匙");
    ob->SetLong(sprintf("噩梦旅馆%d号房间的钥匙。", x));
    ob->SetMass(50);
    ob->SetValue(100);
    ob->SetRead(sprintf("噩梦旅馆。\n%d号房间。\n", x));
    ob->SetId( ({ "key", "hotel key", 
                environment(this_object())->query_key_id(x) }) );
    if(ob->move(this_player())) {
        message("my_action", "你掉了你的钥匙！", this_player());
        message("other_action", sprintf("%s掉了%s的钥匙！",
                    this_player()->query_cap_name(), possessive(this_player())),
                environment(this_object()), ({ this_player() }) );
        ob->move(environment(this_object()));
    }
    return 1;
}
