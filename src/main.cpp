#include "main.h"
#include "autoSelect/selection.h"

void initialize(){
    clawPot.calibrate();
    dumpTruckPot.calibrate();
    if (pros::competition::is_connected()){
      selector::init();
    }
}

void disabled() {}

void autonomous() {}

void opcontrol() {
  while(true){
  setLiftMotor();
  setDriveMotors();
}
}
