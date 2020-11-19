#include<xlw_time.h>
	unsigned int num[14];
void display(){
	unsigned int i;
	for(i=13;i>=0;i--)
	num[i]=date[13-i];
 disp(num);		
 delay_nms(100);

}
void main(){
	int i,key;
	key=key_scan();
	time_init();
	while(1)
{
	display();
}
}


