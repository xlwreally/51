 /*****************************************************************************
 *版权信息：熊立伟
 *文 件 名xlw_time.h
 *当前版本：V1.0
 *MCU 型号：STC12C2052AD
 *开发环境：Keil uVision4
 *晶震频率：12MHZ       
 *完成日期：2020-11-19
 *程序功能：TM1640时间显示程序；
 *免责声明：1.此程序为TM1640时间显示程序，仅作参考之用。
            2.如有直接使用本例程程序造成经济损失的，本人不承担任何责任             
********************************************************************************/
//xlw-time.h
#ifndef _XLW_TIME_H_ //如果没有引入头文件
    #define _XLW_TIME_H_ //那就引入头文件
#include<xlw_driver.h>
int miao=0;		
int fen=0;			
int shi=0;
int ri=19;
int yue=11;
int nian=2020;
int n=0;			//计数
int date[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
int month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
void time_init()						   //定时器初始化函数
{
  TMOD=0x02;							  //选择方式2
	TH0=156;							  //重装初值为156
	TL0=156;							  //运行值为156
	EA=1;								  //开总中断
	ET0=1;								  //开定时器0中断
	TR0=1;								  //开定时器0
}

int leapyear(int year){
	  int a;
    if(year%400==0)
        a=1;
    else
    {
        if(year%4==0&&year%100!=0)
            a=1;
        else
            a=0;
    }
    if(a==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}
void timer() interrupt 1					  //定时器0中断
{
     n++;
	 if(n==4000)								 
	 {	 
		 Led1=~Led1;
		 Led2=~Led2;
	     n=0;
	     miao++;
		 if(miao==60)
		 {
		     miao=0;
		     fen++;
			 if(fen==60)
			 {
			     fen=0;
				 shi++;
				 if(shi==24)
				 {
				    shi=0;
						ri++;
					 if(leapyear(nian)||yue==2){
								if(ri==29){
										ri=0;
										yue++;
									if(yue==12){
										yue=0;
										nian++;
									}
								}
					 }else{
									if(ri==month[yue]){
										ri=0;
										yue++;
									if(yue==12){
										yue=0;
										nian++;
									}
								}
					 }
						 
				 }
			 }
		 }
		 date[0]=miao%10;
		 date[1]=miao/10;
		 date[2]=fen%10;
		 date[3]=fen/10;
		 date[4]=shi%10;
		 date[5]=shi/10;
		 date[6]=ri%10;
		 date[7]=ri/10;
		 date[8]=yue%10;
		 date[9]=yue/10;
		 date[10]=nian%10;
		 date[11]=nian/10%10;
		 date[12]=nian/100%10;
		 date[13]=nian/1000%10;
	
	 }
	 
 
}	  
#endif
