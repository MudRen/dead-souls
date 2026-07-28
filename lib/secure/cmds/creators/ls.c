/*    /cmd *    from Foundation II
 *    a faster, newer ls command
 *    created by Descartes of Borg 940724
 */

#include <lib.h>

inherit LIB_DAEMON;

private mapping file_mapping(string *files);
private string display_ls(mixed targ, int aflag, int lflag, int tflag,
        int nflag, int bflag, int sflag);
private string long_list(string dir, mixed *files);
private string short_list(string dir, mixed *files, int n, int s);

int cmd(string str) {
    string *args, *paths, *options, *files, *tmp, *dirs;
    string show;
    int moref, brief, size;
    int all_files, long_details, time_sort, no_load_info, i, x, maxi;

    if(str == "" || !str) str = previous_object()->query_cwd();
    if(!str) return notify_fail("没有当前工作目录。\n");
    i = sizeof(args = explode(str, " "));
    if(args[0][0] == '-') {
        if((x = strlen(args[0])) > 1) options = explode(args[0][1..x-1], "");
        else options = ({});
        if(i == 1) paths = ({ previous_object()->query_cwd() });
        else paths = args[1..i-1];
    }
    else {
        options = ({});
        paths = args;
    }
    i = sizeof(options);
    while(i--) {
        switch(options[i]) {
            case "a": all_files = 1; break;
            case "l": long_details = 1; break;
            case "t": time_sort = 1; break;
            case "m": moref = 1; break;
            case "n": no_load_info = 1; break;
            case "b": brief = 1; break;
            case "s": size = 1; break;
        }
    }
    for(i=0, maxi = sizeof(paths), files = ({}); i<maxi; i++)
        if(tmp = wild_card(paths[i])) files += tmp;
    if(!sizeof(files)) {
        message("error", "没有该文件或目录。", this_player());
        return 1;
    }
    dirs = filter(files, "is_dir", this_object());
    if(sizeof(files = files - dirs))
        show = display_ls(file_mapping(files),all_files,long_details, time_sort,
                no_load_info, brief, size);
    else show = "";
    if(!(maxi = sizeof(dirs))) {
        if(moref) previous_object()->more(explode(show, "\n"), "system");
        else message("system", show, previous_object());
        return 1;
    }
    for(i=0; i<maxi; i++){
        show += display_ls(dirs[i], all_files, long_details, time_sort,
                no_load_info, brief, size);
    }
    if(!moref && check_string_length(show)) previous_object()->eventPrint(show);
    else print_long_string(this_player(),show);
    return 1;
}

int is_dir(string str) { return (file_size(str) == -2); }

private mapping file_mapping(string *files) {
    mapping borg;
    string *tmp;
    string dir;
    int i, maxi, x;

    for(i=0, maxi = sizeof(files), borg = ([]); i<maxi; i++) {
        x = sizeof(tmp = explode(files[i], "/"));
        if(x == 1) dir = "/";
        else dir = "/"+implode(tmp[0..x-2], "/")+"/";
        if(borg[dir]) borg[dir] += get_dir(dir+tmp[x-1], -1);
        else borg[dir] = get_dir(dir+tmp[x-1], -1);
    }
    return borg;
}

private string display_ls(mixed targ, int aflag, int lflag, int tflag,
        int nflag, int bflag, int sflag) {
    string *cles;
    string ret = "";
    int i, maxi;

    if(stringp(targ) && targ == "/") targ = ([ "/" : get_dir("/", -1) ]);
    else if(stringp(targ)){
        targ = "/"+implode(explode(targ,"/"),"/");
        targ = ([ targ : get_dir(targ+"/", -1) ]);
    }
    for(i=0, maxi = sizeof(cles = keys(targ)); i<maxi; i++) {
        if(!bflag) ret = cles[i]+":\n";
        if(!aflag) targ[cles[i]] = filter(targ[cles[i]], "filter_dots",
                this_object());
        if(tflag)
            targ[cles[i]]=sort_array(targ[cles[i]],"time_sort",this_object());
        if(lflag) ret += long_list(cles[i], targ[cles[i]]);
        else ret += short_list(cles[i], targ[cles[i]], nflag, sflag);
        ret += "\n";
    }
    return ret;
}

