using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor behindsuck;
extern controller Controller1;
extern motor leftsuck;
extern motor rightfront;
extern motor rightbehind;
extern motor rightsuck;
extern motor frontsuck;
extern motor leftfront;
extern motor leftbehind;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );