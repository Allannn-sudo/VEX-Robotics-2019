/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftfront            motor         11              
// Controller1          controller                    
// rightfront           motor         20              
// leftbehind           motor         12              
// rightbehind          motor         14              
// put                  motor         19              
// arm                  motor         10              
// leftsuck             motor         2               
// rightsuck            motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;


competition Competition;



/***********    以下为手动函数        *************/
int ZS=0;
int YS=0;
short js1=0;
short js2=0;
short XQ = 1;
short FX = 1;
int on_off=0;
//电流控制
void Current()
{
  Brain.Screen.setCursor(6, 25); 
  Brain.Screen.print("Time=%f",Brain.Timer.value());
  if(on_off==0)
  {Brain.resetTimer();}
  on_off=0;    
  if((put.current()>2||arm.current()>2||leftsuck.current()>2||rightsuck.current()>2
    ||leftfront.current()>2||leftbehind.current()>2||rightfront.current()>2||rightbehind.current()>2))
  {
    on_off=1;
    if(Brain.Timer.value()>=3)
    {
      leftfront.setStopping(coast);
      leftfront.stop();
      leftbehind.setStopping(coast);
      leftbehind.stop();
      rightfront.setStopping(coast);
      rightfront.stop();
      rightfront.setStopping(coast);
      rightbehind.stop();
      put.setStopping(coast);
      put.stop();
      leftsuck.setStopping(coast);
      leftsuck.stop();
      rightsuck.setStopping(coast);
      rightsuck.stop();
      arm.setStopping(coast);
      arm.stop();  
      Controller1.Screen.print("Current OVER");
      wait(5, seconds); 
      Controller1.Screen.clearLine(); 
    }    
  }
}
//温度控制
void Temperature()
{
  if(put.temperature(percent)>50)
  {
    put.setStopping(coast);
    put.stop();
    Controller1.Screen.print("!!put OVER!!");
  }     
  if(arm.temperature(percent)>50)
  {
    arm.setStopping(coast);
    arm.stop();
    Controller1.Screen.print("!!arm OVER!!");
  } 
  if(leftsuck.temperature(percent)>50||rightsuck.temperature(percent)>50) 
  {
    leftsuck.setStopping(coast);
    leftsuck.stop();
    rightsuck.setStopping(coast);
    rightsuck.stop();
    Controller1.Screen.print("!!suck OVER!!");
  }
  if(leftfront.temperature(percent)>50||leftbehind.temperature(percent)>50
    ||rightfront.temperature(percent)>50||rightbehind.temperature(percent)>50) 
  {
    leftfront.setStopping(coast);
    leftfront.stop();
    leftbehind.setStopping(coast);
    leftbehind.stop();
    rightfront.setStopping(coast);
    rightfront.stop();
    rightfront.setStopping(coast);
    rightbehind.stop();
    Controller1.Screen.print("!!underpan OVER!!");
  }    
}
//驱动底盘开启函数
void ZYMotor(int ZSpeed,int YSpeed)
{
  if(ZSpeed>=0)
  {
    leftfront.setVelocity(ZSpeed, percent); 
    leftfront.spin(forward); 
    leftbehind.setVelocity(ZSpeed, percent); 
    leftbehind.spin(forward);          
  }
  else if(ZSpeed<0)
  {
    leftfront.setVelocity(abs(ZSpeed),percent);
    leftfront.spin(reverse);
    leftbehind.setVelocity(abs(ZSpeed),percent);
    leftbehind.spin(reverse);    
  }

  if(YSpeed>=0)
  {
    rightfront.setVelocity(YSpeed, percent); 
    rightfront.spin(forward); 
    rightbehind.setVelocity(YSpeed, percent); 
    rightbehind.spin(forward);              
  }
  else if(YSpeed<0)
  {
    rightfront.setVelocity(abs(YSpeed), percent); 
    rightfront.spin(reverse); 
    rightbehind.setVelocity(abs(YSpeed), percent); 
    rightbehind.spin(reverse);             
  }

}
//驱动单杆遥控函数
void Single(short c =3,short r = 1)
{  
  float LMD = 0;// Lingmingdu
	float XL = 3; //XieLv
  js1=Controller1.Axis1.position();    
  js2=Controller1.Axis2.position(); 
	if(abs(js1)<80)
		{LMD = 0.6;}
	else
		{LMD = 1.2;} 
	if(!js1) js1 = 1; // prevent divide "0"
	if(abs(js1) <= c && abs(js2) <= c)
	{
		ZS=YS=0;
	}
	else
	{
		if((float)abs(js2)/abs(js1)<=XL) //arcadeControl
		{
			ZS = (js2 * r + js1 * LMD) / 2;
			YS = (js2 * r - js1 * LMD) / 2;
		}
		else // full-speed ahead
		{
			ZS = js2 * r;
			YS = js2 * r;
		}
	}
	ZYMotor(ZS,YS);
}    
//收集方块函数 
void Collect()
{
  if(leftsuck.temperature(percent)>50||rightsuck.temperature(percent)>50)
  {
    leftsuck.setStopping(coast);
    leftsuck.stop();
    rightsuck.setStopping(coast);
    rightsuck.stop();   
  }
  else
  {
    if(Controller1.Axis3.position()>10||Controller1.Axis3.position()<-10)
    {
      leftsuck.setVelocity(Controller1.Axis3.position(), percent); 
      leftsuck.spin(forward); 
      rightsuck.setVelocity(Controller1.Axis3.position(), percent); 
      rightsuck.spin(forward);            
    }     
    else
    {        
      leftsuck.setStopping(hold);
      leftsuck.stop();
      rightsuck.setStopping(hold);
      rightsuck.stop();
    }
  }

}
//放方块
void Catch()
{
  if(put.temperature(percent)>50)
  {
    put.setStopping(hold);
    put.stop();         
  }
  else
  {
    if(Controller1.ButtonL1.pressing()&&put.position(degrees)>-740)
    {
      put.setVelocity(-50, percent); 
      put.spin(forward);
      if(put.position(degrees)<-400)
      {
        put.setVelocity(-20, percent); 
        put.spin(forward);
      }
    }
    else if(Controller1.ButtonL2.pressing()&&put.position(degrees)<0)
    {
      put.setVelocity(80, percent); 
      put.spin(forward);
    }
    else
    {
      put.setStopping(hold);
      put.stop();
    }
  }  
}
//手臂
void Lift()
{
  if(arm.temperature(percent)>50)
  {
    arm.setStopping(coast);
    arm.stop();
  }
  else
  {
    if(Controller1.ButtonUp.pressing()&&arm.position(degrees)<600)
    {
      if(put.position(degrees)>-200)
      {
        put.setVelocity(-50,percent);
        put.spin(forward);
      }
      else
      {
        put.setStopping(hold);
        put.stop();
      }
      arm.setVelocity(100,percent);
      arm.spin(forward);
    }
    else
    {
      if(Controller1.ButtonDown.pressing()&&arm.position(degrees)>0)
      {
        arm.setVelocity(-80,percent);
        arm.spin(forward);
        if(put.position(degrees)>-200)
        {
          put.setVelocity(-50,percent);
          put.spin(forward);
        }
        else
        {
          put.setStopping(hold);
          put.stop();
        }
      }
      else
      {
        arm.setStopping(hold);
        arm.stop();
      }
    }
  }   
}
/***********    以上为手动函数        *************/



