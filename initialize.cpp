#include "main.h"

// #1 Blue Left Side , #2 Blue Right Side , #3 Red Left Side , #4 Red Right Side , #5 Skills
int auto_select = 0;
std::string auto_string = "NO AUTONOMOUS";

void update()
{
	if (auto_select < 0)
		auto_select = 6;
	else if (auto_select > 6)
		auto_select = 0;

	if (auto_select == 0)
		auto_string = "NO AUTONOMOUS";
	else if (auto_select == 1)
		auto_string = "BLUE LEFT SIDE";
	else if (auto_select == 2)
		auto_string = "BLUE RIGHT SIDE";
	else if (auto_select == 3)
		auto_string = "RED LEFT SIDE";
	else if (auto_select == 4)
		auto_string = "RED RIGHT SIDE";
	else if (auto_select == 5)
		auto_string = "AUTO SKILLS";
	else if (auto_select == 6)
		auto_string = "CUSTOM";

	lcd::set_text(1 , auto_string);
}

void on_left_button()
{
	auto_select -= 1;
	update();
}

void on_right_button()
{
	auto_select += 1;
	update();
}

void set_brake_brake()
{
	left_back.set_brake_mode(MOTOR_BRAKE_BRAKE);
	left_front.set_brake_mode(MOTOR_BRAKE_BRAKE);
	right_back.set_brake_mode(MOTOR_BRAKE_BRAKE);
	right_front.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void set_brake_hold()
{
	left_back.set_brake_mode(MOTOR_BRAKE_HOLD);
	left_front.set_brake_mode(MOTOR_BRAKE_HOLD);
	right_back.set_brake_mode(MOTOR_BRAKE_HOLD);
	right_front.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  set_brake_brake();
	claw.tare_position();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	competition_initialize();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
	lcd::initialize();
	lcd::set_text(1 , auto_string);
	lcd::set_text(2 , "< Select Autonomous >");
	lcd::register_btn0_cb(on_left_button);
	lcd::register_btn2_cb(on_right_button);

	// Auton selector from controller or touchscreen LCD display emulator
	while (lcd::read_buttons() != LCD_BTN_CENTER && !master.get_digital(DIGITAL_A))
		{
		if (master.get_digital_new_press(DIGITAL_LEFT))
			on_left_button();
		else if (master.get_digital_new_press(DIGITAL_RIGHT))
			on_right_button();

		delay(5);
		}

	lcd::set_text(2 , "Autonomous Selected.");
	lcd::shutdown();
}
