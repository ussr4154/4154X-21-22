#include "main.h"

//Helpers
void closeClaw(){}

void openClaw(){}

void dumpTruckUp(){}

void dumpTruckDown(){}

//Toggles
void notchToggle(){

    bool notch = false;

    if(notch == false){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
            goalNotch.set_value(true);
            notch = true;
        }
    }
    else if(notch == true){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
            goalNotch.setValue(false);
            notch = false;
        }
    }
}

void clawToggle(){

    bool claw = false;

    if(claw == false){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            closeClaw();
            claw = true;
        }
    }
    else if(claw == true){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            openClaw();
            claw = false;
        }
    }
}

void dumpTruckToggle(){

    bool dumpTruck = false;

    if(dumpTruck == false){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            dumpTruckUp();
            dumpTruck = true;
        }
    }
    else if(dumpTruck == true){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            dumpTruckDown();
            dumpTruck = false;
        }
    }
}
