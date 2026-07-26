/*    /cmds/players/biography.c
 *    from the NIghtmare V Object Library
 *    biography
 *    created by Descartes of Borg 951217
 */

#include <lib.h>
#include <clock.h>
#include <daemons.h>
#include <marriage.h>
#include <message_class.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    class marriage *m;
    mapping *deaths;
    mapping kills;
    string *npcs, *tmp, *col1, *col2, *col3;
    string yrstr;
    int x, cols, birth, i;

    cols = ((int *)this_player()->GetScreen())[0];
    tmp = ({ center(this_player()->GetShort() +
                " 在 " + mud_name() + " 的传记", cols), "" });
    birth = this_player()->GetBirth();
    x = query_year(birth);
    if( x < 0 ) yrstr = (-x) + " BN";
    else yrstr = x + "";
    tmp += ({ sprintf("%:-"+(cols/2)+"s%"+(cols/2)+"s", "等级: " +
                this_player()->GetLevel(), "年龄: " +
                ((time() - birth)/YEAR) + " 年") });
    tmp += ({ "你目前的道德状态为" + this_player()->GetMoralityDescription()
            + "。" });
    tmp += ({ sprintf("你出生于%s年第%s的第%d%s天。",
                yrstr, query_month(birth),
                query_date(birth), ordinal(query_date(birth))) });
    m = (class marriage *)this_player()->GetMarriages();
    if( !sizeof(m) ) tmp += ({ "你从未结过婚。" });
    else {
        class marriage marr;
        string town;

        marr = m[0];
        if( !marr->DivorceDate ) {
            x = query_year(marr->WeddingDate);
            if( x < 0 ) yrstr = (-x) + " BN";
            else yrstr = x + "";
            town = (marr->Location)->GetTown();
            if( !town || town == "wilderness" ) town = ".";
            else town = " in " + town + ".";
            tmp += ({ "你于" + yrstr + "年" +
                    query_month(marr->WeddingDate) + "的第" +
                    ordinal(query_date(marr->WeddingDate)) + "天与" + marr->Spouse + "结婚" + town });
            if( sizeof(m) > 1 ) m = m[1..];
            else m = ({});
        }
        if( i = sizeof(m) ) {
            tmp += ({ "过往婚姻:" });
            while(i--) {
                string yrstr2;

                marr = m[i];
                x = query_year(marr->WeddingDate);
                if( x < 0 ) yrstr = (-x) + " BN";
                else yrstr = x + "";
                x = query_year(marr->DivorceDate);
                if( x < 0 ) yrstr2 = (-x) + " BN";
                else yrstr2 = x + "";
                town = (marr->Location)->GetTown();
                if( !town || town == "wilderness" ) town = "";
                else town = " in " + town;		
                tmp += ({ "你于" + yrstr + "年" +
                        query_month(marr->WeddingDate) + " " +
                        query_date(marr->WeddingDate) + "日与" + marr->Spouse + "结婚" +
                        town + "，于" + yrstr2 + "年" +
                        query_month(marr->DivorceDate) + " " +
                        query_date(marr->DivorceDate) + "日离婚。"
                        });
            }
        }
    }
    deaths = this_player()->GetDeaths();
    if( !(x = sizeof(deaths)) )
        tmp += ({ "你从未经历过死亡的痛苦。" });
    else {
        mapping *d1, *d2;

        tmp += ({ "", "死亡的阴影在以下" +
                consolidate(x, "次") + "降临于你:" });
        if( x == 1 ) {
            d1 = deaths[0..0];
            d2 = ({});
        }
        else {
            d1 = deaths[0..(x-1)];
            d2 = deaths[x..];
        }
        for(i=0; i<x; i++)
            tmp += ({ sprintf("%:-" + (cols/2) + "s%s",
                        (i >= sizeof(d1)) ? "" :
                        d1[i]["enemy"],
                        (i >= sizeof(d2)) ? "" :			
                        d2[i]["enemy"]) });
    }	    
    kills = STATISTICS_D->GetKills(this_player()->GetKeyName());
    npcs = sort_array(keys(kills), 1);
    if( !(x = sizeof(npcs)) )
        tmp += ({ "你从未伤害过他人。" });
    else {
        tmp += ({ "","你应对以下对象的死亡负责:" });
        if( x < 3 ) {
            col1 = npcs[0..0];
            if( x == 2 ) col2 = npcs[1..1];
            else col2 = ({});
            col3 = ({});
        }
        else {
            x = x/3;
            col1 = npcs[0..(x-1)];
            col2 = npcs[x..(x+x-1)];
            col3 = npcs[(2*x)..];
        }
        for(i=0; i<x; i++)
            tmp += ({ sprintf("%:-" + (cols/2) + "s%:-" + (cols/2) + "s%s",
                        (i >= sizeof(col1)) ? "" :			
                        col1[i] + " (" + kills[col1[i]] + ")",
                        (i >= sizeof(col2)) ? "" :			
                        col2[i] + " (" + kills[col2[i]] + ")",
                        (i >= sizeof(col3)) ? "" :
                        col3[i] + " (" + kills[col3[i]] + ")") });
    }
    this_player()->eventPage(tmp, MSG_SYSTEM);
    return 1;
}

string GetHelp(){
    return ("用法: biography\n\n"
            "传记详细记录了你在 " + mud_name() + " 上的生活。"
            "这些信息包括你的出生、死亡、婚姻和其他生活信息。\n"
            "参考: score");
}
