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


void main(){
unsigned int num[]={2,0,2,0,1,1,1,8,2,2,4,2,0,0,};
int i;
time_init();
while(1)
{
//num[0]=key_scan();
	for(i=13;i>=0;i--)
	num[i]=date[13-i];

 disp(num);		
 delay_nms(10);
}
}

void timer() interrupt 1					  //定时器0中断
{
     n++;
	 if(n==4)								 
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
