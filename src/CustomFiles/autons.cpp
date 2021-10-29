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
      100.0, // Maximum linear velocity of the Chassis in m/s
      100.0, // Maximum linear acceleration of the Chassis in m/s^2
      100.0 // Maximum linear jerk of the Chassis in m/s^3
    })
    .withOutput(chassis)
    .buildMotionProfileController();

void goForward(int distance){

  frontLeft.tare_position();

  while(frontLeft.get_position() < distance){
    frontLeft = 127;
    backLeft = 127;
    frontRight = 127;
    backRight = 127;
  }
  frontLeft = 0;
  backLeft = 0;
  frontRight = 0;
  backRight = 0;
}

void goBackward(int distance){

  frontLeft.tare_position();

  while(abs(frontLeft.get_position()) < distance){
    frontLeft = -127;
    backLeft = -127;
    frontRight = -127;
    backRight = -127;
  }
  frontLeft = 0;
  backLeft = 0;
  frontRight = 0;
  backRight = 0;
}

void midGoalAuton(){
  
  chassis->setState({0_ft,0_ft});

  frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  profileController->generatePath(
      {{0_ft, 3.3_ft, 0_deg}, {3.7_ft, 0_ft, 310_deg}}, "midGoal");
    profileController->setTarget("midGoal");
    profileController->waitUntilSettled();

  holdToCloseClaw(127);

  pros::delay(500);

  profileController->generatePath(  
      {{0_ft, 0_ft, 0_deg}, {4_ft, 0_ft, 0_deg}}, "BACK");
  profileController->setTarget("BACK", true);
  profileController->waitUntilSettled();

  holdToOpenClaw(127);

  pros::delay(500);

  holdToOpenClaw(0);
  
}

void lowerDumpTruck(){

  dumpTruck.tare_position();
  
  while(abs(dumpTruck.get_position()) < 3190){
    dumpTruck = -127;
  }

  dumpTruck = 0;
}

void raiseDumpTruck(){

  dumpTruck.tare_position();
  
  while(abs(dumpTruck.get_position()) < 3190){
    dumpTruck = 127;
  }

  dumpTruck = 0;
}

void liftForPlatform(){
  if(liftPot.get_value() < 2930){
    while(liftPot.get_value() < 2930){
      leftLift = -127;
      rightLift = -127;
    }
  }
  else{
    while(liftPot.get_value() > 2930){
      leftLift = 127;
      rightLift = 127;
    }
  }
  leftLift = 0;
  rightLift = 0;
}

void liftForDriving(){
  if(liftPot.get_value() < 1350){
    while(liftPot.get_value() < 1350){
      leftLift = -127;
      rightLift = -127;
    }
  }
  else{
    while(liftPot.get_value() > 1350){
      leftLift = 127;
      rightLift = 127;
    }
  }
  leftLift = 0;
  rightLift = 0;
}

void closeClaw(){
  holdToCloseClaw(127);
  pros::delay(500);
}

void openClaw(){
  holdToOpenClaw(127);
  pros::delay(500);
  holdToCloseClaw(0);
}

void rightGoalAuton(){
  
  chassis->setState({0_ft,0_ft});

  frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {3.8_ft, 0_ft, 0_deg}}, "rightGoal");
    profileController->setTarget("rightGoal");
    profileController->waitUntilSettled();

  holdToCloseClaw(127);

  pros::delay(500);

  profileController->generatePath(  
      {{0_ft, 0_ft, 0_deg}, {4_ft, 0_ft, 0_deg}}, "BACK");
  profileController->setTarget("BACK", true);
  profileController->waitUntilSettled();

  holdToOpenClaw(127);

  pros::delay(500);

  holdToOpenClaw(0);

}

void leftGoalAuton(){
  
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  chassis->setMaxVelocity(180);

  profileController->generatePath(
    {{0_ft, 0_ft, 0_deg}, {4.2_ft, 0.8_ft, 0_deg}}, "goal2Mid");
    profileController->setTarget("goal2Mid");
    profileController->waitUntilSettled();
  holdToCloseClaw(127);

  pros::delay(500);

  profileController->generatePath(
  {{0_ft, 1_ft, 0_deg}, {4.2_ft, 0_ft, 0_deg}}, "BACK");
  profileController->setTarget("BACK", true);
  profileController->waitUntilSettled();
}

void skills(){
  testerAuton();
}

void testerAuton(){

  chassis->setMaxVelocity(160);

  lowerDumpTruck();
  goBackward(500);
  pros::delay(500);
  raiseDumpTruck();
  goForward(100);
  chassis->turnAngle(-5_deg);
  goForward(300);
  chassis->turnAngle(-85_deg);
  goBackward(350);

  chassis->setMaxVelocity(200);

  profileController->generatePath(
    {{0_ft, 0_ft, 0_deg}, {4.4_ft, 1_ft, 0_deg}}, "goal1Skills");
  profileController->setTarget("goal1Skills");
  profileController->waitUntilSettled();
  closeClaw();

  profileController->generatePath(
    {{0_ft, 0_ft, 0_deg}, {6_ft, 0_ft, 0_deg}}, "goal1Dropoff");
  profileController->setTarget("goal1Dropoff");
  profileController->waitUntilSettled();

  openClaw();
  
  profileController->generatePath(
    {{0_ft, 0_ft, 0_deg}, {1_ft, 0_ft, 0_deg}}, "goal2Back");
  profileController->setTarget("goal2Back", true);
  profileController->waitUntilSettled();

  chassis->setState({0_ft,0_ft});

  chassis->turnAngle(90_deg);

  goForward(400);

  closeClaw();

}