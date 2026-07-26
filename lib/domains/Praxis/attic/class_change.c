#define addi(x,y) AddItem(x,y)
#define adde(x,y) AddExit(y) 

inherit "/lib/std/room";

void create() {    

    SetAmbientLight(30);
    SetShort("魔法心灵改变祭坛");
    SetLong(
            "这个房间很干净，里面有几乎全新的家具。一个奇怪的\n"
            "倾斜祭坛在房间中央。带轮子的桌子上覆盖着魔法器具，\n"
            "被推到了墙边。\n");
    addi("furniture",
            "家具都是橡木制的。\n");
    addi("altar",
            "祭坛是木制的，以一个奇怪的角度倾斜。\n");
    addi("tables",
            "桌子上覆盖着各种魔杖、戒指、水晶球、魔法草药，\n"
            "还有一些你甚至无法辨认的东西。\n");
    addi("table",
            "每张桌子都由坚固的橡木制成，可以在房间里推来推去。\n");
    addi("devices","这些器具非常奇特。\n");
    addi("device",
            "一个器具吸引了你的目光。它正往排水沟里喷水。\n");
    addi("water","水看起来凉爽清新。\n");
    addi("drain","排水沟在地板上。\n");
    addi("floor","地板是打扫干净的花岗岩。\n");
    addi("walls","石墙上没有装饰。\n");
    addi("wall","所有的墙都一样。\n");
    addi("stone","这个房间里所有的石头都是花岗岩。\n");
    addi("granite","花岗岩是灰色且粗糙的。\n");
    //new("/obj/mon/wizard")->move(this_object());
}

void init()
{
    ::init();
    add_action("changing","change");
    add_action("helping","help");
}

int helping(string str)
{
    if(str != "changing") return 0;
    write(
            "从一个职业转换到另一个职业的费用是你一半的经验值和\n"
            "五千金币。\n\n"
            "要转换职业，输入'change class to <类型>'，其中类型是你想要转换的职业。"
            "巫师将对你进行手术来做出调整。不会疼的，真的，至少不会太疼。\n");
    return 1;
}

int changing(string str)
{
    int i;

    if(!present("mad wizard"))
    {
        write("疯狂的巫师不在这里为你治疗。\n");
        return 1;
    }
    if(!str)
    {
        write("你不给指示，巫师怎么做手术？\n");
        say("疯狂的巫师敲了"+this_player()->query_cap_name()+
                "的头。\n");
        return 1;
    }
    //wtf does this do?
    //str=extract(str, 9);
    if(str == this_player()->query_class())
    {
        write("疯狂的巫师说：你比我还要疯狂！\n");
        return 1;
    }
    switch(str)
    {
        case "fighter":
        case "cleric":
        case "rogue":
        case "mage":
        case "monk":
            i=1;
            break;
        default: i=0;
    }
    if(!i)
    {
        write("疯狂的巫师说：那是什么职业？\n");
        return 1;
    }
    if( this_player()->query_money("gold") < 5000)
    {
        write("疯狂的巫师说：你需要更多的钱。\n");
        return 1;
    }
    this_player()->add_money("gold", - 5000);
    this_player()->add_exp( - (this_player()->query_exp() / 2) );
    this_player()->set_class(str);
    write("巫师从桌子上拿起一根魔杖，向你发射！\n");
    say("巫师用魔杖向"+this_player()->query_cap_name()+"发射了一道光芒。\n");
    return 1;
}
