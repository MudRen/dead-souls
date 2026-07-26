/* It works now, no define needed.
 * make sure someone does "setmc" or it won't do much.
 * setmc can only be done once, first come, first get i guess ;)
 * by Boy@frontiers.
 * Major corrections and modifications by Crat 25jul05
 */
#include <lib.h>
#include <vendor_types.h>
inherit LIB_STORAGE;

#define DEFAULT_BOUNCE_ROOM "/domains/town/room/adv_guild"
string bounce_room ;		/* File name of the bounce room */
string *voters ;		/* Array of names of users who have voted */
string *agenda ;		/* Array of agenda item strings.  */
mapping votes ;			/* Keys are names, data are votes cast */
string vote_str ;		/* The proposition being voted on  */
int endtime ;			/* Time at which the speaker/vote ends  */
int votelog ;			/* 1 if votes are being announced, else 0 */

string speaker;
string mc;
int x;
object ob;
protected void create() {
    storage::create();
    SetShort("讲台");
    SetLong("这是演讲者的讲台。它大约四英尺高，由某种看起来很昂贵的深纹理木材制成。这个讲台通过赋予演讲者一次认可一个人发言的权力来促进会议的进行。讲台里有一些存放物品的空间，也许里面现在就有东西。有关使用讲台主持会议的更多详细信息，请输入：help podium。");
    SetMass(10);
    SetId( ({"podium", "speaker's podium", "podium.c"}) );
    SetDollarCost(-110);
    SetKeyName("podium");
    SetId(({"podium","handler"}));
    SetAdjectives(({"wood","wooden","meeting","speaker's","Speaker's"}));
    SetDamagePoints(1000);
    SetPreventGet("你拿不了那个。");
    SetMaxCarry(20);

    SetInventory(([
                ]));

    mc = "";
    x = 0;
    speaker = "";

    vote_str = "none" ;
    voters = ({ }) ;
    votes = ([ ]) ;
    agenda = ({ }) ;
    bounce_room = DEFAULT_BOUNCE_ROOM ;

}
void init() {
    ::init();
    add_action("eventSay", "say",1);
    add_action("eventSay", "codesay");
    add_action("eventRaise", "raise");
    add_action("eventCallOn", "recognize");
    add_action("shaddap", "yell");
    add_action("shaddap", "shout");
    add_action("shaddap", "emote");
    add_action("help", "help");
    add_action("quiet", "quiet");
    add_action("changemc", "changemc");
    add_action("SetMc", "setmc");
    add_action ("echo", "echo") ;
    add_action ("vote", "vote") ;
    add_action ("call_for_vote", "call") ;
    add_action ("call_for_roll", "rollcall") ;
    add_action ("permit_entry", "permit") ;
    add_action ("localtime", "time") ;
    add_action ("reset_clock", "reset") ;
    add_action ("show_agenda", "agenda") ;
    add_action ("add_items", "add") ;
    add_action ("remove_item", "remove") ;
    add_action ("clear_items", "clear") ;
    add_action ("eject_player", "eject") ;
    add_action ("privacy", "privacy");
    add_action ("privacy", "priv");
    add_action ("localupdate", "update") ;
    add_action ("localupdate", "reload") ;
    add_action ("step_down", "step" );
    add_action ("RestrictedAction", "zap" );
    add_action ("RestrictedAction", "force" );
}
mixed CanGet(object ob) { return "这个讲台纹丝不动。";}

int RestrictedAction(){
    if(!archp(this_player()) && sizeof(mc) && mc != this_player()->GetKeyName()){
        write("此操作在此受限。");
        return 1;
    }
}

int eventSay(string args) {
    string foo;

    if(!sizeof(args)) return 0;
    args = replace_string(args,"\n","");
    if (mc == this_player()->GetKeyName()) {
        //this_player()->eventPrint("You say %^CYAN%^\"" + capitalize(args) + "\"");
        //say(this_player()->GetName() + " says %^CYAN%^\"" + capitalize(args) + "\"");
        return 0;
    }
    if ( mc != "" && this_player()-> GetKeyName() != speaker ) {
        this_player()->eventPrint("%^RED%^不按顺序发言是不礼貌的。");
        this_player()->eventPrint("如果你想发言，请举手。");
        return 1;
    }
    if ((!args) || (args == " ")) {
        write ("你自言自语。\n") ;
        return 1 ;
    }
    //foo = this_player()->GetCapName() + 
    //" says: %^CYAN%^\"" + capitalize(args)+"\"";
    //say (foo) ;
    //write("You say: %^CYAN%^\"" + capitalize(args)+"\"");
    return 0;

}


