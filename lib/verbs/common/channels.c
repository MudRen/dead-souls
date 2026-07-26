#include <lib.h>
#include <daemons.h>
#include <talk_type.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("channels");
    SetRules("", "STR");
    SetHelp("用法：channels [on | off]\n\n"
            "不带参数时，此命令将显示你可以访问的频道状态。"
            "使用 on|off 参数将开启或关闭所有频道。\n"
            "另见：chan, mute, gag, earmuff, env");
    SetSynonyms(({"chans","lines"}));
}

int cmd(string str);

mixed can_channels(string str) { return 1; }

mixed can_channels_str(string str) { return 1; }

mixed do_channels(string str) {
    return cmd(str);
}

mixed do_channels_str(string str) {
    return cmd(str);
}

int cmd(string str) {
    string *channels;
    string *remote = ({});
    string *local = ({});
    string *i3 = ({});
    string *imc2 = ({});
    string ret = "", RemChans = CHAT_D->GetRemoteChannels();
    int i;

    channels = distinct_array(this_player()->GetChannels());

    if(!str) str = "";

    if(str=="on"){
        for(i=0; i<sizeof(channels);i++){
            if(this_player()->GetBlocked(channels[i]))
                this_player()->SetBlocked(channels[i]);
        }
    }

    if(str=="off"){
        for(i=0; i<sizeof(channels);i++){
            if(!this_player()->GetBlocked(channels[i]))
                this_player()->SetBlocked(channels[i]);
        }
    }

    foreach(string chan in channels){
        string tmp = CHAT_D->GetRemoteChannel(chan);
        if(member_array(tmp, RemChans) != -1){
            remote += ({ chan });
            if(!strsrch(tmp, "Server") && grepp(tmp, ":")){
                imc2 += ({ chan });
            }
            else i3 += ({ chan });
        }
        else local += ({ chan });
    }
    if(sizeof(remote)){
        ret += "远程频道\n--------\n";
        if(sizeof(imc2)){
            imc2 = sort_array(imc2, 1);
            ret += "\nIMC2\n----\n";
            foreach(string chan in imc2){
                ret += chan + "\t" + (this_player()->GetBlocked(chan) ?
                        "(%^RED%^已屏蔽%^RESET%^)" : "") + "\n";
            }
        }
        if(sizeof(i3)){
            i3 = sort_array(i3, 1);
            ret += "\nIntermud-3\n----------\n";
            foreach(string chan in i3){
                ret += chan + "\t" + (this_player()->GetBlocked(chan) ?
                        "(%^RED%^已屏蔽%^RESET%^)" : "") + "\n";
            }
        }
    }
    if(sizeof(local)){
        local = sort_array(local, 1);
        ret += "\n\n本地频道\n--------\n";
        foreach(string chan in local){
            ret += chan + "\t" + (this_player()->GetBlocked(chan) ?
                    "(%^RED%^已屏蔽%^RESET%^)" : "") + "\n";
        }
    }

    if(!sizeof(ret)){
        ret = "没有找到频道。";
    }
    write(ret);
    return 1;
}		
