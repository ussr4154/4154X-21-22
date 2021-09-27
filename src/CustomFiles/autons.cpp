#include "main.h"

std::shared_ptr<OdomChassisController> chassis =
  ChassisControllerBuilder()
    .withMotors({5,4},{7,6})
    .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 16.5_in}, imev5GreenTPR})
    .withOdometry()
    .buildOdometry();

std::shared_ptr<AsyncMotionProfileController> profileController = 
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      3.0, // Maximum linear velocity of the Chassis in m/s
      2.0, // Maximum linear acceleration of the Chassis in m/s^2
      4.0 // Maximum linear jerk of the Chassis in m/s^3
    })
    .withOutput(chassis)
    .buildMotionProfileController();

void 