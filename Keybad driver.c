/*
 * Keybad_driver.c
 *
 * Created: 24/09/2021 4:53:44 PM
 *  Author: kamar salah
 */ 

#include "DIO drivers.h"
#include "Keybad driver.h"

void Keybad_vinit (void)
{
	DIO_vset_port_dir('D',0x0f);                                // first four bin (raws) is output , last four bit (colums)  is input
	DIO_vconected_pullup('D',4,1);                              // activiate internal pull on pin 4
	DIO_vconected_pullup('D',5,1);                              // activiate internal pull on pin 5
	DIO_vconected_pullup('D',6,1);                              // activiate internal pull on pin 6
	DIO_vconected_pullup('D',7,1);                              // activiate internal pull on pin 7
	
}

unsigned char Keybad_u8check_press (void)
{
	unsigned char arr [4][4]= {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}};
	char raw,col,x;
	char returnvla=NOTBRESSED;                                                   // any value dont represents any ASCII code which keybad
	                                                
	for (raw=0; raw<=3; raw++)
	{
		DIO_vwrite_pin ('D', 0,1);                                            // pin 0 in selected port is output
	    DIO_vwrite_pin ('D', 1,1);                                            // pin 1 in selected port is output
	    DIO_vwrite_pin ('D', 2,1);                                            // pin 2 in selected port is output
	    DIO_vwrite_pin ('D', 3,1);                                            // pin 3 in selected port is output
	    DIO_vwrite_pin ('D', raw ,0);                                         // pin 0 in selected port is output
		
		for (col=0; col<=3; col++)
		{
			x=DIO_u8read_pin ('D',(col+4));                                    // check if input pin is 0 or 1                                  
			if(x==0)                                                           // if pressed button 
			{
				returnvla= arr [raw][col];                                     
				break;
			}
			
	   }
	   if (x==0)
	   {
		   break;
	   }
	   
	}
       return returnvla;
}