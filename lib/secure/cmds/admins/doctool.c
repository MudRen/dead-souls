#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;
string doctype, funcname, doc, path;
string *valid_docs = ({"lfun","sefun"});
string *doc_array = ({});
string *headers = ({ "NAME", "SYNOPSIS", "DESCRIPTION", "EXAMPLES", "LOCATION", "SEE ALSO", "Author" });
mapping ContentMap = ([]);
string *headers_left = ({});
string *sourcefiles = ({});

string eventFindInstances(){
    string *raw_list = load_object("/secure/cmds/admins/files")->cmd("-c "+"/lib/");
    string cooked_list = "";
    sourcefiles = ({});
    foreach(string file in raw_list){
        string funex;
        if(last(file, 2) != ".c") continue;
        if(grepp(load_object("/secure/cmds/creators/showfuns")->cmd(file), funcname)){
            funex = function_exists(funcname,load_object(file),1);
            if(funex && !grepp(cooked_list,funex+"\n")){
                sourcefiles += ({ last_string_element(funex,"/") });
                cooked_list += funex+"\n";
            }
        }
    }
    return cooked_list;
}

int eventWriteDoc(){
    string ret = upper_case(funcname)+"\n\n";
    foreach(string header in headers){
        ret += header + "\n        ";
        ret += replace_string(replace_string(ContentMap[header],"\n\n","\n"),"    ","") + "\n\n";
    }
    ret = replace_string(ret,"\n\n\n","\n\n");
    if(doctype == "lfun"){
        string tmp_path;
        foreach(string sourcefl in sourcefiles){
            tmp_path = "/doc/lfun/lib/"+sourcefl;
            if(!directory_exists(tmp_path)) mkdir(tmp_path);
            tmp_path += "/"+funcname;
            write_file(tmp_path, ret,1);
        }
    }

    write("%^GREEN%^output: "+ret+"%^RESET%^");
    write_file(path, ret,1);
    doc_array = ({});
    headers_left = ({});
    sourcefiles = ({});
    return 1;
}

varargs int eventSetSection(string content, string header){
    string tmpstr = " ";
    if(content == "Author" || (header  == "Author" && (!content || content == "")))
        tmpstr = this_player()->GetName();
    if(sizeof(headers_left)){
        if(!content || member_array(content, headers) != -1){
            if(!header) header = content;
            if(!sizeof(ContentMap[header])) ContentMap[header] = tmpstr; 
            if(doctype == "lfun" && header == "LOCATION"){
                headers_left -= ({ "LOCATION "});
            }
            this_object()->eventManageQueries();
            return 1;
        }
    }
    if(content && content != "") ContentMap[header] = content;
    else if(!sizeof(ContentMap[header])) ContentMap[header] = tmpstr;
    if(doctype == "lfun" && header == "LOCATION"){
        headers_left -= ({ "LOCATION "});
    }
    this_object()->eventManageQueries();
    return 1;
}

int eventQueryEntry(string header){
    write("请输入 "+funcname+"() 的 "+header+" 数据：");
    input_to( (: eventSetSection :) , header);
    return 1;
}

int eventManageQueries(){
    if(doctype == "lfun" && sizeof(headers_left) && 
            headers_left[0] == "LOCATION" && member_array("LOCATION",headers_left) != -1){
        call_out( (: eventSetSection, eventFindInstances(), "LOCATION" :), 1);
        if(sizeof(headers_left)) headers_left -= ({ headers_left[0] });
        return 1;
    }
    else if(sizeof(headers_left)){
        eventQueryEntry(headers_left[0]);
        headers_left -= ({ headers_left[0] });
        return 1;
    }
    if(!sizeof(headers_left) && sizeof(ContentMap["Author"])){
        eventWriteDoc();
    }
    return 1;
}

mixed cmd(string args) {
    int x;
    headers_left = ({});
    ContentMap = ([]);
    doc_array = ({});


    if(!archp(previous_object())) return 0;

    if(!args || args == ""){
        write("您需要更具体一些。尝试：help doctool");
        return 1;
    }

    if(sscanf(args,"%s %s",doctype, funcname) != 2){
        write("此命令需要两个参数。例如：\n"
                "doctool lfun GetFunky\n"
                "将开始为库（本地）函数 \"GetFunky\" 执行文档工具。");
        return 1;
    }

    funcname = replace_string(funcname, " ", "");
    if(grepp(funcname,"/")) funcname = last_string_element(funcname, "/");
    write("文档类型："+doctype);
    write("函数名："+funcname);

    if(member_array(doctype, valid_docs) == -1){
        write("这是未知的文档类型。请尝试以下类型之一："+implode(valid_docs, ", ")+"。");
        return 1;
    }

    path = "/doc/"+doctype;
    if(!directory_exists(path)) mkdir(path);
    if(doctype == "lfun"){
        path += "/all";
        if(!directory_exists(path)) mkdir(path);
    }

    path += "/"+funcname;

    if(file_exists(path)) doc = read_file(path);
    else doc = "TEMPLATE";

    //write(doc);

    doc_array = explode(doc,"\n");

    foreach(string header in headers){
        int i, includer = 0;
        string tmp_str = "";
        for(i = 0;i < (sizeof(doc_array)-1); i++){
            if(member_array(doc_array[i],headers) != -1) includer = 0;
            if(includer) tmp_str += doc_array[i]+"\n";
            if(doc_array[i] == header) includer = 1;
        }
        eventSetSection(tmp_str, header);
        write(header+": \n"+tmp_str);
    }

    headers_left = headers;
    eventManageQueries();
    return 1;
}

string GetHelp(){
    return ("语法：doctool [文档类型] 函数名\n\n"
            "协助创建 sefun 和 lfun 文档。\n"
            "由于它会自动扫描许多文件并对其执行操作，\n"
            "此命令可能会严重延迟运行它的 MUD。\n"
            "因此，仅在可以接受偶尔出现较大延迟时使用。"
            "\n\n"
            "前几次运行此命令时出现 \"Too long "
            "evaluation\" 错误是正常的。\n"
            "另见：man, help");
}
