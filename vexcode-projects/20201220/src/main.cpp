/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       miderby                                                   */
/*    Created:      Sun Dec 20 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision10             vision        10              
// LMF                  motor         11              
// LMB                  motor         12              
// RMF                  motor         20              
// RMB                  motor         19              
// LCollect             motor         15              
// RCollect             motor         17              
// FCollect             motor         18              
// BCollect             motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  float w,h,s,k,y,x,g;
  while(1)
  {
    Vision10.takeSnapshot(Vision10__SIG_1RED); 
    w = Vision10.objects[0].width; 
    h = Vision10.objects[0].height; 
    s = w * h;
    Brain.Screen.setCursor(1, 1); 
    Brain.Screen.print("%f",s); 
    k = 0.002;
    g =0.2;
    y = k*(8000 - s);
    x = g*(Vision10.objects[0].centerX - (315/2)); 
    // }
    // if(s>12000){
    //   LMF.setVelocity(k*(s-12000), percent);
    //   LMF.spin(forward);
    //   RMF.setVelocity(k*(s-12000), percent);
    //   RMF.spin(forward);
    //   LMB.setVelocity(k*(s-12000), percent); 
    //   LMB.spin(forward); 
    //   RMB.setVelocity(k*(s-12000), percent); 
    //   RMB.spin(forward);
    //   }
    // else if((s>8000&&s<12000)||s==0)
    //   {
    //   LMF.stop();
    //   LMB.stop();
    //   RMB.stop(); 
    //   RMF.stop(); 
    //   }
    // else if((s<80000))
    // {
      if(Vision10.objects[0].centerX == 0 || s == 0)
      {
        x = 0;
        y = 0;
        LMF.stop(); 
        LMB.stop(); 
        RMB.stop(); 
        RMF.stop(); 
      }
      else
      {
        LMF.setVelocity(y + x, percent);
        LMF.spin(forward);
        RMF.setVelocity(y - x, percent);
        RMF.spin(forward);
        LMB.setVelocity(y + x, percent); 
        LMB.spin(forward); 
        RMB.setVelocity(y - x, percent); 
        RMB.spin(forward);
      }
      
    // }
    // if(s>=12000)
    // {
    //   LMF.setVelocity(0.02*s+12000, percent); 
    //   LMF.spin(forward); 
    //   RMF.setVelocity(0.02*s+12000, percent); 
    //   RMF.spin(forward); 
    //   LMB.setVelocity(0.02*s+12000, percent); 
    //   LMB.spin(forward); 
    //   RMB.setVelocity(0.02*s+12000, percent); 
    //   RMB.spin(forward); 
    // }
    // else if((s>8000&&s<12000)||s==0)
    // {
      
    //   LMF.stop(); 
    //   LMB.stop(); 
    //   RMB.stop(); 
    //   RMF.stop(); 
    // }
    // else
    // {
    //   LMF.setVelocity(-0.02*s+8000, percent); 
    //   LMF.spin(forward); 
    //   RMF.setVelocity(-0.02*s+8000, percent); 
    //   RMF.spin(forward); 
    //   LMB.setVelocity(-0.02*s+8000, percent); 
    //   LMB.spin(forward); 
    //   RMB.setVelocity(-0.02*s+8000, percent); 
    //   RMB.spin(forward); 
    // }
  }
}
