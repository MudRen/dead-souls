#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int eventTranslate(string str){
    string contents;
    if(!file_exists(str)){
        write("文件不存在。");
        return 0;
    }

    load_object("/secure/cmds/creators/lsed")->cmd("/secure/scripts/nm3.lsed "+str);
    return 1;
}


string *eventCompileList(string str){
    string *files = ({});
    if(!str) return ({});

    if(strsrch(str,"/domains/") != 0 &&
            strsrch(str,"/realms/") != 0){
        write("别犯傻。");
        return ({});
    }

    FILE_D->eventHarvestDirs();
    FILE_D->eventHarvestFiles();

    foreach(string file in FILE_D->GetFiles()){
        if(!strsrch(file,str)) files += ({ file });
    }

    rm("/tmp/files.txt");
    foreach(string foo in files){
        write_file("/tmp/files.txt",foo+"\n");
    }

    return files;
}


protected void create() {
    daemon::create();
}

