/*    /secure/lib/connect.c
 *    from the Dead Souls Object Library
 *    the object a user connects to before determining their real body
 *    created by Descartes of Borg 951103
 *    Version: @(#) connect.c 1.2@(#)
 *    Last Modified: 96/05/28
 */

#include <lib.h>
#include ROOMS_H
#include <news.h>
#include <flags.h>
#include <cfg.h>
#include <daemons.h>
#include <message_class.h>
#include "include/connect.h"

#define CUSTOM_FORMAT 0
#define REAL_NAME 0

#ifndef __ANSI_SUBSTITUTE__
#define __ANSI_SUBSTITUTE__ 0x1e
#endif

#ifndef GUEST_ALLOWED
#define GUEST_ALLOWED 1
#endif

inherit LIB_PAGER;
#include <mssp.h>

nosave private int CrackCount, NetDead, MaxPlayers, blindmode;
nosave private string name, Name, Terminal, raza, TrueName, trabajo, extra;
nosave private string Passwort, Gendre, CapNamen, E_Mail, my_ip, client_ip;
nosave private object Player, pile;
nosave private mapping LastError, UserVars;
nosave private int *Screen;
nosave private int rescue, yescre, anyterm;
nosave private string *ip_permitted = ({}), instname, telopt_user;
nosave private string *anyterms = ({"97.107.133.86", "127.0.0.1"});

//Change this to 0 to disable color codes in /news/welcome
//then update the connect.c file.
nosave private int AllowColorSplash = 1;

//Change this to 1 to change your welcome screen to /news/moved
//and to disable the standard login prompts.
nosave private int Moved = 0;

int eventCheckPending(string str);
void eventCompleteChar();
void InputCre(string str);
private void cmdPickClass(string args);
private void cmdListClasses();
private void cmdHelpClass(string args);
private void InputClass(string str);
private void eventSelectClass();

int CheckIp(){
    int ips = 0;
    string tmp_ip;
    if(!SAME_IP_MAX) return 1;
    tmp_ip = query_ip_number();
    if(telopt_user && telopt_user != my_ip) tmp_ip = telopt_user;
    if(!ip_permitted) ip_permitted = ({});
    ip_permitted += PLAYERS_D->GetAdminIPs();
    ip_permitted = singular_array(ip_permitted);
    if(member_array(tmp_ip, ip_permitted) != -1) return 1;
    foreach(object jugador in users()){
        if(query_ip_number(jugador) == tmp_ip) ips++;
    }
    if(ips >= SAME_IP_MAX) return 0;
    return 1;
}

private void create(int binary) {
    extra = "";
    UserVars = ([]);
    if(query_windows()){
        MaxPlayers = 50;
    }
    else {
#ifdef __ULIMIT__
        MaxPlayers = (__ULIMIT__ - 10);
#else
#if __FD_SETSIZE__
        if(!MaxPlayers || MaxPlayers > __FD_SETSIZE__){
            MaxPlayers = (__FD_SETSIZE__ - 10);
        }
#endif
#endif
    }
    if(grepp(__ARCH__, "Solaris")){
#ifndef __M64__
        //Solaris has a problem with fd's over 256 in
        //32-bit applications.
        MaxPlayers = 200;
#endif
    }
    if(!MaxPlayers) MaxPlayers = 1000;
    if(MAX_USERS) MaxPlayers = MAX_USERS;
    CrackCount = 0;
    Name = "";
    Player = 0;
    NetDead = 0;
    if(ENABLE_INSTANCES){
        instname = INSTANCES_D->GetMyInstanceName();
    }
    ip_permitted = explode(read_file(CFG_IP_UNRESTRICT),"\n");
}

