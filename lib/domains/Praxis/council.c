/*
// File     :  /domains/Praxis/council.c
// Comment  :  Town Council Chambers
// 94-07-02 :  Pallando @ Nightmare wrote it
// 94-07-06 :  Manny @ Nightmare added descriptions
// 94-08-18 :  Forlock @ Nightmare added descriptions of plaque & law book
 */
#include <lib.h>
#include <dirs.h>
#include <objects.h>
#include <daemons.h>

#define TOWN_HALL "/domains/Praxis/town_hall"
#define HELP_FILE "/domains/Praxis/commands"
#define TMP_FILE DIR_TMP + "/" + (this_player()->query_name()) + ".proposal"
#define QUORUM 5
#define PASSES 5

inherit LIB_ROOM;

mapping policies = ([]);

void create()
{
    ::create();
    enable_commands(); // Used to echo tells to the Town Hall
    SetProperties( ([
                "mountable" : 1,
                "indoors" : 1,
                "light" : 2,
                "no castle" : 1,
                "no teleport" : 1,
                "no bump" : 1,
                "no attack" : 1,
                "no steal" : 1,
                "no magic" : 1,
                ]) );
    SetShort( "高等议会密室" );
    SetLong(
            "这个房间的灯光昏暗，一组长长的窄桌上摆放的12支蜡烛是唯一的光源。"
            "桌子由最纯净的黑曜石制成，四周环绕着木椅，"
            "每把椅子上都镶嵌着明亮的红宝石图案。"
            "房间的墙上挂着噩梦世界各个职业的旗帜，"
            "每一面都是由这片土地上最好的艺术家创作的。"
            "天花板上有4个华丽的图案，每一个都是这片土地上"
            "大法师的肖像。这些画像给人一种注视着密室内一切的感觉。"
            "法律之书放在一个完全由白金制成的底座上。"
            "西墙上挂着一块牌匾。"
           );
    SetExits( ([
                "down"  : "/domains/Praxis/town_hall",
                ]) );
    SetItems( ([
                "view" : "普拉克西斯的壮观全景。",
                ({ "candles", "candle" }) : "长窄桌上的高大细白蜡烛。",
                "table" : "一张抛光明亮的深黑曜石桌子",
                "obsidian" : "黑曜石是这片土地上最纯净的。",
                ({ "chair", "chairs" }) : "每把椅子的椅身上都镶嵌着独特的红宝石图案。",
                "rubies" : "最稀有的大颗红宝石。",
                "flags" : "6面旗帜，每一面代表这片土地上的一个职业。",
                "ceiling" : "一幅巨大的壁画，描绘了这片土地上最伟大的四位："
                "福洛克、笛卡尔、拉桑德拉和影狼。",
                "plaque" : "一块精心雕刻文字的花岗岩牌匾。",
                "book"   : "法律之书。它的封面由纯金制成，"
                "书页由最优质的皮革制成。里面可以找到"
                "这片土地法律的详细内容。",
                "forlock" : "伟大的执法者，穿着一件镶有深红色衬里的黑色长袍。"
                "福洛克深邃的目光让你充满了善良和正义。",
                    "descartes" : "博格的笛卡尔，骑在一匹伟大的白马上，"
                        "是伟大智慧和知识的化身。",
                    "lassondra" : "长长的黑色波浪卷发披在她宽阔肩膀上的"
                        "绿色大斗篷上。温暖的微笑和慈爱的眼睛"
                        "描绘了对所有人的平等和公正。",
                    "shadowwolf" : "穿着一件带兜帽的长袍，影狼也许是"
                        "四人中最神秘的。影狼的眼睛隐约穿透"
                        "环绕他的黑暗，似乎在直视着你。"
                        ]) );
}

void init()
{
    ::init();
    add_action( "cmd_propose", "propose" );
    add_action( "cmd_repeal", "repeal" );
    add_action( "cmd_cast", "cast" );
    add_action( "cmd_read", "read" );
    add_action( "cmd_law", "law" );
}

int quorum()
{
    object *voters;

    voters = all_inventory( this_object() );
    voters = filter_array( voters, "leaderp", find_object( OB_SIMUL_EFUN ) );
    return sizeof( voters );
}

int votes_needed( string title )
{
    return PASSES + sizeof( policies[title]["Nay"] ) -
        sizeof( policies[title]["Aye"] );
}

int vetos_needed( string title )
{
    return PASSES + sizeof( policies[title]["Aye"] ) -
        sizeof( policies[title]["Nay"] );
}

varargs void display_policy( mapping policy, int as_law )
{
    int then;

    if( as_law )
    {
        then = policy["Time"];
        printf( "自%s，%d %s，%d NM；在%s的推动下\n\n\t\t\%s\n\n%s",
                day( then ), date( then ), month( then ), year( then ),
                capitalize( policy["Proposer"] ), policy["Title"], policy["Text"] );
        return;
    }
    printf(
            "标题：%s\n提议者：%s\n\n%s",
            policy["Title"],
            capitalize( policy["Proposer"] ),
            policy["Text"],
          );
    if( sizeof( policy["Aye"] ) )
        write( wrap( "赞成：" + implode( policy["Aye"], ", " ) ) );
    if( sizeof( policy["Nay"] ) )
        write( wrap( "反对：" + implode( policy["Nay"], ", " ) ) );
    if( sizeof( policy["Abs"] ) )
        write( wrap( "弃权：" + implode( policy["Abs"], ", " ) ) );
}

