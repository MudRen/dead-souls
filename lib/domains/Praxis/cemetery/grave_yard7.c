inherit "/lib/std/room";
object coffin;

void create() {
    ::create();
    SetProperty("light", 0);
    SetShort( "坟墓");
    SetLong(
            "你愚蠢地爬进了普拉克西斯创始人之一的古老坟墓。"
            "你正站在一口棺材关闭的下门上。"
            "上门敞开着，令人毛骨悚然地诱人。"
            "土壤以幽闭恐惧症般的方式压在你周围。");
    SetItems(
            (["under" : "你不能往棺材下面看，你正站在上面。",
             "soil" : "坟墓的土墙很软，散发着泥土的气味。",
             "grave" : "坟墓空荡荡的，令人恐惧和悲伤。"]) );
    SetExits( 
            ([ "up" :	"/domains/Praxis/cemetery/grave_yard2"]) );
}
void init(){
    ::init();
} 
