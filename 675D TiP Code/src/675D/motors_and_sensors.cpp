#include "main.h"

pros::Motor lift(16, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);
pros::Motor conveyor(11, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut tilter('D', false);
pros::ADIDigitalOut tilter_clamp('C', true);
pros::ADIDigitalOut piston_clamp('A', false);
pros::ADIDigitalOut piston_clamp_1('B', false);

pros::ADIDigitalIn limit_page_up ('F');

pros::ADIDigitalOut canstealer('E', false);
