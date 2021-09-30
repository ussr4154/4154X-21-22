#include "main.h"

//Helpers

int clawOpenPos;
int clawClosePos;

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
        
void printClawPosition(){
    while(true){
        std::cout << "Claw Pot Reading:" << clawPot.get_value();
        pros::delay(20);
    }
}


void dumpTruckUp(){}

void dumpTruckDown(){}

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

void clawToggle(){

    if(claw == false){
        while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
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

void dumpTruckToggle(){

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

void setClawMotors(){

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        clawToggle();
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
        holdToOpenClaw(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        holdToCloseClaw(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        dumpTruckToggle();
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        notchToggle();
    }
    else{
        dumpTruck = 0;
        goalClaw = 0;
    }

}