int filter_dots(mixed *file) { return (file[0][0] != '.'); }

int time_sort(mixed *alpha, mixed *beta) {
    if(alpha[2] < beta[2]) return 1;
    else if(alpha[2] > beta[2]) return -1;
    else return 0;
}

private string long_list(string dir, mixed *files) {
    string ret, acc, loaded;
    int i, maxi;

    if(!(maxi = sizeof(files))) return "";
    else ret = "";
    if(master()->valid_read(dir, previous_object())) acc = "r";
    else acc = "-";
    if(master()->valid_write(dir, previous_object())) acc += "w";
    else acc += "-";
    if(member_array(dir[0..strlen(dir)-2],
                previous_object()->GetSearchPath()) != -1) acc += "x";
    else acc += "-";
    for(i=0, maxi=sizeof(files); i<maxi; i++) {
        if(files[i][1] == -2) loaded = "";
        else loaded = (find_object(dir+files[i][0]) ? "*" : "");
        ret += sprintf("%:-3s%:-5s%:-30s %d\t%s",
                loaded, acc, ctime(files[i][2]),
                files[i][1], files[i][0]);
        if(files[i][1] == -2) ret += "/\n";
        else ret += "\n";
    }
    return ret;
}

private string short_list(string dir, mixed *files, int n, int s) {
    string *newfiles;
    string ret, tmp;
    int i, j, max, x, long, ind, cols, rows;

    i = sizeof(newfiles=map_array(files,"map_files",this_object(),({dir,n,s})));
    while(i--) if((x=strlen(newfiles[i])) > long) long = x;
    tmp = previous_object()->GetEnvVar("SCREEN");
    if(!tmp || !sscanf(tmp, "%d", x) || !x) x = 80;
    x = x-2;
    if(long > x/3-3) long = x/3-3;
    cols = x/(long+3);
    rows = (max = sizeof(newfiles))/cols;
    if(max % cols) rows++;
    ret = "";
    for(i=0; i<rows; i++) {
        for(j=0; j<cols; j++) {
            ind = (rows * j) + i;
            if(ind < max) ret += sprintf("%:-"+(long+3)+"s", newfiles[ind]);
            else ret += sprintf("%:-"+(long+3)+"s", "");
        }
        ret += "\n";
    }
    return ret;
}

string map_files(mixed *file, int *flags) {
    string tmp;

    if(flags[1] && flags[2]) {
        if(file[1] == -2) return file[0]+"/";
        else return file[0];
    }
    if(!flags[1]) {
        if(find_object(flags[0]+file[0]) && file[1] != -2) tmp = "*";
        else tmp = " ";
    }
    else tmp = "";
    if(!flags[2]) {
        if(file[1] == -2) tmp = tmp + "    ";
        else if(!file[1]) tmp = tmp + "0   ";
        else if(file[1] < 1024) tmp = " 1   ";
        else tmp = sprintf("%s%:-3d ", tmp, (file[1]/1024));
    }
    return tmp + file[0] + ((file[1] == -2) ? "/" : "");
}

string GetHelp(){
    return ("语法: <ls [-ablmnst] (目录|文件)>\n\n"
            "如果传入单个目录作为参数，将列出该目录中的所有文件和子目录。\n"
            "如果列出单个文件，则显示该文件的信息。\n"
            "如果使用通配符等特殊字符，将显示相关文件和/或目录的信息。\n"
            "选项含义:\n"
            "    -a 列出所有文件，包括以 '.' 开头的文件\n"
            "    -b 简要列表，不显示目录名\n"
            "    -l 详细列出文件的所有信息\n"
            "    -m 通过分页器显示输出\n"
            "    -n 不显示对象加载信息\n"
            "    -s 不显示大小信息\n"
            "    -t 按最后修改时间排序\n\n"
            "-l 选项会覆盖 -n 和 -s 选项。\n"
            "-l 列表的列含义:\n"
            "    * 表示已加载，空格表示未加载\n"
            "    访问权限，格式为 rwx\n"
            "    最后修改时间\n"
            "    文件大小\n"
            "    文件名\n\n另见: cd, mkdir, mv, pwd, rm, rmdir");
}
