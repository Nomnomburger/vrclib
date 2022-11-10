#include "../../include/main.h"
#include "globals.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

/* 4 Motor Drivetrain Definitions */
pros::Motor left_front(1, 1);
pros::Motor right_front(2);
pros::Motor left_back(3, 1);
pros::Motor right_back(4);
// 6 Motor Drivetrain Additional Definitions (Middle Wheel)
pros::Motor left_mid(5);
pros::Motor right_mid(6, 1);

/* Subsystem Definitions */
pros::Motor lift(10);
pros::Motor indexer(11, 1);
pros::Motor intake(12);
pros::Motor shooter(13);

/* Pneumatics Definitions */
pros::ADIDigitalOut piston_1(1);
pros::ADIDigitalOut piston_2(2);

/* Sensor Definitions */
pros::Imu inertial(20);
pros::ADIDigitalIn limit_switch({19, 1}); //using ADI port expander, v5 brain port 19, adi port 1
// Tracking Wheel Definitions (3 Wire Quad Encoder)
pros::ADIEncoder lEncoder(3, 4, 1);
pros::ADIEncoder rEncoder(5, 6);
pros::ADIEncoder mEncoder(7, 8);


/* Auton Selection */
int autonSelection = SKILLS;