 /*****************************************************************************
 *��Ȩ��Ϣ������ΰ
 *�� �� ���xxlw_time.h
 *��ǰ�汾��V1.0
 *MCU �ͺţ�STC12C2052AD
 *����������Keil uVision4
 *����Ƶ�ʣ�12MHZ       
 *������ڣ�2020-11-19
 *�����ܣ�TM1640ʱ����ʾ����
 *����������1.�˳���ΪTM1640ʱ����ʾ���򣬽����ο�֮�á�
            2.����ֱ��ʹ�ñ����̳�����ɾ�����ʧ�ģ����˲��е��κ�����             
********************************************************************************/
//xlw-time.h
#ifndef _XLW_TIME_H_ //���û������ͷ�ļ�
    #define _XLW_TIME_H_ //�Ǿ�����ͷ�ļ�
#include<xlw_driver.h>
int miao=0;		
int fen=0;			
int shi=0;
int ri=19;
int yue=11;
int nian=2020;
int n=0;			//����
int date[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
int month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
void time_init()						   //��ʱ����ʼ������
{
  TMOD=0x02;							  //ѡ��ʽ2
	TH0=156;							  //��װ��ֵΪ156
	TL0=156;							  //����ֵΪ156
	EA=1;								  //�����ж�
	ET0=1;								  //����ʱ��0�ж�
	TR0=1;								  //����ʱ��0
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
void timer() interrupt 1					  //��ʱ��0�ж�
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
