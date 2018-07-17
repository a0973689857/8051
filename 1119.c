#include <reg52.h>
sbit rain=P3^2;							//�B�w ��������
sbit red=P3^3;              //�w�q���~�u�}��
sbit music=P2^3;            //�y��"ĵ����"
sbit GO=P2^1;               //���� 
sbit light=P2^2;            //����
sbit LED=P3^7;              //ĵ�ܿO

sbit motor1=P0^0;						//�w�q���ᰨ�F�}��
sbit motor2=P0^1;
sbit motor3=P0^2;
sbit motor4=P0^3;

sbit motor21=P0^4;					//�w�q��î���F�}��
sbit motor22=P0^5;
sbit motor23=P0^6;
sbit motor24=P0^7;

sbit open=P3^4;             //"�}����"
sbit close=P3^5;           	//"������"
sbit half=P3^6;             //"���B"


sbit voice4=P2^5;						//�y��"�}���G"
sbit voice3=P2^4;						//�y��"����î"
sbit voice2=P2^7;						//�y��"�}��"
sbit voice1=P2^6;						//�y��"����"
sbit DS1820=P2^0;						//�ū�
sbit LA=P1^0;								//7�q �ū� �Ӧ� L
sbit LB=P1^1;								//		|
sbit LC=P1^2;								//		|
sbit LD=P1^3;								//7�q �ū� �Ӧ� H
sbit HA=P1^4;								//7�q �ū� �Q�� L
sbit HB=P1^5;								//		|
sbit HC=P1^6;								//		|
sbit HD=P1^7;								//7�q �ū� �Q�� H
//�Ū�*************************************************************
void ctr();																//�Ū�
void blue_set();
//�ū�*************************************************************
void temp();															//�ū�
void reset_DS1820();				   						//���m�ū�
void write_DS1820(unsigned char dat);			//�g�ū�
unsigned char read_DS1820();							//Ū�ū�
//7�q**************************************************************
void print(int a);												//��ܷū�
void number(int b);
int n[]={0,0,0,0};
int b,t=0,v=0,o=0,q=0,m=0,a=0,ONE=0;
unsigned char X=0;
//���F*************************************************************
void ccw();
void cw();
void ccw2();
void cw2();
void delay(int s);
//���~�u***********************************************************
//void red();
//�D�{��***********************************************************
void main()
{
	blue_set();
	IE=0x85;		//���_
	IP=0x01;		//���_
	while(1)
	{
		temp();	
	}	

}

