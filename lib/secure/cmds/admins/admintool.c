#include <lib.h>
#include <privs.h>
#include <daemons.h>

inherit LIB_DAEMON;

private void validate() {
    if(!this_player()) return 0;
    if( !(master()->valid_apply(({ "ASSIST" }))) )
        error("Illegal attempt to access admintool: "+get_stack()+" "+identify(previous_object(-1)));
}

varargs int Menu(string str);
int MainMenu();
int MainMenuChoice();
int GeneralMenu();
int DaemonMenu();
int UsersMenu();
int DriverMenu();
int GroupsMenu();
int ToggleMudLock();
int ShowLock();
int SetTZ();
int eventSetTZ(string str);
int ChangeEmail();
varargs int eventChangeEmail(string str, int auto);
int SetReboot();
int eventSetReboot(int i);
int AddClass();
int eventAddClass(string str);
int RemoveClass();
int eventRemoveClass(string str);
int AddRace();
int eventAddRace(string str);
int RemoveRace();
int PlayerRace(string str);
int eventRemoveRace(string str);
int AddCurrency();
int eventAddCurrency(string str);
int CurrencyRate(string str);
int CurrencyWeight(string str);
int CurrencyInflation(string str);
int RemoveCurrency();
int eventRemoveCurrency(string str);
int EncrePlayer();
int eventEncrePlayer(string str);
int DecreCreator();
int eventDecreCreator(string str);
mixed EnCre(string args);
mixed DeCre(string args);
int RidUser();
int eventRidUser(string str);
int LogRid(string str);
int DoRid(string who);
int BanishUser();
int eventBanishUser(string str);
int UnBanishUser();
int eventUnBanishUser(string str);
int ChangeName();
int eventChangeName(string str);
int ChangePort();
int eventChangePort(int i);
int ShutDownMud();
int eventShutDownMud(string str);
int RemoveGroup();
int eventRemoveGroup(string str);
int AddGroup();
int eventAddGroup(string str);
int ModGroup();
int eventModGroup(string str);
int eventEditGroup(string str);
int ShowGroups();

string process_input(string str);

string global_group_temp, menu, racepath, currency, ridded, globalstr, file;
string *currencies;
string gnom, gstr;

float rate, weight, inflation;


mixed InvalidChoice(){
    validate();
    write("无效选择，请重试或输入 q 退出。\n");
    Menu();
    return 1;
}

int PlaceHolder(){
    validate();
    write("此功能尚未定义。");
    Menu();
    return 1;
}

varargs int Menu(string str){
    validate();
    if(str) menu = str;
    if(!menu) menu = "main";

    switch (menu){
        case "main" : MainMenu(); break;
        case "general" : GeneralMenu(); break;
        case "daemon" : DaemonMenu();break;
        case "users" : UsersMenu();break;
        case "driver" : DriverMenu();break;
        case "groups" : GroupsMenu();break;
        default : menu = "main"; MainMenu(); break;
    }
    return 1;
}

string process_input(string str){
    validate();
    switch (str) {
        case "q" : write("好的，退出管理工具。\n再见。\n");return " ";
        case "x" : write("好的，退出管理工具。\n再见。\n");return " ";
        case "y" : write("好的，退出管理工具。\n再见。\n");return " ";
        case "z" : Menu("main"); break;
        case "1" : Menu("general"); break;
        case "2" : Menu("daemon");break;
        case "3" : Menu("users");break;
        case "4" : Menu("driver");break;
        case "5" : Menu("groups");break;
        case "a" : ToggleMudLock();break;
        case "b" : ShowLock();break;
        case "c" : SetTZ();break;
        case "d" : ChangeEmail();break;
        case "e" : SetReboot();break;
        case "f" : AddClass();break;
        case "g" : RemoveClass();break;
        case "h" : AddRace();break;
        case "i" : RemoveRace();break;
        case "j" : AddCurrency();break;
        case "k" : RemoveCurrency();break;
        case "n" : RidUser();break;
        case "o" : BanishUser();break;
        case "p" : UnBanishUser();break;
        case "r" : ChangeName();break;
        case "s" : ChangePort();break;
        case "t" : AddGroup();break;
        case "u" : RemoveGroup();break;
        case "v" : ModGroup();break;
        case "w" : ShowGroups();break;
        case "SD": ShutDownMud();break;
        default : InvalidChoice();
    }
    return "(process_input fun finished.)";
}