varargs private void logon(mixed foo) {
    string welcome = "已连接到 "+mud_name()+"，一个LP MUD游戏";
    if(sizeof(architecture())) welcome += " 运行在 "+architecture()+" 上.\n";
    else welcome += ".\n";

    client_ip = query_ip_number();

    call_out((: eventTimeout :), LOGON_TIMEOUT);
    if(mud_name() == "Dead Souls" || mud_name() == "Dead Souls Dev" ){
        welcome += read_file(DS_WELCOME) || "Welcome to " + mud_name() + "!";
    }
    else {
        string wfile;
        if(instname && instname != "global"){
            wfile = NEWS_WELCOME+"."+__PORT__;
        }
        if(!wfile || !file_exists(wfile)) wfile = NEWS_WELCOME;
        welcome += read_file(wfile) || "Welcome to " + mud_name() + "!";
    }
    if(Moved){
        string wfile;
        if(instname && instname != "global"){
            wfile = NEWS_MOVED+"."+__PORT__;
        }
        if(!wfile || !file_exists(wfile)) wfile = NEWS_MOVED;
        welcome = read_file(wfile) || "Welcome to " + mud_name() + "!";
    }
    if(AllowColorSplash){
        receive(terminal_colour(welcome,TERMINAL_D->query_term_info("ansi")));
    }
    else {
        receive(welcome);
    }
    if(!Moved){
        receive("\n" + center("驱动程序: " + version() +
                    "               Mudlib: "+
                    mudlib() + " " + mudlib_version()) + "\n");
        receive("\n请输入你想要使用的名字: ");
        input_to((: InputName :), I_NOESC);
    }
}

private void InputName(string namen, string kill_me) {
    string temp_name, news;
    mixed tmp;
    int toomany;
    name = namen;

    if(member_array(client_ip, anyterms) != -1){
        if(telopt_user){
            int bar = sscanf(telopt_user, "%*d.%*d.%*d.%*d");
            if(bar == 4){
                client_ip = telopt_user;
                anyterm = 1;
                extra = " ["+my_ip+"]";
            }
        }
    }

    if(!CheckIp()){
        receive("\n来自你所在地址的登录用户过多。\n");
        receive("请稍后再试。\n");
        flush_messages();
        Destruct();
        return;
    }

    if(sizeof(users()) >= MaxPlayers){
        toomany = 1;
    }

    if(lower_case(name) == "guest" && !GUEST_ALLOWED){
        name = "";
        receive("\n访客账号已被禁用。\n");
    }

    if( !name || name == "" ) {
        if( kill_me ) {
            if(!Moved) receive("\n或许可以下次再试？\n");
            Destruct();
            return;
        }
        else {
            if(!Moved){
                receive("\n你必须输入一个名字才能加入游戏！\n");
                receive("\n请输入你想要使用的名字: ");
            }
            input_to((: InputName :), I_NOESC, "kill me");
            return;
        }
    }

    if(grepp(name, "MSSP-REQUEST")){
        log_file("mssp",timestamp() + " " + my_ip + extra + "\n");
        receive(mssp_reply());
        flush_messages();
        input_to((: InputName :), I_NOESC);
        return;
    }
    if(sscanf(name,"%s_rescue",temp_name) == 1) {
        name = temp_name;
        rescue = 1;
    }
    Name = convert_name(name);
    name = capitalize(name);
    if( master()->is_locked() || toomany) {
        if(toomany){
            news = "Too many players logged in!";
        }
        else news = read_file(NEWS_LOCKED) || "No reason logged.";
        receive("\n" + mud_name() + " is locked.  Reason:\n" + news + "\n");
        if( CanLogin() ) receive("\n        >>> Access allowed <<<\n");
        else {
            receive("\n        >>> Access denied <<<\n");
            flush_messages();
            Destruct();
            return;
        }
    }
    if( !user_exists(Name) ) {
        eventCreatePlayer(name);
        return;
    }
    if( !(BANISH_D->eventConnect(Name, client_ip)) ) {
        news = read_file(NEWS_BANISHED) || "你不被允许进入这里。\n";
        receive("\n" + news + "\n");
        Destruct();
        return;
    }
    if( (tmp = CHARACTER_D->eventConnect(Name)) != 1 ) {
        if( tmp ) receive(tmp + "\n");
        else receive("你的一个角色最近刚刚登录过。\n"
                "你必须等待更长时间才能再次登录。\n");
        Destruct();
        return;
    }

    if( find_player(Name) ) NetDead = 1;

    if(Name != "guest"){
        receive("密码: ");
        input_to((: InputPassword :), I_NOECHO | I_NOESC, name);
    }
    else InputPassword("guest","Guest");
}

