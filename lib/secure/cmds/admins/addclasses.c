#include <lib.h>
#include <cfg.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd() {
    string *classes = get_dir(CFG_CLASSES+"/");
    foreach(string element in classes){
        string str = CFG_CLASSES+"/"+element;
        if(file_exists(str)) {
            catch( CLASSES_D->AddClass(str) );
        }
    }
    write("完成。");
    return 1;
}

string GetHelp() {
    return ("语法: addclasses\n\n"
            "将 CFG_CLASSES 目录中的所有职业文件导入到"
            "职业守护进程中。如果使用前未移除所有现有职业，"
            "可能会失败。");
}
