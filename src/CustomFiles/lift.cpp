#include "main.h"

void setLift(int power){
    liftMotor = power;
}

void setLiftMotor(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
        setLift(-127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
        setLift(127);
    }
    else{
        setLift(0);
    }
}
