#include "main.h"

//Helpers
class clawClass {
    private:
        int clawOpenPos;
        int clawClosePos;

    public:

        void open(){
            while (clawPot.get_value() < clawOpenPos) {
                goalClaw = 127;
            }
        }

        void close(){
            while (clawPot.get_value() > clawClosePos) {
                goalClaw = -127;
            }
        }
};

void dumpTruckUp(){}

void dumpTruckDown(){}

bool dumpTruckBoolean = false; // Down = false, Up = true
bool notch = false; // Down = false, up = true
bool claw = false; //Open = false, Closed = true

clawClass theClaw; //Creates an instance of the class "clawClass"

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
        while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            pros::delay(1);
        }
        theClaw.close();
        claw = true;

    }
    else {
        while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            pros::delay(1);
        }
        theClaw.open();
        claw = false;
    }
}

void dumpTruckToggle(){

    if(dumpTruckBoolean == false){
        while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            pros::delay(1);
        }
        dumpTruckUp();
        dumpTruck = true;
    }

    else {
        while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            pros::delay(1);
        }
        dumpTruckDown();
        dumpTruck = false;

    }
}
