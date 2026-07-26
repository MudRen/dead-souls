/*    Installation object for Dead Souls
 *    Original author: George Reese
 */

#include <lib.h>
#include <cfg.h>
#include <dirs.h>
#include <flags.h>
#include <daemons.h>
#include <runtime_config.h>

string Name, CapName, Password;
object Admin;
int blindmode;

protected void InputName(string str);

protected void logon() {
    receive("欢迎来到 Dead Souls " + mudlib_version() +
            " 安装过程！！\n\n");
    receive("你将被问到一系列问题来创建一个管理员角色。\n\n");
    receive("你的MUD管理员用户名是什么？\n ");
    input_to((: InputName :), I_NOESC);
}

protected void InputPassword(string str);

protected void CheckBlind(string str){
    if( !str || str == "" || lower_case(str)[0..0] == "y" ) {
        receive("\n好的，已禁用默认俯视地图。\n");
        blindmode = 1;
    }
    else receive("\n好的，允许默认俯视地图行为。\n");
    receive("\n请创建一个至少5个字符的密码: \n");
    input_to((: InputPassword :), I_NOECHO | I_NOESC);
}

protected void InputName(string str) {
    if( !(BANISH_D->valid_name(Name = convert_name(CapName = str)))
            || lower_case(str) == "guest") {
        receive("这不是一个有效的名字。\n");
        receive("名字: ");
        input_to((: InputName :));
        return;
    }
    Admin = master()->player_object(Name);
    Admin->SetKeyName(Name);
    mkdir(DIR_PLAYERS "/" + Name[0..0]);
    receive("\n你是否使用为视障人士设计的屏幕阅读器？(y/n)\n");
    input_to((: CheckBlind :), I_NOESC);
}

protected void ConfirmPassword(string str);

protected void InputPassword(string str) {
    if( strlen(str) < 5 ) {
        receive("密码长度必须至少为5个字符。\n");
        receive("密码: ");
        input_to((: InputPassword :), I_NOECHO | I_NOESC);
        return;
    }
    Password = str;
    receive("\n确认密码: ");
    input_to((: ConfirmPassword :), I_NOECHO | I_NOESC);
}

protected void InputCapName(string str);

protected void ConfirmPassword(string str) {
    if( str != Password) {
        receive("\n两次输入的密码不一致。密码: ");
        input_to((: InputPassword :), I_NOECHO | I_NOESC);
        return;
    }
    Admin->SetPassword(crypt(Password, 0));
    CapName = capitalize(CapName);
    receive("\n输入你的显示名称 (" + CapName + " 是默认值): ");
    input_to((: InputCapName :), I_NOESC);
}

protected void InputGender(string str);

protected void InputCapName(string str) {
    if( !str || str == "" ) str = CapName;
    if( convert_name(str) != Name ) {
        receive("\n你不能这样做！显示名称 (按回车使用默认值): ");
        input_to((: InputCapName :), I_NOESC);
        return;
    }
    Admin->SetCapName(CapName = capitalize(str));
    receive("\n请选择一个性别 (male男性, female女性, neutral中性, 或none无): ");
    input_to((: InputGender :), I_NOESC);
}

protected void InputRealName(string str);

protected void InputGender(string str) {
    if( str ) str = lower_case(str);
    if( !str || str == "" || ((str[0] != 'f' && str[0] != 'm') &&
                member_array(str, ({"male","female","neutral","none"})) == -1)){
        receive("\n请选择一个性别 (male男性, female女性, neutral中性, 或none无): ");
        receive("男性、女性、中性还是无？ ");
        input_to((: InputGender :));
        return;
    }
    if( str[0] == 'f' ) Admin->SetGender("female");
    else if( str[0] == 'm' ) Admin->SetGender("male");
    else if( str == "none" ) Admin->SetGender("neuter");
    else Admin->SetGender("neutral");
    receive("你的真实姓名是什么？ ");
    input_to((: InputRealName :), I_NOESC);
}

protected void InputEmail(string str);

protected void InputRealName(string str) {
    if( !str || str == "" ) str = "Unknown";
    Admin->SetRealName(str);
    receive("你的电子邮箱地址是什么？ ");
    input_to((: InputEmail :), I_NOESC);
}

protected void InputEmail(string str) {
    object ob, tool;
    string tmp = "";
    string filep = DIR_PLAYERS "/"+Name[0..0]+"/"+Name+__SAVE_EXTENSION__;
    string filec = DIR_CRES "/"+Name[0..0]+"/"+Name+__SAVE_EXTENSION__;
    int foo, err;

    if( !str || str == "" ) str = "Unknown";
    load_object("secure/cmds/admins/admintool")->eventChangeEmail(str,1);
    Admin->SetEmail(str);
    Admin->SetRace("human");
    Admin->SetPrompt("cwd");
    Admin->AddCurrency("silver",random(100)+57);
    Admin->SetTown("FirstAdmin");
    Admin->eventForce("cd");
    Admin->eventForce("home");
    Admin->SetWimpy(20);
    Admin->SetTerminal("ansi");
    Admin->SetLanguage("Common",100);
    Admin->SetDefaultLanguage("Common");
    if(blindmode){
        Admin->SetProperty("wizmapping", 0);
        Admin->SetProperty("minimapping", 0);
        Admin->SetProperty("screen reader", 1);
    }
    Admin->save_player(Name);
    make_workroom(Name,1);
    PLAYERS_D->AddPlayerInfo(Name);

    tmp = read_file(CFG_GROUPS);

    if(sizeof(tmp)) cp(CFG_GROUPS, "/secure/save/backup/groups.orig");

    rm(CFG_GROUPS);
    tmp = replace_string(tmp, "ADMIN", Name);
    write_file(CFG_GROUPS, tmp);

    tmp = "";

    tmp = read_file(CONFIG_H);

    if(sizeof(tmp)){
        cp(CONFIG_H, "/secure/save/backup/config."+__PORT__+".bak");
        rm(CONFIG_H);
        tmp = replace_string(tmp, "DEBUG_NAME", Name);
        write_file(CONFIG_H, tmp);
    }

    catch(cp(NETWORK_H,"/secure/save/backup/network."+__PORT__+".orig"));

    if( ob = find_object(LIB_CONNECT) ) destruct(ob);
    cp(DIR_SECURE_LIB "/connect.c", DIR_SECURE_LIB "/connect.first.c");
    rm(DIR_SECURE_LIB "/connect.c");
    cp(DIR_SECURE_LIB "/connect.real", DIR_SECURE_LIB "/connect.c");
    destruct(Admin);
    mkdir(DIR_CRES "/" + Name[0..0]);
#if ENABLE_INSTANCES
    filec = new_savename(filec);
    filep = new_savename(filep);
#endif
    err = rename(filep, filec);
    if(err){
        receive("\n发生了一个不幸的错误。\n");
    }
    receive("\n你将被断开连接，MUD将关闭。\n");
    receive("请重启MUD并以管理员角色重新登录。\n");
    flush_messages();
    destruct(master());
    tool = load_object("/secure/cmds/admins/admintool");
    if(tool) foo = tool->eventChangeName("Dead_Souls_"+Name, 1); 
    if(foo){
        receive("\n\nMUD名称已更改。使用 admintool 进行自定义。");
        receive("\n更多信息，请登录后输入: help admintool\n");
    }
    else {
        receive("MUD名称未更改。\n");
    }
    flush_messages();
    cp(IMC2_D+".c", "/secure/save/backup/imc2.orig");
    PLAYERS_D->AddPlayerInfo(Name);
    shutdown();
    destruct(this_object());
}

string GetKeyName() { return Name; }
