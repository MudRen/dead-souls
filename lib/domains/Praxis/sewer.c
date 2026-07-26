
inherit "/lib/std/room";

void create() {
    ::create();
    SetProperty("light", -1);
    SetProperty("indoors", 1);
    SetShort( "一条令人作呕的下水道");
    SetLong(
            "普拉克西斯地下的这些下水道里满是黏液。"
           );
    SetItems(
            (["sewers" : "普拉克西斯地下的恶心人类排泄物隧道。",
             "slime" : "恶心，太恶心了。",
             ({"wall", "east wall"}) : "一面沾满黏液的恶心墙壁。",
             "ceiling" : "一个沾满黏液的恶心天花板。",
             ]));
    SetExits(
            (["west" : "/domains/Praxis/sewer_ent", 
             ]));
}
void init(){
    ::init();
}