private void InputPassword(string pass, string cap) {
    string control;

    if(Name != "guest"){

        if( !pass || pass == "" ) {
            receive("\n你必须输入密码。请稍后再试。\n");
            Destruct();
            return;
        }
        if(!cap || cap == "") {
            receive("\n发生了一个异常错误。请重试。\n");
            Destruct();
            return;
        }

        control = PLAYERS_D->GetPlayerData(Name,"Password");
        if( control != crypt(pass, control) ) {
            receive("\n无效的密码。\n");
            if( ++CrackCount > MAX_PASSWORD_TRIES ) {
                receive("\n不再允许更多尝试\n");
                unguarded( (: log_file("/secure/log/security",
                  "Maximum password tries exceeded by " +
                        Name + " from " + client_ip + extra + "\n") :) );
                filter(users(), (: archp :))->eventPrint("System %^MAGENTA%^"
                        "<error>%^RESET%^ Maximum password "
                        "attempts exceeded by " + cap +
                        " from " + client_ip + ".\n",
                        MSG_ERROR);
                Destruct();
                return;
            }
            receive("密码: ");
            input_to( (: InputPassword :), I_NOECHO | I_NOESC, cap);
            return;
        }

        if(rescue) unguarded( (: wipe_inv(name) :) );
    }

    Player = master()->player_object(Name);
    if( !Player ) {
        receive("\n似乎现在正在进行一些维护工作，请稍后再试。\n");
        Destruct();
        return;
    }
    PLAYERS_D->AddPlayerInfo(Player);
    if( !Player->GetRace() || Player->GetRace() == "blob"
            || Name == "guest" ) {
        Player->SetRace("human");
    }

    if( !NetDead ){
        call_out( (: eventCheckPending, lower_case(Name) :), 3);
        eventEnterGame();
    }
    else eventReEnterGame(cap);
}

private void eventCreatePlayer(string cap) {
    string tmpdir, lcname = lower_case(Name);
    string *tmpfiles = ({});
    if( !(BANISH_D->valid_name(lcname)) ) {
        receive(capitalize(cap) + " 不是一个有效的名字。\n");
        receive(mud_name() + " 要求所有名字符合以下要求：\n");
        receive("\t所有字符必须是：\n");
        receive("\t\tA-Z\n\t\ta-z\n\t\t'\n\t\t-\n");
        receive("\t最小长度：" + MIN_USER_NAME_LENGTH + "\n");
        receive("\t最大长度：" + MAX_USER_NAME_LENGTH + "\n");
        receive("\n请输入一个新名字：\n");
        input_to( (: InputName :), I_NOESC );
        return;
    }
    tmpdir = DIR_PLAYERS "/" + lcname[0..0] + "/";
    if(directory_exists(tmpdir)){
        tmpfiles += get_dir(tmpdir);
    }
    tmpdir = DIR_CRES "/" + lcname[0..0] + "/";
    if(directory_exists(tmpdir)){
        tmpfiles += get_dir(tmpdir);
    }
    foreach(string tmpfile in tmpfiles){
        if(!strsrch(tmpfile, lcname+".")){
            receive("\n这个名字已被使用。请选择一个新的名字。\n");
            input_to( (: InputName :), I_NOESC );
            return;
        }
    }
    if( !(BANISH_D->eventConnect(Name, client_ip)) ) {
        string news;

        news = read_file(NEWS_REGISTER) || "No registration info.\n";
        receive(news);
        flush_messages();
        Destruct();
        return;
    }
    receive("你真的希望被称为 " + cap + " 吗? (y/n) \n");
    input_to((: ConfirmName :), I_NOESC, cap);
}

private BlindCheck(string ans, string cap){
    if( !ans || ans == "" || lower_case(ans)[0..0] == "y" ) {
        receive("\n好的，禁用默认的俯视地图。\n");
        blindmode = 1;
    }
    else receive("\n好的，允许默认的俯视地图行为。\n");
    log_file("new_players", Name + " (" + ctime(time()) + ")\n");
    receive("\n创建一个至少5个字符的密码: \n");
    input_to((: CreatePassword :), I_NOECHO | I_NOESC, cap);
}

