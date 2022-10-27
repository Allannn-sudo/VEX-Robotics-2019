#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor suckLeft = motor(PORT1, ratio18_1, false);
motor suckRight = motor(PORT10, ratio18_1, true);
motor leftfront = motor(PORT12, ratio18_1, true);
motor leftbehind = motor(PORT13, ratio18_1, true);
motor rightfront = motor(PORT19, ratio18_1, false);
motor rightbehind = motor(PORT20, ratio18_1, false);
motor suckBehind = motor(PORT14, ratio6_1, false);
motor suckFront = motor(PORT18, ratio6_1, false);
/*vex-vision-config:begin*/
signature Vision__SIG_RED = signature (1, 7073, 10045, 8559, -1627, 1, -813, 2.1, 0);
signature Vision__SIG_BLUE = signature (2, -2945, -1365, -2155, 8229, 11383, 9806, 2.5, 0);
vision Vision = vision (PORT16, 50, Vision__SIG_RED, Vision__SIG_BLUE);
/*vex-vision-config:end*/
limit LimitSwitch = limit(Brain.ThreeWirePort.A);
limit LimitSwitchB = limit(Brain.ThreeWirePort.B);
line Lineleft = line(Brain.ThreeWirePort.C);
line Lineright = line(Brain.ThreeWirePort.D);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}