varargs mixed MainMenu(string str) {
    string tmp;
    validate();
    tmp = "\tDead Souls 管理工具\n";
    tmp += "\t=====================\n\n";
    tmp += "\t\t1) 通用设置\n";
    tmp += "\t\t2) 守护进程\n";
    tmp += "\t\t3) 用户管理\n";
    tmp += "\t\t4) 驱动设置\n";
    tmp += "\t\t5) 权限组\n\n";
    tmp += "\t\tq) 退出\n";

    this_player()->eventPrint(tmp, "foo");

    input_to((: process_input :));
    return 1;
}

protected int GeneralMenu() {
    string tmp;

    validate();
    tmp = "\tDead Souls 管理工具 - 通用设置\n";
    tmp += "\t\n\n";
    tmp += "\t\ta) 切换游戏锁定状态\n";
    tmp += "\t\tb) 显示当前锁定状态\n";
    tmp += "\t\tc) 更改时区\n";
    tmp += "\t\td) 更改管理员邮箱\n";
    tmp += "\t\te) 更改重启间隔\n";
    tmp += "\t\tSD) 关闭游戏\n\n";
    tmp += "\t\tz) 返回主菜单\n";
    tmp += "\t\tq) 退出\n";

    this_player()->eventPrint(tmp, "foo");
    input_to((: process_input :));
    return 1;
}

int DaemonMenu() {
    string tmp;

    validate();
    tmp = "\tDead Souls 管理工具 - 守护进程\n";
    tmp += "\t\n\n";
    tmp += "\t\tf) 添加职业\n";
    tmp += "\t\tg) 移除职业\n";
    tmp += "\t\th) 添加种族\n";
    tmp += "\t\ti) 移除种族\n";
    tmp += "\t\tj) 添加货币\n";
    tmp += "\t\tk) 移除货币\n\n";
    tmp += "\t\tz) 返回主菜单\n";
    tmp += "\t\tq) 退出\n";

    this_player()->eventPrint(tmp, "foo");
    input_to((: process_input :));
    return 1;
}

int UsersMenu() {
    string tmp;

    validate();
    tmp = "\tDead Souls 管理工具 - 用户管理\n";
    tmp += "\t\n\n";
    tmp += "\t\tn) 彻底删除用户\n";
    tmp += "\t\to) 封禁用户名\n";
    tmp += "\t\tp) 解封用户名\n\n";
    tmp += "\t\tz) 返回主菜单\n";
    tmp += "\t\tq) 退出\n";

    this_player()->eventPrint(tmp, "foo");
    input_to((: process_input :));

    return 1;
}

int DriverMenu(){
    string tmp;

    validate();
    tmp = "\tDead Souls 管理工具 - 驱动设置\n";
    tmp += "\t^^^^^^^^^^^^^^^^^^^^^^*******^^^^^\n";
    tmp += "\t\n\n";
    tmp += "\t\tr) 显示游戏名称\n";
    tmp += "\t\ts) 更改游戏连接端口\n\n";
    tmp += "\t\tz) 返回主菜单\n";
    tmp += "\t\tq) 退出\n";

    this_player()->eventPrint(tmp, "foo");
    input_to((: process_input :));

    return 1;
}

int GroupsMenu(){
    string tmp;

    validate();
    tmp = "\tDead Souls 管理工具 - 权限组\n";
    tmp += "\t^^^^^^^^^^^^^^^^^^^^^^*******^^^^^\n";
    tmp += "\t\n\n";
    tmp += "\t\tt) 添加权限组\n";
    tmp += "\t\tu) 移除权限组\n";
    tmp += "\t\tv) 修改权限组\n";
    tmp += "\t\tw) 显示权限组\n\n";
    tmp += "\t\tz) 返回主菜单\n";
    tmp += "\t\tq) 退出\n";
    tmp += "\n\n注意：此菜单已%^RED%^弃用%^RESET%^。\n";
    tmp += "请使用 \"groupmod\" 命令代替。\n";

    this_player()->eventPrint(tmp, "foo");
    input_to((: process_input :));

    return 1;
}

string GetHelp(){
    return ("语法: <admintool>\n\n"
            "菜单驱动的工具，用于编辑游戏配置。\n"
            "要更改游戏名称或端口号，请选择驱动设置菜单。\n"
            "使用用户管理菜单将玩家提升为创造者身份。\n"
            "使用权限组菜单将某人设为助理管理员。\n");
}