private void AgeCheck(string ans, string cap) {
    if( !ans || ans == "" || lower_case(ans)[0..0] != "y" ) {
        receive("\n对不起。你的年龄不足以在这里玩耍。\n");
        Destruct();
        return;
    }
    log_file("new_players", Name + " (" + ctime(time()) + ")\n");
    unguarded( (: log_file("/secure/log/new_players", Name + " from "
      + client_ip + extra + " (" + ctime(time()) + ")\n") :) );
    receive("\n你是否使用视觉障碍辅助屏幕阅读器？是(y)/否(n)\n");
    input_to((: BlindCheck :), I_NOESC, cap);
}

private void ConfirmName(string ans, string cap) {
    if( !ans || ans == "" || lower_case(ans)[0..0] != "y" ) {
        receive("\n好的，请输入你真正想要的名字: \n");
        input_to( (: InputName :), I_NOESC );
        return;
    }
    receive("\n你是否已满13周岁? (y/n) \n");
    input_to((: AgeCheck :), I_NOESC, cap);
}

private void eventReEnterGame(string cap) {
    if( interactive(Player) ) {
        receive("\n你当前已存在一个交互式副本。\n");
        receive("你是否希望接管这个副本？是(y)/否(n)\n");
        input_to((: ConfirmReconnect :), I_NOESC, cap);
        return;
    }
    if( exec(Player, this_object()) ) {
        if(rescue)
            if(sizeof(deep_inventory(Player)))
                deep_inventory(Player)->eventMove(ROOM_FURNACE);
        log_file("enter", cap + " (exec): " + ctime(time()) + "\n");
        unguarded( (: log_file("/secure/log/enter", Name + " (exec): " +
          ctime(time()) + " from " + client_ip + extra + "\n") :) );
        Player->eventReconnect();
        Player->RemoveProperty("afk");
        if(!anyterm){
            Player->CancelCharmode();
            Player->SetProperty("reprompt", 0);
            Player->SetTeloptIp(0);
        }
        else {
            Player->SetTeloptIp(telopt_user);
        }
        if(creatorp(Player))
            Player->AddChannel((CHAT_D->GetSystemChannels() - ({"muds"})));
        SNOOP_D->ReportReconnect(Player->GetKeyName());
        call_out( (: eventCheckPending, lower_case(Name) :), 3);
    }
    receive("\n重新连接出现问题。\n");
    Destruct();
}

private void ConfirmReconnect(string ans, string cap) {
    object tmp;

    if( !stringp(ans) || ans == "" || lower_case(ans)[0..0] != "y" ) {
        receive("\n那么请稍后再试！\n");
        Destruct();
        return;
    }
    if(rescue)
        if(sizeof(deep_inventory(Player))) deep_inventory(Player)->eventMove(ROOM_FURNACE);
    log_file("enter", cap + " (reconnect) ("+ctime(time())+")\n");
    unguarded( (: log_file("/secure/log/enter", Name + " (reconnect) from "
      + client_ip + extra + " (" + ctime(time()) + ")\n") :) );
    exec(tmp = new(LIB_PLAYER), Player);
    exec(Player, this_object());
    destruct(tmp);
    if(anyterm){
        int oldlock = Player->GetProperty("screenlock");
        Player->SetCharmode(1);
        Player->SetProperty("reprompt",1);
        Player->SetProperty("commandecho", "blue");
        Player->SetProperty("keepalive", 5);
        Player->SetProperty("screenlock", 0);
        Player->SetScreen(80, 25);
        Player->SetProperty("screenlock", oldlock);
        Player->SetTeloptIp(telopt_user);
    }
    else {
        Player->SetTeloptIp(0);
    }
    Player->eventPrint("\n允许登录。\n", MSG_SYSTEM);
    call_out( (: eventCheckPending, lower_case(Name) :), 3);
    Destruct();
}

private int CanLogin() {
    string group;

    if( BANISH_D->GetGuest(Name) ) return 1;
    foreach(group in LOCKED_ACCESS_ALLOWED)
        if( member_group(Name, group) ) return 1;
    return 0;
}

