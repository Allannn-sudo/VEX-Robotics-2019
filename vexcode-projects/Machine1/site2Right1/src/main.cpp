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
// Vision               vision        18              
// Lineleft             line          C               
// Lineright            line          D               
// GyroE                gyro          E               
// LineTrackerA         line          A               
// LineTrackerB         line          B               
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
  {Slope = 10;}
  else
  {Slope = 13;} 
	if(fabs(x)<95)
	{sensitivity = 0.4;}
	else
	{sensitivity = 0.7;} 
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

//电流控制移动
void Current(float zspeed,float yspeed,float Current1,int stopping)
{
  while(leftbehind.current()<Current1)
  {
    ZYMotor(zspeed,yspeed);
  }
  Stop(stopping,1);
}
//陀螺仪角度精准移动
void Gyro(float location,float KP,float KI,float KD)
{
  
  //GyroE.setRotation(calibration, degrees);  
  //float KP=0.6,KI=0.072,KD=60;
  float Rotation,error;
  float integral=0,lasterror=0,derivative,speed;
  while(1)
  {
    Rotation=GyroE.rotation(degrees)  ;
    Brain.Screen.setCursor(1, 1); 
    Brain.Screen.print("Rotation=%f",Rotation);
    Brain.Screen.setCursor(2, 1); 
    Brain.Screen.print("head=%f",GyroE.heading(degrees) );
    error=location-Rotation;
    integral=integral*0.812+error ;
    derivative=error-lasterror;
    speed=KP*error+KI*integral+KD*derivative;
    lasterror=error;
    ZYMotor(speed,-speed);
    if((Rotation>location-1&&Rotation<location+1&&location>0&& leftfront.velocity(rpm) <5&&leftfront.isDone()==1 )
    ||(Rotation<location+1&&Rotation>location-1&&location<0&& leftfront.velocity(rpm) <5&&leftfront.isDone()==1))
    {
      break;
    }
  }
  Stop(1,1);
}
//机器人启动
void Spin()
{
  suckLeft.setStopping(brake); 
  suckRight.setStopping(brake); 
  suckLeft.stop(); 
  suckRight.stop(); 
  Brain.Timer.reset(); 
  while(Brain.Timer.value()<0.5 )
  {
    if(Brain.Timer.value()<0.4)
    {
      suckLeft.setVelocity(-30, percent); 
      suckRight.setVelocity(-30, percent); 
      suckLeft.spin(forward); 
      suckRight.spin(forward); 
    }
    ZYMotor(30,30);
    suckBehind.setVelocity(20,percent);
    suckBehind.spin(forward);
  }
  suckBehind.stop();
  suckLeft.stop(); 
  suckRight.stop();
  Stop(1,1);
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
void GO2(float zspeed,float yspeed,float degree,int stopping)
{
  if(yspeed+zspeed>0)
  {
    rightfront.setPosition(0, degrees);  
    while(rightfront.position(degrees)<degree)
    {
      ZYMotor(zspeed,yspeed);
    }
    Stop(stopping,1);
  }
  if(yspeed+zspeed<0)
  {
    rightfront.setPosition(0, degrees);
    while(rightfront.position(degrees)>-degree)
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
void suckspin(int frontspeed,int middlespeed,int behindspeed )
{
    suckLeft.setVelocity(frontspeed, percent); 
    suckRight.setVelocity(frontspeed, percent); 
    suckLeft.spin(forward); 
    suckRight.spin(forward); 
    suckFront.setVelocity(middlespeed, percent); 
    suckFront.spin(forward); 
    suckBehind.setVelocity(behindspeed, percent); 
    suckBehind.spin(forward);

}
//吸球电机停止
void suckstop(int front,int middle,int behind)
{
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
//***************************************************************************//
//*********************以下为自动任务方案*************************************//
void RightTurn1()/////////红后2个纵横桩或蓝前2个纵横桩////////////////
{
  suckspin(40,60,0);
  GOtime(70,10,1.2,1);
  GOtime(35,35,1.5,1);
  /////第一球/////
  while(LineTrackerA.reflectivity()<15 )
  {
    suckspin(50,100,80);
  }
  while(LineTrackerB.reflectivity()<15 )
  {
    suckspin(50,100,80);
  }
  suckstop(1,1,1);
  wait(0.1, seconds);
  ////第二球////
  while(LineTrackerA.reflectivity()<15 )
  {
    suckspin(30,100,80);
  }
  while(LineTrackerB.reflectivity()<15 )
  {
    suckspin(30,100,80);
  }
  suckstop(1,1,1);
  
  wait(0.1, seconds);
  ////第三球////
  Brain.Timer.reset(); 
  int t;
  while(Lineleft.reflectivity()<15&&Lineright.reflectivity()<15 )
  {
    suckspin(8,100,80);
    if(Brain.Timer.value() <0.2)
    {t=1;}
    else if(Brain.Timer.value() <0.4)
    {t=0;}
    else
    {Brain.Timer.reset();}
    if(t==1)
    {ZYMotor(40,40);}
    if(t==0)
    {Stop(2,1);}
  }
  ZYMotor(0,0);
  wait(0.1,seconds);
  suckstop(1,1,1);
  suckspin(-100,0,0);
  wait(0.1,seconds);
  GO(-30,-30,500,1);
  suckstop(1,1,1);
  Gyro(280,0.6,0.072,60);
}
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
suckspin(int frontspeed,int middlespeed,int behindspeed);
////////////////////////frontspeed：吸球前电机速度
////////////////////////middlespeed：吸球中电机速度
////////////////////////behindspeed：吸球后电机速度

//吸球电机停止
suckstop(int front,int middle,int behind)
////////////////////////front :前吸电机停止（1代表停止，0代表不停）
////////////////////////middle:中吸电机停止（1代表停止，0代表不停）
////////////////////////behind:后吸电机停止（1代表停止，0代表不停）

////陀螺仪角度精准移动
Gyro(float location,float KP,float KI,float KD)
////////////////////////location :位置（负值左转，正值右转）
////////////////////////KP:比例，范围（0~1的小数）目标值与实际侧向值的差值越大，KP值越小（根据实际情况而定）
////////////////////////KI:积分，范围（0.0xxx）将目标值与实际侧向值的差值（误差）累加，用于纠正过去的误差
////////////////////////KD:导数，范围（xx两位数）
******************************************************************************/
//********************在此处编写自动程序***************************************//
void autonomous(void) {
  Vision.takeSnapshot(Vision__SIG_RED);
  suckBehind.setMaxTorque(100, percent);
  Brain.Timer.reset();
  /*float Rotation;
  while(1)
  {
    Rotation=GyroE.rotation(degrees) ;
    Brain.Screen.setCursor(1, 1); 
    Brain.Screen.print("r=%f",Rotation);
  }*/
  Spin();
  RightTurn1();
  
}

//在此处编写遥控程序
void usercontrol(void) {
  suckBehind.setMaxTorque(100, percent); 
  Brain.Timer.reset(); 
  float s,h,w;
  float z;
  float lineTrackerA,lineTrackerB;
  int Direction=0,team=0;
  float x,y;
  int launch,recyle,num;
  float lineleft,lineright;
  Stop(2,0);
  while(1)
  {
    lineTrackerA=LineTrackerA.reflectivity(); 
    lineTrackerB=LineTrackerB.reflectivity();
    lineleft=Lineleft.reflectivity();
    lineright=Lineright.reflectivity();
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
    /***********************************红蓝方切换***********************************/
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
    /******************************底盘遥控自定义函数******************************/
    Controller(10, 1,x,y);
    ////////////////对方球检测面积///////////////////////
    h=Vision.objects[0].height; 
    w=Vision.objects[0].width; 
    s=w*h;
    /////////////////////////////////////////
    if(lineTrackerA>40&&z>2)
    {
      if(s<2000)
      {
        if(lineTrackerB>40)
        {suckBehind.setVelocity(0, percent);}
        else
        {suckBehind.setVelocity(100, percent);}
      }
      else
      {
        if(launch==1)
        {num=1;}
        else
        {num=2;}
      }
      suckLeft.setVelocity(z, percent); 
      suckRight.setVelocity(z, percent);
    }
    else
    {
      if(launch==1)
      {num=4;}
      else
      {num=3;}
      suckLeft.setVelocity(z, percent); 
      suckRight.setVelocity(z, percent);
    }
    if(launch==1)
    {suckBehind.setVelocity(100, percent); }
    else
    {
      if(recyle==1)
      {suckBehind.setVelocity(-100, percent);}
      else
      {
        if(lineTrackerA>40&&z>2&&s<2000&&lineTrackerB<40)
        {
          if(lineTrackerB>40)
          {
            suckBehind.setVelocity(0, percent);
            
          }
          else
          {suckBehind.setVelocity(100, percent);}
        }
        else
        {suckBehind.setVelocity(0, percent);} 
      }
    }
    if(lineTrackerB>40)
    {
      if((lineleft>10||lineright>10)&&z>2&&launch==0)
      {num=5;}
    }
    
    /////////////////////////////////////////
    if(num==1||num==4)
    {suckFront.setVelocity(80, percent);}
    else if(num==2||num==5)
    {suckFront.setVelocity(0, percent);}
    else if(num==3)
    {suckFront.setVelocity(z, percent);}
    ///////////////////////////////////////
    suckLeft.spin(forward);
    suckRight.spin(forward); 
    suckFront.spin(forward);
    ///////////////////////////////////////
    if(s>9600)
    {
      Brain.Timer.reset(); 
    }
    if(Brain.Timer.value() <0.11)
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
    Brain.Screen.print("lineTrackerA=%f",lineTrackerA); 
    Brain.Screen.setCursor(3, 1); 
    Brain.Screen.print("lineleft=%f",lineleft); 
    Brain.Screen.setCursor(4, 1); 
    Brain.Screen.print("lineright=%f",lineright);
    Brain.Screen.setCursor(5, 1); 
    Brain.Screen.print("lineTrackerB=%f",lineTrackerB);
    
  }
}
//******************************************************//

//
// 主函数使用场地控制器切换运行自动和遥控程序函数
//
int main() {
  GyroE.calibrate(); 
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