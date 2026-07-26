#include <lib.h>
#include <position.h>

inherit LIB_CHAMBER;

mapping Floors;
int elevator_speed;

protected void create() {
    chamber::create();
    SetKeyName("elevator");
    SetId(({"box"}));
    SetAdjectives(({"simple"}));
    SetShort("一部电梯");
    SetLong("这是一个大型箱式运输工具，用于沿固定垂直轴线运送物品和人员。");
    SetRace("vehicle");
    SetPosition(POSITION_NULL);
    SetMelee(0);
    SetNoClean(1);
    SetMount(1);
    SetMountStyle("driven");
    SetVisibleRiders(0);
    SetOpacity(100);
    SetMaxHealthPoints(20);
    SetMaxCarry(30000);
}

void init(){
    ::init();
}

int eventMove(mixed foo){
    int ret;
    ret = ::eventMove(foo);
    return ret;
}

mapping GetFloors(){
    return copy(Floors);
}

mapping SetFloors(mapping floors){
    object *buttons = ({});
    buttons = filter(all_inventory(), 
            (: base_name($1) == LIB_ELEVATOR_BUTTON :));
    if(sizeof(buttons)) buttons->eventDestruct();
    Floors = floors;
    foreach(mixed key, mixed val in Floors){
        object button = new(LIB_ELEVATOR_BUTTON);
        string tmpname = cardinal(atoi(key));
        string *tmpid = ({ key, "button" });
        if(!undefinedp(tmpname)) tmpid += ({ tmpname });
        button->SetAdjectives( ({ key, "elevator" }) ); 
        button->SetId( tmpid );
        button->SetKeyName( "button" );
        button->SetElevator(this_object());
        //button->SetInvis(0);
        AddItem(button);
        //button->eventMove(this_object());
    }
}

int GetSpeed(){
    return elevator_speed;
}

int SetSpeed(int x){
    return (elevator_speed = x);
}