private private void eventEnterGame() {
    if(!exec(Player, this_object())) {
        debug("problem connecting");
        receive("\n连接出现问题。\n");
        Player->eventDestruct();
        destruct(this_object());
        return;
    }
    if( Terminal ) Player->SetTerminal(Terminal);
    if( Screen ) Player->SetScreen(Screen[0], Screen[1]);
    Player->Setup();
    if(creatorp(Player)){
        string profile = user_path(Player->GetKeyName())+".profile";
        if(file_exists(profile)){
            string q = "";
            if(!MASTER_D->GetPerfOK()) q = "-q ";
            Player->eventForce("source "+q+profile);
        }
    }
    Player->RemoveProperty("afk");
    if(creatorp(Player))
        Player->AddChannel(((CHAT_D->GetSystemChannels()) - ({"muds"})));
    SNOOP_D->CheckBot(Player->GetKeyName());
    unguarded( (: log_file("/secure/log/enter", Name + " (enter): " +
      ctime(time()) + " from " + client_ip + extra + "\n") :) );
    if(anyterm){
        int oldlock = Player->GetProperty("screenlock");
        Player->SetCharmode(1);
        Player->SetProperty("reprompt",1);
        Player->SetProperty("commandecho", "blue");
        Player->SetProperty("keepalive", 5);
        Player->SetProperty("screenlock", 0);
        Player->SetScreen(80, 25);
        Player->SetProperty("screenlock", oldlock);
        Player->SetTeloptIp(telopt_user);
    }
    else {
        Player->SetTeloptIp(0);
    }
    call_out( (: destruct(this_object()) :), 10);
}

private void CreatePassword(string pass, string cap) {
    if( strlen(pass) < 3) {
        receive("\n你的密码长度必须至少为5个字符。\n");
        receive("请选择另一个密码: ");
        input_to( (: CreatePassword :), I_NOECHO | I_NOESC, cap);
        return;
    }
    receive("\n请确认你的密码: ");
    input_to( (: ConfirmPassword :), I_NOECHO | I_NOESC, cap, pass);
}

private void ConfirmPassword(string control, string cap, string pass) {
    if( control == pass ) {
        Player = master()->player_object(Name);
        pass = crypt(pass, 0);
        Passwort = pass;
        receive("\n\n请选择一个性别：男性(male)/女性(female)/中性(neutral)/无(none)\n");
        input_to((: InputGender :), I_NOESC, cap);
        return;
    }
    receive("\n密码输入不匹配，请重新选择密码: ");
    input_to((: CreatePassword :), I_NOECHO | I_NOESC, cap);
    return;
}

private void InputGender(string str, string cap) {
    if( str != "male" && str != "female"
            && str != "neuter" && str != "neutral" && str != "none") {
        receive("\n请选择：男性(male)/女性(female)/中性(neutral)/无(none)\n");
        receive("性别: ");
        input_to((: InputGender :), I_NOESC, cap);
        return;
    }
    if(str == "none") str = "neuter";
    Gendre = str;
    if(CUSTOM_FORMAT){
        receive("\nYou may format " + cap + " to appear however you wish "
                "using spaces, ', or -.\nEnter a display name "
                "(default: " + cap +"): \n");
        input_to((: InputCapName :), I_NOESC, cap);
    }
    else {
        InputCapName(cap, cap);
    }
}

private void InputCapName(string name, string cap) {
    if( !name || name == "" ) name = cap;
    if( !(BANISH_D->valid_cap_name(name, Name)) ) {
        receive("\n这不是一个有效的姓名格式，请重新选择：\n");
        input_to((: InputCapName :), I_NOESC, cap);
        return;
    }
    cap = capitalize(name);
    CapNamen = cap;
    receive("\n出于安全原因，" + mud_name() + "需要一个有效的电子邮件地址。\n"
            "电子邮件: \n");
    input_to((: InputEmail :), I_NOESC);
}

private void InputEmail(string email) {
    string user, host;

    if( !email || sscanf(email, "%s@%s", user, host) != 2 ) {
        receive("\n这不是一个有效的电子邮件地址。\n");
        receive("请输入一个有效的电子邮件地址: \n");
        input_to( (: InputEmail :), I_NOESC );
        return;
    }
    E_Mail = email;
    if(REAL_NAME){
        receive("\n如果你不介意，请输入你的真实姓名(可选): \n");
        input_to( (: InputRealName :), I_NOESC );
    }
    else {
        InputRealName("");
    }
}

