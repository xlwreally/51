
 /*****************************************************************************
 *��Ȩ��Ϣ������ΰ
 *�� �� ���xxlw_drive.h
 *��ǰ�汾��V1.0
 *MCU �ͺţ�STC12C2052AD
 *����������Keil uVision4
 *����Ƶ�ʣ�12MHZ       
 *������ڣ�2020-11-19
 *�����ܣ�TM1640��������
 *����������1.�˳���ΪTM1640�������򣬽����ο�֮�á�
            2.����ֱ��ʹ�ñ����̳�����ɾ�����ʧ�ģ����˲��е��κ�����             
********************************************************************************/
//xlw-driver.h
#ifndef _XLW_DRIVER_H_ //���û������ͷ�ļ�
    #define _XLW_DRIVER_H_ //�Ǿ�����ͷ�ļ�
	#include <STC12C2052AD.h>		   //ͷ�ļ�
#include "intrins.h"		   //����_nop_()ָ��ͷ�ļ�
//void disp(int num[14]);
//char key_scan();
/********************������ƶ˿�**********************/
sbit DIN=P1^0;				  
sbit CLK=P1^1;
sbit Beep=P1^2;
sbit Key0=P3^0;
sbit Key1=P3^1;						
sbit Key2=P3^2;
sbit Key3=P3^3;	
sbit Led2=P3^5;
sbit Led1=P3^7;
/********************��������*************************/
unsigned char code CODE[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,};	

/********************��ʱ��������ʱnms******************/
void delay_nms(unsigned int n)
{
unsigned int i;
while(n--)
for(i=0;i<550;i++);
}

/********************Start����*************************/
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
/********************Stop����*************************/
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

/***************����8bit���ݣ��ӵ�λ��ʼ**************/
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

/************��ʾ����************/
void disp(int num[14])
{
 I2CStart();
 I2CWritebyte(0x40);	//�����������ã���ͨģʽ����ַ�Զ���һ
 I2CStop();
 I2CStart();
 I2CWritebyte(0xc2);	//��ַ�������ã���ʼ��ַ00H
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
 I2CWritebyte(0x8c);	//��ʾ���ƣ���ʾ������������Ϊ11/16
 I2CStop();
}
char key_scan()
{
	char KeyV=8;				
	if(Key0==0||Key1==0||Key2==0||Key3==0)		//�ж��Ƿ��а�������
	{
		 if(Key0==0)		//�ж��ĸ�����������//
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
		}		  			//�ж��ĸ�����������//
		
		if(KeyV != 0)		//�а�������ʱ���������ּ��
              while(Key0==0||Key1==0||Key2==0||Key3==0);
   }
 			 return KeyV;
    			//����KeyV����ʶ��һ������������
}


#endif