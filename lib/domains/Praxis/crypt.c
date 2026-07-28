#include <lib.h>

#define PH "/realms/drakken/clerics/"
#define SAVE_FILE "/domains/Praxis/data/cleric_crypt"
#define WHAMMER "/realms/zaknaifen/weap/whammer"
#define PHYL "/realms/zaknaifen/armor/phylactery"

inherit LIB_ROOM;

int prayers,is_hammer,is_phyl;

void create() {
    ::create();
    prayers = 0;
    is_hammer = 0;
    is_phyl = 0;
    RestoreObject(SAVE_FILE);	// restore is_hammer and is_phyl
    SetProperties(([
                "no attack": 1,
                "no steal":1,
                "no castle":1,
                "holy ground":1,
                "light"   : 2,
                "indoors" : 1,
                ]));
    SetShort("一个小地窖");
    SetLong("祭坛室是从普拉克西斯所依靠的古老灰色石头中雕刻出来的。"
            "墙壁上燃烧的蜡烛使影子在房间里以混乱而迷人的方式舞动。"
            "一个大祭坛从房间中央的地面升起，雕刻在石头中的台阶向上延伸。");
    SetExits( ([
                "up" : "/domains/Praxis/cleric_hall"
                ]) );
    SetItems(([
                "altar":(: this_object(), "exaaltar" :),
                "scenes" : "你看到坦波斯在各种战斗中挥舞着他强大的%^CYAN%^战锤%^RESET%^，"
                "这些战斗你从宗教学习中认出来了。",
                ({"stones","stone"}):
                "冰冷的灰色石头被用来雕刻这个地下房间的工具弄得皱巴巴的。",
                ({"shadows","shadow"}):
                "影子随着闪烁的烛光音乐迷人地在房间里舞动。",
                "steps" :  "台阶雕刻在灰色石头中，因岁月中无数脚步的踩踏而磨损。",
                ({"walls","wall"}):
                "墙壁是从普拉克西斯地下的石头粗凿而成，排列着许多闪烁的蜡烛。",
                ({"candle","candles"}):
                "蜡烛放在沿墙设置的铁架上，由动物脂肪制成。"
                "烛光随风摇曳，创造出影子嬉戏舞蹈的音乐。",
                "stands" : "支架由%^BLACK%^%^BOLD%^黑色%^RESET%^铁制成，结构简单。"
                "每个支架上放着三到四支点燃的蜡烛。",
                    ]));
}

void exaaltar() {
    string str;

    str = "祭坛由古老的灰色石头制成，非常巨大。祭坛两侧雕刻着坦波斯与神话野兽战斗的场景。"
        "祭坛顶部是平的，上面有用%^YELLOW%^金色%^RESET%^描绘的锤子图案。";
    if (is_hammer) str += "%^CYAN%^战锤%^RESET%^放在上面，完美地嵌入痕迹之中。";
    if (is_phyl) str += "一个%^YELLOW%^金色%^RESET%^护符盒部分遮住了痕迹。";
    write(str);
}

void reset()
{
    ::reset();
    if (!present("box")) {
        //new(PH "obj/donation")->move(this_object());
    }
    prayers = 0;
}

void init()
{
    ::init();
    add_action("pray_func","pray");
}

