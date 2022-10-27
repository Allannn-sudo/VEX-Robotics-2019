/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       miderby                                                   */
/*    Created:      Sun Sep 20 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// behindsuck           motor         15              
// Controller1          controller                    
// leftsuck             motor         1               
// rightfront           motor         19              
// rightbehind          motor         21              
// rightsuck            motor         16              
// frontsuck            motor         13              
// leftfront            motor         9               
// leftbehind           motor         14              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  float x,y;
  float leftspeed,rightspeed;
  while(1)
  {
    x = Controller1.Axis1.position();
    y = Controller1.Axis2.position();
    if(fabs(x)<= 15 && fabs(y)<= 15)
    {
      leftspeed = 0;
      rightspeed = 0;
    }
    else
    {
      if(fabs(y/x) >= 3) //Gradient Tune
      {
        leftspeed = y;
        rightspeed = y;
      }
      else
      {
        leftspeed = y + x;
        rightspeed = y - x;
      }
    }
    leftfront.setVelocity(leftspeed, percent); 
    leftfront.spin(forward); 
    
    leftbehind.setVelocity(leftspeed, percent); 
    leftbehind.spin(forward); 
    
    rightfront.setVelocity(rightspeed, percent); 
    rightfront.spin(forward); 

    rightbehind.setVelocity(rightspeed, percent); 
    rightbehind.spin(forward); 
  }
}
