/*   statconvert.c
 *   A utility which reduces or raises SetSkill and SetStat lines
 *   in a file by a specified percentage.
 *   created by Blitz@Dead Souls
 */

void GetHelp(string str);

string ConvertLine(string str, int change, int line, string search)
{
    string s1, s2, cut, n, tmp;
    int a, b, val;

    if(!archp(previous_object())) return 0;
    while( (a = strsrch(str, search)) > -1 ) {
        tmp = str[a..];
        b = strsrch(tmp, ")");
        if( b < 0) break;
        cut = tmp[0..b];
        if( sscanf(cut, "%s,%s", s1, s2) != 2 ) break;
        s2 = replace_string(s2, " ", "");
        sscanf(s2, "%s)", s2);
        val = to_int(s2);
        if( !val ) break;
        val = val - (val / (100 / change));
        n = sprintf("%s, %d)", s1[0] + "@@@" + s1[1..], val);
        str = replace_string(str, cut, n);
        write("行 "+line+": "+cut+" -> "+val+"。");
    }
    str = replace_string(str, search[0] + "@@@" + search[1..], search);
    return str;
}

void Convert(string s, int change) {
    string args, file, str;
    string *files, *tmp;
    int i;

    if(!archp(previous_object())) return 0;
    if( !sizeof(s) ) args = "*.c";
    else args = s;
    files = wild_card(args);
    if( !i = sizeof(files) ) {
        message("info", "未找到文件: "+implode(files, " "),
                this_player() );
        return;
    }
    foreach(file in files) {
        string line;
        int    changed = 0;

        str = read_file(file);
        if( !sizeof(str) ) continue;
        i = sizeof(tmp = explode(str, "\n"));
        write("正在检查: "+file);
        while(i--) {
            line = tmp[i];
            line = ConvertLine(line, change, i, "SetSkill");
            line = ConvertLine(line, change, i, "SetStat");
            if( tmp[i] != line ) changed = 1;
            if( changed ) tmp[i] = line;
        }
        if( changed ) {
            rename(file, file+"~");
            write(file+": 正在写入新文件...");
            write_file(file, implode(tmp, "\n"));
        }
    }
}

mixed cmd(string str) {
    string files;
    int change;

    if(!archp(previous_object())) return 0;
    if( !sizeof(str) || (sscanf(str, "%s %d", files, change) != 2) || !change) {
        GetHelp(0);
        return 1;
    }
    files = absolute_path(this_player()->query_cwd(), files);
    Convert(files, change);
    return 1;
}


string GetHelp(){
    return ("语法: statconvert <文件名 | 通配符> <百分比>\n\n"
            "此命令搜索指定文件，将所有 SetSkill 和 SetStat "
            "按指定百分比降低。\n\n"
            "示例: statconvert *.c 10\n"
            "  - 搜索当前路径下所有 .c 文件，将所有\n"
            "    技能和属性设置降低10%\n\n"
            "注意: 传入负数可以提高设置值。");
}
