/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\DEMO-VEX EDR                                     */
/*    Created:      Wed Sep 09 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// suckLeft             motor         1               
// suckRight            motor         10              
// leftfront            motor         11              
// leftbehind           motor         12              
// rightfront           motor         13              
// rightbehind          motor         14              
// suckBehind           motor         15              
// suckFront            motor         17              
// Lineleft             line          A               
// Lineright            line          B               
// Vision               vision        18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

//****************以下为遥控程序函数***********************//

int leftspeed  = 0;
int rightspeed = 0;
void Stop(int stopping,int yes)
{
  if(stopping==1)
  {
    leftfront.setStopping(brake); 
    leftbehind.setStopping(brake); 
    rightfront.setStopping(brake); 
    rightbehind.setStopping(brake); 
  }
  if(stopping==2)
  {
    leftfront.setStopping(coast); 
    leftbehind.setStopping(coast); 
    rightfront.setStopping(coast); 
    rightbehind.setStopping(coast); 
  }
  if(stopping==3)
  {
    leftfront.setStopping(hold); 
    leftbehind.setStopping(hold); 
    rightfront.setStopping(hold); 
    rightbehind.setStopping(hold); 
  }
  if(yes==1)
  {
    leftfront.stop(); 
    leftbehind.stop(); 
    rightfront.stop(); 
    rightbehind.stop(); 
  }
}
void ZYMotor(int ZSpeed,int YSpeed)
{
  leftfront.setVelocity(ZSpeed, percent); 
  leftfront.spin(forward); 
  leftbehind.setVelocity(ZSpeed, percent); 
  leftbehind.spin(forward); 
  rightfront.setVelocity(YSpeed, percent); 
  rightfront.spin(forward); 
  rightbehind.setVelocity(YSpeed, percent); 
  rightbehind.spin(forward);
}
void Controller(short c ,short reverse,float x,float y )
{  
  float sensitivity ;// 灵敏度
	float Slope ; //斜率
  if(fabs(y)<25)
  {Slope = 2;}
  else
  {Slope = 4;} 
	if(fabs(x)<55)
	{sensitivity = 1;}
	else
	{sensitivity = 0.5;} 
	if(!x) x = 1; // 防止除 "0"
	if(fabs(x) <= c && fabs(y) <= c)
	{
		leftspeed=rightspeed=0;
	}
	else
	{
		if(  (float)  fabs(y) /  fabs(x) <= Slope ) //arcadeControl
		{
			leftspeed   = (y * reverse + x * sensitivity) *0.8;
			rightspeed  = (y * reverse - x * sensitivity) *0.8;
		}
		else // full-speed ahead
		{
			leftspeed  = y * reverse;
			rightspeed = y * reverse;
		}
	}
	ZYMotor(leftspeed,rightspeed);
}
//*********************以上为遥控程序函数*************************************//

//*********************以下为自动程序函数*************************************//
//   底盘电机停止
//   Stop(int a,int b)

