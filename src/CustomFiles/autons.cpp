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

void goForwardSlow(int distance){

  frontLeft.tare_position();

  while(frontLeft.get_position() < distance){
    frontLeft = 76;
    backLeft = 76;
    frontRight = 76;
    backRight = 76;
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

void goBackwardSlow(int distance){

  frontLeft.tare_position();

  while(abs(frontLeft.get_position()) < distance){
    frontLeft = -76;
    backLeft = -76;
    frontRight = -76;
    backRight = -76;
  }
  frontLeft = 0;
  backLeft = 0;
  frontRight = 0;
  backRight = 0;
}

void turnRight(int degrees){

  inertial.tare_rotation();

  float kP = 0.3;
  float kD = 0.0;
  float prevError = 0.0;

  while(inertial.get_rotation() < degrees){

    double error = degrees - inertial.get_rotation();
    double derivative = error - prevError;
    prevError = error;

    int power = error*kP + derivative*kD;

    frontLeft = power;
    frontRight = -power;
    backLeft = power;
    backRight = -power;

  }

  frontLeft = 0;
  frontRight = 0;
  backLeft = 0;
  backRight = 0;

}

void turnLeft(int degrees){

  inertial.tare_rotation();

  float kP = 0.3;
  float kD = 0.0;
  float prevError = 0.0;

  while(fabs(inertial.get_rotation()) < degrees){

    double error = degrees - inertial.get_rotation();
    double derivative = error - prevError;
    prevError = error;

    int power = error*kP + derivative*kD;

    frontLeft = -power;
    frontRight = power;
    backLeft = -power;
    backRight = power;

  }

  frontLeft = 0;
  frontRight = 0;
  backLeft = 0;
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
  if(liftPot.get_value() < 1400){
    while(liftPot.get_value() < 1400){
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
  
  goForward(1850);

  holdToCloseClaw(127);

  pros::delay(400);

  goBackward(1650);

  openClaw();

}

void skills(){
  testerAuton();
}

void testerAuton(){
  
  chassis->setMaxVelocity(100);

  lowerDumpTruck();
  chassis->moveDistance(-1.4_ft);
  pros::delay(500);
  raiseDumpTruck();
  chassis->moveDistance(0.3_ft);
  chassis->turnAngle(-5_deg);
  chassis->moveDistance(0.7_ft);
  chassis->turnAngle(-83_deg);

  frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

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

  chassis->setMaxVelocity(100);

  chassis->turnAngle(75_deg);

  chassis->setMaxVelocity(200);

  goForwardSlow(700);

  closeClaw();

  liftForDriving();

  profileController->generatePath(
    {{0_ft, 0_ft, 0_deg}, {2_ft, 0_ft, 0_deg}}, "goal2Align");
  profileController->setTarget("goal2Align", true);
  profileController->waitUntilSettled();

  chassis->turnAngle(88_deg);

  chassis->setMaxVelocity(200);

  lowerDumpTruck();

  profileController->generatePath(
    {{0_ft, 0_ft, 0_deg}, {7_ft, 0_ft, 0_deg}}, "goal2Score");
  profileController->setTarget("goal2Score");
  profileController->waitUntilSettled();

  chassis->turnAngle(-75_deg);

  profileController->setTarget("goal2Score", true);
  profileController->waitUntilSettled();

  chassis->turnAngle(75_deg);
  
  profileController->setTarget("goal2Score");
  profileController->waitUntilSettled();

   chassis->turnAngle(-75_deg);

  profileController->setTarget("goal2Score", true);
  profileController->waitUntilSettled();

  chassis->turnAngle(75_deg);
  
  profileController->setTarget("goal2Score");
  profileController->waitUntilSettled();

}