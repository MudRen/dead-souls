#include <lib.h>
#include <objects.h>
#include <daemons.h>

inherit LIB_DAEMON;
string *features = ({ "GetLong", "GetShort", "GetAmbientLight",
        "GetDayLight", "GetNightLight", "GetDayLong", "GetNightLong",
        "GetDayShort", "GetNightShort", "GetExitMap", "GetFlyRoom",
        "GetSinkRoom", "GetClimate", "GetTerrainType", 
        "GetItemsMap", "GetProperties", "GetSmellMap", "GetListenMap",
        "GetGravity", "GetMedium", "GetPlayerKill", "GetTown",
        });


mixed cmd(string str){
    mapping RoomElements = ([]);
    object here = environment(this_player());
    object staff = present("tanstaafl",this_player());
    if(!here) return 0;

    if(!staff){
        write("你必须持有创造者法杖才能使用此命令。");
        return 1;
    }

    if(file_exists(base_name(here)+".c")){
        write("当前环境已经是非虚拟房间。");
        return 1;
    }

    foreach(string feature in features){
        RoomElements[feature] = call_other(here, feature);
    }

    cp("/obj/room.c", base_name(here)+".c");

    reload(base_name(here));

    foreach(mixed key, mixed val in RoomElements){
        string tmp, file_contents;
        write("%^RED%^"+key+"%^RESET%^: "+identify(val));
        if(!val || ((mapp(val) || stringp(val)) && !sizeof(val)) ) true(); 
        else {
            //write(key+": "+identify(val));
            key = replace_string(key,"Get","Set",1);
            switch(key){
                case "SetExitMap" : key = "SetExits"; break;
                case "SetItemsMap" : key = "SetItems"; break;
                case "SetSmellMap" : key = "SetSmell"; break;
                case "SetListenMap" : key = "SetListen"; break;
                default :
            }
            if(key == "SetTerrainType"){
                tmp = implode(TYPES_D->eventCalculateTypes("terrain",val),"|");
                tmp = "SetTerrainType("+tmp+");";
                staff->eventDelete(environment(this_player()), "SetTerrainType");
                file_contents = staff->eventAppendLast(base_name(environment(this_player()))+".c", "create", tmp);
                rm(base_name(environment(this_player()))+".c");
                if(!grepp(file_contents,"terrain_types.h")){
                    write_file(base_name(environment(this_player()))+".c",
                            "#include <terrain_types.h>\n",1);
                }
                write_file(base_name(environment(this_player()))+".c",file_contents);
            }
            else if(key == "SetMedium"){
                tmp = TYPES_D->eventCalculateTypes("medium",val);
                tmp = "SetMedium("+tmp+");";
                staff->eventDelete(environment(this_player()), "SetMedium");
                file_contents = staff->eventAppendLast(base_name(environment(this_player()))+".c", "create", tmp);
                rm(base_name(environment(this_player()))+".c");
                if(!grepp(file_contents,"medium.h")){
                    write_file(base_name(environment(this_player()))+".c",
                            "#include <medium.h>\n",1);
                }
                write_file(base_name(environment(this_player()))+".c",file_contents);

            }
            else if(mapp(val)){
                val = staff->eventStringifyMap(val);
                tmp = key + "( "+val+" );";
                staff->eventDelete(environment(this_player()), key);
                file_contents = staff->eventAppendLast(base_name(environment(this_player()))+".c", "create", tmp);
                write_file(base_name(environment(this_player()))+".c",file_contents,1);
            }
            else staff->eventModify(environment(this_player()),lower_case(key)+" "+val);
        }
        staff->eventModify(environment(this_player()),"setshort "+RoomElements["GetShort"]);
    }
    return 1;
}

string GetHelp() {
    return ("语法: unvirt\n\n"
            "此命令会收集你当前所站的虚拟房间的数据，并尝试\n"
            "创建一个非虚拟房间，写入该虚拟房间所模拟使用的文件。\n"
            "如果你对该文件没有写权限，命令将以一种不太美观的方式失败。\n"
            "参见: modify, create, delete, copy, areaclone, "
            "areagoto, arealist");
}