/***********    以下为自动函数        *************/
//驱动底盘停止
void stop()
{
  leftfront.setStopping(hold);
  leftfront.stop();
  leftbehind.setStopping(hold);
  leftbehind.stop();
  rightfront.setStopping(hold);
  rightfront.stop();
  rightfront.setStopping(hold);
  rightbehind.stop(); 
  wait(0.01, seconds); 
}
//驱动底盘转弯
void turn(float speed,float degree,int LR)
{
  if(LR==-1)
  {
    rightfront.setPosition(0, degrees);  
    while(rightfront.position(degrees)<degree)
    {
      ZYMotor(-speed,speed);
    }
    stop();
  }
  if(LR==1)
  {
    leftfront.setPosition(0, degrees); 
    while(leftfront.position(degrees)<degree)
    {
      ZYMotor(speed,-speed);
    }
    stop();
  }
}
//驱动底盘直行
void GO(float zspeed,float yspeed,float degree)
{
  if(yspeed+zspeed>0)
  {
    leftfront.setPosition(0, degrees);  
    while(leftfront.position(degrees)<degree)
    {
      ZYMotor(zspeed,yspeed);
    }
    stop();
  }
  if(yspeed+zspeed<0)
  {
    leftfront.setPosition(0, degrees);
    while(leftfront.position(degrees)>-degree)
    {     
      ZYMotor(zspeed,yspeed);
    }
    stop();
  }  
}
//驱动电机移动时间
void GOtime(float zspeed,float yspeed,float Time)
{
  Brain.Timer.reset(); 
  while(Brain.Timer.value()<Time)
  {
    ZYMotor(zspeed,yspeed);
  }
  stop();
}
//放方块
void Put(int speed,int degree)
{
  put.setVelocity(speed, percent);
  put.spinFor(forward, degree*(-1), degrees);  
}
//吸方块
void suck(int speed)
{
  leftsuck.setVelocity(speed, percent); 
  leftsuck.spin(forward);
  rightsuck.setVelocity(speed, percent); 
  rightsuck.spin(forward);
}
//吸方块电机停止
void suckstop()
{
  leftsuck.setStopping(hold);
  leftsuck.stop();
  rightsuck.setStopping(hold);
  rightsuck.stop();
}
/***********    以上为自动函数        *************/

