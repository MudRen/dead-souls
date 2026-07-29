#include <lib.h>
inherit LIB_BOT;
inherit LIB_ACTIVATE;

object player, bot, ob, noobster;
nosave string name, watchline;
nosave int count, active, tip, tipnumber, current_tip, hb, mooch, greeting, greetwait;
string *watchlist = ({});
nosave string save_file = save_file("/domains/campus/save/jennybot");

mixed GreetingResponse(object who, mixed foo, string message, mixed bar){
    message = lower_case(message);
    if(!strsrch(message, "hi") || !strsrch(message, "hello") ||
            !strsrch(message, "hey") || !strsrch(message, "sup")){
        tell_player(who,"这位女士没有回应你的问候，"+
                "但你觉得你可以：\n%^BOLD%^look at woman%^RESET%^");
    }
    return 1;
}

string LongDesc(){
    string ret;
    if(!active){
        ret = "仔细一看，这位迷人的年轻女士根本不是女士……她是一个安卓机器人！她似乎完全静止不动，脸上挂着友好的微笑。也许你可以通过输入 %^RED%^activate bot%^RESET%^ 让她做些什么。";
    }
    else {
        ret = "仔细一看，这位迷人的年轻女士根本不是女士……她是一个安卓机器人！她似乎正在为这个MUD做新人指导，带着异常友好的举止。也许你可以通过输入 %^RED%^deactivate bot%^RESET%^ 让她安静下来。";
    }
    return ret;
}


protected void create(){
    watchlist = ({});
    ::create();
    RestoreObject(save_file);
    SetKeyName("jennybot");
    SetId(({"guide","guidebot","fembot","bot","jennifer","niffy","android","jenny","robot","woman","lady"}));
    SetAdjectives(({"orientation","young","female","polite","pretty","guide","newbie","simple","extremely"}));
    SetGender("female");
    SetShort("一位彬彬有礼的年轻女士");
    SetLong( (: LongDesc :) );
    SetInventory(([
                "/domains/campus/armor/pillbox_hat" : "wear hat",
                "/domains/campus/armor/wglove_r" : "wear white right glove",
                "/domains/campus/armor/wglove_l" : "wear white left glove",
                "/domains/campus/armor/necklace" : "wear necklace on neck",
                "/domains/campus/armor/bluedress" : "wear dress",
                ]));
    SetMelee(1);
    SetPolyglot(1);
    SetLevel(99);
    SetRace("android");
    SetAction(1, ({
                "珍妮理了理她的头发。",
                "导游机器人珍妮稍微补了补妆。",
                "珍妮微笑着。"}));
    AddCommandResponse("shutdown", (: eventTurnOff :));
    AddCommandResponse("shut down", (: eventTurnOff :) );
    AddCommandResponse("shut up", (: eventTurnOff :));
    AddCommandResponse("go away", (: eventTurnOff :) );
    SetTalkResponses( ([
                "hi" : (: GreetingResponse :),
                "hey" : (: GreetingResponse :),
                "sup" : (: GreetingResponse :),
                "hello" : (: GreetingResponse :),
                ]) );
    set_heart_beat(1);
    ob=this_object();
    count=210;
    tip=0;
    tipnumber = 16;
    greeting = 0;
    greetwait = 0;
    SetLanguage("common",100);
    SetDefaultLanguage("common");
}

varargs int eventGreet(string newbie){
    object noob;
    string guy,prespiel,spiel;
    if((!newbie || newbie == "") || !noobster){
        return 0;
    }
    if(!newbie || newbie == "") newbie = noobster->GetKeyName();
    if(newbie && newbie != "there") noob = find_player(newbie);
    if(noob && newbie != "there") guy = noob->GetName();
    else guy = "there";
    tell_room(environment(this_object()),"这位彬彬有礼的年轻女士突然活了过来！\n");
    prespiel = "珍妮机器人说，\"%^BOLD%^CYAN%^ 你好，"+guy;
    spiel = read_file("/domains/campus/txt/jenny/spiel.txt");
    tell_room(environment(this_object()),prespiel+spiel);
    tell_room(environment(this_object()),"\n\t%^RED%^activate bot%^RESET%^（激活机器人）\n");
    eventForce("yell DEDDA SORUZE: GETTO DA ZE!");
    tell_room(environment(this_object()),"这位彬彬有礼的年轻女士再次变得一动不动。");
    noob->SetProperty("greeted",1);
    return 1;
}

int eventCheckNoob(){
    object* people;
    people=(get_livings(environment(this_object()),1));
    if(sizeof(people)){
        foreach(object dude in people){
            int greeted;
            greeted = dude->GetProperty("greeted");
            if(!greeted && dude->GetLevel() < 2 ) {
                greeting = 1;
                noobster = dude;
            }
        }
    }
    return 1;
}

void init(){
    ::init();
    add_action("next_tip","next");
    eventCheckNoob();
}

int next_tip(string str){
    if(!str) return 0;
    if(str=="") return 0;
    if(str="tip"){
        if(active != 1) { write("珍妮机器人未激活。"); return 1; }
        if(tip == tipnumber) ob->eventForce("say 抱歉，没有更多提示了。");
        else {
            this_object()->eventDoTip(tip);
        }
        return 1;
    }
}

