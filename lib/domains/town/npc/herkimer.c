#include <lib.h>
#include <daemons.h>

inherit LIB_LEADER;
int JoinGuild(object ob, string verb, string what);
int TeachSpell(object who, string verb, string spell);

string *spells;
mapping AvailableSpells, RestrictedSpells;

int WieldStaff(){
    if(!present("staff",this_object())){
        new("/domains/town/weap/leostaff")->eventMove(this_object());
        tell_room(environment(),"赫克默拍了拍手，一根大"+
                "木杖凭空出现。");
        this_object()->eventForce("wield staff");
        this_object()->eventForce("say 你这可怜的傻瓜！");
        this_object()->eventForce("cast buffer");
    }
    return 1;
}

protected void create() {
    leader::create();
    SetKeyName("herkimer");
    SetId(({"archwizard","wizard","herkermer","herkirmer"}));
    SetAdjectives(({"old","gentle","kindly"}));
    SetShort("善良的巫师赫克默");
    SetLong("这位善良的老巫师是当地魔法商店的主人，"+
            "这里同时也是法师公会。你可以请赫克默教你法术，"+
            "如果你有能力学习，他会教你，但要收费。"+
            "他那锐利的蓝眼睛似乎能看穿你，"+
            "但他白胡子下的微笑让人感到安心。");
    SetLevel(300);
    SetUnique(0);
    SetRace("human");
    SetGender("male");
    SetClass("mage");
    SetInventory(([
                "/domains/town/armor/robe":"wear robe",
                "/domains/town/armor/wizard_hat":"wear hat",

                ]));
    SetSpellBook( ([ "buffer" : 100, "meditate" : 100, "missile" : 100, "fireball" : 100, "whip" : 100 ]) );
    SetAction(5, ({
                "赫克默若有所思地挠了挠胡子。",
                "赫克默似乎在努力回忆什么。", "赫克默沉思着。",
                "赫克默思考着。", "赫克默仔细思考着。",
                "赫克默说：\"%^BOLD%^CYAN%^你不必成为法师也能学习法术，但成为法师确实有帮助。%^RESET%^\"",
                "赫克默说：\"%^BOLD%^CYAN%^你越多使用魔法技能，就会变得越熟练。%^RESET%^\"",
                "赫克默说：\"%^BOLD%^CYAN%^施放法术会消耗你的法力值。确保你不会意外耗尽！%^RESET%^\"",
                "赫克默说：\"%^BOLD%^CYAN%^如果你加入我们然后又离开公会，你将不再被允许成为法师。%^RESET%^\"",
                "赫克默说：\"%^BOLD%^CYAN%^有些法术需要完全集中注意力。如果你移动或被攻击，可能会打断施法。%^RESET%^\"",
                "赫克默说：\"%^BOLD%^CYAN%^当然，所有魔法训练对公会成员都是免费的。%^RESET%^\"",
                }));
    SetCombatAction(50, ({ (: WieldStaff :), "say 你想干什么？",
                "say 别逼我毁了你","cast fireball", "cast missile", "cast buffer"}) );
    SetCommandResponses( ([
                "join": (: JoinGuild :),
                "teach" : (: TeachSpell :),
                "learn" : "我还有很多要学的，年轻人，但不是从你那里学。",
                ]) );
    AvailableSpells = ( ([
                "fireball" : 1000,
                "greater fireball" : 3000,
                "light" : 100,
                "missile" : 500,
                "buffer" : 200,
                "greater buffer" : 2000,
                "meditate" : 500,
                "whip" : 10000,
                ]) );
    RestrictedSpells = ( ([
                "greater fireball" : 3000,
                "light" : 100,
                "greater buffer" : 2000,
                "whip" : 10000,
                ]) );
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
    SetCustomXP(10);
}

void init(){
    string key;
    int val;
    ::init();
    spells = ({});
    foreach(key,val in AvailableSpells){
        spells += ({ key });
    }
}

int JoinGuild(object ob, string verb, string what){
    if(ob->GetClass() == "mage") {
        eventForce("say 你已经是成员了，笨蛋。");
        return 1;
    }
    eventForce("say 嗯...想加入我们的公会，是吗？");

    if(!this_player()->GetQuest("Orc Slayer Quest")){
        eventForce("say 首先你必须证明自己的价值。帮助我的兄弟里奥找到屠兽者之剑，我会很高兴地欢迎你加入我们的大家庭。在那之前，你不能加入法师公会。");
        return 1;
    }
    if(ob->GetClass() == "explorer" || !ob->GetClass()){
        eventForce("say 很好，"+ob->GetName()+"。");
        eventForce("say 欢迎加入法师公会！现在你*非常*有魔法了！你必须经常练习魔法，因为你现在比以前体弱了。你的魔法越强，你就越强！");
        ob->ChangeClass("mage");
#if 0
        if(ob->GetLevel() == 1){
            eventForce("say you have been demoted to a Level 1 player. However, you still retain your experience and your questing history, so just ask Dirk to promote you again a few times.");
        }
#endif
        return 1;
    }
    eventForce("say 抱歉，在我看来你已经选择了你的专业。作为公会会长公会的成员，我不能把你从"+capitalize(ob->GetClass())+"公会中除名。");
    return 1;
}

int TeachSpell(object who, string verb, string spell){
    int cost, onhand;
    mapping myspells;
    if(!spell || spell == ""){
        eventForce("say 请再问一次，这次请指定你想学的法术。");
        return 1;
    }
    if(!SPELLS_D->GetSpell(spell)){
        eventForce("say 抱歉，那不是我能教你的法术。");
        return 1;
    }
    if(who->GetClass() != "mage" &&
            member_array(spell, keys(RestrictedSpells)) != -1){
        eventForce("那个法术仅限公会成员学习。");
        return 1;
    }
    if(member_array(spell,spells) == -1){
        eventForce("say 那个法术现在不可用。");
        eventForce("say 我能教你的法术有 "+implode(spells,", ")+"。");
        return 1;
    }
    myspells = who->GetSpellBook();
    if(myspells[spell]){
        eventForce("say 你已经知道那个法术了。");
        return 1;
    }
    cost = AvailableSpells[spell];
    onhand = who->GetCurrency("silver");
    if(who->GetClass() != "mage" && onhand < cost) {
        eventForce("say 你没有足够的银币来支付那个法术。");
        eventForce("say "+spell+"需要"+cost+"银币，而你"+
                "只有"+onhand+"。");
        eventForce("say 我只接受银币。这是魔法的需要。如果你愿意，你可以试着在街对面的银行把其他货币兑换成银币。");
        return 1;
    }
    tell_room(environment(this_object()),"赫克默闭上眼睛，低声念叨着，挥动着双手。");
    if(!who->eventLearnSpell(spell)){
        eventForce("shake");
        eventForce("say 你现在似乎没有能力学习那个法术。");
        return 1;
    }
    eventForce("smile");
    eventForce("say 恭喜你。你现在掌握了"+spell+"法术的神秘知识。明智地使用它。");
    if(who->GetClass() != "mage") who->AddCurrency("silver",-cost);
    return 1;
}

int eventReceiveObject() {
    object ob, player;
    ob = previous_object();
    player = this_player();

    if( !ob || !::eventReceiveObject() ) return 0;
    if( ob->GetKeyName() == "orc slayer" ) {
        eventForce("say 抱歉，你找错大巫师了。");
        eventForce("say 你要找的是里奥。他的工作室在教堂地下室。");
        eventForce("give orcslayer to "+this_player()->GetKeyName());
        return 1;
    }

    AddCarriedMass(ob->GetMass());
    return 1;
}
