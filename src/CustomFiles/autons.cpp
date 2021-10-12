#include "main.h"
#include "autoSelect/selection.h"
using namespace okapi;

std::shared_ptr<OdomChassisController> chassis =
  ChassisControllerBuilder()
    .withMotors({9,4},{2,1})
    .withDimensions({AbstractMotor::gearset::green, (36.0 / 60.0)}, {{3.25_in, 16.5_in}, imev5GreenTPR})
    .withOdometry()
    .buildOdometry();

std::shared_ptr<AsyncMotionProfileController> profileController = 
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      5.0, // Maximum linear velocity of the Chassis in m/s
      0.5, // Maximum linear acceleration of the Chassis in m/s^2
      4.0 // Maximum linear jerk of the Chassis in m/s^3
    })
    .withOutput(chassis)
    .buildMotionProfileController();

void midGoalAuton(){
  
  chassis->setState({0_ft,0_ft});

  frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {4.5_ft, 1_ft, 358_deg}}, "goal2Mid");
    profileController->setTarget("goal2Mid");
    profileController->waitUntilSettled();

  holdToCloseClaw(127);

  pros::delay(500);

  profileController->generatePath(  
      {{0_ft, 2_ft, 0_deg}, {3_ft, 0_ft, 0_deg}}, "BACK");
  profileController->setTarget("BACK", true);
  profileController->waitUntilSettled();
  
}