//�Ū�*************************************************************
void blue_set()
{	   
	TMOD = 0x21 ;					// ???TIMER1 ?????? 2
	TH1 = -03 ;					  // ?????? 9600Bd
	TR1 = 1 ;							// ??? TIMER1
	SCON = 0x50 ;					// ??????????????? 1	
}
void ctr()
{
	if(RI==1)
	{
		RI=0;							// ??? RI ???
		ACC=SBUF;					// ?????????????????ACC ??
		b=ACC;
		b=b&0x0f;
	if(b==0)
	{
			voice2=0;
			delay(1000);
			voice2=1;	
			delay(1000);

		while(b==0)
		{
				cw();
			 if(RI==1)
				{
				RI=0;							// ??? RI ???
				ACC=SBUF;					// ?????????????????ACC ??
				b=ACC;
				b=b&0x0f;		
				}	
		}
		t=1;
	 }
	 if(b==1)
	 {

			voice1=0;
			delay(1000);
			voice1=1;	
			delay(1000);
			 
		while(b==1)
		{		 
				ccw();
		 		if(RI==1)
				{
				RI=0;							// ??? RI ???
				ACC=SBUF;					// ?????????????????ACC ??
				b=ACC;
				b=b&0x0f;		
				}	
		}
		t=1;
	 }
	 if(b==4)
	 {		
		t=0;
	 }
	 if(b==5)
	 {		
		motor1=1;motor2=1;motor3=1;motor4=1; 	
	 }
	 if(b==2)
	 {

			voice3=0;
			delay(1000);
			voice3=1;	
			delay(1000);
		
		while(b==2)
		{
			cw2();
			if(RI==1)
			{
				RI=0;							// ??? RI ???
				ACC=SBUF;					// ?????????????????ACC ??
				b=ACC;
				b=b&0x0f;		
			}	
		}
	}
	 if(b==3)
	 {

			voice4=0;
			delay(1000);
			voice4=1;	
			delay(1000);
		
		while(b==3)
		{		
			ccw2();
			if(RI==1)
			{
				RI=0;							// ??? RI ???
				ACC=SBUF;					// ?????????????????ACC ??
				b=ACC;
				b=b&0x0f;		
			}	
		}
	 }		
	}	

}
//�ū�*************************************************************
void temp()					
{
	int i=0,l=0,n=0,z=0;
	unsigned char low_bit=0;
	unsigned char hi_bit=0;	
	if(RI==1)
	{
	ctr();
	}
	reset_DS1820();						
	write_DS1820(0xCC); 				
	write_DS1820(0x44); 				
	reset_DS1820();							
	write_DS1820(0xCC); 				
	write_DS1820(0xBE); 				
	low_bit=read_DS1820();    			
	hi_bit=read_DS1820();    			
	low_bit=low_bit>>4;   				
	X=hi_bit<<4;            			
	X=X|low_bit;	
	print(0);
	print(1);		
	
	
if(X>=27&&t==0)								//ALL OPEN
	{
		GO=0;
		ctr();
		if(v==0)										//�y��
		{
			voice2=0;										//�y��"����}��"
			delay(1000);
			voice2=1;
			delay(1000);
			v=1;
		}
		if(ONE==0)									//��î
		{
		if(light==0&&ONE==0)
		{
			voice3=0;									//�y��"��î�V�U"
			delay(1000);
			voice3=1;
			delay(1000);
			if(ONE==0)
			{
				for(z=0;z<450;z++)        //��î��ƤU
				{
					cw2();				
          ONE=1;					
				}
				
			
		   }
	  }
	 }
		if(light==1&&ONE==1)				//��î
		{
			voice4=0;									//�y��"��î�V�W"
			delay(1000);
			voice4=1;
			delay(1000);
			if(ONE==1)
			{
				for(z=0;z<450;z++)        //��î��ƤU
				{
					ccw2();
					ONE=0;
				}
				
			}
		}
	if(open==1)							//�P�_����O�_���}
	{
		cw();
	}
		
	}	
	if (X<=26&t==0)								//�}�@�b
	{
		GO=1;
		ctr();
		if(v==0)									//�y��
		{
			voice2=0;										//�y��"����}��"
			delay(1000);
			voice2=1;
			delay(1000);
			v=1;
		}
		if(ONE==0)								//��î
		{
		 if(light==0&&ONE==0)
		 {
			voice3=0;									//�y��"��î�V�U"
			delay(1000);
			voice3=1;
			delay(1000);
			if(ONE==0)
			{
				for(z=0;z<450;z++)        //��î��ƤU
				{
					cw2();
					ONE=1;
				}
			
	  	}
	   }
	 }
		if(light==1&&ONE==1)			//��î
		  {
			  voice4=0;									//�y��"��î�V�W"
			  delay(1000);
			  voice4=1;
			  delay(1000);
			  if(ONE==1)
			 {
				for(z=0;z<450;z++)        //��î��ƤU
				{
					ccw2();
					ONE=0;
				}
				
			 }
		  }
	  
		
		if(half==0)
		{
			cw();
		 if(open==0)
		 {
			 while(half==0)
			 {
					ccw();
			 }
		 }
		}
	}
	
	
		
}

void reset_DS1820()						
{
  DS1820 = 1;						   	
	delay(8);
	DS1820 = 0;						 	
	delay(80);							   
	DS1820 = 1;							
	delay(14);		
}

void write_DS1820(unsigned char dat)	
{
	unsigned char i=0;
 	for (i=8; i>0; i--)
 	{
  		DS1820 = 0;					
  		DS1820 = dat&0x01;			
  		delay(5);
  		DS1820 = 1;				
  		dat>>=1;					
 	}
	delay(4);
}

