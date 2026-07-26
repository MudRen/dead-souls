#include <lib.h>
inherit LIB_ROOM;

string ReadList(){
    string muggleret = "AVAILABLE SPELLS:\n\n"
        "\tfireball, cost 1000:\tput the hurt on an opponent\n"
        "\tmissile, cost 500:\tCheaper and easier to learn than fireball\n"
        "\tbuffer, cost 200:\tconjure an invisible shield around you\n"
        "\tmeditate, cost 500:\tconjure an aura that speeds stamina recovery\n"
        "\n"
        "Example: If you want to learn the buffer spell:\n\n"
        "\"ask herkimer to teach buffer\"\n"
        "\n"
        "Please note that the spell may fail many times before "
        "you have enough practice and experience to cast "
        "it properly. All sales final.\n";
    string mageret = "AVAILABLE SPELLS:\n\n"
        "\tfireball:\tput the hurt on an opponent\n"
        "\tgreater fireball:\tput the serious hurt on an opponent\n"
        "\tmissile:\tCheaper and easier to learn than fireball\n"
        "\tlight:\t\tMakes you glow brightly enough to see in the dark.\n"
        "\tbuffer:\t\tconjure an invisible shield around you\n"
        "\tgreater buffer:\t\tconjure a powerful invisible shield around you\n"
        "\tmeditate:\tconjure an aura that speeds stamina recovery\n"
        "\twhip:\t\tconjure a powerful energy whip\n"
        "\n"
        "Example: If you want to learn the buffer spell:\n\n"
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
    SetLong("这里是当地的法师公会。你可以在这里请求公会会长让你加入，或者教你法术。例如，你可以 \"ask herkimer to join\" 或 \"ask herkimer to teach missile\"。魔法商店在北边。\n%^GREEN%^这里有一份你可以阅读的法术清单。%^RESET%^");
    SetItems( ([
                ({"list","list on the wall"}) : "一份可用法术的清单",
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
