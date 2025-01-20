#include "car.h"


Control robot();

void setup() {
  robot.init();
}

void loop() {
  robot.lineFollowing();
}