private void InputRealName(string rname) {
    if( !rname || rname == "" ) rname = "Unknown";
    TrueName = rname;
    if(!HUMANS_ONLY){
        receive("\n\n你现在必须选择一个种族。\n");
        receive("选择种族会影响你角色的物理特征。\n");
        receive("\n你可以使用以下命令：\n");
        receive("\tlist - 列出所有可选的种族\n");
        receive("\thelp - 了解种族的含义\n");
        receive("\thelp [种族名称] - (例如 \"help human\") 获取特定种族的信息\n");
        receive("\tpick [种族名称] - 为你自己选择一个特定的种族\n");
        receive("\n\t可选种族: ");
        receive(implode(sort_array(RACES_D->GetRaces(1), 1), " "));
        receive("\n\n种族: \n");
        input_to((: InputRace :), I_NOESC);
    }
    else InputRace("pick human");
}

private void InputRace(string str) {
    string cmd, args;
    string *valid = ( RACES_D->GetRaces(1) || ({}) );

    if( str == "" || !str ) {
        receive("\nRace: ");
        input_to((: InputRace :), I_NOESC);
        return;
    }
    if( sscanf(str, "%s %s", cmd, args) != 2 ) {
        cmd = str;
        args = 0;
    }
    if(member_array(cmd, valid) != -1){
        args = cmd;
        cmd = "pick";
    }
    switch(cmd) {
        case "list":
            cmdList();
        return;

        case "help":
            cmdHelp(args);
        return;

        case "pick":
            cmdPick(args);
        return;

        default:
        receive("\n无效命令。\n种族: \n");
        input_to((: InputRace :), I_NOESC);
        return;
    }
}

private void cmdHelp(string args) {
    function f;
    string * races = RACES_D->GetRaces(1);
    string help;

    f = function(string str) {
        receive("\nRace: \n");
        input_to((: InputRace :), I_NOESC);
    };
    if( !args ) {
        help = read_file(DIR_PLAYER_HELP + "/races") ||
            "读取帮助文件出错。\n";
        eventPage(explode(help, "\n"), MSG_HELP, f);
        return;
    }
    if( member_array(args = lower_case(args), races) == -1 ) {
        receive("该种族不存在。\n\n种族: \n");
        input_to((: InputRace :), I_NOESC);
        return;
    }
    help = RACES_D->GetHelp(args);
    eventPage(explode(help, "\n"), MSG_HELP, f);
}

private void cmdList() {
    string list;

    list = format_page(sort_array(RACES_D->GetRaces(1), 1), 5);
    receive(list);
    receive("\nRace: \n");
    input_to((: InputRace :), I_NOESC);
}

private void cmdPick(string args) {
    if( !args || args == "" ) {
        receive("你必须指定一个要选择的种族。\n\n种族: \n");
        input_to((: InputRace :), I_NOESC);
        return;
    }
    if( member_array(args = lower_case(args),
                RACES_D->GetRaces(1)) == -1 ) {
        receive("该种族不存在。\n种族: \n");
        input_to((: InputRace :), I_NOESC);
        return;
    }
    raza = args;
    if(!AUTO_WIZ){
        if(CLASS_SELECTION){
            eventSelectClass();
            return;
        }
        eventCompleteChar();
    }
    if(AUTO_WIZ == 2) InputCre("creator");
    else {
        receive("该游戏已启用自动创建者模式。\n");
        receive("这意味着如果你希望，可以自动\n");
        receive("提升为创建者状态。\n\n");
        receive("如果你想成为玩家，输入: player\n");
        receive("如果你想成为创建者，输入: creator\n");
        receive("你的选择是什么？\n");
        input_to((: InputCre :), I_NOESC);
    }
}

private void eventSelectClass(){
    receive("\n\n你现在必须选择一个职业。\n");
    receive("选择职业会影响你角色的技能。\n");
    receive("\n你可以使用以下命令：\n");
    receive("\tlist - 列出所有可选的职业\n");
    receive("\thelp - 了解职业的含义\n");
    receive("\thelp 职业名称 - (例如 \"help explorer\") 获取特定职业的信息\n");
    receive("\tpick 职业名称 - 为你自己选择一个特定的职业\n");
    receive("\n\t可选职业: ");
    receive(implode(sort_array(CLASSES_D->GetClasses(1), 1), " "));
    receive("\nClass: \n");
    input_to((: InputClass :), I_NOESC);
}