unsigned char read_DS1820()		
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)	
 	{
	  	DS1820 = 0; 				
	  	dat>>=1;					
	  	DS1820 = 1; 			
	  	if(DS1820)				   
	    dat|=0x80;
	  	delay(4);
 	}
 	return(dat);					
}
//7�q**************************************************************
void print(int a)
{
	switch(a)
	{	
		case 0:
		  number(X%10);
			LA=n[0];
			LB=n[1];
			LC=n[2];
			LD=n[3];
			break;
		case 1:
		  number(X/10);
			HA=n[0];
			HB=n[1];
			HC=n[2];
			HD=n[3];
			break;
	}
}	
void number(int b)	//�C�q�X
{
	switch(b)
	{
		case 0:
			n[0]=0;
			n[1]=0;
			n[2]=0;
			n[3]=0;
			break;
				
		case 1:
			n[0]=1;
			n[1]=0;
			n[2]=0;
			n[3]=0;
			break;
		
		case 2:
			n[0]=0;
			n[1]=1;
			n[2]=0;
			n[3]=0;
			break;
		
		case 3:
			n[0]=1;
			n[1]=1;
			n[2]=0;
			n[3]=0;
			break;
		
		case 4:
			n[0]=0;
			n[1]=0;
			n[2]=1;
			n[3]=0;
			break;
		
		case 5:
			n[0]=1;
			n[1]=0;
			n[2]=1;
			n[3]=0;
			break;
		
		case 6:
			n[0]=0;
			n[1]=1;
			n[2]=1;
			n[3]=0;
			break;
		
		case 7:
			n[0]=1;
			n[1]=1;
			n[2]=1;
			n[3]=0;
			break;
		
		case 8:
			n[0]=0;
			n[1]=0;
			n[2]=0;
			n[3]=1;
			break;
		
		case 9:
			n[0]=1;
			n[1]=0;
			n[2]=0;
			n[3]=1;
			break;

				
	}
}




//���F************************************************************
void cw()							//����
{

	  int s;
	  s=1650;
	  motor1=0;motor2=1;motor3=1;motor4=1; 	delay(s);				
	  motor1=1;motor2=0;motor3=1;motor4=1; 	delay(s);				
	  motor1=1;motor2=1;motor3=0;motor4=1; 	delay(s);				
	  motor1=1;motor2=1;motor3=1;motor4=0; 	delay(s);				
		
}
void ccw()		        //����
{
	  int s;
	  s=1650;
  	motor1=1;motor2=1;motor3=1;motor4=0; 	delay(s);				
	  motor1=1;motor2=1;motor3=0;motor4=1; 	delay(s);				
	  motor1=1;motor2=0;motor3=1;motor4=1; 	delay(s);				
	  motor1=0;motor2=1;motor3=1;motor4=1; 	delay(s);				
}
void cw2()						//����
{

	  int s;
	  s=250;
	  motor21=0;motor22=1;motor23=1;motor24=1; 	delay(s);				
	  motor21=1;motor22=0;motor23=1;motor24=1; 	delay(s);				
	  motor21=1;motor22=1;motor23=0;motor24=1; 	delay(s);				
	  motor21=1;motor22=1;motor23=1;motor24=0; 	delay(s);				
		
}
void ccw2()				  	//����
{
int s;
	  s=250;
  	motor21=1;motor22=1;motor23=1;motor24=0; 	delay(s);				
	  motor21=1;motor22=1;motor23=0;motor24=1; 	delay(s);				
	  motor21=1;motor22=0;motor23=1;motor24=1; 	delay(s);				
	  motor21=0;motor22=1;motor23=1;motor24=1; 	delay(s);				
}
void delay(int s)					
{
	int m;
	for(m=0;m<s;m++);
}
//���_************************************************************
void int0(void)interrupt 2 //���~�u���_
{  	
	int i=0;
	 LED=0;
	 music=0;
	 delay(1000);
	 delay(1000);
	 delay(1000);
	 delay(1000);
	 delay(1000);
	 delay(1000);
	 
	 music=1;
	for(i=0;i<360;i++)
	{
	 delay(1000);
	}
 	 LED=1;
}

void int1(void)interrupt 0	//�B�w�P�������_
{
	int q=0;
 if(close==1)
 {
	voice1=0;
	delay(1000);
	voice1=1;
 }
	delay(1000);
	while(close!=0)
	{
		ccw();
	}
	for(q=0;q<13;q++)
	{
		delay(10000);
	}
	
	v=0;
	q=0;
	GO=1;
}	