int ToggleMudLock(){
    string *line_array;
    string lockline, newline, newfile, line_string, junk;
    int num;

    validate();
    line_string = read_file(CONFIG_H);
    if(!sizeof(line_string)) write("无法读取文件。");
    line_array = explode(line_string, "\n");
    if(!sizeof(line_array)) write("数组长度为零。");

    foreach(string line in line_array){
        if(strsrch(line,"MUD_IS_LOCKED") != -1){
            lockline = line;
        }
    }
    if(sscanf(lockline,"%s%d",junk, num) < 2) {
        write("操作失败，您需要立即手动编辑 "+CONFIG_H+" 文件。");
        return 0;
    }
    if(num == 0) {
        write("正在锁定游戏。\n");
        num = 1;
    }
    else {
        write("正在解锁游戏。\n");
        num = 0;
    }
    newline = junk + num;
    newfile = replace_string(line_string, lockline, newline);
    write_file(CONFIG_H,newfile,1);
    load_object("/secure/cmds/creators/update")->cmd("/secure/daemon/master");
    load_object("/secure/cmds/creators/update")->cmd("/secure/lib/connect");
    write("\n");
    Menu();
    return 1;
}

int ShowLock(){
    validate();
    if(load_object("/secure/daemon/master")->is_locked()){
        write("游戏已锁定，只有管理员和指定人员可以登录。\n");
    }
    else write("游戏未锁定，玩家可以自由登录。\n");
    Menu();
    return 1;
}


int SetTZ(){
    validate();
    write("请输入所需的时区：\n");
    input_to( (: eventSetTZ :) );
    return 1;
}

int eventSetTZ(string str){
    string ret;

    validate();
    ret = set_tz(str);
    write(ret+"\n");
    load_object("/secure/cmds/creators/update")->cmd("/daemon/time");
    Menu();
    return 1;
}

int ChangeEmail(){
    validate();
    write("当前管理员邮箱是："+admin_email());
    write("请输入游戏管理员的新邮箱地址：\n");
    input_to( (: eventChangeEmail :) );
    return 1;
}

varargs int eventChangeEmail(string str, int auto){
    string *line_array;
    string lockline, newline, newfile, line_string, junk, email;

    validate();
    if(strsrch(str,"@") == -1 ) {
        write("这不是一个有效的邮箱地址。");
        if(!auto) Menu();
        return 0;
    }
    str == replace_string(str, "#", "");
    line_string = read_file(CONFIG_H);
    if(!sizeof(line_string)) write("无法读取文件。");
    line_array = explode(line_string, "\n");
    if(!sizeof(line_array)) write("数组长度为零。");
    foreach(string line in line_array){
        if(strsrch(line,"ADMIN_EMAIL") != -1){
            lockline = line;
        }
    }
    if(sscanf(lockline,"%s\"%s\"",junk, email) < 2) {
        write("操作失败，您需要立即手动编辑 "+CONFIG_H+" 文件。");
        if(!auto) Menu();
        return 0;
    }

    newline = junk + "\""+str+"\"";
    newfile = replace_string(line_string, lockline, newline);
    write_file(CONFIG_H,newfile,1);
    load_object("/secure/cmds/creators/update")->cmd("/secure/sefun/sefun");
    write("\n");
    if(!auto) Menu();
    return 1;
}

int SetReboot(){
    validate();
    write("当前重启间隔设置为 "+EVENTS_D->GetRebootInterval()+" 小时。");
    write(load_object("/cmds/players/nextreboot")->cmd("string"));
    write("请输入新的间隔时间（小时）：\n");
    input_to( (: eventSetReboot :) );
    return 1;
}

int eventSetReboot(mixed i){
    int num, check;

    validate();
    if(!intp(i) && !sscanf(i,"%d",num)){
        write("设置新间隔失败。\n");
        Menu();
        return 1;
    }
    if(intp(i)) num = i;
    check = EVENTS_D->SetRebootInterval(num);
    reload(EVENTS_D);
    if(num == check)
        write("重启间隔已设置为 "+EVENTS_D->GetRebootInterval()+" 小时。");
    else
        write("重启间隔无法设置，当前间隔为："+check+" 小时。");
    Menu();
    return 1;
}

int AddClass(){
    validate();
    write("当前可用的职业："+implode(load_object(CLASSES_D)->GetClasses()," "));
    write("请输入您要添加的职业名称：\n");
    input_to( (: eventAddClass :) );
    return 1;
}

int eventAddClass(string str){
    string classpath;
    mixed* classes;

    validate();
    if(!str) {
        write("无效的职业名称。\n");
        Menu();
        return 1;
    }

    classpath = "/secure/cfg/classes/"+str;
    write("正在查找 "+classpath+"...");
    classes = load_object(CLASSES_D)->GetClasses();
    if(member_array(str,classes) != -1) {
        write("该职业已经存在。\n");
        Menu();
        return 1;
    }
    if(file_size(classpath) < 1) {
        write("要添加职业，您必须先创建并编辑一个职业文件，");
        write("然后将其放置在 /secure/cfg/classes 目录中与其他职业文件一起。\n");
        write("操作失败：没有找到该职业文件\n");
        Menu();
        return 1;
    }
    CLASSES_D->AddClass(classpath);
    write("当前可用的职业："+implode(load_object(CLASSES_D)->GetClasses()," ")+"\n");

    Menu();
    return 1;
}

