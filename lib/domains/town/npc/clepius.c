#include <lib.h>

inherit LIB_NPC;

object *slips;
int busy;

protected void create() {
    npc::create();
    SetKeyName("clepius");
    SetId(({"clepius","doctor","healer"}));
    SetAdjectives(({"a.s.", "A.S.", "doctor","dr","Dr.","dr."}));
    SetShort("治疗师克勒皮乌斯");
    SetLong("克勒皮乌斯是一位善良的老人，以他近乎超人的治疗能力而闻名。"+
            "甚至有传言说他能够复活死者。他在镇上经营医疗服务，"+
            "需要时可以向他求助，但他的帮助不是免费的。");
    SetLevel(50);
    SetRace("human");
    SetClass("mage");
    SetGender("male");
    SetInventory(([
                "/domains/town/weap/rod":1,
                "/domains/town/obj/medbag":1,
                "/domains/town/armor/toga":"wear toga",
                ]) );
    slips = ({});
    busy=0;
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
    SetCustomXP(10);
}

void init(){
    ::init();
}

int CanReceive() {
    if(present("healer token", this_object())){
        return 0;
    }

    eventForce("nod");
    set_heart_beat(1);
    return 1;
}

int CheckBag(){
    object bag,slip;
    string player, problem;
    slip = present("healer token", this_object());
    if(!slip && busy == 1) {
        eventForce("say 这有点奇怪...\n\n");
        eventForce("抱歉，我一定是把你的单子放错地方了。你还有另一张吗？");
        busy = 0;
        return 1;
    }
    if(slip){
        busy = 1;
        eventForce("say 嗯嗯...");
        problem = slip->GetProperty("problem");
        player = slip->GetPatient();
        this_object()->DiagPatient(player,problem);
    }
    return 1;
}

void heart_beat(){
    if(busy == 0 && present("healer token", this_object())){
    }

    this_object()->CheckBag();
}

int ejectRabble(string str){
    object *riffraff,patient;
    environment()->SetProperty("busy",1);
    riffraff = get_livings(environment(this_object()));
    if(! patient = present(str,environment(this_object())) ){
        patient = find_player(str);
    }
    foreach(object bum in riffraff){
        if( bum->GetKeyName() != patient->GetKeyName() &&
                bum->GetKeyName() != "clepius" ){
            tell_object(bum,"The doctor ejects you from his office in order to "+
                    "treat "+patient->GetName()+".\n\n");
            bum->eventMoveLiving("/domains/town/room/healer");
            tell_object(patient,"The doctor ejects "+bum->GetName()+" from "+
                    "his office in order to treat you.");
        }
    }
    return 1;
}

int NextPatient(){
    eventForce("put my first slip in bin");
    environment()->SetProperty("busy",0);
    tell_room(load_object("/domains/town/room/healer"),"从后面的房间里"+
            "你听到医生喊道：\"%^BOLD%^CYAN%^下一位！%^RESET%^\"");
    tell_room(environment(),"医生探进东边的门口"+
            "喊道：\"%^BOLD%^CYAN%^下一位！%^RESET%^\"");
    busy = 0;
    environment()->SetProperty("busy",0);
    return 1;

}

int PerformHeal(string dude){
    object person;
    int hp,mhp;
    person = present(dude,environment());
    if(!person) {
        eventForce("look");
        eventForce("shrug");
        return 1;
    }
    eventForce("say 好吧...让我看看你。");
    hp = person->GetHealthPoints();
    mhp = person->GetMaxHealthPoints()-10;
    if(hp > mhp){
        eventForce("say 你看起来没事。把你的单子收回去，留到真正需要的时候再用。");
        eventForce("give my first slip to "+dude);
        return 1;
    }
    if(present("clepius mojo",person)){
        eventForce("say 你身上已经有药膏了。让它发挥作用，然后再回来。");
        eventForce("give my first slip to "+dude);
        return 1;
    }
    eventForce("say 是的，你可以接受一点治疗。");
    tell_room(environment(),"克勒皮乌斯用力地将治疗药膏涂抹在你身上。你能感觉到它在加速你身体的恢复。");
    new("/secure/obj/mojo")->eventMove(person);
    return 1;
}

int PerformRegenerate(string dude){
    int i;
    mapping stumps;
    object person;
    person = present(dude,environment());
    stumps=person->GetMissingLimbs();

    eventForce("say 那让我们数数四肢吧。嗯嗯嗯...");

    if(!sizeof(stumps)) {
        eventForce("say 你没有缺胳膊少腿。把这张单子卖给詹姆斯吧。");
        eventForce("give my first slip to "+dude);
        return 1;
    }
    for(i=0;i<sizeof(stumps);i++){
        person->RestoreLimb(stumps[i]);
        tell_object(person,"The doctor regenerates your "+stumps[i]+".");
        return 1;
    }
}

int PerformExcision(string dude){
    string what,whom;
    object person,thing,slug;
    int firearms_wounds, wounds;

    person = present(dude,environment(this_object()));
    slug=present("firearms_wound",person);
    wounds=0;
    wounds=person->GetLead();
    if(!slug){
        eventForce("say 你体内没有异物。");
        eventForce("give my first slip to "+dude);
        return 1;
    }

    tell_room(environment(this_object()),"克勒皮乌斯灵巧地从"+dude+"体内取出了一个铅弹。", ({person}));
    tell_object(person,"克勒皮乌斯灵巧地从你体内取出了一个铅弹。");
    slug=new("/domains/town/obj/spent");
    if(wounds > 0) {
        person->AddLead("firearms_wounds", -1);
        slug->SetShort("a spent firearm slug");
        --wounds;
        slug->eventMove(this_object());
        if(person->GetLead() < 1){                                         
            slug=present("firearms_wound",person);
            if(slug) slug->eventDestruct();
        }
        return 1;
    }

    slug->eventMove(this_object());
    slug=present("firearms_wound",person);
    if(wounds < 1 && slug){                                 
        slug->eventDestruct();
    }
    return 1;
}

int DiagPatient(string dude, string problem){
    if(!present(dude,environment())) {
        NextPatient();
        return 1;
    }

    ejectRabble(dude);

    if(problem == "regenerate") {
        PerformRegenerate(dude);
        NextPatient();
    }
    if(problem == "heal"){
        PerformHeal(dude);
        NextPatient();
    }
    if(problem == "excise"){
        PerformExcision(dude);
        NextPatient();
    }
    return 1;
}

