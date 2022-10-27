#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor behindsuck = motor(PORT15, ratio18_1, false);
controller Controller1 = controller(primary);
motor leftsuck = motor(PORT1, ratio18_1, false);
motor rightfront = motor(PORT19, ratio18_1, false);
motor rightbehind = motor(PORT21, ratio18_1, false);
motor rightsuck = motor(PORT16, ratio18_1, true);
motor frontsuck = motor(PORT13, ratio18_1, false);
motor leftfront = motor(PORT9, ratio18_1, true);
motor leftbehind = motor(PORT14, ratio18_1, true);

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