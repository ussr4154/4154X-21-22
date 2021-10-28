#include "main.h"
#include "autoSelect/selection.h"

void initialize(){
    clawPot.calibrate();
    liftPot.calibrate();
    if (pros::competition::is_connected()){
      selector::init();
    }
    else {
      pros::lcd::initialize();
    }
}

void disabled() {}

void autonomous() {
  
  leftLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rightLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  goalClaw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  dumpTruck.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

/*if (pros::competition::is_connected()){
  if(selector::auton == 1)
    midGoalAuton();
  if(selector::auton == -1)
    midGoalAuton();
  if(selector::auton == 2)
    rightGoalAuton();
  if (selector::auton == -2)
    rightGoalAuton();
  if(selector::auton == -3)
    leftGoalAuton();
  if(selector::auton == 3)
    leftGoalAuton();
  if(selector::auton == 0)
    skills();
  }
else{*/
  testerAuton();
// }
}

void opcontrol() {

leftLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
rightLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
goalClaw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
dumpTruck.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  while(true){
  setLiftMotor();
  setDriveMotors();
  setClawMotors();
  if (pros::lcd::is_initialized())
    pros::lcd::print(0, "Claw Potentiometer: %i",clawPot.get_value());
    pros::lcd::print(1, "Lift Potentiometer: %i",liftPot.get_value());

  pros::delay(10);
}
}
