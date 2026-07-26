#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("lemur");
    SetAdjectives( ({"small", "startling", "grey", "gray"}) );
    SetId( ({"primate", "simian"}) );
    SetShort("一只狐猴");
    SetLong("这只小动物的外表令人惊讶。它看起来很像小型猴子和浣熊的杂交。它有一个细长的口鼻部，眼睛周围的皮毛是深色的，像强盗的面具。然而它的身体明显是猿类的，有着猴子那样的可缠绕的前肢。它灰色的毛茸茸的身体末端是一条荒谬地长的尾巴，上面有黑白条纹。");
    SetLevel(1);
    SetMelee(1);
    SetRace("primate");
    SetMaxHealthPoints(40);
    SetGender("male");
}
void init(){
    ::init();
}
