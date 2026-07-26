#include <lib.h>
#include <daemons.h>
#include <dirs.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("help", "help");
    add_action("read", "read");
}

void create() {
    ::create();
    SetSmell( "default", "房间里弥漫着旧书的霉味。");
    SetProperties((["light":2, "no castle" : 1, "indoors" :1 ]) );
    SetShort( "普拉克西斯图书馆");
    SetLong(
            "欢迎来到普拉克西斯高等学府图书馆！\n"
            "图书馆里摆满了层层叠叠的书架，一直延伸到天花板。"
            "皮革装帧的书籍等待着被阅读。东大道在图书馆的西边。"
            "命令 <read books> 可以显示有哪些书可供阅读，"
            "输入 <read [书名]> 可以阅读特定的书籍。");
    SetItems(
            (["library" : "现实世界的法则在这里被解释。",
             "shelf" : "上面放着书。",
             "shelves" : "书籍摆满了书架。",
             "book" : "众多书籍之一。",
             "books" : "它们遍布书架各处。"]) );
    SetExits( 
            (["west" : "/domains/Praxis/east_road1"]) );

}

int read(string str) {
    string *dir;
    string *tmp;
    string tmp_str;
    int i,j,k;

    if(!str) {
        notify_fail("读什么？\n");
        return 0;
    }
    if(str == "volume" || str == "book") {
        notify_fail("哪本"+str+"？\n");
        return 0;
    }
    if(str == "volumes" || str == "books") {
        message("info", "可供阅读的书籍有：",this_player());
        dir = get_dir(DIR_LIBRARY + "/");
        for(i=0; i<sizeof(dir); i++) dir[i] = replace_string(dir[i], "_", " ");
        message("info", replace_string(format_page(dir, 3), "\n", " "),
                this_player());
        message("info", "输入 <read [书名]> 可以阅读特定的书籍。", this_player());
    }
    else {
        str = replace_string(str, " ", "_");
        if(file_size(DIR_LIBRARY + "/"+str) == -1) {
            notify_fail("这里没有那本书。\n");
            return 0;
        }
        this_player()->more(DIR_LIBRARY + "/"+str);
    }
    return 1;
}

int help(string str) {
    if(!str) return 0;
    if(str != "library") {
        notify_fail("你帮助了"+str+"。\n");
        return 0;
    }
    write("你可以阅读图书馆里的内容。\n输入 <read books>。\n");
    return 1;
}


