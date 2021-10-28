#include "main.h"

//Helpers

void holdToOpenClaw(int power){
    goalClaw = power;
}

void holdToCloseClaw(int power){
    goalClaw = -power;
}

void holdToRaiseDumpTruck(int power){
    dumpTruck = power;
}

void holdToLowerDumpTruck(int power){
    dumpTruck = -power;
}

//Toggles

void setClawMotors(){

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        holdToOpenClaw(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        holdToCloseClaw(127);
    }
    else{
        goalClaw = 0;
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
        holdToRaiseDumpTruck(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        holdToLowerDumpTruck(127);
    }
    else{
        dumpTruck = 0;
    }

}