int eventCallOn(string args) {
    if (present((object)args)) {
        if (mc == this_player()->GetKeyName()) {
            speaker = args;
            write("你已经请"+speaker+"发言了。\n");
            find_living(args)->eventPrint("%^CYAN%^" + capitalize(mc) + "请你发言，你现在可以说话了。");
            return 1;
        }
        else {
            this_player()->eventPrint("只有主持人可以这样做。");
            return 1;
        }
    }
    else {
        write("%^CYAN%^此人不在这里，无法被请发言。");
        return 1;
    }
}	


int eventRaise() {
    string dude;
    dude=this_player()->GetKeyName();
    if(dude != mc && dude != speaker) {
        tell_room(environment(this_player()),
                this_player()->GetName()+" raises "+
                possessive(this_player())+
                " hand.", ({this_player()}) );
        this_player()->eventPrint("%^CYAN%^你举起了手。");
        return 1;
    }
    else {
        write("你已经可以说话了。说出你的想法吧。");
        return 1;
    }
}


int shaddap() {
    if(mc != "" && this_player()->GetKeyName() != speaker){
        write("%^RED%^现在这样做是不礼貌的。");
        return 1;
    }
}


int help(string args) {
    if (args != "podium") {
        return 0;
    }
    else {
        write("%^GREEN%^这是演讲者的讲台，是演讲者在演讲时站立的地方。这个讲台有特殊功能，如果你是主持人，它可以阻止其他人不按顺序发言。%^RESET%^");
        if (this_player()->GetKeyName() == mc) {
            write("%^RED%^可用命令：");
            write("%^YELLOW%^recognize %^RESET%^：请另一个人发言。");
            write("%^YELLOW%^say %^RESET%^：作为主持人，你可以随时发言。");
            write("%^YELLOW%^quiet %^RESET%^：撤销你最后请发言的人的发言权。");
            write("%^YELLOW%^changemc %^RESET%^：辞去主持人职务，让别人接替。");
            write("%^YELLOW%^add <内容>%^RESET%^：将议程项目<内容>添加到议程末尾。");
            write("%^YELLOW%^remove <编号>%^RESET%^：从议程中删除第<编号>项议程。");
            write("%^YELLOW%^clear agenda%^RESET%^：清除议程。");
            write("%^YELLOW%^permit <名字>%^RESET%^：允许玩家<名字>在锁定时进入会议室。");
            write("%^YELLOW%^eject <名字>%^RESET%^：将玩家<名字>逐出会议室。");
            write("%^YELLOW%^time <数字> [minutes/seconds]%^RESET%^：将时钟设置为<数字>分钟或秒。");
            write("%^YELLOW%^reset clock%^RESET%^：清除时钟。");
            write("%^YELLOW%^step down%^RESET%^：辞去首席演讲者职务。");
            write("%^YELLOW%^rollcall <数字> [minutes/seconds] <议题>%^RESET%^：发起唱名投票，\n"
                    "\t持续数字分钟或秒，议题为<议题>。");
            write("%^YELLOW%^add after <编号> <内容>%^RESET%^：在第<编号>项议程后添加议程项目<内容>。\n"
                    "\tadd after 0 <内容> 添加到列表顶部。");
            write("%^YELLOW%^call <数字> [minutes/seconds] <议题>%^RESET%^：发起投票，持续数字分钟\n"
                    "\t或秒，议题为<议题>。");
            return 1;
        }
        else {
            write("%^RED%^可用命令：");
            write("%^YELLOW%^raise %^RESET%^：举手，向主持人示意你想发言。");
            write("%^YELLOW%^say %^RESET%^：发言，只有在主持人请你发言后才能使用此命令。");
            if (x == 0) {
                write("%^YELLOW%^setmc%^RESET%^：目前没有主持人，使用此命令设置一个。");
            }
            return 1;
        }
    }
}


int quiet() {
    if (mc == this_player()->GetKeyName()) {
        write("%^CYAN%^你感谢" + capitalize(speaker) + "的发言。");
        find_living(speaker)->eventPrint("%^CYAN%^" + capitalize(mc) + "感谢你的发言。");
        speaker = mc;
        return 1;
    }
    write ("只有主持人可以使用此命令。\n") ;
    return 1;
}


