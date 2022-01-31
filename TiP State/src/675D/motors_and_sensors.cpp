#include "main.h"

pros::Motor lift_l(13, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor lift_r(14, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor conveyor(4, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut tilter_l('A', false);
pros::ADIDigitalOut tilter_r('B', false);
pros::ADIDigitalOut tilter_clamp('C', false);
pros::ADIDigitalOut piston_clamp('D', false);
