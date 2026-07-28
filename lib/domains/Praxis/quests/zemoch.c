inherit "/std/quest_ob";

void create() {
    ::create();
    set_name("zemoch");
    set_id( ({ "zemoch", "quest_object", "zemoch quest" }));
    set_short("泽莫克任务");
    set_long(
            "你必须阻止邪恶的泽莫克人继续献祭无辜者。\n"
            "帮助他人将有助于你摧毁泽莫克人的邪神阿扎什。\n"
            "任务等级：高等凡人，极其困难\n" );
    set_quest_points(45);
}
