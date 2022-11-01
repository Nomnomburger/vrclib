#include "../../include/main.h"
#include "globals.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(6, 1);
pros::Motor right_front(16);
pros::Motor left_back(4, 1);
pros::Motor right_back(13);
pros::Motor left_mid(5);
pros::Motor right_mid(15, 1);

pros::Motor lift(2);
pros::Motor indexer(1, 1);
pros::ADIDigitalOut front_goal_grappler(2); //Actually Front
pros::ADIDigitalOut back_goal_grappler(1);

pros::Imu imu_sensor(14);

pros::ADIUltrasonic sonar(5, 6);



int autonSelection = SKILLS; // default auton selected