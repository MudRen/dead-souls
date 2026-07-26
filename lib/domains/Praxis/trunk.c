inherit "/lib/std/room";

void create() {
    ::create();
    SetShort("树干上部");
    SetLong(
            "法师树的上部树干中雕刻出了一个非常大的房间。"
            "小楼梯向下通往树的入口，向上则通往树外，"
            "进入广阔的树枝树冠。");
    SetProperties( (["light"     : 2, 
                "indoors"   : 1 ,
                "no castle" : 1]) );
    SetItems( ([
                "mage tree"   : "你被活生生的木质墙壁环绕，看不到树的全貌。",
                "upper trunk" : "你在树干里。",
                "entrance"    : "入口在你下面的房间里。",
                "canopy"      : "你上方是绿叶繁茂的树枝。上去吧。",
                "room"        :  (: this_object(), "print_long" :),
                "trunk"       : "你在树干里。",
                "tree"        : "你被活生生的木质墙壁环绕，看不到树的全貌。",
                "branches"    : "你上方是绿叶繁茂的树枝。上去吧。",
                "walls"       : "这个房间有墙壁。想想看。它们是木制的，"
                "这很合理，因为你在一棵树里面。",
                "stairway"    : "当你把体重压上去时，木质楼梯嘎吱作响。"]) );
    SetExits( (["down" : "/domains/Praxis/mage_hall",
                "up"   : "/domains/Praxis/branches"]) );
}

void print_long() {
    write (this_object()->GetLong());
}
void init(){
    ::init();
}
