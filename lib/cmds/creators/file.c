#include <lib.h>

inherit LIB_DAEMON;

int cmd(string str) {
    object ob;
    string basename, filename;

    if(!str || str == "here") {
        ob = environment(this_player());
    }

    else ob = get_object(str, this_player());

    if(!ob) {
        write("找不到该对象。");
        return 1;
    }

    filename = file_name(ob);
    basename = base_name(ob);

    write("对象唯一标识符: "+filename);
    write("加载的文件: "+basename+".c");

    return 1;
}

string GetHelp() {
    return "Syntax: file [thing]\n\n"+
        "Provides information about the thing's name and file of origin.\n"+
        "With no argument, it defaults to your location.\n";
}