private void InputClass(string str){
    string cmd, args;
    string *valid = ( CLASSES_D->GetClasses(1) || ({}) );

    if( str == "" || !str ) {
        receive("\nClass: ");
        input_to((: InputClass :), I_NOESC);
        return;
    }
    if( sscanf(str, "%s %s", cmd, args) != 2 ) {
        cmd = str;
        args = 0;
    }
    if(member_array(cmd, valid) != -1){
        args = cmd;
        cmd = "pick";
    }
    switch(cmd) {
        case "list":
            cmdListClasses();
        return;

        case "help":
            cmdHelpClass(args);
        return;

        case "pick":
            cmdPickClass(args);
        return;

        default:
        receive("\n无效命令。\n职业: \n");
        input_to((: InputClass :), I_NOESC);
        return;
    }
}

private void cmdHelpClass(string args){
    function f;
    string* Classes = CLASSES_D->GetClasses(1);
    string help;

    f = function(string str) {
        receive("\nClass: \n");
        input_to((: InputClass :), I_NOESC);
    };
    if( !args ) {
        help = HELP_D->GetHelp("player documents classes") ||
            "读取帮助文件出错。\n";
        eventPage(explode(help, "\n"), MSG_HELP, f);
        return;
    }
    if( member_array(args = lower_case(args), Classes) == -1 ) {
        receive("该职业不存在。\n\n职业: \n");
        input_to((: InputClass :), I_NOESC);
        return;
    }
    help = HELP_D->GetHelp("classes "+args);
    eventPage(explode(help, "\n"), MSG_HELP, f);
}

private void cmdListClasses() {
    string list;

    list = format_page(sort_array(CLASSES_D->GetClasses(1), 1), 5);
    receive(list);
    receive("\nClass: \n");
    input_to((: InputClass :), I_NOESC);
}

private void cmdPickClass(string args) {
    if( !args || args == "" ) {
        receive("你必须指定一个要选择的职业。\n\n职业: \n");
        input_to((: InputClass :), I_NOESC);
        return;
    }
    if( member_array(args = lower_case(args),
                CLASSES_D->GetClasses(1)) == -1 ) {
        receive("该职业不存在。\n职业: \n");
        input_to((: InputClass :), I_NOESC);
        return;
    }
    trabajo = args;
    eventCompleteChar();
}

int eventCre(string str){
    mixed mixt;
    if(yescre && AUTO_WIZ > 0){
        mixt = load_object("/secure/cmds/admins/encre")->cmd(str);
    }
    destruct(this_object());
    return 1;
}

int eventCheckPending(string str){
    mixed mixt;
    str = lower_case(str);
    if(member_array(str,PLAYERS_D->GetPendingEncres()) != -1){
        PLAYERS_D->RemovePendingEncre(str);
        mixt = load_object("/secure/cmds/admins/encre")->cmd(str);
    }
    else if(member_array(str,PLAYERS_D->GetPendingDecres()) != -1){
        PLAYERS_D->RemovePendingDecre(str);
        mixt = load_object("/secure/cmds/admins/decre")->cmd(str);
    }
    if(member_array(str,PLAYERS_D->GetPendingPauses()) != -1){
        PLAYERS_D->RemovePendingPause(str);
        mixt = Player->SetPlayerPaused(1);
    }
    else if(member_array(str,PLAYERS_D->GetPendingUnpauses()) != -1){
        PLAYERS_D->RemovePendingUnpause(str);
        mixt = Player->SetPlayerPaused(0);
    }
    destruct(this_object());
    return 1;
}

void InputCre(string str){
    if(!str || str == "" || !sizeof(str) || !stringp(str)) str = "foo";
    if(str != "creator" && str != "player"){
        receive("\n无效选择。\n");
        receive("如果你想成为玩家，输入: player\n");
        receive("如果你想成为创建者，输入: creator\n");
        receive("你的选择是什么？\n");
        input_to((: InputCre :), I_NOESC);
        return;
    }
    if(str == "creator"){
        yescre = 1;
        receive("\n---\n你将在登录后不久自动成为创建者");
        receive("\n---\n");
    }
    if(CLASS_SELECTION){
        eventSelectClass();
        return;
    }
    else {
        eventCompleteChar();
    }
}

