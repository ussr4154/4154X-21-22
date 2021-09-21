#include "main.h"

void setLift(int power){
    liftMotor = power;
}

void setLiftMotor(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        setLift(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        setLift(-127);
    }
    else{
        setLift(0);
    }
}