int RemoveClass(){
    validate();
    write("当前可用的职业："+implode(load_object(CLASSES_D)->GetClasses()," "));
    write("请输入您要移除的职业：\n");
    input_to( (: eventRemoveClass :) );
    return 1;
}

int eventRemoveClass(string str){
    validate();
    if(!str){
        write("这不是一个有效的职业。\n");
        Menu();
        return 1;
    }

    if(member_array(str,load_object(CLASSES_D)->GetClasses()) == -1) {
        write("该职业已经不存在了。\n");
        Menu();
        return 1;
    }

    load_object(CLASSES_D)->RemoveClass(str);
    write("当前可用的职业："+implode(load_object(CLASSES_D)->GetClasses()," ")+"\n");
    Menu();
    return 1;
}

int AddRace(){
    validate();
    write("当前可用的种族："+implode(load_object(RACES_D)->GetRaces()," "));
    write("请输入您要添加的种族名称：\n");
    input_to( (: eventAddRace :) );
    return 1;
}

int eventAddRace(string str){
    mixed* races;

    validate();
    if(!str) {
        write("无效的种族名称。\n");
        Menu();
        return 1;
    }

    racepath = "/secure/cfg/races/"+str;
    write("正在查找 "+racepath+"...");
    races = load_object(RACES_D)->GetRaces();
    if(member_array(str,races) != -1) {
        write("该种族已经存在。\n");
        Menu();
        return 1;
    }
    if(file_size(racepath) < 1) {
        write("要添加种族，您必须先创建并编辑一个种族文件，");
        write("然后将其放置在 /secure/cfg/races 目录中与其他种族文件一起。\n");
        write("操作失败：没有找到该种族文件\n");
        Menu();
        return 1;
    }

    write("玩家是否可以选择此种族？");
    write("除 yes 以外的回答将被视为否。\n");
    input_to( (: PlayerRace :) );
    return 1;
}

int PlayerRace(string str){
    string *response_array = ({"yes","ok","y","yeah","yes, please"});

    validate();
    if(!str) str = "no";
    if(member_array(str,response_array) != -1) RACES_D->AddRace(racepath, 1);
    else RACES_D->AddRace(racepath);
    write("当前可用的种族："+implode(load_object(RACES_D)->GetRaces()," ")+"\n");

    Menu();
    return 1;
}

int RemoveRace(){
    validate();
    write("当前可用的种族："+implode(load_object(RACES_D)->GetRaces()," "));
    write("请输入您要移除的种族：\n");
    input_to( (: eventRemoveRace :) );
    return 1;
}

int eventRemoveRace(string str){
    validate();
    if(!str){
        write("这不是一个有效的种族。\n");
        Menu();
        return 1;
    }

    if(member_array(str,load_object(RACES_D)->GetRaces()) == -1) {
        write("该种族已经不存在了。\n");
        Menu();
        return 1;
    }

    load_object(RACES_D)->RemoveRace(str);
    write("当前可用的种族："+implode(load_object(RACES_D)->GetRaces()," ")+"\n");
    Menu();
    return 1;
}

int AddCurrency(){
    validate();
    write("当前可用的货币："+implode(ECONOMY_D->__QueryCurrencies()," "));
    write("请输入您要添加的货币名称：\n");
    input_to( (: eventAddCurrency :) );
    return 1;
}

int eventAddCurrency(string str){
    string query;

    validate();
    currency = str;
    if(!str || str == "") {
        write("无效的货币名称。\n");
        Menu();
        return 1;
    }

    currencies = ECONOMY_D->__QueryCurrencies();
    if(member_array(str,currencies) != -1) {
        write("该货币已经存在。\n");
        Menu();
        return 1;
    }
    if(sizeof(currencies) > 2){
        query = "其汇率或价值应该是多少？作为参考，"+currencies[0]+" ";
        query += "的汇率为 "+ ECONOMY_D->__Query(currencies[0],"rate")+"，"+currencies[1]+" ";
        query += "的汇率为 "+ ECONOMY_D->__Query(currencies[1],"rate")+"，"+currencies[2]+" ";
        query += "的汇率为 "+ ECONOMY_D->__Query(currencies[2],"rate")+"。\n";
    }
    else query = "其汇率或价值应该是多少？";

    write(query);
    input_to( (: CurrencyRate :) );
    return 1;
}