int refreshlist(){
    string playername;
    playername = this_player()->GetKeyName();
    if(watchlist && member_array(playername, watchlist) != -1) mooch = 1;
    else {
        if(!watchlist) watchlist = ({});
        watchlist += ({ playername });
        mooch = 0;
    }
    watchlist = distinct_array(watchlist);
    SaveObject(save_file,1);
    return 1;
}

int eventTurnOff(mixed arg){
    if( active == 0 ){
        write("珍妮机器人已经处于未激活状态。");
    }
    tip = 0;
    if( active != 0) {
        eventForce("yell DEDDA SORUZE: GETTO DA ZE!");
        tell_room(environment(this_object()),"珍妮点了点头，再次变得一动不动，"+
                "她的表情凝固了，目光呆滞地望向前方。");
    }
    active=0;
    return 1;
}

int eventTurnOn(mixed arg){
    if(!ob) ob = this_object();
    player=this_player();
    name=this_player()->GetName();
    if(!name || !sizeof(name)) name = "player";
    if(active==1){
        write("珍妮机器人已经处于激活状态。");
        return 1;
    }
    refreshlist();
    active=1;
    hb=0;
    tip=1;
    write("这个女性安卓机器人活了过来！她对你微笑，整了整她的裙子。");
    ob->eventForce("say 你好，"+name+"！我是珍妮，LPC大学的"+
            "新手导游机器人。我是一个非常简单的安卓机器人，所以"+
            "请不要期望太多互动。");
    ob->eventForce("smile "+name);
    ob->eventForce("say 我在这里给你一些提示。要停用我，只需"+
            "输入：%^RED%^deactivate bot%^CYAN%^。");
    ob->eventForce("say 要跳到下一个提示，请输入：next tip");
    return 1;
}

int eventAct4(){
    if(!new("/domains/campus/obj/note")->eventMove(this_object())){
        tell_room(environment(this_object()),"哎呀！出了个问题，"+
                "我没有纸条给你。就假装我已经给你了吧。不过请给管理员发邮件报告这个问题。");
        return 1;
    }
    if(player && environment(this_object()) == environment(player)) {
        eventForce("give note to "+player->GetName());
    }
    return 1;
}

int eventAct6(){
    if(!new("/domains/campus/obj/map")->eventMove(this_object())){
        tell_room(environment(this_object()),"哎呀！出了个问题，"+
                "我没有地图给你。就假装我已经给你了吧。不过请给管理员发邮件报告这个问题。");
        return 1;
    }
    if(player && environment(this_object()) == environment(player)) {
        eventForce("give map to "+player->GetName());
    }
    return 1;
}

int eventAct8(){
    if(mooch || !new("/domains/campus/armor/newbie_cap")->eventMove(this_object())){
        tell_room(environment(this_object()),
                "我没有帽子给你。就假装我已经给你了吧。");
    }
    if(mooch || !new("/domains/campus/obj/squirtbag")->eventMove(this_object())){
        tell_room(environment(this_object()),
                "我没有袋子给你。就假装我已经给你了吧。");
    }
    if(player && environment(this_object()) == environment(player)) {
        eventForce("give cap to "+player->GetName());
    }
    if(player && environment(this_object()) == environment(player)) {
        eventForce("give bag to "+player->GetName());
    }
    return 1;
}

int eventAct9(){
    eventForce("smile "+player->GetName());
    if(!new("/domains/campus/meals/badapple")->eventMove(this_object())){
        tell_room(environment(this_object()),"哎呀！出了个问题，"+
                "我没有烂苹果给你。就假装我已经给你了吧。不过请给管理员发邮件报告这个问题。");
    }
    if(!new("/domains/campus/meals/apple")->eventMove(this_object())){
        tell_room(environment(this_object()),"哎呀！出了个问题，"+
                "我没有苹果给你。就假装我已经给你了吧。不过请给管理员发邮件报告这个问题。");
    }
    if(player && environment(this_object()) == environment(player)) {
        eventForce("give first apple to "+player->GetName());
        eventForce("give my apple to "+player->GetName());
        return 1;
    }
}

int eventAct11(){
    eventForce("smirk");
    return 1;
}

int eventSwitch(int arg){
    switch(arg){
        case 4:eventAct4();break;
        case 6:eventAct6();break;
        case 8:eventAct8();break;
        case 9:eventAct9();break;
        case 11:eventAct11();break;
        default:write("");break;
                return 1;
    }
}

int eventDoTip(int i){
    tip++;
    hb=0;
    eventSwitch(i);
    if(tip > tipnumber) {
        this_object()->eventTurnOff("bot");
        return 1;
    }
    tell_room(environment(this_object()),read_file("/domains/campus/txt/jenny/"+i+".txt"));

}

void heart_beat(){
    hb++;
    if(greeting) greetwait++;
    if(noobster && greetwait > 0){
        eventGreet();
        noobster = 0;
        greetwait = 0;
        greeting = 0;
    }
    if(hb > 20 && active) eventDoTip(tip);
}
