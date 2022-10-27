using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern signature Vision10__SIG_1RED;
extern signature Vision10__SIG_2BLUE;
extern signature Vision10__SIG_3;
extern signature Vision10__SIG_4;
extern signature Vision10__SIG_5;
extern signature Vision10__SIG_6;
extern signature Vision10__SIG_7;
extern vision Vision10;
extern motor LMF;
extern motor LMB;
extern motor RMF;
extern motor RMB;
extern motor LCollect;
extern motor RCollect;
extern motor FCollect;
extern motor BCollect;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );