inherit "/lib/std/room";

void create() {
    ::create();
    SetProperty("light", 2);
    SetShort( "丛林");
    SetLong(
            "丛林的湿度不断增加。"
            "从四面八方向你逼近的植被在北边和东边变得更加茂密。"
            "向南和向西看则显得温和一些。");
    SetItems(
            (["jungle" : "一片充满绿色植被的不断增长的雨林。",
             "vegetation" : "各种你从未见过的植物在此生长。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["northeast" : "/domains/Praxis/rain_forest",
             "southwest" : "/domains/Praxis/wild2"]) );
}
void init(){
    ::init();
}
