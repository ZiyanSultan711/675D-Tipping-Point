#include "main.h"

pros::Motor lift_l(13, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor lift_r(14, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor conveyor(4, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut tilter_l('C', false);
pros::ADIDigitalOut tilter_r('D', false);
pros::ADIDigitalOut tilter_clamp('E', false);
pros::ADIDigitalOut piston_clamp('F', false);

pros::ADIDigitalIn limit_page_up ('G');
pros::ADIDigitalIn limit_page_down ('H');
