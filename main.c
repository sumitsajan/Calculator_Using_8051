#include<reg51.h>
#define COL P2
#define ROW P0
#define display P1

void delay(unsigned int value);
 void conv1();
 void conv2();
 void add();
 void anticonv();
 void subb();
void mul();
void div();
void perform();
void command_set();
void two_digit();
void two_digit1();
sbit En =P3^2;
sbit Rs =P3^0;
sbit Rw =P3^1;

unsigned char y=0;
unsigned char x=0;
unsigned char result=0; 
unsigned char acc=0;
unsigned char sign=0;
unsigned char count=0;
unsigned char p;
unsigned char q;
unsigned char z=0;
unsigned char b=0;
unsigned char c=0;
void command()
{

     Rs=0;     // Since we give command we have to make RS=0
     Rw = 0;  // since we write the data on lcd we have to make R/W pin 0
     En = 1; // to take new character
     En = 0;
delay(1);
}

unsigned char calculator[4][4] = {'7','8','9','/',
	                                '4','5','6','*',
	                                '1','2','3','-',
	                                'c','0','=','+'};

	
void DISPLAY()
{

         Rs=1;      // As we send data make RS=1
			   Rw=0;     //  since we write the data on lcd we have to make R/W pin 0
         En = 1;
         En = 0;
         delay(1);

}	
														
void main()
{
	unsigned char col,row;
	
		
	command_set();
 	
	while(1)
	{
	COL =0xFF;
	  do
		{
		  ROW =0x00;
			col=COL;
			col &= 0x0F;
		}while(col != 0x0F);
		
		do
		{
 
		delay(1);
		col =COL;
		col &= 0x0F;
	
	}while(col == 0x0F);
		
	while(1)
	{		
	  ROW = 0x0FE;
		col =COL;
		col &=0x0F;

		if(col != 0x0F)
			
		{
		  row = 0;
			break;
		}
		
		ROW = 0xFD;
		col = COL;
		col &= 0x0F;
	 
		if(col != 0x0F)
			
		{
		  row =1;
			break;
		
		}
		
		 ROW = 0xFB;
		 col = COL;
		 col &= 0x0F;
		 
		if(col != 0x0F)
		{
		  row = 2;
			break;
		}
		
		ROW = 0xF7;
		col = COL;
		col &= 0x0F;
		
		row =3;
		
		break;
	}
	
	if(col == 0x0E)
	{
		acc = calculator[row][0];
	}
	else if (col == 0x0D)
	{
 		
		acc = calculator[row][1];
	}		
	else if(col == 0x0B)
	{
		acc = calculator[row][2];
	}
	else  
	{
 
		acc = calculator[row][3];
	}
    
	if(acc==0x63)
	{
	   command_set();
		count=0;
		z=0;
		continue;
	}
	
	 display = acc;
	  DISPLAY();
	
	
	if(acc==0x3D)
	{
 		perform();
 
	}
	
	
	if(acc==0x2B)
	{
			z=1;
	   sign=acc;
		continue;
	}
	 else if (acc==0x2D)
	 {
		 	z=1;
	    sign =acc;
		 continue;
	 }
	 
	 else if(acc==0x2A)
	 {
		 	z=1;
	    sign=acc;
		 continue;
	 
	 }
	 else if(acc==0x2F)
	 {
		 	z=1;
	    sign=acc;
		 continue;
	 
	 }
	 
	 	if(acc=='0' || acc == '1' || acc == '2' || acc == '3' || acc == '4'
		   || acc == '5' || acc == '6' || acc == '7' || acc == '8' || acc == '9' ) 
	    { 
               count++;
       }
	
			 
           if(count==1 && z==0)

           {
                conv1();
						 p=0x0F;
						              
           }

           else if(count==2 && z== 0)

            {
              p = acc & 0x0F;
              two_digit();							
            }
            else if((count==2 && z==1) || (count==3 && z==1))

            {
               conv2();							
            }
						else if((count==3 && z==1) || (count==4 && z==1))
						{
						  c = acc & 0x0F;
							two_digit1();							
						} 
}
	
}

void conv1()
{
		x = acc & 0x0F;
    q=x;	  
}

void two_digit()
{
    	x=x*10;
	    q=x+p;
}

void conv2()
{	
	y = acc & 0x0F;
   b=y;	
}


void two_digit1()
{
    	y=y*100;
	    b=y+c;
}

 
void perform()
{

	if (sign == 0x2B)
	{
	  add();
	}
	else if (sign == 0x2D)
	{ 
	   subb();
	}
	
		else if (sign == 0x2A)
	{
	   mul();
	}
	
		else if (sign == 0x2F)
	{
	   div();
	}
}


void add()
{	
	 
  result = q+b;
	anticonv();
}

void subb()
{
 
   result = q-b;
   anticonv();
}

void mul()
{
 
  result = q*b;
	anticonv();
}

void div()
{
 
 result=q/y;
	anticonv();
}

void anticonv()
{
   unsigned char d1,d2,d3,d4;
	 
	d1=result / 10;
	d2=result % 10;
	d3=d1 / 10;
	d4=d1 % 10;
	
	d3 = d3 | 0x30;
	display=d3;
	DISPLAY();
	
	d4 = d4 | 0x30;
	display=d4;
	DISPLAY();
	

  d2 = d2 | 0X30;
	display=d2;
	DISPLAY();
	
}


void command_set()
{

  display = 0x38;
    command();

     display = 0x01;
    command();
		
     display = 0x0C;
     command();
		 
      
     display = 0x06;
     command();
		 
 
     display = 0x80;
     command();

}

void delay(unsigned int value)
{
  unsigned int g,h;
	for(g=0;g<1275;g++)
	{
	  for(h=0;h<value;h++)
		{}
	}
}