//机器人启动
void Spin()
{
  Brain.Timer.reset(); 
  while(Brain.Timer.value()<0.5 )
  {
    if(Brain.Timer.value()>0.3)
    {
      suckLeft.setVelocity(-40, percent); 
      suckRight.setVelocity(-40, percent); 
      suckLeft.spin(forward); 
      suckRight.spin(forward); 
    }
    ZYMotor(30,30);
    suckBehind.setVelocity(20,percent);
    suckBehind.spin(forward);
  }
  suckBehind.stop();
  Brain.Timer.reset(); 
  while(Brain.Timer.value()<1 )
  {
    suckLeft.setVelocity(50, percent); 
    suckRight.setVelocity(50, percent); 
    suckLeft.spin(forward); 
    suckRight.spin(forward); 
    ZYMotor(-30,-30);
  }
  Stop(1,1);
  suckLeft.stop(); 
  suckRight.stop();  
} 
//驱动底盘转弯
void Turn(float speed,float degree,int LR,int stopping)
{
  if(LR==-1)
  {
    rightfront.setPosition(0, degrees);  
    while(rightfront.position(degrees)<degree)
    {
      ZYMotor(-speed,speed);
    }
    Stop(stopping,1);
  }
  if(LR==1)
  {
    leftfront.setPosition(0, degrees); 
    while(leftfront.position(degrees)<degree)
    {
      ZYMotor(speed,-speed);
    }
    Stop(stopping,1);
  }
}
//驱动底盘直行
void GO(float zspeed,float yspeed,float degree,int stopping)
{
  if(yspeed+zspeed>0)
  {
    leftfront.setPosition(0, degrees);  
    while(leftfront.position(degrees)<degree)
    {
      ZYMotor(zspeed,yspeed);
    }
    Stop(stopping,1);
  }
  if(yspeed+zspeed<0)
  {
    leftfront.setPosition(0, degrees);
    while(leftfront.position(degrees)>-degree)
    {     
      ZYMotor(zspeed,yspeed);
    }
    Stop(stopping,1);
  }  
}
//驱动电机移动时间
void GOtime(float zspeed,float yspeed,float Time,int stopping)
{
  Brain.Timer.reset(); 
  while(Brain.Timer.value()<Time)
  {
    ZYMotor(zspeed,yspeed);
  }
  Stop(stopping,1);
}
//吸球电机开启
void suckspin(int frontspeed,int middlespeed,int behindspeed,int Position )
{
  int front,middle,behind;
  behind=Position%10;//*********************个位
  middle=(Position-behind)%100/10;//********十位
  front=(Position-behind-middle)/100;//*****百位
  if(front==1)//前
  {
    suckLeft.setVelocity(frontspeed, percent); 
    suckRight.setVelocity(frontspeed, percent); 
    suckLeft.spin(forward); 
    suckRight.spin(forward); 
  }
  if(middle==1)//中
  {
    suckFront.setVelocity(middlespeed, percent); 
    suckFront.spin(forward); 
  }
  if(behind==1)//后
  {
    suckBehind.setVelocity(behindspeed, percent); 
    suckBehind.spin(forward); 
  }
}
//吸球电机停止
void suckstop(int Position)
{
  int front,middle,behind;
  behind=Position%10;
  middle=(Position-behind)%100/10;
  front=(Position-behind-middle)/100;
  if(front==1)
  {
    suckLeft.setStopping(brake); 
    suckRight.setStopping(brake); 
    suckLeft.stop(); 
    suckRight.stop(); 
  }
  if(middle==1)
  {
    suckFront.setStopping(brake); 
    suckFront.stop(); 
  }
  if(behind==1)
  {
    suckBehind.setStopping(brake); 
    suckBehind.stop(); 
  }
}
//*********************以上为自动程序函数*************************************//

// *************************//
competition Competition;//**//
//**************************//
//重置所有电机角度值
void pre_auton(void) {
  
  vexcodeInit();
  leftfront.setPosition(0, degrees); 
  leftbehind.setPosition(0, degrees); 
  rightfront.setPosition(0, degrees); 
  rightbehind.setPosition(0, degrees); 
  suckFront.setPosition(0, degrees); 
  suckBehind.setPosition(0, degrees); 
  suckLeft.setPosition(0, degrees); 
  suckRight.setPosition(0, degrees); 
}
/****************************自动调用函数***************************************
//机器人启动
Spin();

//驱动底盘停止
Stop(int stopping,int yes);    
////////////////////////stopping:停止模式（1：刹车  2：滑行  3：锁死）
////////////////////////yes:是否停止（1：停止  非1数：不停）

//驱动底盘转弯
Turn(float speed,float degree,int LR,int stopping);
////////////////////////speed：驱动底盘速度参数范围：0~100
////////////////////////degree：驱动底盘转动的角度：大于0的数
////////////////////////LR：左转 -1，右转 1
////////////////////////stopping:停止模式（1：刹车  2：滑行  3：锁死）

//驱动底盘直行
GO(float zspeed,float yspeed,float degree,int stopping);
////////////////////////zspeed：左电机速度
////////////////////////yspeed：右电机速度
////////////////////////degree：转动的角度（大于0的数）
////////////////////////stopping：停止模式（1：刹车  2：滑行  3：锁死）

//驱动电机移动时间
GOtime(float zspeed,float yspeed,float Time,int stopping);
////////////////////////zspeed：左电机速度
////////////////////////yspeed：右电机速度
////////////////////////Time：转动的时间
////////////////////////stopping：停止模式（1：刹车  2：滑行  3：锁死）

//吸球电机开启
suckspin(int frontspeed,int middlespeed,int behindspeed,int Position );
////////////////////////frontspeed：吸球前电机速度
////////////////////////middlespeed：吸球中电机速度
////////////////////////behindspeed：吸球后电机速度
////////////////////////Position：吸球电机位置（百位：前吸  十位：中吸  个位：后吸）
                                  （1表示转动，0表示不动）例如：111，100，011

//吸球电机停止
suckstop(int Position);
////////////////////////Position：吸球电机位置（百位：前吸  十位：中吸  个位：后吸）
                                  （1表示转动，0表示不动）例如：111，100，011

******************************************************************************/
//********************在此处编写自动程序***************************************//
void autonomous(void) {
  suckBehind.setMaxTorque(100, percent);
  Brain.Timer.reset();
  Spin();
  GOtime(40,40,0.9,1);
  Turn(90,325,-1,1);
  GOtime(40,40,1.6,1);
  suckspin(100,100,100,111);
  wait(0.7, seconds); 
  suckstop(111);
  GOtime(-50,-50,0.6,1);
  
  suckspin(-100,-100,-100,111);
  wait(0.4, seconds);
  suckstop(111);
  
  Turn(90,480,1,1);
  GOtime(50,50,2.3,1);
  Turn(90,300,1,1);
  GOtime(50,50,1.3,1);
  suckspin(100,100,100,111);
  wait(1,seconds);
  suckstop(110);
  GOtime(50,50,0.5,1);
  Turn(90,15,1,1);
  wait(1,seconds);
  suckstop(111);
  GOtime(-50,-50,1,1);
  
  /*#斜走程序
  Turn(90,116,1,1);
  GOtime(50,50,2.2,1);
  suckspin(100,100,100,111);
  wait(1,seconds);
  suckstop(110);
  Turn(90,15,1,1);
  wait(1,seconds);
  suckstop(111);
  GOtime(-50,-50,1,1);
  */
  //Turn(100,180,-1,1);
  //GOtime(40,40,0.7,1);
}

