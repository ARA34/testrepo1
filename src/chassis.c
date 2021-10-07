#include "main.h"    // includes API.h and other headers
#include "chassis.h"

void chassisSet(int left, int right) {
  motorSet(1, right);
  motorSet(10, left);
}

void liftSet(int speed) {
  motorSet(4, speed);
}
