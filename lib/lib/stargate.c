#include <lib.h>
#include <daemons.h>
#include "/lib/include/stargate.h"

/**
 * 2006-03-28, jonez
 *  - based on a suggestion from rhk, changed so that one cannot enter the
 *    gate unless status is "outbound". this makes the object closer to the
 *    (theoretical) math and also to what happens on the show.
 */

/**
 * based on portal.c by Brodbane - March 2006
 *
 * $Id: stargate.c,v 1.1 2006/04/05 05:48:39 jam Exp $
 *
 * The desired functionality is much like a "star gate": users dialed
 * letters or full words that lined up with destinations.  A portal opens to
 * that destination briefly.  To define destinations you must setup a
 * constant below then add it to the switch statement in the cmdDial
 * function.  This object is crude and basic, but gets the job done.
 *
 * 2006-03-22, jonez
 *   - original version of this file is from Daelas@Moraelinost
 * 2006-03-23, jonez
 *   - altered so code uses existing verbs (touch, enter) where possible. last add_action is for dial command.
 *   - added single mapping called "database" and made the "dial" command use it.
 *   - dial command no longer uses switch/case, making adding a new destination simpler
 *   - made use of SetPreventGet() / SetPreventPut()
 *   - made use of new stargate daemon
 *   - made use of LIB_STARGATE
 *   - made use of STARGATE_D
 *
 * IDEAS:
 *  - create a daemon that holds the stargate network [DONE]
 *  - allow for stargate failure
 *  - add dhd object
 *  - change the code so that it uses a single mapping of names and
 *    destinations, perhaps in a database file. currently an update to the
 *    object requires an update for all the objects. [DONE]
 *  - dhd skill (thanks plato)
 *  - delay when dialing gate. destination dhd lights up?
 *  - player should not be able to dial earth if earth is already connected elsewhere (need daemon) [DONE]
 *  - make use of existing verbs (enter, touch) instead of doing our own thing. [DONE]
 *  - daemon should contain a class that maps the various gates to each other. see lib/include/door.h [DONE]
 *  - shout "off world activation" into the gateroom when the gate engages.
 *  - track status as "incoming" or "outgoing".. you can only "enter" an outgoing gate (rhk) [DONE]
 *  - if room is empty, shut down the gate (rhk)
 *  - change callout time when someone goes through the gate (rhk)
 */

inherit LIB_ITEM;

nosave private string origin;
nosave private int connect_time;

string displayLong();
string displayShort();

void create(){ 
    item::create();

    SetKeyName("stargate");
    SetId(({"stargate", "gate", "gateway", "ring"}));
    SetAdjectives(({"stargate"}));
    SetShort( (: displayShort :) );

    SetLong( (: displayLong :) );

    AddItem( "inner ring", "第二个环——内环——放置在大环内部，"
            "似乎可以转动。");
    SetMass(1000);
    SetBaseCost("silver",50);
    SetPreventGet("星门由纯纳夸达制成，无法移动。");
    SetPreventPut("星门由纯纳夸达制成，无法移动！");
    SetTouch("你感到手下的星门嗡嗡作响，充满能量。");
}

void init(){
    ::init();
    add_action( "cmdDial", "dial" );
    add_action( "cmdEnter", "enter");
}


void SetOrigin(string o, string d){
    if (o == "" || d == "") return;    
    origin = lower_case(o);
    if(!sizeof(STARGATE_D->GetStargate(origin))){
        STARGATE_D->SetStargate(origin, d);
    }
}

string GetOrigin(){
    return origin;
}

void eventConnect(string destination){
    int ret;

    destination = lower_case(destination);

    if (origin == destination){
        write("你尝试拨号星门，但最后一个V形标记没有锁定");
        say(this_player()->GetName() + "尝试拨号星门，但最后一个V形标记没有锁定");
        return;
    }

    ret = STARGATE_D->eventConnect(origin, destination);
    if (ret){
        string d = STARGATE_D->GetDestination(destination);
        write("古老的环形结构锁定到位，一道传送门在能量爆发中形成。");
        say("古老的环形结构锁定到位，一道传送门在能量爆发中形成。");
        tell_room(d, "古老的环形结构锁定到位，一道传送门在能量爆发中形成");
        call_out("eventDisconnect", 10+random(5));
        connect_time = time();
        return;
    }

    write("你尝试拨号星门，但什么也没有发生。");
    say(this_player()->GetName() + "尝试拨号星门但失败了。");

    return;
}

int eventDisconnect(){
    string endpoint = STARGATE_D->GetEndpoint(origin);
    string e = STARGATE_D->GetDestination(origin);
    string d = STARGATE_D->GetDestination(endpoint);
    if(d) tell_room(d, "星门上的V形标记解除锁定，传送门消失了。");
    if(e) tell_room(e, "星门上的V形标记解除锁定，传送门消失了。");
    connect_time = 0;
    return STARGATE_D->eventDisconnect(origin);
}

string status(){
    return STARGATE_D->GetStatus(origin);  
}

mixed cmdDial(string s){
    object ob;
    string flipside;
    if (s)
    {
        if(STARGATE_D->GetDestination(s)) 
            flipside = STARGATE_D->GetDestination(s);
        eventConnect(s);
        if(sizeof(flipside) && !ob) ob = load_object(flipside);
        if(!ob){
            write("星门突然开始关闭。");
            eventDisconnect();
        }
        return 1;
    }

    return 0;

}

int cmdEnter(string what){
    string endpoint, destination;
    object who;

    if(!answers_to(what, this_object()))
    {
        return 0;
    }

    if (status() != "outbound")
    {
        return 0;
    }

    who = this_player();
    endpoint = STARGATE_D->GetEndpoint(origin);
    destination = STARGATE_D->GetDestination(endpoint);
    who->eventPrint("你穿过星门的事件视界。");
    who->eventMoveLiving(destination,
            "$N走入了事件视界，消失了。",
            "$N从事件视界中走出。");
    return 1;
}

int eventEnter(object who){
    string endpoint;

    if (!who) return 0;

    endpoint = STARGATE_D->GetEndpoint(origin);
    if (status() == "connected")
    {
        who->eventPrint("你穿过星门的事件视界。");
        who->eventMoveLiving(endpoint,
                "$N走入了事件视界，消失了。",
                "$N从事件视界中走出。");
    }
    return 1;
}

string displayLong(){
    string buf, stat;

    buf = "This is the Stargate of legend.  The Stargate was created "
        "from naquadah ore, similar to black quartz.  It is a perfectly "
        "circular device approximately ten meters in diameter and "
        "comprised of two sets of rings and nine chevrons placed "
        "equidistant along its outer circumference.";

    stat = status();

    if (stat == "outbound" || stat == "inbound")
    {
        buf += " There is an event horizon in the center of the ring that looks like shimmering water.";
    }
    else if (stat == "idle")
    {
        buf += " This gate is currently idle.";
    }
    return buf;
}

string displayShort(){
    string stat;
    stat = status();
    switch (stat)
    {
        case "inbound":
            return "an inbound stargate";
        case "outbound":
            return "an outbound stargate";
        case "idle":
            return "an idle stargate";
        default:
            return "a broken stargate";
    }
}

void heart_beat(){
    if(connect_time && (time() - connect_time ) > 60){
        eventDisconnect();
    }
}