int changemc(string args) {
    if (args != 0) {
        if ( this_player()->GetKeyName() != mc ) {
            write("%^RED%^你不是主持人，不能把这个职位让给别人。");
            return 1;
        }
        else {
            if (!present(args)) {
                write("%^CYAN%^" + args + "不在这里，因此不能成为主持人。");
                return 1;
            }
            else {
                write("%^CYAN%^你把讲台交给了" + args);
                mc = args;
                say("%^CYAN%^" + capitalize(args) + "是新的首席演讲者。");
                find_living(mc)->eventPrint("%^BLUE%^你是新的首席演讲者！");
                find_living(mc)->eventPrint("命令\"help podium\"可以帮助你，如果你不知道该怎么做的话。");
                return 1;
            }
        }
    }
    else {
        write("%^CYAN%^语法：");
        write("changemc <玩家>");
        return 1;
    }
}

int step_down(string args){
    if (args == "down") {
        if ( this_player()->GetKeyName() != mc ) {
            write("%^RED%^你不是主持人，不能辞去这个职位。");
            return 1;
        }
        say("%^CYAN%^" + capitalize(mc) + "已辞去首席演讲者职务。");
        write ( "你辞去了首席演讲者职务" );
        mc = "";
        x--;
        load_object(base_name(environment(this_object())))->AutoDeactivate();    
        return 1;
    }
    else {
        write("%^CYAN%^语法：");
        write("<step down>");
        return 1;
    }

}

int SetMc(string args) {
    object ob;
    if(args) ob = find_living(args);
    if(!args || !ob) ob = this_player();
    if(!member_group(ob, "MODERATORS")){
        write("此人不是版主组的成员。");
        write("管理员应使用admintool命令将适当的人添加到该用户组中。");
        return 1;
    }
    if (x==0) {
        if (args != 0) {
            if (present(args) ) {
                mc = args;
                say("%^CYAN%^" + capitalize(mc) + "是演讲者。");
                write("你把" + capitalize(args) + "设为演讲者。");
                find_living(mc)->eventPrint("命令\"help podium\"可以帮助你，如果你不知道该怎么做的话。");
                x++;
                return 1;
            }
            else {
                write("你不能把他/她设为演讲者，他/她不在这里！");
                return 1;
            }
        }
        else {
            write("%^CYAN%^语法：");
            write("setmc <玩家>");
            return 1;
        }
    }
    else {
        write("已经有一位演讲者了，你不能再设置另一位。");
        return 1;
    }
}

int privacy(string str){

    if ( mc != this_player()->GetKeyName() ) {
        write ("只有主持人可以使用隐私力场。\n") ;
        return 1 ;
    }
    if(str=="on" || str == "1"){
        load_object(base_name(environment(this_object())))->set_privacy( 1 );
        write("你启用了隐私力场。\n");
        say(this_player()->GetName()+"在房间周围启用了隐私力场。");
        return 1;
    }
    if(str=="off" || str == "0"){
        load_object(base_name(environment(this_object())))->AutoDeactivate();
        write("你关闭了隐私力场。\n");
        say(this_player()->GetName()+"关闭了房间周围的隐私力场。");
        return 1;
    }
}

// Echoing is always forbidden. It's just too much of a hassle.
int echo (string str) {
    write ("会议室始终禁止使用回声。\n") ;
    return 1 ;
}

// Permit_entry lets the mc bring someone into the conference room
// when it is locked.
int permit_entry (string name) {

    object user ;
    int oldlock ;

    if ( mc != this_player()->GetKeyName() ) {
        write ("只有主持人可以允许进入锁定的会议室。\n") ;
        return 1 ;
    }
    user = find_player(name) ;
    if (!user) {
        write ("没有该名称的用户。\n") ;
        return 1 ;
    }
    if (present(user,environment(this_object()))) {
        write (capitalize(name)+"已经在这里了！\n") ;
        return 1 ;
    }
    // We save the old locked status of the room, and restore it when we're
    // done. You can "permit" entry into an unlocked conference if you want
    // to: it saves the person the trouble of walking.
    oldlock = load_object(base_name(environment(this_object())))->get_privacy() ;
    load_object(base_name(environment(this_object())))->set_privacy( 0 );
    user -> eventMove(environment(this_object())) ;
    load_object(base_name(environment(this_object())))->set_privacy( oldlock );
    write ("你把"+capitalize(name)+"带入了会议室。\n") ;
    tell_object (user, capitalize(mc)+"允许你进入。\n") ;
    say (capitalize(name)+"已被允许进入会议室。\n", user) ;
    return 1 ;
}



