#include <lib.h>

inherit LIB_DAEMON;

varargs int cmd(string str){
#if GRID
    if(!str){
        write("网格显示: "+ (this_player()->GetVisibleGrid() ? "开启" : "关闭"));
        return 1;
    }
    if(str == "on"){
        if(this_player()->GetVisibleGrid()){
            write("你已经在显示网格坐标了。");
            return 1;
        }
        this_player()->SetVisibleGrid(1);
        if(this_player()->GetVisibleGrid()){
            write("你现在可以看到网格坐标了。");
        }
        else {
            write("失败。坐标未显示。");
        }
        return 1;
    }
    if(str == "off"){
        if(!(this_player()->GetVisibleGrid())){
            write("网格坐标显示已禁用。");
            return 1;
        }
        this_player()->SetVisibleGrid(0);
        if(!(this_player()->GetVisibleGrid())){
            write("网格坐标显示已禁用。");
        }
        else {
            write("失败。坐标仍在显示。");
        }
        return 1;
    }
    write("试试: help showgrid");
    return 1;
#else
    write("此功能已禁用。");
    return 1;
#endif
}

string GetHelp(){
    return ("Syntax: showgrid [ on | off ]\n\n"
            "Adds global grid coordinates for you environment "
            "to the room description, if "
            "ROOMS_D enables them and they are available."); 
}
