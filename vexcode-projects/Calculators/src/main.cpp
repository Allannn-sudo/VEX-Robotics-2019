/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       miderby                                                   */
/*    Created:      Sun Jan 10 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  float x,y;
  int a = 0,b1=0,a1 = 0,c=0;
  while(1)
  {
    x = Brain.Screen.xPosition(); 
    y = Brain.Screen.yPosition(); 
    Brain.Screen.setFillColor(transparent); 
    Brain.Screen.setCursor(1, 37); 
    Brain.Screen.print("x = %f",x); 
    Brain.Screen.setCursor(500, 37); 
    Brain.Screen.print("y = %f",y); 
    Brain.Screen.drawRectangle(10, 50, 50, 50); 
    Brain.Screen.drawRectangle(10, 105, 50, 50); 
    Brain.Screen.drawRectangle(10, 160, 50, 50); 
    Brain.Screen.drawRectangle(65, 50, 50, 50);
    Brain.Screen.drawRectangle(65, 105, 50, 50);
    Brain.Screen.drawRectangle(65, 160, 50, 50); 
    Brain.Screen.drawRectangle(120, 50, 50, 50); 
    Brain.Screen.drawRectangle(120, 105, 50, 50); 
    Brain.Screen.drawRectangle(120, 160, 50, 50); 
    Brain.Screen.drawRectangle(175, 50, 50, 50); 
    Brain.Screen.drawRectangle(175, 105, 50, 50); 
    Brain.Screen.drawRectangle(175, 160, 50, 50); 
    Brain.Screen.drawRectangle(230, 50, 50, 50); 
    Brain.Screen.drawRectangle(230, 105, 50, 50); 
    Brain.Screen.drawRectangle(230, 160, 50, 50); 
    Brain.Screen.drawRectangle(285, 50, 50, 50); 
    Brain.Screen.drawRectangle(285, 105, 50, 50); 
    Brain.Screen.drawRectangle(285, 160, 50, 50); 
    Brain.Screen.drawCircle(408, 125, 70);
    Brain.Screen.setCursor(4, 20);
    Brain.Screen.print("+"); 
    Brain.Screen.setCursor(7, 20);
    Brain.Screen.print("-"); 
    Brain.Screen.setCursor(4, 3);
    Brain.Screen.print("1"); 
    Brain.Screen.setCursor(4, 9);
    Brain.Screen.print("2"); 
    Brain.Screen.setCursor(4, 15);
    Brain.Screen.print("3"); 
    Brain.Screen.setCursor(7, 3);
    Brain.Screen.print("4"); 
    Brain.Screen.setCursor(7, 9);
    Brain.Screen.print("5"); 
    Brain.Screen.setCursor(7, 15);
    Brain.Screen.print("6"); 
    Brain.Screen.setCursor(10, 3);
    Brain.Screen.print("7"); 
    Brain.Screen.setCursor(10, 9);
    Brain.Screen.print("8"); 
    Brain.Screen.setCursor(10, 15);
    Brain.Screen.print("9"); 
    Brain.Screen.setCursor(10, 20);
    Brain.Screen.print("0"); 
    if((x > 175 && x < 225) && (y>175&&y<225))
    {
      Brain.Screen.setCursor(1, 1); 
      Brain.Screen.print("0"); 
    }
    if((x > 10 && x < 60) && (y>50&&y<100))
    {
      Brain.Screen.setCursor(1, 1); 
      Brain.Screen.print("1"); 
    }
    if((x > 65 && x < 115) && (y>50&&y<100))
    {
      Brain.Screen.setCursor(1, 1); 
      Brain.Screen.print("2"); 
    }
    if((x > 120 && x < 170) && (y>50&&y<100))
    {
      Brain.Screen.setCursor(1, 1); 
      Brain.Screen.print("3"); 
    }
    if((x > 10 && x < 60) && (y>105&&y<165))
    {
      Brain.Screen.setCursor(1, 1); 
      Brain.Screen.print("4"); 
    }
    if((x > 65 && x < 115) && (y>105&&y<165))
    {
      Brain.Screen.setCursor(1, 1); 
      Brain.Screen.print("5"); 
    }
    if((x > 120 && x < 170) && (y>105&&y<165))
    {
      Brain.Screen.setCursor(1, 1); 
      Brain.Screen.print("6"); 
    }
    if((x > 10 && x < 60) && (y>175&&y<225))
    {
      Brain.Screen.setCursor(1, 1); 
      Brain.Screen.print("7"); 
    }
    if((x > 65 && x < 115) && (y>175&&y<225))
    {
      Brain.Screen.setCursor(1, 1); 
      Brain.Screen.print("8"); 
    }
    if((x > 120 && x < 170) && (y>175&&y<225))
    {
      Brain.Screen.setCursor(1, 1); 
      Brain.Screen.print("9"); 
    }
    //////////////////////////////////
    Brain.Screen.setCursor(1, 8); 
    Brain.Screen.print("%d+%d=%d",a1,b1,a1+b1); 
    /////////////////////////////////
      if((x > 175 && x < 225) && (y>50&&y<100))
    {
      if( Brain.Screen.pressing() )
      a = a + 1;
      a1 = a;
      wait(0.5,seconds);
      Brain.Screen.clearLine(); 
    }
    else
    {
      if((x> 175&&x<225)&&(y>105&&y<165))
      {
        if(Brain.Screen.pressing())
        {
          a = a - 1;
          a1 = a;
          wait(0.5,seconds);
          Brain.Screen.clearLine(); 
        }
      }
      else
      {
        a1 = a;
      }
    }
  }
}
  