// Eject_player lets the mc banish a player from the room and dump
// him in the bounce room.
int eject_player (string str) {
    object env = environment(this_player());
    object ob ;

    if ( mc != this_player()->GetKeyName() ) {
        write ("只有主持人可以驱逐玩家。\n") ;
        return 1 ;
    }
    ob = find_player(str) ;
    if (!ob || !present (ob, environment(this_object()))) {
        write ("这里没有名为"+capitalize(str)+"的玩家。\n") ;
        return 1 ;
    }
    write ("你把"+capitalize(str)+"逐出了房间！\n") ;
    tell_object (ob, "你已被逐出房间。\n") ;
    say (capitalize(str)+"已被逐出房间。\n") ;
    ob->eventMove(bounce_room) ;
    if(env) env->AddEjected(ob);
    return 1 ;
}

// Localtime shows the user the amount of time left on the room clock.
// The name is chosen to avoid colliding with the time() efun.
// The mc may also use this function to set the time on the clock
// and start it running. See the help documents for more information on
// how the clock works.
varargs int localtime (string str) {

    int i, min, sec ;
    string foo ;

    // If no string, then we just indicate how much time is left on the clock.
    if (!str) {
        if (!endtime || endtime == 0) {
            write ("时钟目前没有在运行。\n") ;
            return 1 ;
        }
        i = time() ;
        i = endtime - i ;
        min = (i/60) ;
        sec = i - (min*60) ;
        if (min==1) {
            write ("时钟显示剩余1分钟"+sec+"秒。\n") ;
        } else {
            write ("时钟显示剩余"+min+"分钟"+sec+"秒。\n") ;
        }
        return 1 ;
    }
    // If there is a string, then the user is trying to set the clock to some
    // number of minutes or seconds.
    if ( mc != this_player()->GetKeyName() ) {
        write ("只有主持人可以设置时钟。\n") ;
        return 1 ;
    }
    // You cannot set a new time if the clock is running. This is for safety.
    // You must reset the clock first. See below.
    if (endtime!=0) {
        write ("时钟正在运行。你必须先重置时钟。\n") ;
        return 1 ;
    }
    if (sscanf(str, "%d min%s", i, foo) == 2) {
        i=i*60 ;
    } else {
        if (sscanf(str, "%d seconds", i) != 1) {
            write ("你必须设置分钟或秒数：例如，3 minutes 或 90 seconds。\n") ;
            return 1 ;
        }
    }
    write ("你把时钟设置为"+str+"。\n") ;
    say (capitalize(mc)+"把时钟设置为"+str+"。\n") ;
    endtime = time()+i ;
    // We call_out to a function that prints a message when time runs out.
    call_out ("expire_time", i) ;
    return 1 ;
}

// Reset_clock lets the mc clear the clock before setting a new time
// on it.
int reset_clock (string str) {
    if (!str || str!="clock") {
        notify_fail ("Reset what?\n") ;
        return 0 ;
    }
    if ( mc != this_player()->GetKeyName() ) {
        write ("只有主持人可以重置时钟。\n") ;
        return 1 ;
    }
    if (endtime==0) {
        write ("时钟没有在运行。\n") ;
        return 1 ;
    }
    endtime = 0 ;
    write ("你清除了时钟。\n") ;
    say (capitalize(mc)+"清除了时钟。\n") ;
    // Clear any pending call_outs that may be left behind.
    remove_call_out("expire_time") ;
    remove_call_out("expire_vote") ;
    return 1 ;
}

// Expire_time lets the conference room know that time has expired. It
// doesn't force the speaker to shut up or anything like that: that's left
// to the mcs discretion.
int expire_time() {
    tell_room (environment(this_object()),"时间到了。\n") ;
    endtime = 0 ;
}


