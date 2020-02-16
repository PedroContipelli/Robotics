#include "main.h"
#include <ctime>
int ease = 15;
int tile = 1570;
int speed = 120; // Slow / Fast?
int turn = 850;
int waitMS = 250;
int timeout = 5; // TEST THIS!!!!!!!!!!!

void wait()
{
  delay(waitMS);
}

void reset_encoders()
{
  wait();
  left_back.tare_position();
  left_front.tare_position();
  right_back.tare_position();
  right_front.tare_position();
  launcher1.tare_position();
  launcher2.tare_position();
}

void stop_all()
{
  left_back.move(0);
  left_front.move(0);
  right_back.move(0);
  right_front.move(0);
  launcher1.move(0);
  launcher2.move(0);
  intake.move(0);
  claw.move(0);
  opcontrol();
}

void auto_fire_launcher()
{
  reset_encoders();
  launcher1.move_absolute(launcher_ticks , speed);
  launcher2.move_absolute(launcher_ticks , speed);
  int start_time = time(NULL);

  while (launcher1.get_position() < launcher_ticks - ease)
  {
    if (time(NULL) - start_time > timeout)
      stop_all();

    delay(2);
  }
}

void move_forward(double pos , int speed)
{
  reset_encoders();
  left_back.move_absolute(pos , speed);
  left_front.move_absolute(pos , speed);
  right_back.move_absolute(pos , speed);
  right_front.move_absolute(pos , speed);
  int start_time = time(NULL);

  while (left_front.get_position() < pos - ease)
  {
    if (time(NULL) - start_time > timeout)
      stop_all();

    delay(2);
  }
}

void move_forward(double pos)
{
  move_forward(pos , speed);
}

void move_backward(double pos)
{
  reset_encoders();
  left_back.move_absolute(-pos , speed);
  left_front.move_absolute(-pos , speed);
  right_back.move_absolute(-pos , speed);
  right_front.move_absolute(-pos , speed);
  int start_time = time(NULL);

  while (left_back.get_position() > -pos + ease)
  {
    if (time(NULL) - start_time > timeout)
      stop_all();

    delay(2);
  }
}

void turn_left(double turn)
{
  reset_encoders();
  left_back.move_absolute(-turn , speed);
  left_front.move_absolute(-turn , speed);
  right_back.move_absolute(turn , speed);
  right_front.move_absolute(turn , speed);
  int start_time = time(NULL);

  while (left_front.get_position() > -turn + ease)
  {
    if (time(NULL) - start_time > timeout)
      stop_all();

    delay(2);
  }
}

void turn_left()
{
  turn_left(turn);
}

void turn_right(double turn)
{
  reset_encoders();
  left_back.move_absolute(turn , speed);
  left_front.move_absolute(turn , speed);
  right_back.move_absolute(-turn , speed);
  right_front.move_absolute(-turn , speed);
  int start_time = time(NULL);

  while (left_front.get_position() < turn - ease)
  {
    if (time(NULL) - start_time > timeout)
      stop_all();

    delay(2);
  }
}

void turn_right()
{
  turn_right(turn);
}

void turn_180()
{
  turn_right(2*turn);
}

void flip_cap()
{
  wait();
  claw.tare_position();
  claw.move(127);
  int start_time = time(NULL);

  while (claw.get_position() < 330 - ease)
  {
    if (time(NULL) - start_time > timeout)
      stop_all();

    delay(2);
  }

  claw.move(0);
}

void intake_on()
{
  intake.move(100);
}

void intake_off()
{
  intake.move(0);
}

void autonomous()
{
  lcd::set_text(2 , "Autonomous Running...");
  set_brake_hold();
  move_forward(5000);

  if (auto_select == 6) // CUSTOM (TESTING)
  {
    auto_fire_launcher();
    move_forward(0.12*tile);
    turn_right(turn + 20);
    intake_on();
    move_forward(1.7*tile);
    move_backward(0.2*tile);
    turn_180();
    move_backward(0.35*tile);
    flip_cap();
    intake_off();
    move_forward(1.97*tile);
    turn_right(turn + 30);
    intake_on();
    move_forward(1*tile);
    auto_fire_launcher();
    move_forward(1.1*tile);
    intake_off();
    move_backward(1*tile);
    turn_left();
    move_backward(0.7*tile);
    flip_cap();
    // move_forward(0.7*tile);
    // turn_left();
    // move_forward(2*tile);
    // turn_left();
    // move_forward(2*tile);
  }
  else if (auto_select == 1) // BLUE LEFT SIDE
  {

  }
  else if (auto_select == 2) // BLUE RIGHT SIDE
  {

  }
  else if (auto_select == 3) // RED LEFT SIDE
  {

  }
  else if (auto_select == 4) // RED RIGHT SIDE
  {

  }
  else if (auto_select == 5) // AUTO SKILLS
  {

  }

  lcd::set_text(2 , "Driver Control...");
}