int CurrencyRate(string str){
    string query;

    validate();
    if(!str || !sscanf(str,"%f",rate) ){
        write("无效的汇率，货币未添加。\n");
        Menu();
        return 1;
    }
    if(sizeof(currencies) > 2){
        query = "其重量应该是多少？作为参考，"+currencies[0]+" ";
        query += "的重量为 "+ ECONOMY_D->__Query(currencies[0],"weight")+"，"+currencies[1]+" ";
        query += "的重量为 "+ ECONOMY_D->__Query(currencies[1],"weight")+"，"+currencies[2]+" ";
        query += "的重量为 "+ ECONOMY_D->__Query(currencies[2],"weight")+"。\n";
    }
    else query = "其重量应该是多少？";
    write(query);
    input_to( (: CurrencyWeight :) );
    return 1;
}


int  CurrencyWeight(string str){
    string query;

    validate();
    if(!str || !sscanf(str,"%f",weight) ){
        write("无效的重量，货币未添加。\n");
        Menu();
        return 1;
    }
    if(sizeof(currencies) > 2){
        query = "其通胀率应该是多少？作为参考，"+currencies[0]+" ";
        query += "的通胀率为 "+ ECONOMY_D->__Query(currencies[0],"inflation")+"，"+currencies[1]+" ";
        query += "的通胀率为 "+ ECONOMY_D->__Query(currencies[1],"inflation")+"，"+currencies[2]+" ";
        query += "的通胀率为 "+ ECONOMY_D->__Query(currencies[2],"inflation")+"。\n";
    }
    else query = "其通胀率应该是多少？";
    write(query);
    input_to( (: CurrencyInflation :) );
    return 1;
}

int CurrencyInflation(string str){
    validate();
    if(!str || !sscanf(str,"%f",inflation) ){
        write("无效的通胀率，货币未添加。\n");
        Menu();
        return 1;
    }
    write(identify(previous_object(-1)));
    write("ECONOMY_D->add_currency(\""+currency+"\", "+rate+", "+inflation+", "+weight+");");
    ECONOMY_D->add_currency(currency, rate, inflation, weight);
    write("谢谢，货币已添加。\n");
    Menu();
    return 1;
}

int RemoveCurrency(){
    validate();
    currencies = ECONOMY_D->__QueryCurrencies();
    if(sizeof(currencies) == 1) {
        write("请在移除最后一种货币之前先添加另一种货币。");
        write("移除最后一种货币会导致游戏出现异常行为。");
        return 1;
    }
    write("可用的货币："+ identify(currencies) +"。");
    write("您要移除哪种货币？\n");

    input_to( (: eventRemoveCurrency :) );
    return 1;
}

int eventRemoveCurrency(string str){
    validate();
    if(!str || member_array(str, currencies) == -1) {
        write("无效的货币，没有移除任何货币。\n");
        Menu();
        return 1;
    }
    ECONOMY_D->remove_currency(str);
    write("剩余的货币："+identify(ECONOMY_D->__QueryCurrencies())+"\n");
    Menu();
    return 1;
}

int RidUser(){
    validate();
    write("请输入您要删除的玩家名称。\n");
    input_to( (: eventRidUser :) );
    return 1;
}

int eventRidUser(string str){
    validate();
    if(!str){
        write("无效的输入。\n");
        Menu();
        return 1;
    }

    if( !user_exists(str) ) {
        write("没有这个人："+str+"。\n");
        Menu();
    }
    DoRid(str);
    return 1;
}

int DoRid(string who) {
    object ob;
    string str;

    validate();
    ridded = lower_case(who);
    str = convert_name(who);
    who = capitalize(who);
    if( member_group(str, PRIV_SECURE) || member_group(str, PRIV_ASSIST) ){
        write("您必须先将此人从安全权限组中移除。");
        Menu();
        return 1;
    }
    if( ob = find_player(ridded)) {
        who = ob->GetCapName();
        message("system", "您正在被从 " + mud_name() + " 中删除。",
                ob);
        ob->eventForce("quit");
    }
    file = player_save_file(ridded);
    write("目标是："+ridded);
    write("请输入删除 " + ridded + " 的原因。\n");
    unguarded( (: rm(file) :) );
    input_to( (: LogRid :) );
    return 1;
}

int LogRid(string str){
    validate();
    globalstr = str;
    log_file("rid", "\n" + ridded + " by " + this_player()->GetCapName() + "\n" + str + "\n");
    write(ridded + " 已从 " + mud_name() + " 中删除。");
    Menu();
    return 1;
}

int BanishUser(){
    validate();
    write("请输入要封禁的名称：\n");
    input_to( (: eventBanishUser :) );
    return 1;
}

