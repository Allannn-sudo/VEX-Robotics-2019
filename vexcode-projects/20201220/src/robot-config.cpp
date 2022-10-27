#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision10__SIG_1RED = signature (1, 6251, 9151, 7701, -697, 561, -68, 1, 0);
signature Vision10__SIG_2BLUE = signature (2, -2619, -1651, -2135, 6281, 11325, 8803, 2.2, 0);
vision Vision10 = vision (PORT10, 50, Vision10__SIG_1RED, Vision10__SIG_2BLUE);
/*vex-vision-config:end*/
motor LMF = motor(PORT11, ratio18_1, true);
motor LMB = motor(PORT12, ratio18_1, true);
motor RMF = motor(PORT20, ratio18_1, false);
motor RMB = motor(PORT19, ratio18_1, false);
motor LCollect = motor(PORT15, ratio18_1, false);
motor RCollect = motor(PORT17, ratio18_1, false);
motor FCollect = motor(PORT18, ratio18_1, false);
motor BCollect = motor(PORT13, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}