// Show_agenda lets users see the current agenda.
int show_agenda() {

    int i ;

    if (!agenda || sizeof(agenda)==0) {
        write ("议程尚未设定。\n") ;
        return 1 ;
    }
    write ("当前议程：\n") ;
    for (i=0;i<sizeof(agenda);i++) {
        write ((i+1)+". "+agenda[i]+"\n") ;
    }
    return 1 ;
}



// Clear_speakers erases the speakers list or agenda, depending on argument.
int clear_items (string str) {
    if ( mc != this_player()->GetKeyName() ) {
        write ("只有主持人可以清除议程。\n") ;
        return 1 ;
    }
    if (!str || str!="agenda") {
        write ("用法：clear [agenda]\n") ;
        return 1 ;
    }
    agenda = ({ }) ;
    write ("议程已被清除。\n") ;
    say ("议程已被清除。\n") ;
    return 1 ;
}

// Add_agenda_item lets the mc add an agenda item. If the argument
// is of the form "after <int> <string>", then string is added to the
// agenda AFTER item int. Agenda items are numbered 1-N rather than 0-(N-1).
int add_items (string str) {

    int post ;
    string prop ;

    if ( mc != this_player()->GetKeyName() ) {
        notify_fail ("只有主持人可以添加议程项目。\n") ;
        return 0 ;
    }
    if (!str) {
        write ("用法：add item 或 add after N item\n") ;
        return 1 ;
    }
    if (sscanf(str,"after %d %s", post, prop)!=2) {
        agenda += ({ str }) ;
        write ("已将以下项目添加到议程\n"+str+"\n") ;
        return 1 ;
    }
    if (post<0 || post>=sizeof(agenda)) {
        notify_fail ("项目编号超出范围。\n") ;
        return 0 ;
    }
    if (post==0) agenda = ({ prop }) + agenda ; else
        agenda = agenda[0..post-1] + ({ prop }) + agenda[post..sizeof(agenda)] ;
    write ("已在第"+post+"项之后添加以下议程项目：\n"+
            prop+"\n") ;
    return 1 ;
}

// Remove_item lets the mc take an item off the agenda.
int remove_item (string str) {

    int agitem ;

    if (!str) {
        notify_fail ("用法：remove <议程项目编号>\n") ;
        return 0 ;
    }
    if (sscanf(str,"%d",agitem)!=1) {
        notify_fail ("用法：remove <议程项目编号>\n") ;
        return 0 ;
    }
    if (agitem<0 || agitem>sizeof(agenda)) {
        write ("项目编号超出范围。\n") ;
        return 0 ;
    }
    // Convert to 0-(N-1) numbering.
    agitem = agitem-1 ;
    write (agitem+"\n") ;
    write ("正在删除以下议程项目：\n"+agenda[agitem]+"\n") ;
    if (agitem==0) {
        agenda = agenda[1..sizeof(agenda)-1] ;
    } else {
        if (agitem == sizeof(agenda)-1) {
            agenda = agenda[0..sizeof(agenda)-2] ;
        } else {
            agenda = agenda[0..agitem-1] + agenda[agitem+1..sizeof(agenda)-1] ;
        }
    }
    return 1 ;
}

// Vote lets a player cast a vote on the proposed issue. See the help
// document for details on how voting works.
int vote (string str) {
    // With no argument, we print the proposal, if there is one.
    if (!str) {
        if (!vote_str || vote_str=="none") {
            write ("当前没有进行投票。\n") ;
            return 1 ;
        }
        write ("投票议题："+vote_str+"\n") ;
        return 1 ;
    }
    // If there is a argument, we interpret that string as a vote cast.
    if (!vote_str || vote_str=="none") {
        write ("当前没有进行中的投票。\n") ;
        return 1 ;
    }
    if (str!="yes" && str!="no" && str!="abstain") {
        write ("请投 yes（赞成）、no（反对）或 abstain（弃权）。\n") ;
        return 1 ;
    }
    if (member_array( this_player()->GetName(),voters)!=-1) {
        write ("你已经投过票了！\n") ;
        return 1 ;
    }
    voters += ({ this_player()->GetName() }) ;
    votes[str] = votes[str]+1 ;
    write ("你对"+vote_str+"投了"+str+"。\n") ;
    // If this is a roll call vote - ie, the votes are being logged - we announce
    // the vote to the log file and to the room.
    if (votelog) {
        say (capitalize(this_player()->GetName())+"投了"+capitalize(str)+"。\n") ;
    }
    return 1 ;
}

