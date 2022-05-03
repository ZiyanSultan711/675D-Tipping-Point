#include "main.h"

pros::Motor lift(16, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);
pros::Motor conveyor(11, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut tilter('D', false);
pros::ADIDigitalOut tilter_clamp('C', false);
pros::ADIDigitalOut piston_clamp('A', true);
pros::ADIDigitalOut piston_clamp_1('B', true);

pros::ADIDigitalIn limit_page_up ('F');

pros::ADIDigitalOut canstealer('E', false);
