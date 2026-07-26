/* Stupid blackjack table
 * works, other than the fact that the value of ace always equals 1.
 * by boy@frontiers.
 * (You can get two of the same card, like two 8 of spades.)
 * Too hard and too much work to simulate a whole deck.
 */
#include <lib.h>
inherit LIB_ITEM;
void StupidAce();
int needace;
int aceval;
int gameon;
int score;
int dscore;
int bet;
int plidle;
string playername,oldplayername;
object player,oldplayer,here;
void cleanup();
void eventDealerHit();
void YouWin();
void YouLose();

int read(string args) {
    write("小字写着……");
    write(" %^CYAN%^庄家17点停牌。");     write(" %^CYAN%^平局归庄家。");
    write("deal <金额> : 开始游戏，下注<金额>");     write(" hit : 要求发一张牌");
    write(" stand pat : 结束游戏");
    return 1;
}

protected void create() {
    ::create();
    SetShort("一张21点赌桌");
    SetLong("这里放着一张小型机械21点赌桌，表面覆盖着绿色毛毡。");
    SetPreventGet("你拿不了这个！");
    SetMass(0);
    SetId( ({"table", "blackjack table"}) );
    SetKeyName("table");
    SetItems( ([
                ({"writing","letters"}): "桌子上的一些文字。试试\"read writing on table\"",
                ]) );
    SetRead( ([
                ({"writing","letters"}) : (: read :),
                ]) );
    SetDefaultRead("default", (: read :) );
    oldplayername="this_is_a_silly_string";
}
void init() {
    ::init();
    add_action("eventHit", "hit");
    add_action("eventStand", "stand");
    add_action("eventDeal", "deal");
}
int eventHit() {
    int done;
    int cardscore;
    string card, suit;
    int x;
    done = 0;
    if (gameon == 0) {
        write("游戏还没开始，输入\"deal\"开始一局。");
        return 1;
    }
    if(gameon == 1 && this_player()->GetName() != oldplayername) {
        write("你现在没有在玩。");
        return 1;
    }
    x = random(13);
    switch (x + 1) {
        case 1 : card = "Ace";
                 break;
        case 11 : card = "Jack";
                  break;
        case 12 : card = "Queen";
                  break;
        case 13 : card = "King";
                  break;
        default : card = ""+(x + 1);
    }
    switch (random(4)) {
        case 1 : suit = "Hearts";
                 break;
        case 2 : suit = "Spades";
                 break;
        case 3 : suit = "Diamonds";
                 break;
        case 0 : suit = "Clubs";
    }
    write("%^BLUE%^你得到一张" + suit + card);
    if (x == 0) {
        StupidAce();
        cardscore = aceval;
        done = 1;
    }
    if (x > 9) {
        cardscore = 10;
        done = 1;
    }
    else {
        if (done == 0) {
            cardscore = x + 1;
        }
    }
    score += cardscore;
    if (score > 21) {
        if(aceval == 11) {
            aceval = 1;
            score -= 11;
            write("%^CYAN%^你的分数是 " + score);
        }
        else {
            YouLose();
        }
    }
    if (score == 21) {
        YouWin();
    }
    return 1;
}
int eventStand(string str) {
    int lose;

    if(str != "pat") return 0;
    if (gameon == 0) {
        write("游戏还没开始，输入\"deal\"开始一局");
        return 1;
    }
    if(gameon == 1 && this_player()->GetName() != oldplayername) {
        write("你现在没有在玩。");
        return 1;
    }
    write("%^CYAN%^你的最终分数是 " + score);

    if (dscore < 22) {
        write("%^BOLD%^庄家的分数是 " + dscore);
    }
    else {
        write("%^BOLD%^庄家爆牌了");
    }
    if (score > dscore && score < 21) {
        YouWin();
    }
    else {
        if (dscore > 21) {
            YouWin();
        }
        else {
            YouLose();
        }
    }
    return 1;
}
void cleanup() {
    oldplayername = "this_is_a_silly_string";
    aceval=0;
    score = 0;
    dscore = 0;
    bet = 0;
    gameon = 0;
}
int eventDeal(string args) {
    player=this_player();
    playername=player->GetName();
    here=environment(this_object());
    if(oldplayer) plidle=query_idle(oldplayer);

    if (!args) {
        write("%^YELLOW%^请重试，包括你想下注的金额。");
        return 1;
    }
    sscanf(args, "%d", bet);
    if(!intp(bet) || bet <= 0){
        write("你必须下注一个金额。\n");
        return 1;
    }
    if (this_player()->GetCurrency("silver") < bet) {
        write("你没有那么多银币！");
        return 1;
    }
    if (gameon == 1 && present(oldplayername,here) && plidle < 120 ) {
        write("%^RED%^"+oldplayername+"正在玩。只有一个玩家的位置。");
        return 1;
    }
    if (gameon == 1 && present(oldplayername,here) && plidle > 120 ) {
        write("%^RED%^"+oldplayername+"之前在玩，但"+nominative(oldplayer)+"已经闲置了，庄家把"+objective(oldplayer)+"踢出了游戏。",oldplayer);
        say(oldplayername+"因为闲置被踢出了21点游戏。",oldplayer);
        tell_object(oldplayer,"你因为闲置被踢出了21点游戏。");
        cleanup();
    }
    if (gameon == 1 && !present(oldplayername,here) ) {
        write("%^RED%^"+oldplayername+"之前在玩，但"+nominative(oldplayer)+"已经离开了，庄家把"+objective(oldplayer)+"踢出了游戏。");
        say(oldplayername+"因为离开被踢出了21点游戏。",oldplayer);
        tell_object(oldplayer,"你突然想起你中途离开了一个21点游戏，你可能已经被踢出了。");
        cleanup();
    }

    oldplayername = playername;
    oldplayer = player;
    gameon = 1;
    write("%^RED%^你请庄家让你加入下一局。");
    say("%^YELLOW%^" + this_player()->GetName() + "开始玩21点。");
    this_player()->AddCurrency("silver", -bet);
    eventDealerHit();
    eventHit();
    eventHit();
    write("%^CYAN%^你当前的分数是  " + score);
    return 1;
}
void eventDealerHit() {

    int cardscore;
    int x;
    while (dscore < 17) {
        x = random(13);
        if (x > 9) {
            dscore += 10;
        }
        else {
            dscore += x;
        }
    }
}
void YouLose() {
    write("你的分数是 " + score);
    write("%^RED%^你输了");
    say("%^YELLOW%^" + this_player()->GetName() + "输了。");
    cleanup();
}
void YouWin() {
    write("你的分数是 " + score);
    write("%^GREEN%^你赢了！");
    say("%^YELLOW%^" + this_player()->GetName() + "赢了！");
    this_player()->AddCurrency("silver", 2 * bet);
    cleanup();
}
void StupidAce() {
    int temp;
    if ((score + 11) > 21) {
        aceval = 1;
    }
    else {
        aceval = 11;
    }
    temp = aceval + score;
    write("%^CYAN%^你当前的分数是 " + temp);
}

