#include <lib.h>
#include <daemons.h>
#include <rooms.h>

inherit LIB_DAEMON;

mixed findit(string str){
    string file, tmpfile;
    object room;
    int err;
    if(str == "here"){
        tmpfile = base_name(environment(this_player()));
        file = lpc_file(base_name(environment(this_player())));
    }
    else {
        file = lpc_file(str);
        tmpfile = str;
    }
    if(!file_exists(file) && str != "here"){
        file = lpc_file(this_player()->query_cwd()+"/"+str);
        if(!directory_exists(path_prefix(str))){
            tmpfile = this_player()->query_cwd()+"/"+str;
        }
    }
    if(file_exists(file)) return file;
    err = catch(room = load_object(tmpfile));
    if(room) return room;
    return 0;
}

protected mixed ResetGrid(){
    object drone;
    object *drones = ({});
    string *starts = ({});
    string start;
    int err = 0;
    drones = findobs("/domains/default/npc/drone3");
    starts = ({ROOM_START+".c", "/domains/Ylsrim/room/tower.c",
            "/domains/Praxis/square.c", "/domains/campus/room/tunnel"});
    foreach(mixed arr in get_dir("/domains/", -1)){
        if(arr[1] == -2) start = "/domains/"+arr[0]+"/room/start.c";
        if(sizeof(start) && file_exists(start)) starts += ({ start });
        start = "";
    } 
    drones->eventDestruct();
    MAP_D->zero();
    ROOMS_D->zero();
    ROOMS_D->eventDestruct();
    MAP_D->eventDestruct();
    foreach(start in distinct_array(starts)){
        mixed lerr = 0;
        lerr = catch( reload(start, 0, 1));
        if(lerr){ 
            err++;
            write("重新加载出错 "+start+"："+lerr);
            continue;
        }
        drone = new("/domains/default/npc/drone3");
        lerr = catch( drone->eventMove(start) );
        if(lerr){
            err++;
            write("移动映射无人机到 "+start+" 时出错："+lerr);
        }
        else write("正在为 "+start+" 分配映射无人机");
    }
    write("\n正在重新映射。遇到 "+err+" 个错误。");
    return 1;
}

mixed cmd(string args) {
    string s1, s2, s3, coord, cmd;
    mixed file;
    object room;
    int err;
    if(!this_player() || !archp(this_player())) return "lol";
    if(!args){
        write("尝试：help gridconfig");
        return 1;
    }
    if(args == "reset"){
        return ResetGrid();
    }
    if(sscanf(args,"%s %s %s",s1,s2,s3) == 3){
        file = findit(s2);
        cmd = s1;
        coord = s3;
        if(!file){
            write("未找到房间。");
            return 1;
        }
        if(objectp(file)) room = file;
        if(!room) err = catch(room = load_object(file));
        if(err || !room){
            write("房间无法加载。");
            return 1;
        }
        if(cmd != "set"){
            write("尝试：help gridconfig");
            return 1;
        }
        if(sscanf(coord,"%s,%s,%s",s1,s2,s3) != 3){
            s3 = 0;
            if(sscanf(coord,"%s,%s",s1,s2) != 2){
                write("输入：help gridconfig");
                return 1;
            }
        }
        coord = coord + (s3 ? "" : ",0");
        ROOMS_D->SetRoom(room, this_player(), coord);
        write(file+" 的坐标为："+
                ROOMS_D->GetCoordinates(room));
        return 1;
    }
    if(sscanf(args,"%s %s",s1,s2) == 2){
        file = findit(s2);
        cmd = s1;
        if(!file){
            write("未找到房间。");
            return 1;
        }
        if(objectp(file)) room = file;
        if(!room) err = catch(room = load_object(file));
        if(err || !room){
            write("房间无法加载。");
            return 1;
        }
        if(cmd != "unset"){
            write("尝试：help gridconfig");
            return 1;
        }
        ROOMS_D->SetRoom(room, this_player(), "0,0,0");
        write(file+" 的坐标为："+
                ROOMS_D->GetCoordinates(room));
        return 1;
    }
    write("您未能正确使用此命令。");
    return 1;
}

string GetHelp(string args) {
    return ("语法：gridconfig set <房间> <坐标>\n"
            "        gridconfig unset <房间>\n"
            "        gridconfig reset\n\n"
            "修改 ROOMS_D 中指定房间的网格坐标表。"
            "如果参数为 \"reset\"，则清除房间守护进程和地图守护进程，"
            "并使用映射无人机缓慢重建。注意这可能会导致MUD延迟。"
            "另请注意，房间守护进程将忽略 /realms/ 和 /open/ 中房间的坐标设置。\n"
            "另见：mudconfig, admintool");
}
