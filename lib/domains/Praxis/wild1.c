inherit "/lib/std/room";

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetShort( "普拉克西斯郊外的荒野");
    SetLong(
            "村庄外的植被随着你向东行进而变得茂密，形成了丛林。");
    SetItems(
            (["jungle" : "一片充满亡命之徒和神秘事物的荒野区域。",
             "village" : "冒险者的城镇普拉克西斯。",
             "vegetation" : "向东越来越茂密。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["east" : "/domains/Praxis/wild2",
             "west" : "/domains/Praxis/e_boc_la3"]) );
}
void init(){
    ::init();
}
