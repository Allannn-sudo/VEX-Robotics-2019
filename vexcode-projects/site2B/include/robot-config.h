using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor suckLeft;
extern motor suckRight;
extern motor leftfront;
extern motor leftbehind;
extern motor rightfront;
extern motor rightbehind;
extern motor suckBehind;
extern motor suckFront;
extern signature Vision__SIG_RED;
extern signature Vision__SIG_BLUE;
extern signature Vision__SIG_3;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;
extern limit LimitSwitch;
extern limit LimitSwitchB;
extern line Lineleft;
extern line Lineright;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );