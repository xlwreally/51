
 /*****************************************************************************
 *版权信息：熊立伟
 *文 件 名xlw_drive.h
 *当前版本：V1.0
 *MCU 型号：STC12C2052AD
 *开发环境：Keil uVision4
 *晶震频率：12MHZ       
 *完成日期：2020-11-19
 *程序功能：TM1640驱动程序
 *免责声明：1.此程序为TM1640驱动程序，仅作参考之用。
            2.如有直接使用本例程程序造成经济损失的，本人不承担任何责任             
********************************************************************************/
//xlw-driver.h
#ifndef _XLW_DRIVER_H_ //如果没有引入头文件
    #define _XLW_DRIVER_H_ //那就引入头文件
	#include <STC12C2052AD.h>		   //头文件
#include "intrins.h"		   //包含_nop_()指令头文件
//void disp(int num[14]);
//char key_scan();
/********************定义控制端口**********************/
sbit DIN=P1^0;				  
sbit CLK=P1^1;
sbit Beep=P1^2;
sbit Key0=P3^0;
sbit Key1=P3^1;						
sbit Key2=P3^2;
sbit Key3=P3^3;	
sbit Led2=P3^5;
sbit Led1=P3^7;
/********************定义数据*************************/
unsigned char code CODE[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,};	

/********************延时函数，延时nms******************/
void delay_nms(unsigned int n)
{
unsigned int i;
while(n--)
for(i=0;i<550;i++);
}

/********************Start函数*************************/
void I2CStart()
{
    DIN=1;
    CLK=1;
	_nop_();
	_nop_();
	DIN=1; 
	_nop_();
	_nop_();
	DIN=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	CLK=0;
	_nop_();
	_nop_();
}
/********************Stop函数*************************/
void I2CStop()
{
	CLK=1;
	_nop_();
	_nop_();
	DIN=0;
	_nop_();
	_nop_();
	DIN=1;
	_nop_();
	_nop_();
	CLK=0;
	DIN=0;

}

/***************发送8bit数据，从低位开始**************/
void I2CWritebyte(unsigned char oneByte)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
    CLK=0;
	if(oneByte&0x01) 
	  DIN=1;
	else 
	  DIN=0;
	_nop_();
	_nop_();
	_nop_();
	CLK=1;
	oneByte=oneByte>>1;
	}
	CLK=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	DIN=0;
	_nop_();
	_nop_();
}

/************显示函数************/
void disp(int num[14])
{
 I2CStart();
 I2CWritebyte(0x40);	//数据命令设置：普通模式，地址自动加一
 I2CStop();
 I2CStart();
 I2CWritebyte(0xc2);	//地址命令设置：初始地址00H
I2CWritebyte(CODE[num[13]]);
I2CWritebyte(CODE[num[12]]);
I2CWritebyte(CODE[num[7]]);
I2CWritebyte(CODE[num[6]]);
I2CWritebyte(CODE[num[5]]);
I2CWritebyte(CODE[num[4]]);
I2CWritebyte(CODE[num[10]]);
I2CWritebyte(CODE[num[11]]);
I2CWritebyte(CODE[num[2]]);
I2CWritebyte(CODE[num[9]]);
I2CWritebyte(CODE[num[8]]);
I2CWritebyte(CODE[num[3]]);
I2CWritebyte(CODE[num[0]]);
I2CWritebyte(CODE[num[1]]);

 I2CStop();

 I2CStart();
 I2CWritebyte(0x8c);	//显示控制：显示开，脉冲宽度设为11/16
 I2CStop();
}
char key_scan()
{
	char KeyV=8;				
	if(Key0==0||Key1==0||Key2==0||Key3==0)		//判断是否有按键按下
	{
		 if(Key0==0)		//判断哪个按键被按下//
		{	
			KeyV=1;
		}
		else if(Key1==0)
		{
			KeyV= 2;
		}
		else if(Key2==0)
		{	
			KeyV=3;
		}
		else if(Key3==0)
		{
			KeyV=4;
		}
		else 
		{
			 return KeyV;
		}		  			//判断哪个按键被按下//
		
		if(KeyV != 0)		//有按键按下时，进行松手检测
              while(Key0==0||Key1==0||Key2==0||Key3==0);
   }
 			 return KeyV;
    			//返回KeyV来标识哪一个按键被按下
}


#endif