void eventCompleteChar(){
    Player->SetRace(raza);
    Player->SetProperty("brand_spanking_new",1);
    Player->AddCurrency("silver",random(100)+57);
    Player->SetPassword(Passwort);
    Player->SetGender(Gendre);
    Player->SetCapName(CapNamen);
    Player->SetEmail(E_Mail);
    Player->SetRealName(TrueName);
    if(lower_case(raza) != "poleepkwa"){
        Player->SetLanguage("Common",100);
        Player->SetDefaultLanguage("Common");
        this_player()->SetWimpy(20);
    }
    else {
        Player->SetGender("neutral");
    }
    if(blindmode){
        Player->SetProperty("wizmapping", 0);
        Player->SetProperty("minimapping", 0);
        Player->SetProperty("screen reader", 1);
    }
    if(yescre) Player->SetPrompt("cwd");
    else Player->SetPrompt("status");
    if(trabajo) Player->ChangeClass(trabajo);
    this_player()->SetTerminal("ansi");
    PLAYERS_D->AddPlayerInfo(Name);
    call_out( (: eventCre, Name :), 3);
    eventEnterGame();
}

private void eventTimeout() {
    if( !interactive(this_object()) ) {
        Destruct();
    }
    else if( query_idle(this_object()) > LOGON_TIMEOUT ) {
        receive("\n登录超时。\n");
        Destruct();
    }
    else call_out( (: eventTimeout :), LOGON_TIMEOUT );
}

varargs int eventPrint(string msg, mixed cl, mixed arg3) {
    if( !cl || !intp(cl) ) return 0;
    if( cl & MSG_NOWRAP ) receive(strip_colours(msg));
    else receive(wrap(strip_colours(msg), GetScreen()[0]));
    return 1;
}

private private void Destruct() {
    if( Player && !NetDead ) destruct(Player);
    remove_call_out();
    destruct(this_object());
}

void eventDestruct() {
    Destruct();
}

string GetKeyName() {
    if(!interactive(this_object())) return 0;
    else if(Name) return Name;
    else return "";
}

string GetCapName() {
    string tmp;

    tmp = GetKeyName();
    return (tmp ? capitalize(tmp) : "");
}

private void terminal_type(string str) {
    if( !stringp(str) ) return;
    else Terminal = lower_case(str);
}

private void window_size(int width, int height) {
    Screen = ({ width, height });
}

private void CreateGuest() {
    receive("输入你想要使用的名字: \n");
    input_to( (: GetGuestName :), I_NOESC );
}

private void GetGuestName(string nom) {
    object ob;

    return;
    if( !nom || nom == "" || user_exists(convert_name(nom)) ) {
        receive("非法名字选择，请重试: ");
        return;
    }
    ob->SetCapName(nom);
    exec(ob, this_object());
    ob->Setup();
}

int *GetScreen() {
    if( Screen ) return Screen;
    else return ({ 79, 25 });
}

void SetLastError(mapping m) {
    if (previous_object() != master()) return;
    LastError = m;
}

mapping GetLastError() {
    string caller = base_name(previous_object());
    if( caller == "/secure/cmds/creator/dbxwhere" ||
            caller  == "/secure/cmds/player/dbxframe" ) return LastError;
    error("Privilege Violation: " + caller);
}

int GetMaxPlayers(){
    return MaxPlayers;
}

void receive_environ(mixed foo){
    mixed *uservars;
    uservars = explode(foo, sprintf("%c", __ANSI_SUBSTITUTE__));
    foreach(string uservar in uservars){
        mixed tmp_arr = explode(uservar, sprintf("%c", 1));
        if(!sizeof(tmp_arr)) continue;
        if(sizeof(tmp_arr) < 2) tmp_arr += ({ 0 });
        UserVars[tmp_arr[0]] = tmp_arr[1];
    }
    if(!telopt_user && UserVars["USER"]) telopt_user = UserVars["USER"];
}
