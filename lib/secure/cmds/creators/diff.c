/*
// /bin/dev/_diff.c
// Finds the difference between two files.
// This file is a part of the TMI distribution mudlib.
// Please retain this header if you use this code.
// Devised & Written by Douglas Reay (Pallando @ TMI, Ephemeral Dale, etc)
// Version 1.0  92-11-28
//
// Watcher@TMI (93-04-10) changed it so the output is put through the
//  user's more pager system, and made the headlines stand out a bit better.
// Pallando (93-05-28) Added this command to Dead Souls's mudlib.
//                     Changed its name from "compare" to "diff"
 */

#include <lib.h>
#include <message_class.h>

inherit LIB_DAEMON;

int sort( string mem, mixed arr )
{
    return -1 == member_array( mem, arr );
}

mixed get_lines( string file_name )
{
    string file;

    file_name = absolute_path( "cwd", file_name );
    switch( file_size( file_name ) ) 
    {
        case -2: { write( file_name + " 是一个目录。\n" ); return 0; }
        case -1: { write( file_name + " 不是一个文件。\n" ); return 0; }
    }
    if( !master()-> valid_read( file_name,
                previous_object(), "diff" ) )
    {
        write( file_name + " : 权限被拒绝。\n" );
        return 0;
    }
    file = read_file( file_name );
    if( !file ) 
    {
        write( file_name + " 是空的。\n" );
        return 0;
    }
    return explode( file, "\n" );
}

int cmd( string a )
{
    string output, file_name1, file_name2;
    string *lines1, *lines2;
    string *ONEnotTWO, *TWOnotONE;

    if( !a || 2 != sscanf( a, "%s %s", file_name1, file_name2 ) )
    {
        notify_fail( "Syntax: diff <file1> <file2>\n" ); 
        return 0;
    }
    lines1 = get_lines( file_name1 );
    lines2 = get_lines( file_name2 );
    if( !pointerp( lines1 ) || !pointerp( lines2 ) )
    {
        notify_fail( "未进行比较。\n" );
        return 0;
    }
    if( lines1 == lines2 )
    {
        write( file_name1 + " 和 " + file_name2 + " 是同一个文件。\n" );
        return 1;
    }
    ONEnotTWO = filter( lines1, "sort", this_object(), lines2 );
    TWOnotONE = filter( lines2, "sort", this_object(), lines1 );
    if( ONEnotTWO == TWOnotONE )
    {
        write( file_name1 + " 和 " + file_name2 + " 的行内容相同。\n" );
        return 1;
    }
    output = "[在 " + file_name1 + " 中但不在 " + file_name2 + " 中:]\n" +
        implode( ONEnotTWO, "\n" ) + "\n" +
        "\n[在 " + file_name2 + " 中但不在 " + file_name1 + " 中:]\n" +
        implode( TWOnotONE, "\n" ) + "\n";

    this_player()->eventPage( explode(output, "\n"), MSG_SYSTEM | MSG_NOCOLOUR);

    return 1;
}

string GetHelp(){
    return ("语法: diff <文件1> <文件2>\n\n"
            "报告两个文件之间的差异。");
}

