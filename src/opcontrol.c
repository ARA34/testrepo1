/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "claw.h"
#include "homeshoulder.h"
#include "chassis.h"
//hello this is just a comment... / notes for me

/*-------------------------------PORTS------------------------------------------

SHOULDER = 4

*/


/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

 void holdShoulderAt(int td) { //target degree
   int kp = 1;
   int maxd = 127;
   Encoder shoulderEncoder;
   shoulderEncoder = encoderInit(QUAD_TOP_PORT, QUAD_BOTTOM_PORT, true);
     int error = td - encoderGet(shoulderEncoder);
     int output = kp * error;
     if(abs(error)  < maxd) {
       liftSet(output);
     } else {
       liftSet(output/ abs(output)*maxd);
     }
   }

void operatorControl() {
  int power, turn;
  printf("before the while loop in opcontrol \n");
  while(1) {
    printf("hello main loop print \n");
    holdShoulderAt(50);
  		power = joystickGetAnalog(1,0); //vertical axis on right joystick
  		turn = joystickGetAnalog(1,2); //horizontal axis on right

      //printf("the pot value %d \n", pot);
      //chassisSet(power - turn, power + turn);
  		//motorSet(1, power - turn);// right wheels
  		//motorSet(10,power + turn); // left wheels
      //clawSet(joystickGetAnalog(1, 4));

      if (joystickGetDigital(1,6, JOY_UP)) {
        liftSet(127);
        //printf("1 \n");
      }
      else if (joystickGetDigital(1,6, JOY_DOWN)) {
        liftSet(-127);
        //printf("2 \n");
      }
      else {//if not moving then dont move
        liftSet(0);
        //printf("3 \n");
      }
      if(joystickGetDigital(1,8, JOY_RIGHT )) {
        printf("calling holdShoulderAt \n");
        holdShoulderAt(50);
      }
      if (joystickGetDigital(1, 8,JOY_UP)) {
        printf("Calling homeshoulder its commented out rn tho \n");
      //commenting out for now  homeShoulder(50);
      }

  		delay(200);

  }
}
