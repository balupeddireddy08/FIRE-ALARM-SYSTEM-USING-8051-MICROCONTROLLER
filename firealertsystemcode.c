#include<reg51.h> //header file of 51 families
sbit sensor=P1^0; //_sbit is the datatype used to assign single _bit to i/o _bit
sbit rs=P1^1; //rs pin enables a user to select Instr or Char mode 
sbit rw=P1^2; //read and write information of lcd
sbit en=P1^3; //enable pin latches the info at datapins
sbit buzzer=P3^0;
//Definiging the functions
void lcdinit(); //lcd intializing function
void lcddat(unsigned char); //by this function characters are passed on to the LCD screen
void lcdcmd(unsigned char); //send command on lcd
void lcddis(unsigned char *); //text to display on the LCD
void delay(); //to delay for some time
void main()
{
	buzzer=0;
	sensor=0;
	back:lcdinit();
	lcddis("  FIRE ALERT   "); //message display on the screen
	lcdcmd(0xc0); //this command will force the cursor to second line
	lcddis("   SYSTEM ");
	delay();
	while(1)
	{
		if(sensor==1)
		{
			lcdcmd(0x01); //clear the display
			lcddis("FIRE OCCURED");
			lcdcmd(0xc0);
			lcddis("MOVE FROM EXIT");
			delay();
			delay();
			buzzer=1;
		}
		goto back;
	}
}
void lcdinit()
{
	lcdcmd(0x38); //initialize all the crystals in lcd 
	lcdcmd(0x01);// clear the screen
	lcdcmd(0x10); //shift the cursor to left
	lcdcmd(0x0c); //it displays the cursor blinking
	lcdcmd(0x80); //set DDRAM address or coursor positin on display
}
void lcdcmd(unsigned char val)
{
	P2=val; //
	rs=0; //instr cmd rig is selected ,allow to send cmd  
	rw=0;//write operation is done
	en=1;
	delay();
	en=0;
}
void lcddat(unsigned char dat)
{
	P2=dat;
	rs=1; //_data _register is selected, allowing the user to send _data
	rw=0;
	en=1;
	delay();
	en=0;
}
void lcddis(unsigned char *s)
{
	unsigned char w;
	for(w=0;s[w]!='\0';w++)
	{
	lcddat(s[w]);	
	}
}
void delay()
{
	unsigned int v1;
	for(v1=0;v1<10000;v1++);
}