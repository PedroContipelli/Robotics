// This file (main.h) should be in include folder

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "pros/apix.h"
using namespace pros;

// All global variables and functions declared here in header file
extern Motor left_back;
extern Motor left_front;
extern Motor right_back;
extern Motor right_front;
extern Motor claw;
extern Motor intake;
extern Motor launcher1;
extern Motor launcher2;
extern int launcher_ticks;
extern int auto_select;
extern Controller master;
extern void set_brake_hold();
extern void set_brake_brake();

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#endif  // _PROS_MAIN_H_