int pray_func(string str) {
    object ob, ob2, *inv;
    string limb;
    int i,j;

    ob = this_player();
    inv = all_inventory(ob);
    for (i=0; i<sizeof(inv); i++) {
        if ((!str || strlen(str) == 0) && inv[i]->id("hammer of tempos") && is_hammer == 0) {
            tell_room(this_object(),ob->query_cap_name()+"在祭坛前低声祈祷。当"+
                    nominative(ob)+"祈祷时，一个半神的影子出现在祭坛上。"
                    "你感受到暗影的力量，分享着他在祈祷中的喜悦，因为你注意到"
                    "这个影子是坦波斯本人的化身！"
                    "坦波斯注意到"+ob->query_cap_name()+"携带着他的%^CYAN%^战锤%^RESET%^并将其取走！"
                    "暗影消散后，%^CYAN%^战锤%^RESET%^出现在祭坛上。",ob);
            tell_object(ob,"你在祭坛前低声祈祷。当你祈祷时，一个半神的影子出现在祭坛上。"
                    "你感受到暗影的力量，跟着重复祈祷，因为你注意到"
                    "这个影子是坦波斯本人的化身！"
                    "坦波斯注意到你携带着他的%^CYAN%^战锤%^RESET%^并将其取走！"
                    "暗影消散后，%^CYAN%^战锤%^RESET%^出现在祭坛上。");
            is_hammer = 1;
            SaveObject(SAVE_FILE);	// save is_hammer
            inv[i]->destruct();
            return 1;
        } else if ((!str || strlen(str) == 0) && inv[i]->id("hammer of tempos") && is_hammer == 1) {
            tell_room(this_object(),ob->query_cap_name()+"在祭坛前低声祈祷。当"+
                    nominative(ob)+"祈祷时，一个半神的影子出现在祭坛上。"
                    "你感受到暗影的力量，分享着他在祈祷中的喜悦，因为你注意到"
                    "这个影子是坦波斯本人的化身！"
                    "坦波斯注意到"+ob->query_cap_name()+"携带着他的%^CYAN%^战锤%^RESET%^并将其取走！",ob);
            tell_object(ob,"你在祭坛前低声祈祷。当你祈祷时，一个半神的影子出现在祭坛上。"
                    "你感受到暗影的力量，跟着重复祈祷，因为你注意到"
                    "这个影子是坦波斯本人的化身！"
                    "坦波斯注意到你携带着他的%^CYAN%^战锤%^RESET%^并将其取走！");
            inv[i]->destruct();
            return 1;
        }
        if ((!str || strlen(str) == 0) && inv[i]->id("phylactery") && is_phyl == 0) {
            tell_room(this_object(),ob->query_cap_name()+"在祭坛前低声祈祷。当"+
                    nominative(ob)+"祈祷时，一个半神的影子出现在祭坛上。"
                    "你感受到暗影的力量，分享着他在祈祷中的喜悦，因为你注意到"
                    "这个影子是坦波斯本人的化身！"
                    "坦波斯注意到"+ob->query_cap_name()+"携带着他的护符盒并将其取走！"
                    "暗影消散后，护符盒出现在祭坛上。",ob);
            tell_object(ob,"你在祭坛前低声祈祷。当你祈祷时，一个半神的影子出现在祭坛上。"
                    "你感受到暗影的力量，跟着重复祈祷，因为你注意到"
                    "这个影子是坦波斯本人的化身！"
                    "坦波斯注意到你携带着他的护符盒并将其取走！"
                    "暗影消散后，护符盒出现在祭坛上。");
            is_phyl = 1;
            SaveObject(SAVE_FILE);	// save is_phyl
            inv[i]->destruct();
            return 1;
        } else if ((!str || strlen(str) == 0) && inv[i]->id("phylactery") && is_phyl == 1) {
            tell_room(this_object(),ob->query_cap_name()+"在祭坛前低声祈祷。当"+
                    nominative(ob)+"祈祷时，一个半神的影子出现在祭坛上。"
                    "你感受到暗影的力量，分享着他在祈祷中的喜悦，因为你注意到"
                    "这个影子是坦波斯本人的化身！"
                    "坦波斯注意到"+ob->query_cap_name()+"携带着他的护符盒并将其取走！",ob);
            tell_object(ob,"你在祭坛前低声祈祷。当你祈祷时，一个半神的影子出现在祭坛上。"
                    "你感受到暗影的力量，跟着重复祈祷，因为你注意到"
                    "这个影子是坦波斯本人的化身！"
                    "坦波斯注意到你携带着他的护符盒并将其取走！");
            inv[i]->destruct();
            return 1;
        }
    }
    if (is_hammer) {
        j = 0;
        for (i=0; i<sizeof(inv); i++)
            if (inv[i]->id("hammer of tempos")) {
                j = 1;
                break;
            }
        if (str == "for warhammer" && j == 0 && ob->query_alignment() >= 1000 && ob->query_level() > 5) {
            ob2 = new(WHAMMER);
            if (ob2) {
                tell_room(this_object(),ob->query_cap_name()+"在祭坛前低声祈祷。当"+
                        nominative(ob)+"祈祷时，一个半神的影子出现在祭坛上。"
                        "你感受到暗影的力量，分享着他在祈祷中的喜悦，因为你注意到"
                        "这个影子是坦波斯本人的化身！"
                        "坦波斯注意到祭坛上的%^CYAN%^战锤%^RESET%^并将其交给了"+ob->query_cap_name()+"！",ob);
                tell_object(ob,"你在祭坛前低声祈祷。当你祈祷时，一个半神的影子出现在祭坛上。"
                        "你感受到暗影的力量，跟着重复祈祷，因为你注意到"
                        "这个影子是坦波斯本人的化身！"
                        "坦波斯注意到祭坛上他的%^CYAN%^战锤%^RESET%^并将其交给了你！");
                tell_room(this_object(),"祈祷结束后，暗影消失了。",({}));
                is_hammer = 0;
                SaveObject(SAVE_FILE);	// save is_hammer
                ob2->move(ob);
                return 1;
            }
        }
    }
    if (is_phyl) {
        j = 0;
        for (i=0; i<sizeof(inv); i++)
            if (inv[i]->id("phylactery")) {
                j = 1;
                break;
            }
        if (str == "for phylactery" && j==0 && ob->query_alignment()>=800 && ob->query_level()>5 && ob->query_skill("faith")>50) {
            ob2 = new(PHYL);
            if (ob2) {
                tell_room(this_object(),ob->query_cap_name()+"在祭坛前低声祈祷。当"+
                        nominative(ob)+"祈祷时，一个半神的影子出现在祭坛上。"
                        "你感受到暗影的力量，分享着他在祈祷中的喜悦，因为你注意到"
                        "这个影子是坦波斯本人的化身！"
                        "坦波斯注意到祭坛上的护符盒并将其交给了"+ob->query_cap_name()+"！",ob);
                tell_object(ob,"你在祭坛前低声祈祷。当你祈祷时，一个半神的影子出现在祭坛上。"
                        "你感受到暗影的力量，跟着重复祈祷，因为你注意到"
                        "这个影子是坦波斯本人的化身！"
                        "坦波斯注意到祭坛上他的护符盒并将其交给了你！");
                tell_room(this_object(),"祈祷结束后，暗影消失了。",({}));
                is_phyl = 0;
                SaveObject(SAVE_FILE);	// save is_phyl
                ob2->move(ob);
                return 1;
            }
        }
    }
    if (prayers < 7) {
        tell_room(this_object(),ob->query_cap_name()+"在祭坛前低声祈祷。当"+
                nominative(ob)+"祈祷时，一个半神的影子出现在祭坛上。"
                "你感受到暗影的力量，分享着他在祈祷中的喜悦，因为你注意到"
                "这个影子是坦波斯本人的化身！",ob);
        tell_object(ob,"你在祭坛前低声祈祷。当你祈祷时，一个半神的影子出现在祭坛上。"
                "你感受到暗影的力量，跟着重复祈祷，因为你注意到"
                "这个影子是坦波斯本人的化身！");
        tell_room(this_object(),"祈祷结束后，暗影消失了。",({}));
        if (random(100) <(15+ob->query_base_stats("charisma"))) ob->add_alignment(random(3)+10-prayers);
    } else {
        limb = ob->return_limb();
        tell_room(this_object(),ob->query_cap_name()+"在祭坛前低声祈祷。当"+
                nominative(ob)+"祈祷时，一个半神的影子出现在祭坛上。"
                "你感受到暗影的力量和他在你心中激起的恐惧！"
                "这个影子再次是坦波斯本人的化身，但这一次他对如此频繁的打扰感到厌烦！"
                "他挥动战锤攻击了"+ob->query_cap_name()+
                "！"+ ( is_hammer ?
                    "这一次战锤是真的！\n坦波斯用他的%^CYAN%^战锤%^RESET%^在"+limb+
                    "中彻底摧毁了"+ob->query_cap_name()+"！"
                    : "幸运的是"+objective(ob)+"的战锤也是影子，因此伤害很小。"
                    ) ,ob);
        tell_room(this_object(),"坦波斯认为"+ob->query_cap_name()+"不值得他费心，便消失了。",ob);
        tell_object(ob,"你在祭坛前低声祈祷。当你祈祷时，一个半神的影子出现在祭坛上。"
                "你感受到暗影的力量和他在你心中激起的恐惧！"
                "这个影子再次是坦波斯本人的化身，但这一次他对如此频繁的打扰感到厌烦！"
                "他挥动战锤攻击了你！"
                + ( is_hammer ?
                    "这一次战锤是真的！\n坦波斯用他的%^CYAN%^战锤%^RESET%^在"+limb+
                    "中彻底摧毁了你！"
                    : " 幸运的是战锤也是影子，因此伤害很小。"
                  ) );
        ob->do_damage(limb,5+random(prayers)+is_hammer*25);
        tell_object(ob,"坦波斯认为你不值得他费心，便消失了。");
    }
    prayers++;
    return 1;
}
