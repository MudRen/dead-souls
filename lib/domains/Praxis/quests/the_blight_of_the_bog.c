inherit "/std/quest_ob";

void create() {
    ::create();
    set_name("the_blight_of_the_bog");
    set_id( ({"blight", "quest_object", "the blight of the bog"}) );
    set_short( "%^GREEN%^%^BOLD%^沼泽之灾任务%^RESET%^");
    set_long( "有传言说一种奇怪的疾病正在肆虐北方森林的部分区域。"
            "你必须找到这种疾病的源头，并想出办法在它摧毁"
            "沼泽周围的整片森林之前治愈这场可怕的灾难。\n"
            "任务等级：高等凡人");
    set_quest_points(40);
}