int eventBanishUser(string str){
    validate();
    if(member_array(str,BANISH_D->query_banished()) != -1) {
        write("该名称已被封禁。\n");
        Menu();
        return 1;
    }
    if(!user_exists(str = lower_case(str))) {
        write(capitalize(str)+" 现在已被封禁。\n");
        catch(call_other(BANISH_D, "banish_name", str));
    }
    else {
        write("该名称的玩家已存在。\n");
        this_player()->eventPrint(FINGER_D->GetFinger(str));
    }
    Menu();
    return 1;
}

int UnBanishUser(){
    validate();
    write("请输入要解封的名称：\n");
    input_to( (: eventUnBanishUser :) );
    return 1;
}

int eventUnBanishUser(string str){
    validate();
    if(member_array(str,BANISH_D->query_banished()) == -1) {
        write("该名称未被封禁。");
        Menu();
        return 1;
    }
    catch(call_other(BANISH_D, "unbanish_name", str));
    write(str+" 已被解封。\n");
    Menu();
    return 1;
}

int ChangeName(){
    validate();
    write("当前游戏名称是 "+mud_name());
    write("要更改游戏名称，请使用命令：");
    write("mudconfig mudname <名称>");
    Menu();
    return 1;
}

varargs int eventChangeName(string newname, int automated){
    string *line_array;
    string mconfig, nameline, newline, newfile, line_string, junk, name;

    validate();
    if(!newname || newname == "") {
        write("名称更改已取消。\n");
        Menu();
        return 1;
    }

    if(automated){
        if(mud_name() != "DeadSoulsNew" &&
                mud_name() != "DeadSoulsWin")
            return 0;
    }

    if(!find_object(INSTANCES_D) || !ENABLE_INSTANCES ||
            INSTANCES_D->GetMyInstanceName() == "global"){
        mconfig = "/secure/cfg/mudos.cfg";
    }
    else {
        mconfig = "/secure/cfg/mudos."+query_host_port()+".cfg";
    }

    line_string = read_file(mconfig);
    if(!sizeof(line_string)) write("无法读取文件。");
    line_array = explode(line_string, "\n");
    if(!sizeof(line_array)) write("数组长度为零。");

    if(!sizeof(line_array) || !sizeof(line_string)) {
        if(!automated) Menu();
        return 0;
    }

    foreach(string line in line_array){
        if(strsrch(line,"name :") != -1){
            nameline = line;
        }
    }

    if(!nameline || sscanf(nameline,"%s : %s",junk, name) < 2) {
        write("操作失败，您需要立即用原始文件覆盖 "+mconfig+"。");
        if(!automated) Menu();
        return 0;
    }

    if(automated){
        if(name != "DeadSoulsWin" && name != "DeadSouls" &&
                name != "Dead Souls" && name != "DeadSoulsNew") newname = name;
        cp(mconfig,"/secure/cfg/mudos.orig");
    }

    newline = junk + " : " + newname;
    newfile = replace_string(line_string, nameline, newline);
    write_file(mconfig,newfile,1);
    cp(mconfig,"/secure/cfg/mudos.autobak."+query_host_port());
    if(automated && query_windows()){
        cp(mconfig,"/secure/cfg/mudos.win32");
    }
    write("\n");
    if(!automated)  {
        write("\n游戏名称已更改，请重启游戏以激活新名称。\n");
        write("\n您要现在关闭游戏以激活更改吗？\n");
        input_to( (: eventShutDownMud :) );
    }
    return 1;
}

int ChangePort(){
    validate();
    if(!find_object(INSTANCES_D) || !ENABLE_INSTANCES ||
            INSTANCES_D->GetMyInstanceName() == "global"){
        write("当前游戏网络端口是 "+query_host_port());
        write("请输入游戏的新网络端口：\n");
        input_to( (: eventChangePort :) );
    }
    else {
        write("管理工具中对实例禁用了端口更改功能。");
        Menu();
    }

    return 1;
}

varargs int eventChangePort(string newport, int automated){
    string *line_array;
    string nameline, newline, newfile, line_string, junk, name;
    int num;

    validate();
    if(!newport || newport == "") {
        write("端口更改已取消。\n");
        Menu();
        return 1;
    }

    if(!sscanf(newport,"%d", num) > 0 || num < 1 || num > 65535 ) {
        write("无效的端口：需要 1 到 65535 之间的数字。");
        write("端口更改已取消。\n");
        Menu();
        return 1;
    }

    line_string = read_file("/secure/cfg/mudos.cfg");
    if(!sizeof(line_string)) write("无法读取文件。");
    line_array = explode(line_string, "\n");
    if(!sizeof(line_array)) write("数组长度为零。");

    foreach(string line in line_array){
        if(strsrch(line,"external_port_1 :") != -1){
            nameline = line;
        }
    }

    if(!nameline || sscanf(nameline,"%s : %s",junk, name) < 2) {
        write("操作失败，您需要立即用原始文件覆盖 /secure/cfg/mudos.cfg。");
        if(!automated) Menu();
        return 0;
    }

    newline = junk + " : telnet " + newport;
    newfile = replace_string(line_string, nameline, newline);
    write_file("/secure/cfg/mudos.cfg",newfile,1);
    if(!automated)  {
        write("\n游戏端口已更改，请重启游戏以激活新端口。");
        write("注意：如果您选择的端口是 1024 或以下，您的操作系统可能要求游戏以特权用户身份运行。");
        write("\n您要现在关闭游戏以激活更改吗？\n");
        input_to( (: eventShutDownMud :) );
    }
    return 1;
}

