#include "main.h"

//Helpers

double clawOpenPos = 4095.0;
double clawClosePos = 90.0;

void openClaw(){
    while (clawPot.get_value() < clawOpenPos) {
        goalClaw = 127;
    }
}

void closeClaw(){
    while (clawPot.get_value() > clawClosePos) {
        goalClaw = -127;
    }
}

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

bool dumpTruckBoolean = false; // Down = false, Up = true
bool notch = false; // Down = false, up = true
bool claw = false; //Open = false, Closed = true

//Toggles
void notchToggle(){


    if(notch == false){
        while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
            pros::delay(1);
        }
        goalNotch.set_value(false);
        notch = true;
    }
    else if(notch == true){
        while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
            pros::delay(1);
        }
        goalNotch.set_value(true);
        notch = false;
    }
}

/*void clawToggle(){

    if(claw == false){
        while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            pros::delay(1);
        }
        closeClaw();
        claw = true;

    }
    else {
        while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            pros::delay(1);
        }
        openClaw();
        claw = false;
    }
}
*/
/*void dumpTruckToggle(){

    if(dumpTruckBoolean == false){
        while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            pros::delay(1);
        }
        dumpTruckUp();
        dumpTruck = true;
    }

    else {
        while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            pros::delay(1);
        }
        dumpTruckDown();
        dumpTruck = false;

    }
}
*/

void setClawMotors(){

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        holdToOpenClaw(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        holdToCloseClaw(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
        holdToRaiseDumpTruck(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        holdToLowerDumpTruck(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        notchToggle();
    }
    else{

        dumpTruck = 0;
        goalClaw = 0;
        /*if (claw == false)
            goalClaw = 0;
        else
            goalClaw = -30;
        */
    }

}