//在此处编写遥控程序
void usercontrol(void) {
  suckBehind.setMaxTorque(100, percent); 
  Brain.Timer.reset(); 
  float s,h,w;
  float z;
  float lineleft,lineright;
  int Direction=0,team=0;
  float x,y;
  int launch,recyle;
  Stop(2,0);
  while(1)
  {
    /***********************************按键切换***********************************/
    if( Controller1.ButtonA.pressing()&&Controller1.ButtonB.pressing()  )
    {
      Direction++;
      while(Controller1.ButtonA.pressing()&&Controller1.ButtonB.pressing())
      {wait(0.02, seconds); }
    }
    if(Direction%2>0)
    {
      y=Controller1.Axis3.position() ;
      x=Controller1.Axis4.position() ;
      z=Controller1.Axis2.position() ;
      launch=Controller1.ButtonR1.pressing();//发射
      recyle=Controller1.ButtonR2.pressing();//回收
    }
    else
    {
      y=Controller1.Axis2.position() ;
      x=Controller1.Axis1.position() ;
      z=Controller1.Axis3.position() ;
      launch=Controller1.ButtonL1.pressing();//发射
      recyle=Controller1.ButtonL2.pressing();//回收
    }

    if( Controller1.ButtonLeft.pressing()&&Controller1.ButtonDown.pressing()  )
    {
      team++;
      Brain.Screen.clearScreen(); 
      while(Controller1.ButtonLeft.pressing()&&Controller1.ButtonDown.pressing())
      {wait(0.02, seconds); }
    }
    if(team%2>0)
    {
      Vision.takeSnapshot(Vision__SIG_RED);
      Brain.Screen.setFillColor(blue); 
      Brain.Screen.drawRectangle(20, 60, 400, 200); 
    }
    else
    {
      Vision.takeSnapshot(Vision__SIG_BLUE);
      Brain.Screen.setFillColor(red); 
      Brain.Screen.drawRectangle(20, 60, 400, 200); 
    }
    /*****************************************************************************/
    lineleft=Lineleft.reflectivity() ;
    lineright=Lineright.reflectivity() ;

    Controller(10, 1,x,y);
    ///////////////////////////////////
    
    suckLeft.setVelocity(z, percent); 
    suckRight.setVelocity(z, percent);
    suckLeft.spin(forward);
    suckRight.spin(forward); 
    suckFront.setVelocity(z, percent);
    suckFront.spin(forward);
    ///////////////////////////////////////
    if(launch==1)
    {
      suckBehind.setVelocity(100, percent); 
      suckFront.setVelocity(100, percent);
    }
    else
    {
      if(recyle==1)
      {
        suckBehind.setVelocity(-100, percent);
      }
      else
      {
        suckBehind.setVelocity(0, percent);
      }
    }
    /////////////////////////////////////////
    
    h=Vision.objects[0].height; 
    w=Vision.objects[0].width; 
    s=w*h;
    if(s>20000)
    {
      Brain.Timer.reset(); 
    }
    if(Brain.Timer.value() <0.4)
    {
      suckBehind.spin(reverse);
    }
    else
    {
      suckBehind.spin(forward);
    }
    /////////////////////////////////////
    Brain.Screen.setCursor(1, 1); 
    Brain.Screen.print("s=%f",s); 
    Brain.Screen.setCursor(2, 1); 
    Brain.Screen.print("lineright=%f",lineright); 
    wait(20, msec); 
  }
}
//******************************************************//

//
// 主函数使用场地控制器切换运行自动和遥控程序函数
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