int ShutDownMud(){
    validate();
    write("您确定吗？");
    input_to( (: eventShutDownMud :) );
    return 1;
}

int eventShutDownMud(string str){
    string *response_array = ({"yes","ok","y","yeah","yes, please"});

    validate();
    if(!str) str = "no";
    if(member_array(str,response_array) == -1){
        write("关闭已取消。\n");
        Menu();
        return 1;
    }

    write("正在关闭游戏。\n");
    if(this_player()->GetForced()) return 0;

    shout("游戏被 " + this_player()->GetKeyName() + " 关闭了。\n");
    log_file("game_log", ctime(time())+" 游戏被 "+
            this_player()->GetKeyName()+" 关闭(admintool)\n");
    foreach(object dude in users()){
        if(sizeof(base_name(dude)) && !archp(dude)) dude->eventForce("quit");
    }
    shutdown();
    write("关闭完成。");
    Menu();
    return 1;
}

int AddGroup(){
    validate();
    write("\n当前权限组文件：\n"+read_file("/secure/cfg/groups.cfg")+"\n\n");
    write("\n您要添加的权限组名称是什么？\n");
    input_to( (: eventAddGroup :) );
    return 1;
}

int eventAddGroup(string str){
    string config_file, new_config_file;
    string *line_array;
    string *top_array;
    string *bottom_array;

    validate();
    top_array = ({});
    bottom_array = ({});

    if(!str || str == "") {
        write("\n权限组添加已取消。\n");
        Menu();
        return 1;
    }
    config_file = read_file("/secure/cfg/groups.cfg");
    if(!sizeof(config_file)) {
        write("无法读取文件，添加已取消。\n");
        Menu();
        return 1;
    }

    str = upper_case(str);
    if(strsrch(config_file,"("+str+")") != -1 ) {
        write("\n该权限组已存在，添加已取消。\n");
        Menu();
        return 1;
    }

    line_array = explode(config_file, "\n");
    if(!sizeof(line_array)) {
        write("\n数组长度为零，添加已取消。\n");
        Menu();
        return 1;
    }

    foreach(string line in line_array){
        if(strsrch(line,"(") != -1 &&
                    first(line,1) != "#"){
                bottom_array += ({ line });
                }
                else top_array += ({ line });
                }

                bottom_array += ({"("+str+") "});

                new_config_file = implode(top_array,"\n");
                new_config_file += "\n";
                new_config_file += implode(bottom_array,"\n");
                write_file("/secure/cfg/groups.cfg",new_config_file,1);
                write("\n权限组 "+str+" 已添加。\n");
                load_object("/secure/cmds/creators/update")->cmd("/secure/daemon/master");
                load_object("/secure/cmds/creators/update")->cmd("/secure/lib/connect");
                Menu();
                return 1;
                }

                int RemoveGroup(){
                    validate();
                    write("\n当前权限组文件：\n"+read_file("/secure/cfg/groups.cfg")+"\n\n");
                    write("\n您要移除的权限组名称是什么？\n");
                    input_to( (: eventRemoveGroup :) );
                    return 1;
                }

