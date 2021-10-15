#include "main.h"

//Motors
pros::Motor frontLeft(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor frontRight(9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor backLeft(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor backRight(4, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor goalClaw(7, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor dumpTruck(8, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor liftMotor(5, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);

//Sensors & Pistons
pros::ADIDigitalOut goalNotch('D');
pros::ADIDigitalOut leftWing('B');
pros::ADIDigitalOut rightWing('C');
pros::ADIAnalogIn clawPot ('A');
pros::ADIAnalogIn dumpTruckPot ('E');

//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
