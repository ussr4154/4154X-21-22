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
            goalNotch.set_value(false);
            notch = false;
        }
    }
}

void clawToggle(){

    bool claw = false;
    clawClass theClaw;

    if(claw == false){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            theClaw.close();
            claw = true;
        }
    }
    else if(claw == true){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            theClaw.close();
            claw = false;
        }
    }
}

void dumpTruckToggle(){

    bool dumpTruck = false;

    if(dumpTruck == false){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
          while (dumpTruck == false){
            dumpTruckUp();
            dumpTruck = true;
          }
        }
    }
    else if(dumpTruck == true){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
          while (dumpTruck == true) {
            dumpTruckDown();
            dumpTruck = false;
          }
        }
    }
}