int eventRemoveGroup(string str){
    string config_file, new_config_file;
    string *line_array;
    string *top_array;
    string *bottom_array;

    validate();
    top_array = ({});
    bottom_array = ({});

    if(!str || str == "") {
        write("\n权限组移除已取消。\n");
        Menu();
        return 1;
    }
    config_file = read_file("/secure/cfg/groups.cfg");
    if(!sizeof(config_file)) {
        write("无法读取文件，移除已取消。\n");
        Menu();
        return 1;
    }

    str = upper_case(str);
    if(strsrch(config_file,"("+str+")") == -1 ) {
        write("\n该权限组不存在，移除已取消。\n");
        Menu();
        return 1;
    }

    if(str == "SECURE" || str == "ASSIST"){
        write("\n这是一个已配置的管理权限组，您不能使用管理工具移除它。");
        write("如果您确实知道自己在做什么并想移除该权限组，您需要手动使用编辑器操作。\n");
        Menu();
        return 1;
    }

    line_array = explode(config_file, "\n");
    if(!sizeof(line_array)) {
        write("\n数组长度为零，移除已取消。\n");
        Menu();
        return 1;
    }

    foreach(string line in line_array){
        if(strsrch(line,"(") != -1 && first(line,1) != "#"){
                if(strsrch(line,"("+str+")") == -1 ) bottom_array += ({ line });
                }
                else if(strsrch(line,"("+str+")") == -1 ) top_array += ({ line });
                }

                new_config_file = implode(top_array,"\n");
                new_config_file += "\n";
                new_config_file += implode(bottom_array,"\n");
                write_file("/secure/cfg/groups.cfg",new_config_file,1);
                load_object("/secure/cmds/creators/update")->cmd("/secure/daemon/master");
                load_object("/secure/cmds/creators/update")->cmd("/secure/lib/connect");
                write("\n权限组 "+str+" 已移除。\n");
                Menu();
                return 1;
                }

                int ModGroup(){
                validate();
                write("\n当前权限组文件：\n"+read_file("/secure/cfg/groups.cfg")+"\n\n");
                write("\n您要修改的权限组名称是什么？\n");
                input_to( (: eventModGroup :) );
                return 1;
                }

int eventModGroup(string str){
    string config_file;

    validate();
    if(!str || str == "") {
        write("\n权限组修改已取消。\n");
        Menu();
        return 1;
    }
    config_file = read_file("/secure/cfg/groups.cfg");
    if(!sizeof(config_file)) {
        write("无法读取文件，修改已取消。\n");
        Menu();
        return 1;
    }

    str = upper_case(str);
    if(strsrch(config_file,"("+str+")") == -1 ) {
        write("\n该权限组不存在，修改已取消。\n");
        Menu();
        return 1;
    }

    if(!sizeof(explode(config_file, "\n"))) {
        write("\n数组长度为零，修改已取消。\n");
        Menu();
        return 1;
    }

    write(str);
    global_group_temp = str;
    write("权限组格式必须正确输入。如果成员是张三、李四和王五，请输入：\n");
    write("张三:李四:王五\n");
    write("\n重要的是在名字之间加上冒号。如果只有一个成员赵六，请输入：\n");
    write("赵六\n");
    write("\n您希望该权限组包含哪些成员？\n");
    input_to ( (: eventEditGroup :) );
    return 1;
}

int eventEditGroup(string members){
    string config_file, new_config_file, str;
    string *line_array;
    string *top_array;
    string *bottom_array;
    string *dudes;

    validate();
    members = lower_case(members);
    top_array = ({});
    bottom_array = ({});

    config_file = read_file("/secure/cfg/groups.cfg");
    line_array = explode(config_file, "\n");
    str = global_group_temp;
    global_group_temp = "";


    if(str == "ASSIST" || str == "SECURE" ) {
        if(!securep(this_player())){
            write("只有完全管理员才能执行此操作。");
            Menu();
            return 1;
        }
    }

    if(str == "SECURE"){
        validate();
        if(!members || members == "") {
            write("您不能将 SECURE 权限组留空，修改已取消。\n");
            Menu();
            return 1;
        }
        if(strsrch(members,":") != -1) dudes = explode(members,":");
        else dudes = ({ members });

        if(member_array(this_player()->GetKeyName(),dudes) == -1) {
            write("使用管理工具修改此行时必须包含您自己，修改已取消。\n");
            Menu();
            return 1;
        }
    }

    foreach(string line in line_array){
        if(strsrch(line,"(") != -1 && first(line,1) != "#"){
                if(strsrch(line,"("+str+")") == -1 ) bottom_array += ({ line });
                }
                else if(strsrch(line,"("+str+")") == -1 ) top_array += ({ line });
                }

                new_config_file = implode(top_array,"\n");
                new_config_file += "\n";
                new_config_file += implode(bottom_array,"\n");
                new_config_file += "\n";
                new_config_file += "("+str+") "+members;
                write_file("/secure/cfg/groups.cfg",new_config_file,1);
                load_object("/secure/cmds/creators/update")->cmd("/secure/daemon/master");
                load_object("/secure/cmds/creators/update")->cmd("/secure/lib/connect");
                write("\n权限组 "+str+" 已修改。\n");
                Menu();
                return 1;
                }

                int ShowGroups(){
                validate();
                write("\n当前权限组文件：\n"+read_file("/secure/cfg/groups.cfg")+"\n\n");
                Menu();
                return 1;
                }

mixed cmd(string args) {
    validate();
    Menu("main");
    return 1;
}
