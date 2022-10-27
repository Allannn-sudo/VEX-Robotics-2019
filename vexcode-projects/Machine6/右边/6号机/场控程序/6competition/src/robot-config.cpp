#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftfront = motor(PORT11, ratio18_1, true);
controller Controller1 = controller(primary);
motor rightfront = motor(PORT20, ratio18_1, false);
motor leftbehind = motor(PORT12, ratio18_1, false);
motor rightbehind = motor(PORT14, ratio18_1, true);
motor put = motor(PORT19, ratio36_1, true);
motor arm = motor(PORT10, ratio36_1, false);
motor leftsuck = motor(PORT2, ratio36_1, false);
motor rightsuck = motor(PORT3, ratio36_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}