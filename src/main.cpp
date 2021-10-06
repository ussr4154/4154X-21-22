#include "main.h"
#include "autoSelect/selection.h"

void initialize(){
    clawPot.calibrate();
    dumpTruckPot.calibrate();
    if (pros::competition::is_connected()){
      selector::init();
    }
    else {
      pros::lcd::initialize();
    }
}

void disabled() {}

void autonomous() {}

void opcontrol() {

liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
goalClaw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
dumpTruck.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  while(true){
  setLiftMotor();
  setDriveMotors();
  setClawMotors();
  if (pros::lcd::is_initialized())
    pros::lcd::print(0, "Claw Potentiometer: %i",clawPot.get_value());

  pros::delay(10);
}
}