int cmd_law( string arg )
{
    mapping policy;

    if( arg )
    {
        if( undefinedp( policy = POLITICS_D-> query_policy( arg ) ) )
            write( "没有这条法律：" + arg + "\n" );
        else
            display_policy( policy, 1 );
    } else {
        printf( "法律之书包含以下内容：\n  %s\n",
                wrap( implode( sort_array( keys(
                                POLITICS_D-> query_policies() ), 1 ), "\n  " ) ) );
    }
    return 1;
}

int cmd_read( string arg )
{
    mapping policy;

    if( arg )
    {
        if( arg == "book" || arg == "law" )
            write( "使用\"law\"命令。\n" );
        else if( arg == "plaque" )
            write( read_file( HELP_FILE ) );
        else if( undefinedp( policy = policies[arg] ) )
            write( "没有这个提案：" + arg + "\n" );
        else
            display_policy( policy );
    } else {
        if( !sizeof( policies ) )
            write( "没有等待通过的提案。\n" );
        else
            write( "以下提案等待通过：\n" +
                    wrap( implode( keys( policies ), ", " ) ) );
    }
    return 1;
}

int cmd_propose( string title )
{
    if( !title ) return notify_fail( "语法：propose <标题>\n" );
    title = lower_case( title );
    if( policies[title] || POLITICS_D-> query_policy( title ) )
        return notify_fail( "那已经存在了。\n" );
    if( ( quorum() < QUORUM ) && !archp( this_player() ) )
        return notify_fail( "没有" + QUORUM + "名投票者在场。\n" );
    write( "输入你的提案：\n" );
    this_player()-> edit( TMP_FILE,
            (: "callback_propose" :),
            (: "abort_propose" :),
            title,
            );
    return 1;
}

void abort_propose( string title ) { write( "中止提案。\n" ); }

void callback_propose( string title )
{
    string proposal;

    proposal = read_file( TMP_FILE );
    rm( TMP_FILE );
    if( !proposal )
    {
        write( "中止提案。\n" );
        return;
    }

    policies[title] = ([
            "Title" : title,
            "Proposer" : this_player()-> query_name(),
            "Time" : time(),
            "Text" : proposal,
            "Voted" : ([]),
            "Aye" : ({}),
            "Nay" : ({}),
            "Abs" : ({}),
            ]);
    display_policy( policies[title] );
    write( "你有半小时的时间来获得" + votes_needed( title ) + "张选票\n" );
    call_out( "last_warning", 1500, title );
}

void last_warning( string title )
{
    object proposer;

    if( !policies[title] ) return;
    call_out( "delete_proposal", 300, title );
    if( !proposer = find_player( policies[title]["Proposer"] ) ) return;
    tell_object( proposer,
            "***** 最后警告 *****\n"+
            "提案" + title + "将在5分钟后被删除\n除非"+
            "你能在那之前找到" + votes_needed( title ) + "张选票。\n" );
}

void delete_proposal( string title )
{
    map_delete( policies, title );
}

int cmd_repeal( string title )
{
    mapping policy;

    if( !title ) return notify_fail( "语法：repeal <标题>\n" );
    title = lower_case( title );
    if( !policy = POLITICS_D-> query_policy( title ) )
        return notify_fail( "没有这条法律：" + title + "。\n" );
    if( ( quorum() < QUORUM ) && !archp( this_player() ) )
        return notify_fail( "没有" + QUORUM + "名投票者在场。\n" );
    policy["Proposer"] = this_player()-> query_name();
    policy["Repeal"] = 1;
    policies[title] = policy;
    call_out( "delete_proposal", 1800, title );
    write( "你有半小时的时间来获得废除" +
            title + "所需的选票。\n" );
    return 1;
}

int cmd_cast( string arg )
{
    string vote, title, name;

    if( !arg ||
            ( ( 2 != sscanf( arg, "%s on %s", vote, title ) ) &&
              ( 2 != sscanf( arg, "%s %s", vote, title ) )      ) )
        return notify_fail( "语法：cast <投票> on <标题>\n" );
    if( !policies[title] )
        return notify_fail( "没有这个提案：" + title + "。\n" );
    name = this_player()-> query_name();
    if( policies[title]["Voted"][name] )
        policies[title][policies[title]["Voted"][name]] -= ({ name });
    vote = lower_case( vote[0..2] );
    switch( vote )
    {
        case "aye":
            policies[title]["Aye"] += ({ name }); break;
        case "nay":
            policies[title]["Nay"] += ({ name }); break;
        case "abs":
            policies[title]["Abs"] += ({ name }); break;
        default:
            return notify_fail( "你的投票必须是'aye'、'nay'或'abs'。\n" );
    }
    policies[title]["Voted"][name] = capitalize( vote );
    if( policies[title]["Repeal"] )
    {
        if( vetos_needed( title ) < 1 )
        {
            say( title + "不再是法律了。\n" );
            POLITICS_D-> repeal_policy( title );
            delete_proposal( title );
            return 1;
        }
    }
    else if( votes_needed( title ) < 1 )
    {
        say( "提案：" + title + "已被写入法律之书。\n" );
        POLITICS_D-> set_policy( title, policies[title] );
        delete_proposal( title );
        return 1;
    }
    write( "好的。\n" );
    return 1;
}

void receive_message( string msg_class, string msg )
{
    /*
       write( "class = " + msg_class + "\n" );
     */
    message( msg_class, msg, all_inventory( this_object() ), ({ this_player() }) );
    TOWN_HALL-> receive_message( msg_class, msg );
}

// Wizard test functions

mixed query_policies() { return policies; }

void alter_proposal( string title, string field, mixed value )
{
    policies[title][field] = value;
}

void make_law( string title )
{
    POLITICS_D-> set_policy( title, policies[title] );
    delete_proposal( title );
}

void repeal_law( string title )
{
    POLITICS_D-> repeal_policy( title );
    delete_proposal( title );
}

/* EOF */
