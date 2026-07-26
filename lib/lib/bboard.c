/*    /lib/bboard.c
 *    from Nightmare 3.3
 *    the Dead Souls bulletin board system
 *    created by Descartes of Borg 940920
 */

#include <lib.h>
#include <daemons.h>
#include "include/bboard.h"

inherit LIB_ITEM;

nosave private string tmpdir;
nosave private string __BoardID;
nosave private string *__EditOK;
nosave string gstr, gfile, gdude;
string Location;

void create(){
    string path;
    item::create();
    SetNoClean(1);
    SetId( ({ "board", "message board" }) );
    SetLong("一块用来阅读和发布消息的公告板。要阅读第一条消息：read 1\n要发布消息：post <消息标题>\n");
    SetPreventGet("你不能拿走那个！");
    SetPreventPut("你不能把那个放进去！");
    SetPreventDrop("丢掉公告板？");
    SetNoCondition(1);
    SetRead( (: GetLong :) );
    __EditOK = ({});
    path = base_name(this_object());
    if(!strsrch(path, "/secure/")) tmpdir = DIR_SECURE_TMP;
    else tmpdir = DIR_TMP;
}

void RegisterLocation(){
    object env = environment();
    if(!env) Location = 0;
    else Location = base_name(env);
    BBOARD_D->RegisterLocation(query_board_id(), Location);
}

void init(){
    item::init();
    add_action("cmd_post", "post");
    add_action("cmd_read", "read");
    add_action("cmd_followup_and_respond", ({ "followup", "respond "}));
    add_action("cmd_remove", "remove");
    add_action("cmd_edit", "edit");
    RegisterLocation();
}

private int valid_edit(string author){
    string who = this_player()->GetKeyName();
    if(who == author) return 1;
    if(archp(this_player())) return 1;
    return 0;
}

int cmd_post(string str){
    string file;

    if(!str) return notify_fail("你必须指定一个标题。\n");
    if(file_exists(file = tmpdir + "/" + this_player()->GetKeyName())){
        message("system", "你有一篇未完成的帖子等待处理。",this_player());
        message("system", "        e) 编辑它，或 n) 开始新帖", this_player());
        message("prompt", "\n命令 (默认 'n'): ", this_player());
        input_to("begin_post", str, file, (: continue_post :));
    }
    else {
        write("写完后，在空行输入一个句号，然后 ");
        write("在冒号提示符 (:) 处输入小写 x 并回车。\n");
        write("像这样:\n.\nx\n");
        begin_post("n", str, file, (: continue_post :));
    }
    return 1;
}

protected void begin_post(string cmd, string subj, string file, function f){
    if(cmd == "" || !cmd) cmd = "n";
    else cmd = cmd[0..0];
    if(cmd != "n" && cmd != "e"){
        message("system", "无效的公告板命令。", this_player());
        return;
    }
    if(cmd == "n" && file_exists(file)) rm(file);
    (*f)(subj, file);
}

void continue_post(string subj, string file){
    this_player()->eventEdit(file, (: end_post, subj, 0 :));
}

void end_post(string subj, string mail){
    string file, msg;
    object env = room_environment(this_player());

    file = tmpdir + "/" + this_player()->GetKeyName();
    if(!(msg = read_file(file))){
        message("system", "没有读取到文件！", this_player());
        if(file_exists(file)) rm(file);
        return;
    }
    else rm(file);
    if( !mail )
        BBOARD_D->add_post(query_board_id(),
                this_player()->GetCapName(), subj, msg);
    message("system", "消息已发布！", this_player());
    tell_room(env, this_player()->GetName()+" 在公告板上发布了消息。",
            ({ this_player() }));
}

int cmd_read(string str){
    string junk;
    mapping *posts;
    int x, i, maxi;
    object env = room_environment(this_player());

    if(str){
        if(str == "board" || sscanf(str,"board %s",junk) ){
            write("要阅读第一条帖子，输入: read 1");
            write("要阅读第二条，输入: read 2");
            write("依此类推。");
            return 1;
        }

        maxi = sizeof(posts = BBOARD_D->query_posts(query_board_id()));
        if(!str){
            for(i=0, x = -1; i<maxi; i++)
                if(member_array(this_player()->GetKeyName(),
                            posts[i]["read"]) == -1){
                    x = i;
                    break;
                }
            if(x == -1) return notify_fail("没有未读帖子。\n");
        }
        else if(!(x = to_int(str))) return notify_fail("阅读什么？\n");
        else x--;
        if(x < 0 || x >= sizeof(posts))
            return notify_fail("无效的帖子编号。\n");
        str = "帖子 #%^YELLOW%^" + (x+1) + "%^RESET%^ 作者: %^YELLOW%^" +
            posts[x]["author"] + "%^RESET%^\n标题: %^CYAN%^" +
            posts[x]["subject"] + "%^RESET%^\n\n";
        str += posts[x]["post"];

        tell_room(env, this_player()->GetName()+" 阅读了公告板。",
                ({ this_player() }));
        BBOARD_D->mark_read(query_board_id(),x,this_player()->GetKeyName());
        this_player()->eventPage(explode(str, "\n"), "system");
        return 1;
    }
}

