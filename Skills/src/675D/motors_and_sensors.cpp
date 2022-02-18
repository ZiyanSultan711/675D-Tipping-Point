#include "main.h"

pros::Motor lift(13, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
pros::Motor conveyor(4, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut tilter_l('E', true);
pros::ADIDigitalOut tilter_r('F', true);
pros::ADIDigitalOut tilter_clamp('G', false);
pros::ADIDigitalOut piston_clamp('H', true);

pros::ADIDigitalIn limit_page_up ('D');

pros::ADIDigitalOut blocker('C', false);