// Call_for_vote allows the mc to call for a secret-ballot vote on
// a proposal.
int call_for_vote (string str) {

    string timestr, subjstr ;
    int i ;

    if ( mc != this_player()->GetKeyName() ) {
        write ("只有主持人可以发起投票。\n") ;
        return 1 ;
    }
    // Must specify an amount of time for which votes may be cast, and a subject
    // which people are voting on.
    if (!str) {
        write ("用法：call <数字> <minutes|seconds> <议题>\n") ;
        return 1 ;
    }
    if (sscanf(str,"%d %s %s",i,timestr,subjstr)!=3) {
        write ("用法：call <数字> <minutes|seconds> <议题>\n") ;
        return 1 ;
    }
    // This is going to reset the clock: so we want to force the mc to
    // clear the clock first.
    if (endtime!=0) {
        write ("时钟正在运行。你必须先重置时钟。\n") ;
        return 1 ;
    }
    if (timestr=="minutes") {
        i = i * 60 ;
    } else {
        if (timestr!="seconds") {
            write ("请以分钟或秒为单位输入时间。\n") ;
            return 1 ;
        }
    }
    vote_str = subjstr ;
    // This is a secret ballot so we don't want to log the votes.
    votelog = 0 ;
    write ("你发起了关于"+vote_str+"的投票。\n") ;
    say (capitalize(mc)+"发起了关于"+vote_str+"的投票。\n") ;
    say (capitalize(mc)+"把时钟设置为"+str+"。\n") ;
    endtime = time()+i ;
    // Call out to a function which totals the votes at the end of the vote time.
    call_out ("expire_vote",i) ;
    return 1 ;
}

// Call_for_roll is exactly like call_for_vote EXCEPT that it calls for
// a roll-call vote: that is, all votes are announced and logged.
int call_for_roll (string str) {

    string timestr, subjstr ;
    int i ;

    if ( mc != this_player()->GetKeyName() ) {
        write ("只有主持人可以发起投票。\n") ;
        return 1 ;
    }
    if (!str) {
        write ("用法：rollcall <数字> <minutes|seconds> <议题>\n") ;
        return 1 ;
    }
    if (sscanf(str,"%d %s %s",i,timestr,subjstr)!=3) {
        write ("用法：rollcall <数字> <minutes|seconds> <议题>\n") ;
        return 1 ;
    }
    if (endtime!=0) {
        write ("时钟正在运行。你必须先重置时钟。\n") ;
        return 1 ;
    }
    if (timestr=="minutes") {
        i = i * 60 ;
    } else {
        if (timestr!="seconds") {
            write ("请以分钟或秒为单位输入时间。\n") ;
            return 1 ;
        }
    }
    vote_str = subjstr ;
    // This is a roll call vote so we log the votes and announce them.
    votelog = 1 ;
    write ("你发起了关于"+vote_str+"的唱名投票。\n") ;
    say (capitalize(mc)+"发起了关于"+vote_str+"的唱名投票。\n") ;
    say (capitalize(mc)+"把时钟设置为"+str+"。\n") ;
    endtime = time()+i ;
    call_out ("expire_vote",i) ;
    return 1 ;
}

// Expire_vote finishes the vote and tabulates the results. It does not
// announce the outcome because some votes required 2/3 or 3/4 to pass
// rather than a simple majority.
int expire_vote() {
    tell_room (environment(this_object()), "时间到。投票结束。\n") ;
    endtime = 0 ;
    tell_room (environment(this_object()), "投票结果：\n"+
            "赞成：  "+votes["yes"]+"     反对：   "+votes["no"]+"       弃权：  "+
            votes["abstain"]+"\n") ;
    voters = ({ }) ;
    votes["yes"] = 0 ;
    votes["no"] = 0 ;
    votes["abstain"] = 0 ;
    vote_str="none" ;
}

int localupdate() {
    if(!archp(this_player())){
        write ("在会议室中你不能更新对象。\n") ;
        return 1;
    }
}

int eventDestruct(){
    if(sizeof(mc) && !this_player() || (this_player() && !archp(this_player()))){
        write("你不能摆弄讲台。");
        return 0;
    }
    else return ::eventDestruct();
}

int eventMove(mixed dest){
    if(sizeof(mc)){
        write("不行。");
        return 0;
    }
    else return ::eventMove(dest);
}

