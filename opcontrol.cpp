#include "main.h"

Motor left_back   (11);
Motor left_front  (9);
Motor right_back  (20 , true);
Motor right_front (12 , true);
Motor claw        (15);
Motor intake      (10);
Motor launcher1   (13);
Motor launcher2   (14 , true);
int launcher_ticks = 900;
bool reverse_drive = false;
bool santa_displayed = false;

Controller master (CONTROLLER_MASTER);

void driver_fire_launcher()
{
  launcher1.move_relative(launcher_ticks , 100);
  launcher2.move_relative(launcher_ticks , 100);
}

void opcontrol()
{
  while (true)
  {
    if (!santa_displayed)
    {
      santa_displayed = true;
      LV_IMG_DECLARE(santa);
      lv_obj_t * img_src = lv_img_create(lv_scr_act(), NULL);
      lv_img_set_src(img_src, &santa);
      lv_obj_set_pos(img_src, 10, 10);
      lv_obj_set_drag(img_src, true);
    }

    // MOTOR CONTROL
    left_back.move(!reverse_drive ? master.get_analog(ANALOG_LEFT_Y) : -master.get_analog(ANALOG_RIGHT_Y));
    left_front.move(!reverse_drive ? master.get_analog(ANALOG_LEFT_Y) : -master.get_analog(ANALOG_RIGHT_Y));
    right_back.move(!reverse_drive ? master.get_analog(ANALOG_RIGHT_Y) : -master.get_analog(ANALOG_LEFT_Y));
    right_front.move(!reverse_drive ? master.get_analog(ANALOG_RIGHT_Y) : -master.get_analog(ANALOG_LEFT_Y));

    // CLAW CONTROL
    if (master.get_digital(DIGITAL_L1) || master.get_digital(DIGITAL_R1))
      claw.move(127);
    else if (master.get_digital(DIGITAL_L2) || master.get_digital(DIGITAL_R2))
      claw.move(-80);
    else
      claw.move_velocity(0);

    // INTAKE TOGGLE
    if (master.get_digital_new_press(DIGITAL_X))
      intake.move(100);
    else if (master.get_digital_new_press(DIGITAL_B))
      intake.move(-100);
    else if (master.get_digital_new_press(DIGITAL_Y))
      intake.move(0);

    // FIRE LAUNCHER
    if (master.get_digital_new_press(DIGITAL_A))
      driver_fire_launcher();

    // REVERSE DRIVE
    if (master.get_digital_new_press(DIGITAL_UP))
      reverse_drive = !reverse_drive;

    // AUTONOMOUS TEST BUTTON
    if (master.get_digital_new_press(DIGITAL_LEFT))
    {
      santa_displayed = false;
      competition_initialize();
      autonomous();
    }

    // BRAKES
    if (master.get_digital_new_press(DIGITAL_DOWN))
    {
      if (left_back.get_brake_mode() == MOTOR_BRAKE_BRAKE)
      {
        set_brake_hold();
        lcd::set_text(3 , "BRAKE HOLD");
      }
      else
      {
        set_brake_brake();
        lcd::set_text(3 , "NORMAL BRAKE");
      }
    }

    // EVERY WHILE LOOP NEEDS TO HAVE AT LEAST 2 MS DELAY OR IT BREAKS
    delay(5);
  }

}
