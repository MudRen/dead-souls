#include <lib.h>
#include <cfg.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd() {
    string *races = get_dir(CFG_RACES+"/");
    foreach(string race in races){
        string str = CFG_RACES+"/"+race;
        if(file_exists(str)) {
            catch( RACES_D->AddRace(str) );
        }
    }
    write("完成。");
    return 1;
}

string GetHelp(){
    return ("语法: addraces\n\n"
            "将 CFG_RACES 目录中的所有种族文件导入到"
            "种族守护进程中。如果使用前未移除所有现有种族，"
            "可能会失败。");
}