//重置所有电机角度值
void pre_auton(void) {
  vexcodeInit();
  leftsuck.setPosition(0, degrees);
  rightsuck.setPosition(0, degrees);
  arm.setPosition(0, degrees);
  put.setPosition(0, degrees);
  leftfront.setPosition(0, degrees);
  leftbehind.setPosition(0, degrees);
  rightfront.setPosition(0, degrees);
  rightbehind.setPosition(0, degrees);
}


//自动程序函数名
/*
驱动底盘停止  *****  stop();                       *****无参数
驱动底盘转弯  *****  turn(speed,degree,LR);        *****三个参数  speed=速度，  degree=角度，  LR=转弯方向（-1=左转，1=右转）
驱动底盘直行  *****  GO(zspeed,yspeed,degree);     *****三个参数  zspeed=左电机速度，  yspeed=右电机速度，  degree=角度
驱动电机移动时间***  GOtime(zspeed,yspeed,Time);   *****三个参数  zspeed=左电机速度，  yspeed=右电机速度，  Time=时间
放方块       *****  Put(speed,degree);            *****两个参数  speed=速度，  degree=角度
吸方块       *****  suck(speed);                  *****一个参数  speed=速度
吸方块电机停止*****  suckstop();                   *****无参数
*/

//自动程序
void autonomous(void) {
/****************以下为根据自动函数编写15秒自动程序****************/
put.setVelocity(50, percent); 
put.spinFor(forward,-390, degrees); 
/****************以上为根据自动函数编写15秒自动程序****************/
}

//手动程序
void usercontrol(void) {
  leftfront.setStopping(coast); 
  leftbehind.setStopping(coast);
  rightfront.setStopping(coast);
  rightbehind.setStopping(coast);
  put.setStopping(hold);
  arm.setStopping(hold);
  leftsuck.setStopping(hold);
  rightsuck.setStopping(hold);

  while(1)
  {
    Brain.Screen.setCursor(1, 25); 
    Brain.Screen.print("leftsuck t=%f",leftsuck.temperature(percent));
    Brain.Screen.setCursor(2, 25);
    Brain.Screen.print("rightsuck t=%f",rightsuck.temperature(percent));
    Brain.Screen.setCursor(3, 25);
    Brain.Screen.print("rightsuck deg=%f",rightsuck.position(degrees));
    Brain.Screen.setCursor(5, 25);
    Brain.Screen.print("put t=%f",put.temperature(percent));
    Brain.Screen.setCursor(4, 25);
    Brain.Screen.print("arm t=%f",arm.temperature(percent));
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("put c=%f",put.current());
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("arm c=%f",arm.current());
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("leftsuck c=%f",leftsuck.current());
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print("rightsuck c=%f",rightsuck.current());
    Brain.Screen.setCursor(5, 1);
    Brain.Screen.print("leftfront c=%f",leftfront.current());
    Brain.Screen.setCursor(6, 1);
    Brain.Screen.print("leftbehind c=%f",leftbehind.current());
    Brain.Screen.setCursor(7, 1);
    Brain.Screen.print("rightfront c=%f",rightfront.current());
    Brain.Screen.setCursor(8, 1);
    Brain.Screen.print("rightbehind c=%f",rightbehind.current());
    Current();
    Temperature();
    Collect();
    Catch();
    Lift();
    Single(10,FX);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
