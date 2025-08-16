#include <lib.h>
inherit LIB_ROOM;

string ReadList(){
    string muggleret = "可用法术：\n\n"
        "\t火球术，费用1000：\t\t给对手造成伤害\n"
        "\t飞弹术，费用500：\t\t比火球术更便宜更容易学习\n"
        "\t护盾术，费用200：\t\t在你身边召唤隐形护盾\n"
        "\t冥想术，费用500：\t\t召唤加速耐力恢复的灵气\n"
        "\n"
        "示例：如果你想学习护盾术：\n\n"
        "\"ask herkimer to teach buffer\"\n"
        "\n"
        "请注意，在你有足够的练习和经验之前，法术可能会失败很多次。所有销售都是最终的。\n";
    string mageret = "可用法术：\n\n"
        "\t火球术：\t\t给对手造成伤害\n"
        "\t强力火球术：\t\t给对手造成严重伤害\n"
        "\t飞弹术：\t\t比火球术更便宜更容易学习\n"
        "\t光亮术：\t\t让你发光，足以在黑暗中看见\n"
        "\t护盾术：\t\t在你身边召唤隐形护盾\n"
        "\t强力护盾术：\t\t在你身边召唤强大的隐形护盾\n"
        "\t冥想术：\t\t召唤加速耐力恢复的灵气\n"
        "\t能量鞭：\t\t召唤强大的能量鞭\n"
        "\n"
        "示例：如果你想学习护盾术：\n\n"
        "\"ask herkimer to teach buffer\"\n"
        "\n";
    if(this_player()->GetClass() == "mage") return mageret;
    return muggleret;
}
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("法师公会");
    SetLong("这是当地的法师公会。在这里你可以请求"+
            "公会会长让你加入，或者教你法术。"+
            "例如，你可以\"ask herkimer to join\"或"+
            "\"ask herkimer to teach missile\"。魔法商店"+
            "在北边。"
            "\n%^GREEN%^这里有一个你可以阅读的法术列表。%^RESET%^");
    SetItems( ([
                ({"list","list on the wall"}) : "一个可用法术的列表",
                ]) );
    SetInventory(([
                "/domains/town/npc/herkimer" : ({60, 1}),
                ]));
    SetRead(({"list","list on wall"}) , (: ReadList :) );
    SetExits( ([
                "north" : "/domains/town/room/magic_shop"
                ]) );

}
void init(){
    ::init();
}