int cmd_followup_and_respond(string str){
    mapping post;
    function f;
    string file, verb;
    int x;

    if(!str) return notify_fail(capitalize(verb=query_verb())+"哪篇帖子？\n");
    if((x=to_int(str)) < 1 ||
            x>BBOARD_D->query_number_posts(query_board_id()))

        return notify_fail("无效的帖子编号。\n");
    x--;
    post = BBOARD_D->query_post(query_board_id(), x);
    if((verb = query_verb()) == "respond") f = (: continue_mail, post :);
    else f = (: continue_followup, post :);
    str = post["subject"];
    if(!str) str = "Re: "+possessive_noun(post["author"])+" 的帖子";
    else if(strlen(str) <= 4 || str[0..3] != "Re: ") str = "Re: "+str;
    if(file_exists(file = tmpdir + "/" + this_player()->GetKeyName())){
        message("system", "你有一篇未完成的帖子等待处理。",this_player());
        message("system", "        e) 编辑它，或 n) 开始新帖", this_player());
        message("prompt", "\n命令 (默认 'n'): ", this_player());
        input_to("begin_post", str, file, f);
    }
    else begin_post("n", str, file, f);
    return 1;
}

void continue_followup(mapping post, string subj, string file){
    message("prompt", "\n是否包含原文 (默认 'n'): ",this_player());
    input_to("check_include_text", subj, file, post, 0);
}

void continue_mail(mapping post, string subj, string file){
    message("prompt", "\n是否包含原文 (默认 'n'): ",this_player());
    input_to("check_include_text", subj, file, post, 1);
}

protected void check_include_text(string ans, string subj, string file, mapping
        post, int mail){

    string msg;

    if(ans == "" || !ans) ans = "n";
    else ans = ans[0..0];
    if(ans == "y"){
        msg = post["author"] + " 曾写道...\n>";
        msg += implode(explode(post["post"], "\n"), "\n> ")+"\n";
        write_file(file, msg);
    }
    this_player()->eventEdit(file, (: end_post, subj, (mail ? post : 0) :));
}

int cmd_remove(string str){
    mapping post;
    int x;
    object env = room_environment(this_player());

    if((x = to_int(str)) < 1 ||
            x > BBOARD_D->query_number_posts(query_board_id()))
        return notify_fail("无效的帖子编号。\n");
    post = BBOARD_D->query_post(query_board_id(), x-1);
    if(!valid_edit(convert_name(post["author"]))){
        write("你没有权限删除那个！\n");
        return 1;
    }
    BBOARD_D->remove_post(query_board_id(), x-1);
    message("system", "帖子 "+x+" 已删除。", this_player());
    tell_room(env, this_player()->GetName()+" 从公告板上删除了一篇帖子。",
            ({ this_player() }));
    return 1;
}

int cmd_edit(string str){
    mapping post;
    string file;
    int x;

    if((x = to_int(str)) < 1 ||
            x > BBOARD_D->query_number_posts(query_board_id()))
        return notify_fail("无效的帖子编号。\n");
    post = BBOARD_D->query_post(query_board_id(), x-1);
    if(!valid_edit(convert_name(post["author"]))){
        write("你没有权限编辑那篇帖子！\n");
        return 1;
    }
    file = tmpdir + "/" + this_player()->GetKeyName() + ".bb";
    gstr = post["post"];
    gfile = file;
    unguarded( (: write_file(gfile, gstr, 1) :) );
    this_player()->edit(file, (: end_edit, post["subject"], x-1 :) );
    return 1;
}

void end_edit(string subj, int num){
    string file, msg;

    file = tmpdir + "/" + this_player()->GetKeyName();
    if(!(msg = read_file(file))){
        message("system", "没有读取到文件！", this_player());
        return;
    }
    else rm(file);
    BBOARD_D->remove_post(query_board_id(), num);
    BBOARD_D->add_post(query_board_id(),
            this_player()->GetCapName(), subj, msg);
    message("system", "消息已发布！", this_player());
}

string GetExternalDesc(){
    mapping *posts;
    string msg;
    int i, maxi;

    msg = item::GetExternalDesc();
    maxi = sizeof(posts = BBOARD_D->query_posts(query_board_id()));
    msg += "\n";
    if(!maxi) msg += "目前没有帖子。\n";
    else for(i=0; i < maxi; i++){
        int lu;

        if(!this_player()) lu = 1;
        else if(member_array(this_player()->GetKeyName(),
                    posts[i]["read"]) == -1) lu = 0;
        else lu = 1;
        msg += sprintf("[%:-3d] %s %:-17s \"%:-27s %s\n",
                (i+1), (lu ? "     " : "(new)"), posts[i]["author"]+":",
                posts[i]["subject"]+"\"", query_board_time(posts[i]["time"]));
    }
    return msg;
}

void set_board_id(string str){ __BoardID = str; }

string query_board_id(){ return __BoardID; }

string query_board_time(int x){
    string date, day, mon, year, hour, ret;

    if(sscanf(ctime(x), "%s %s  %s %s %s", day, mon, date, hour, year) !=5)
        sscanf(ctime(x), "%s %s %s %s %s", day, mon, date, hour, year);

    sscanf(hour, "%s:%s:%*s", hour, ret);
    return(hour+ret+" "+day+" "+date+" "+mon);
}
