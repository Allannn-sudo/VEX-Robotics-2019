using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor leftfront;
extern controller Controller1;
extern motor rightfront;
extern motor leftbehind;
extern motor rightbehind;
extern motor put;
extern motor arm;
extern motor leftsuck;
extern motor rightsuck;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );