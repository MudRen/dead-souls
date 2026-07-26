#include <daemons.h>

mixed cmd(string args) {
    object ob = this_player();
    int i, cre = creatorp(ob);
    string *channels;
    string command, channel;
    if(!args) return "用法: help chan";
    i = sscanf(args, "%s %s", command, channel);
    if(!channel) return "用法: help chan";
    channels = distinct_array(ob->GetChannels());
    if(command == "block"){
        if(member_array(channel, channels) == -1){
            write("你没有订阅该频道。");
            return 1;
        }
        if(ob->GetBlocked(channel)){
            write(channel + " 已经被屏蔽了。");
        }
        else ob->SetBlocked(channel, 1);
        return 1;
    } 
    if(command == "unblock"){
        if(member_array(channel, channels) == -1){
            write("你没有订阅该频道。");
            return 1;
        }
        if(!ob->GetBlocked(channel)){
            write(channel + " 已经取消屏蔽了。");
        }
        else ob->SetBlocked(channel, 0);
        return 1;
    }
    if(!cre){
        write("用法: help chan");
        return 1;
    }
    if(command == "add"){
        if(!creatorp(this_player())){
            write("用法: help chan");
            return 1;
        }
        if(channel == "all"){
            string *allchans = CHAT_D->GetChannels();
            allchans += CHAT_D->GetRemoteChannels();
            foreach(string chan in allchans){
                //tc("chan: "+identify(chan));
            }
            allchans = sort_array(singular_array(allchans), 1);
            allchans -= ({ "muds" });
            foreach(string chan in allchans){
                string lchan;
                if(sscanf(chan,"%*s:%s",lchan) != 2) lchan = chan;
                if(!ob->GetChannel(lchan)){
                    ob->AddChannel(lchan);
                    if(ob->GetChannel(lchan)){
                        write("已添加: "+lchan);
                    }
                }
            }
            write("完成。");
            return 1;
        }
        if(member_array(channel, channels) != -1){
            write("你已经订阅了该频道。");
            return 1;
        }
        ob->AddChannel(channel);
        channels = distinct_array(ob->GetChannels());
        if(member_array(channel, channels) == -1){
            write("添加频道失败。");
        }
        else {
            write("你已添加频道 "+channel+"。");
        }
        return 1;
    }
    if(command == "remove"){
        if(!creatorp(this_player())){
            write("用法: help chan");
            return 1;
        }
        if(channel == "all"){
            string *allchans = ob->GetChannels();
            foreach(string chan in allchans){
                ob->RemoveChannel(chan);
                if(!(ob->GetChannel(chan))){
                    write("已移除: "+chan);
                }
            }
            write("完成。");
            return 1;
        }
        if(member_array(channel, channels) == -1){
            write("你已经取消订阅该频道了。");
            return 1;
        }
        ob->RemoveChannel(channel);
        channels = distinct_array(ob->GetChannels());
        if(member_array(channel, channels) != -1){
            write("移除频道失败。");
        }
        else {
            write("你已移除频道 "+channel+"。");
        }
        return 1;
    }
    write("用法: help chan");
    return 1;
}

string GetHelp(){
    int cre = creatorp(this_player());
    string ret = "用法: chan block <频道>\n";
    ret += "        chan unblock <频道>\n";
    if(cre){
        ret += "        chan add <频道>\n";
        ret += "        chan remove <频道>\n";
    }
    ret += "\n";
    ret += "显示或修改用户在可用频道上的频道策略。";
    ret += "\n参考: lines, gag, earmuff, env, hist, channels";
    return ret;
}
