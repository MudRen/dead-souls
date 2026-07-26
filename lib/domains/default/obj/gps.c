#include <lib.h>
#include <daemons.h>
#include <vendor_types.h>
inherit LIB_ITEM;
mapping Tracked = ([]);
mixed gtmp;

string LongDesc(){
    string ret;
    Tracked = ([]);
    if(creatorp(this_player())){
        ret = "这个小型电子设备旨在提供关于你在世界中位置的信息（如果可用）。指令：coord, prox";
    }
    else {
        ret = "这是创造者用来分析他们在 MUD 中位置的设备。";
    }
    return ret;
}

void create(){
    ::create();
    SetKeyName("GPS device");
    SetAdjectives( ({"gps", "global positioning", "system", "small"}) );
    SetId( ({"gps", "device", "appliance"}) );
    SetShort("一个GPS设备");
    SetLong( (: LongDesc :) );
    SetNoCondition(1);
    SetMass(20);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
    add_action("GetCoord","coord");
    add_action("GetProx","prox");
    add_action("GetShell","shell");
    add_action("StartTrack","track");
    add_action("StopTrack","untrack");
}

int GetCoord(){
    string ret;
    if(!creatorp(this_player())) return 0;
    ret = ROOMS_D->GetCoordinates(environment(this_player()));
    if(!sizeof(ret) || ROOMS_D->GetGrid(ret)["room"] !=
            base_name(environment(this_player()))){
        ret = "看起来你目前无法接收关于你位置的定位数据。";
    }
    else{
        mixed foo = ROOMS_D->GetGrid(ret);
        if(foo && creatorp(this_player())){
            ret += " "+identify((foo["room"] || ""));
        }
    }
    write(ret);
    return 1;
}

int GetProx(int i){
    string ret = "";
    int x, y, z;
    string coords;
    if(!creatorp(this_player())) return 0;
    coords = ROOMS_D->GetCoordinates(environment(this_player()));
    if(!sizeof(coords) || ROOMS_D->GetGrid(coords)["room"] !=
            base_name(environment(this_player())) ||
            sscanf(coords,"%d,%d,%d",x,y,z) != 3){
        ret = "看起来你目前无法接收关于你位置的邻近数据。";
    }
    else{
        if(ROOMS_D->GetGrid(x+","+(y+1)+","+z)["room"])
            ret += "North: "+ROOMS_D->GetGrid(x+","+(y+1)+","+z)["room"];
        if(ROOMS_D->GetGrid(x+","+(y-1)+","+z)["room"])
            ret += "\nSouth: "+ROOMS_D->GetGrid(x+","+(y-1)+","+z)["room"];
        if(ROOMS_D->GetGrid((x+1)+","+y+","+z)["room"])
            ret += "\nEast: "+ROOMS_D->GetGrid((x+1)+","+y+","+z)["room"];
        if(ROOMS_D->GetGrid((x-1)+","+y+","+z)["room"])
            ret += "\nWest: "+ROOMS_D->GetGrid((x-1)+","+y+","+z)["room"];
        if(ROOMS_D->GetGrid((x+1)+","+(y+1)+","+z)["room"])
            ret += "\nNortheast: "+ROOMS_D->GetGrid((x+1)+","+(y+1)+","+z)["room"];
        if(ROOMS_D->GetGrid((x-1)+","+(y+1)+","+z)["room"])
            ret += "\nNorthwest: "+ROOMS_D->GetGrid((x-1)+","+(y+1)+","+z)["room"];
        if(ROOMS_D->GetGrid((x+1)+","+(y-1)+","+z)["room"])
            ret += "\nSoutheast: "+ROOMS_D->GetGrid((x+1)+","+(y-1)+","+z)["room"];
        if(ROOMS_D->GetGrid((x-1)+","+(y-1)+","+z)["room"])
            ret += "\nSouthwest: "+ROOMS_D->GetGrid((x-1)+","+(y-1)+","+z)["room"];
        if(ROOMS_D->GetGrid(x+","+y+","+(z+1))["room"])
            ret += "\nUp: "+ROOMS_D->GetGrid(x+","+y+","+(z+1))["room"];
        if(ROOMS_D->GetGrid(x+","+y+","+(z-1))["room"])
            ret += "\nDown: "+ROOMS_D->GetGrid(x+","+y+","+(z-1))["room"];
    }
    write(ret);
    return 1;
}

int StartTrack(string str){
    object mark = to_object(str);
    if(!mark || !living(mark)){
        mark = find_player(str);
    }
    if(!mark){
        write("找不到那个生物。");
        return 1;
    }
    write("开始追踪"+capitalize(mark->GetKeyName())+"。");
    TRACKER_D->AddTrack(mark, this_object());
    Tracked[str] = mark;
    return 1;
}

int StopTrack(string str){
    object mark;
    if(!Tracked[str]){         
        write("这个设备没有在追踪那个生物。");
        return 1;     
    }
    write("停止追踪"+
            capitalize(Tracked[str]->GetKeyName())+"。");     
    TRACKER_D->RemoveTrack(mark, this_object());
    Tracked[str] = 0;
    return 1;
}

int ReceiveTrackingData(mapping data){
    object env = environment();
    if(!env) return 0;
    tell_object(env, "GPS设备发出嘟嘟声：收到追踪数据 "+
            data["object"]->GetShort()+"："+identify(data));
    return 1;
}

int GetShell(string str){
    mapping Shell = ([]);
    mixed all = ({});
    int shell = atoi(str);
    int i, max = shell+1;
    Shell[0] = room_environment(this_player())->GetNeighbors();
    if(!shell){
        return 1;
    }
    for(i = 1; i < max; i++){ 
        Shell[i] = ({});
        foreach(mixed foo in Shell[i-1]){
            object bar;
            mixed tmparr = ({});
            catch( bar = load_object(foo) );
            if(bar){
                tmparr = (bar->GetNeighbors() - ({ foo }) );
                if(!sizeof(tmparr)){
                    bar->CompileNeighbors();
                    tmparr = (bar->GetNeighbors() - ({ foo }) );
                }
            }
            gtmp = Shell[i-1];
            tmparr = filter(tmparr, (: member_array($1, gtmp) == -1 :) );
            gtmp = all;
            Shell[i] += filter(tmparr, (: member_array($1, gtmp) == -1 :) );
            all += Shell[i];
        }
        Shell[i] = distinct_array(Shell[i]);
    }
    write("距离为"+shell+"的房间："+identify(Shell[shell]));
    return 1;
}
