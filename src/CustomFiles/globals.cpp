#include "main.h"

//Motors
pros::Motor frontLeft(5, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor frontRight(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor backLeft(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor backRight(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor goalClaw(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor dumpTruck(9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor liftMotor(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//Sensors & Pistons
pros::ADIDigitalOut goalNotch('A');
pros::ADIDigitalOut leftWing('B');
pros::ADIDigitalOut rightWing('C');
pros::ADIAnalogIn clawPot ('D');
pros::ADIAnalogIn dumpTruckPot ('E');

//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
