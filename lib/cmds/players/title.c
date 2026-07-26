/*    /cmds/player/title.c
 *    from the Dead Souls LPC Library
 *    allows someone to set their titles
 *    created by Descartes of Borg 950716
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

protected void eventOrderTitles(string *titles, int maxi);
protected void GetTitle(string which, string *titles, int maxi);
protected void GetDest(string which, string *titles, int i, int maxi);

mixed cmd(string args) {
    string *titles;
    int maxi;

    if( creatorp(this_player()) || avatarp(this_player()) ) {
        if( !args || args == "" ) return "把头衔改成什么？";
        else args = this_player()->SetShort(args);
        message("system", "头衔已更改为: " + args, this_player());
        this_player()->save_player(this_player()->GetKeyName());
        update("/secure/daemon/finger");
        return 1;
    }
    if( !(maxi = sizeof(titles = this_player()->GetTitles())) )
        return "你完全没有成就。";
    if( args == "1" || args == "2" ) {
        this_player()->SetTitleLength(to_int(args));
        this_player()->SetShort("foo");
        this_player()->eventPrint("描述中的头衔数量已更改为 " + args + "。");
        this_player()->save_player(this_player()->GetKeyName());
        update("/secure/daemon/finger");
        return 1;
    }
    if( maxi == 1 ) {
        message("system", "你只有一个头衔: " + titles[0],
                this_player());
        return 1;
    }
    else if( maxi == 2 ) {
        function f;

        f = function(string yn, string *titles) {
            yn = (yn || "n");
            if( yn != "y" ) {
                message("system", "头衔保持不变。", this_player());
                return;
            }
            this_player()->SetTitles( ({ titles[1], titles[0] }) );
            message("system", "头衔已反转。", this_player());
            this_player()->save_player(this_player()->GetKeyName());
            update("/secure/daemon/finger");
        };
        message("system", "你有以下头衔:\n\t" +
                titles[0] + "\n\t" + titles[1], this_player());
        message("prompt", "是否要反转它们？ [n] ", this_player());
        input_to(f, titles);
        return 1;
    }
    else eventOrderTitles(titles, maxi);
    return 1;
}

protected void eventOrderTitles(string *titles, int maxi) {
    int i;

    message("system", "你有以下头衔:", this_player());
    for(i=0; i<maxi; i++)
        message("system", "\t" + (i+1) + " " + titles[i], this_player());
    message("prompt", "移动哪个（q退出）？ [" + (maxi) + "] ",
            this_player());
    input_to((: GetTitle :), titles, maxi);
}

protected void GetTitle(string which, string *titles, int maxi) {
    int x;

    if( which == "q" ) {
        this_player()->SetTitles(titles);
        message("system", "完成。", this_player());
        return;
    }
    else if( which == "" || !which ) which = "" + maxi;
    x = to_int(which);
    if( x < 1 || x > maxi ) {
        message("system", "无效的头衔编号。", this_player());
        eventOrderTitles(titles, maxi);
        return;
    }
    x--;
    message("prompt", "将 \"" + titles[x] + "\" 移动到哪个位置？ [1] ",
            this_player());
    input_to( (: GetDest :), titles, x, maxi );
}

protected void GetDest(string which, string *titles, int i, int maxi) {
    string *tmp;
    int j, maxj, x;

    if( which == "q" ) {
        this_player()->SetTitles(titles);
        message("system", "完成。", this_player());
        this_player()->save_player(this_player()->GetKeyName());
        update("/secure/daemon/finger");
        return;
    }
    else if( which == "" || !which ) which = "1";
    x = to_int(which);
    if( x < 1 || x > maxi || x == i+1 ) {
        message("system", "无效的头衔编号。", this_player());
        eventOrderTitles(titles, maxi);
        return;
    }
    x--;
    tmp = allocate(maxj = sizeof(titles));
    for(j=0; j<maxj; j++) {
        if( j == x ) tmp[j] = titles[i];
        else if( (j < x && j < i) || (j > x && j > i) ) tmp[j] = titles[j];
        else if( j > x && j <= i ) tmp[j] = titles[j-1];
        else tmp[j] = titles[j+1];
    }
    eventOrderTitles(tmp, maxi);
}

string GetHelp() {
    if( creatorp(this_player()) ) {
        return ("用法: title <头衔>\n\n"
                "允许你更改头衔。你必须在头衔中包含 $N 标记，"
                "它会被替换为你的名字。例如：\n"
                "\ttitle 我们是 $N 之博格\n"
                "会显示为：\n"
                "\t我们是 笛卡尔 之博格。");
    }
    else {
        return ("用法: title\n\n"
                "允许你重新排列头衔。你的前两个头衔会出现在简短描述中。"
                "此命令是交互式的，会提示你操作。"
                "随时按 'q' 保存更改并退出。\n"
                "你也可以输入 (title 1) 或 (title 2) "
                "来更改描述中显示的头衔数量。");
    }
}

