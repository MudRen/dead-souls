inherit "/lib/std/room";

void create() {
    ::create();
    SetProperty("light", 0);
    SetShort( "地上的一个洞");
    SetLong(
            "你在地上的一个深洞里。这里的光线非常微弱。");
    SetNoClean(1);
    SetExits( ([ ]) );
}

void fixing_a_hole() {
    RemoveItem("hole");
    RemoveExit("up");
}

void digging() {
    AddItem("hole", "一个通往地面的洞。");   AddExit( "up", "/domains/Praxis/west_road2");

}

void reset() {
    object money;
    ::reset();
    if(!present("match"))
        new("/domains/Praxis/obj/misc/match")->move(this_object());
    if(!present("money")) {
        money = new("/lib/pile");
        money->SetCurrency("platinum", random(5));
        money->SetCurrency("silver", random(100));
        money->SetCurrency("copper", random(1000));
        money->move(this_object());
    }
}
void init(){
    ::init();
}
