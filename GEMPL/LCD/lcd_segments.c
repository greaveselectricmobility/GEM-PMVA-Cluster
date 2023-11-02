/***********************************************************************************************************************
* File Name    : lcd_segments.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the LCD segments.
* Creation Date: 28-08-2023
* Author	   : Praveen A
***********************************************************************************************************************/

#include<stdio.h>
#include"lcd.h"
#include"lcd_segments.h"


/*Alert msg*/
char Cap_alphabets[42] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ','0','1','2','3','4','5','6','7','8','9','+','-','*','/','='};
//char Cap_alphabets[42] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ','0','1','2','3','4','5','6','7','8','9'};
char Small_alphabets[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

ERROR_BITS_t ERROR_BITS;
/***********************************************************************************************************************
* Function Name: speed_or_soc_segments
* Description  : This function configures the segments that need to be illuminated for the speed or state of charge (SoC) segments.
* Arguments    : lcd_data_buffer and value of the speed or state of charge
* Return Value : None
***********************************************************************************************************************/
void speed_or_soc_segments(LCD_DATA_BUFF *lcd_data, uint8_t value)
{
	int digit_1 = value%10;
	int temp    = value/10;
	int digit_2 = temp%10;
	int digit_3 = temp/10;
	/****************************************************************************/
	(lcd_data+31)->bit.bit_5 = GET_DISP_DATA_BIT(digit_1,SEGMENT_A); //a/
	(lcd_data+31)->bit.bit_0 = GET_DISP_DATA_BIT(digit_1,SEGMENT_B); //b/
	(lcd_data+31)->bit.bit_1 = GET_DISP_DATA_BIT(digit_1,SEGMENT_C); //c/
	(lcd_data+31)->bit.bit_2 = GET_DISP_DATA_BIT(digit_1,SEGMENT_D); //d/
	(lcd_data+31)->bit.bit_3 = GET_DISP_DATA_BIT(digit_1,SEGMENT_E); //e/
	(lcd_data+31)->bit.bit_7 = GET_DISP_DATA_BIT(digit_1,SEGMENT_F); //f/
    (lcd_data+30)->bit.bit_3 = GET_DISP_DATA_BIT(digit_1,SEGMENT_G); //g/
	(lcd_data+30)->bit.bit_7 = GET_DISP_DATA_BIT(digit_1,SEGMENT_H); //h
	(lcd_data+30)->bit.bit_6 = GET_DISP_DATA_BIT(digit_1,SEGMENT_I); //i
	(lcd_data+30)->bit.bit_5 = GET_DISP_DATA_BIT(digit_1,SEGMENT_J); //j
	(lcd_data+30)->bit.bit_1 = GET_DISP_DATA_BIT(digit_1,SEGMENT_K); //k/
    (lcd_data+30)->bit.bit_2 = GET_DISP_DATA_BIT(digit_1,SEGMENT_L); //l/
	(lcd_data+31)->bit.bit_6 = GET_DISP_DATA_BIT(digit_1,SEGMENT_M); //m/

	if(value>9)
	{	 
        (lcd_data+29)->bit.bit_5 = GET_DISP_DATA_BIT(digit_2,SEGMENT_A); //a/
        (lcd_data+30)->bit.bit_4 = GET_DISP_DATA_BIT(digit_2,SEGMENT_B); //b/
        (lcd_data+29)->bit.bit_1 = GET_DISP_DATA_BIT(digit_2,SEGMENT_C); //c/
        (lcd_data+29)->bit.bit_2 = GET_DISP_DATA_BIT(digit_2,SEGMENT_D); //d/
        (lcd_data+29)->bit.bit_3 = GET_DISP_DATA_BIT(digit_2,SEGMENT_E); //e/
        (lcd_data+29)->bit.bit_7 = GET_DISP_DATA_BIT(digit_2,SEGMENT_F); //f/
        (lcd_data+28)->bit.bit_3 = GET_DISP_DATA_BIT(digit_2,SEGMENT_G); //g/
        (lcd_data+28)->bit.bit_7 = GET_DISP_DATA_BIT(digit_2,SEGMENT_H); //h
        (lcd_data+28)->bit.bit_6 = GET_DISP_DATA_BIT(digit_2,SEGMENT_I); //i
        (lcd_data+28)->bit.bit_5 = GET_DISP_DATA_BIT(digit_2,SEGMENT_J); //j
        (lcd_data+28)->bit.bit_1 = GET_DISP_DATA_BIT(digit_2,SEGMENT_K); //k/
        (lcd_data+28)->bit.bit_2 = GET_DISP_DATA_BIT(digit_2,SEGMENT_L); //l/
        (lcd_data+29)->bit.bit_6 = GET_DISP_DATA_BIT(digit_2,SEGMENT_M); //m/

	}
	else 
	{
        (lcd_data+29)->bit.bit_5 = 0x00;
        (lcd_data+30)->bit.bit_4 = 0x00;
        (lcd_data+29)->bit.bit_1 = 0x00;
        (lcd_data+29)->bit.bit_2 = 0x00;
        (lcd_data+29)->bit.bit_3 = 0x00;
        (lcd_data+29)->bit.bit_7 = 0x00;
        (lcd_data+28)->bit.bit_3 = 0x00;
        (lcd_data+28)->bit.bit_7 = 0x00;
        (lcd_data+28)->bit.bit_6 = 0x00;
        (lcd_data+28)->bit.bit_5 = 0x00;
        (lcd_data+28)->bit.bit_1 = 0x00;
        (lcd_data+28)->bit.bit_2 = 0x00;
        (lcd_data+29)->bit.bit_6 = 0x00;
	}
	 
	if(digit_3)
    {
        (lcd_data+27)->bit.bit_2 = 0x1;
    }
    else
    {
        (lcd_data+27)->bit.bit_2 = 0x0;
    }
	 
}

/***********************************************************************************************************************
* Function Name: disable_segments_run_mode
* Description  : This function configures the segments that need to be unilluminated during discharging state
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void disable_segments_run_mode(LCD_DATA_BUFF *lcd_data)
{
    /********************************11***********************************/
	(lcd_data+32)->bit.bit_0 = 0; //A
	(lcd_data+34)->bit.bit_4 = 0;
	(lcd_data+34)->bit.bit_1 = 0;
	(lcd_data+34)->bit.bit_3 = 0;
	(lcd_data+33)->bit.bit_3 = 0;
	(lcd_data+32)->bit.bit_3 = 0;
	(lcd_data+32)->bit.bit_2 = 0;
	(lcd_data+32)->bit.bit_1 = 0;
	(lcd_data+33)->bit.bit_4 = 0;
	(lcd_data+33)->bit.bit_0 = 0;
	(lcd_data+33)->bit.bit_1 = 0;
	(lcd_data+34)->bit.bit_5 = 0;
	(lcd_data+33)->bit.bit_5 = 0;
	(lcd_data+34)->bit.bit_6 = 0;
	(lcd_data+33)->bit.bit_6 = 0;
	(lcd_data+33)->bit.bit_2 = 0;
	(lcd_data+33)->bit.bit_7 = 0;
	(lcd_data+34)->bit.bit_7 = 0;
	/********************************12***********************************/
	(lcd_data+36)->bit.bit_0 = 0;
	(lcd_data+36)->bit.bit_4 = 0;
	(lcd_data+36)->bit.bit_1 = 0;
	(lcd_data+36)->bit.bit_2 = 0;
	(lcd_data+36)->bit.bit_3 = 0;
	(lcd_data+35)->bit.bit_7 = 0;
	(lcd_data+34)->bit.bit_2 = 0;
	(lcd_data+34)->bit.bit_0 = 0;
	(lcd_data+35)->bit.bit_4 = 0;
	(lcd_data+35)->bit.bit_0 = 0;
	(lcd_data+35)->bit.bit_1 = 0;
	(lcd_data+36)->bit.bit_5 = 0;
	(lcd_data+35)->bit.bit_5 = 0;
	(lcd_data+36)->bit.bit_6 = 0;
	(lcd_data+35)->bit.bit_6 = 0;
	(lcd_data+35)->bit.bit_2 = 0;
	(lcd_data+35)->bit.bit_3 = 0;
	(lcd_data+36)->bit.bit_7 = 0;	
	/********************************13***********************************/
	(lcd_data+37)->bit.bit_4 = 0;
	(lcd_data+38)->bit.bit_0 = 0;
	(lcd_data+39)->bit.bit_5 = 0;
	(lcd_data+39)->bit.bit_7 = 0;
	(lcd_data+38)->bit.bit_7 = 0;
	(lcd_data+37)->bit.bit_7 = 0;
	(lcd_data+37)->bit.bit_6 = 0;
	(lcd_data+37)->bit.bit_5 = 0;
	(lcd_data+37)->bit.bit_0 = 0;
	(lcd_data+38)->bit.bit_4 = 0;
	(lcd_data+38)->bit.bit_5 = 0;
	(lcd_data+38)->bit.bit_1 = 0;
	(lcd_data+37)->bit.bit_1 = 0;
	(lcd_data+38)->bit.bit_2 = 0;
	(lcd_data+37)->bit.bit_2 = 0;
	(lcd_data+38)->bit.bit_6 = 0;
	(lcd_data+37)->bit.bit_3 = 0;
	(lcd_data+38)->bit.bit_3 = 0;
	/********************************14***********************************/
	(lcd_data+41)->bit.bit_4 = 0;
	(lcd_data+40)->bit.bit_0 = 0;
	(lcd_data+41)->bit.bit_5 = 0;
	(lcd_data+41)->bit.bit_6 = 0;
	(lcd_data+41)->bit.bit_7 = 0;
	(lcd_data+39)->bit.bit_3 = 0;
	(lcd_data+39)->bit.bit_6 = 0;
	(lcd_data+39)->bit.bit_4 = 0;
	(lcd_data+39)->bit.bit_0 = 0;
	(lcd_data+40)->bit.bit_4 = 0;
	(lcd_data+40)->bit.bit_5 = 0;
	(lcd_data+40)->bit.bit_1 = 0;
	(lcd_data+39)->bit.bit_1 = 0;
	(lcd_data+40)->bit.bit_2 = 0;
	(lcd_data+39)->bit.bit_2 = 0;
	(lcd_data+40)->bit.bit_6 = 0;
	(lcd_data+40)->bit.bit_7 = 0;
	(lcd_data+40)->bit.bit_3 = 0;
	/********************************15***********************************/
	(lcd_data+41)->bit.bit_0 = 0;
	(lcd_data+43)->bit.bit_4 = 0;
	(lcd_data+43)->bit.bit_1 = 0;
	(lcd_data+43)->bit.bit_3 = 0;
	(lcd_data+42)->bit.bit_3 = 0;
	(lcd_data+41)->bit.bit_3 = 0;
	(lcd_data+41)->bit.bit_2 = 0;
	(lcd_data+41)->bit.bit_1 = 0;
	(lcd_data+42)->bit.bit_4 = 0;
	(lcd_data+42)->bit.bit_0 = 0;
	(lcd_data+42)->bit.bit_1 = 0;
	(lcd_data+43)->bit.bit_5 = 0;
	(lcd_data+42)->bit.bit_5 = 0;
	(lcd_data+43)->bit.bit_6 = 0;
	(lcd_data+42)->bit.bit_6 = 0;
	(lcd_data+42)->bit.bit_2 = 0;
	(lcd_data+42)->bit.bit_7 = 0;
	(lcd_data+43)->bit.bit_7 = 0;
	/********************************16***********************************/
	(lcd_data+45)->bit.bit_0 = 0;
	(lcd_data+45)->bit.bit_4 = 0;
	(lcd_data+45)->bit.bit_1 = 0;
	(lcd_data+45)->bit.bit_2 = 0;
	(lcd_data+45)->bit.bit_3 = 0;
	(lcd_data+44)->bit.bit_7 = 0;
	(lcd_data+43)->bit.bit_2 = 0;
	(lcd_data+43)->bit.bit_0 = 0;
	(lcd_data+44)->bit.bit_4 = 0;
	(lcd_data+44)->bit.bit_0 = 0;
	(lcd_data+44)->bit.bit_1 = 0;
	(lcd_data+45)->bit.bit_5 = 0;
	(lcd_data+44)->bit.bit_5 = 0;
	(lcd_data+45)->bit.bit_6 = 0;
	(lcd_data+44)->bit.bit_6 = 0;
	(lcd_data+44)->bit.bit_2 = 0;
	(lcd_data+44)->bit.bit_3 = 0;
	(lcd_data+45)->bit.bit_7 = 0;
	/********************************17***********************************/
	(lcd_data+46)->bit.bit_4 = 0;
	(lcd_data+47)->bit.bit_0 = 0;
	(lcd_data+48)->bit.bit_5 = 0;
	(lcd_data+48)->bit.bit_7 = 0;
	(lcd_data+47)->bit.bit_7 = 0;
	(lcd_data+46)->bit.bit_7 = 0;
	(lcd_data+46)->bit.bit_6 = 0;
	(lcd_data+46)->bit.bit_5 = 0;
	(lcd_data+46)->bit.bit_0 = 0;
	(lcd_data+47)->bit.bit_4 = 0;
	(lcd_data+47)->bit.bit_5 = 0;
	(lcd_data+47)->bit.bit_1 = 0;
	(lcd_data+46)->bit.bit_1 = 0;
	(lcd_data+47)->bit.bit_2 = 0;
	(lcd_data+46)->bit.bit_2 = 0;
	(lcd_data+47)->bit.bit_6 = 0;
	(lcd_data+46)->bit.bit_3 = 0;
	(lcd_data+47)->bit.bit_3 = 0;
	/********************************18***********************************/
	(lcd_data+50)->bit.bit_7 = 0;
	(lcd_data+49)->bit.bit_0 = 0;
	(lcd_data+50)->bit.bit_6 = 0;
	(lcd_data+50)->bit.bit_5 = 0;
	(lcd_data+50)->bit.bit_4 = 0;
	(lcd_data+48)->bit.bit_3 = 0;
	(lcd_data+48)->bit.bit_6 = 0;
	(lcd_data+48)->bit.bit_4 = 0;
	(lcd_data+48)->bit.bit_0 = 0;
	(lcd_data+49)->bit.bit_4 = 0;
	(lcd_data+49)->bit.bit_5 = 0;
	(lcd_data+49)->bit.bit_1 = 0;
	(lcd_data+48)->bit.bit_1 = 0;
	(lcd_data+49)->bit.bit_2 = 0;
	(lcd_data+48)->bit.bit_2 = 0;
	(lcd_data+49)->bit.bit_6 = 0;
	(lcd_data+49)->bit.bit_7 = 0;
	(lcd_data+49)->bit.bit_3 = 0;
	/********************************19***********************************/
	(lcd_data+57)->bit.bit_0 = 0;
	(lcd_data+59)->bit.bit_4 = 0;
	(lcd_data+59)->bit.bit_1 = 0;
	(lcd_data+59)->bit.bit_3 = 0;
	(lcd_data+58)->bit.bit_3 = 0;
	(lcd_data+57)->bit.bit_3 = 0;
	(lcd_data+57)->bit.bit_2 = 0;
	(lcd_data+57)->bit.bit_1 = 0;
	(lcd_data+58)->bit.bit_4 = 0;
	(lcd_data+58)->bit.bit_0 = 0;
	(lcd_data+58)->bit.bit_1 = 0;
	(lcd_data+59)->bit.bit_5 = 0;
	(lcd_data+58)->bit.bit_5 = 0;
	(lcd_data+59)->bit.bit_6 = 0;
	(lcd_data+58)->bit.bit_6 = 0;
	(lcd_data+58)->bit.bit_2 = 0;
	(lcd_data+58)->bit.bit_7 = 0;
	(lcd_data+59)->bit.bit_7 = 0;
	/********************************20***********************************/
	(lcd_data+61)->bit.bit_0 = 0;
	(lcd_data+61)->bit.bit_4 = 0;
	(lcd_data+61)->bit.bit_1 = 0;
	(lcd_data+61)->bit.bit_2 = 0;
	(lcd_data+61)->bit.bit_3 = 0;
	(lcd_data+60)->bit.bit_7 = 0;
	(lcd_data+59)->bit.bit_2 = 0;
	(lcd_data+59)->bit.bit_0 = 0;
	(lcd_data+60)->bit.bit_4 = 0;
	(lcd_data+60)->bit.bit_0 = 0;
	(lcd_data+60)->bit.bit_1 = 0;
	(lcd_data+61)->bit.bit_5 = 0;
	(lcd_data+60)->bit.bit_5 = 0;
	(lcd_data+61)->bit.bit_6 = 0;
	(lcd_data+60)->bit.bit_6 = 0;
	(lcd_data+60)->bit.bit_2 = 0;
	(lcd_data+60)->bit.bit_3 = 0;
	(lcd_data+61)->bit.bit_7 = 0;
	/********************************21***********************************/
	(lcd_data+62)->bit.bit_4 = 0;
	(lcd_data+63)->bit.bit_0 = 0;
	(lcd_data+64)->bit.bit_5 = 0;
	(lcd_data+64)->bit.bit_7 = 0;
	(lcd_data+63)->bit.bit_7 = 0;
	(lcd_data+62)->bit.bit_7 = 0;
	(lcd_data+62)->bit.bit_6 = 0;
	(lcd_data+62)->bit.bit_5 = 0;
	(lcd_data+62)->bit.bit_0 = 0;
	(lcd_data+63)->bit.bit_4 = 0;
	(lcd_data+63)->bit.bit_5 = 0;
	(lcd_data+63)->bit.bit_1 = 0;
	(lcd_data+62)->bit.bit_1 = 0;
	(lcd_data+63)->bit.bit_2 = 0;
	(lcd_data+62)->bit.bit_2 = 0;
	(lcd_data+63)->bit.bit_6 = 0;
	(lcd_data+62)->bit.bit_3 = 0;
	(lcd_data+63)->bit.bit_3 = 0;
	/********************************22***********************************/
	(lcd_data+66)->bit.bit_4 = 0;
	(lcd_data+65)->bit.bit_0 = 0;
	(lcd_data+66)->bit.bit_5 = 0;
	(lcd_data+66)->bit.bit_6 = 0;
	(lcd_data+66)->bit.bit_7 = 0;
	(lcd_data+64)->bit.bit_3 = 0;
	(lcd_data+64)->bit.bit_6 = 0;
	(lcd_data+64)->bit.bit_4 = 0;
	(lcd_data+64)->bit.bit_0 = 0;
	(lcd_data+65)->bit.bit_4 = 0;
	(lcd_data+65)->bit.bit_5 = 0;
	(lcd_data+65)->bit.bit_1 = 0;
	(lcd_data+64)->bit.bit_1  = 0;
	(lcd_data+65)->bit.bit_2 = 0;
	(lcd_data+64)->bit.bit_2 = 0;
	(lcd_data+65)->bit.bit_6 = 0;
	(lcd_data+65)->bit.bit_7 = 0;
	(lcd_data+65)->bit.bit_3 = 0;
	/********************************23***********************************/
	(lcd_data+66)->bit.bit_0 = 0;
	(lcd_data+68)->bit.bit_4 = 0;
	(lcd_data+68)->bit.bit_1 = 0;
	(lcd_data+68)->bit.bit_3 = 0;
	(lcd_data+67)->bit.bit_3 = 0;
	(lcd_data+66)->bit.bit_3 = 0;
	(lcd_data+66)->bit.bit_2 = 0;
	(lcd_data+66)->bit.bit_1 = 0;
	(lcd_data+67)->bit.bit_4 = 0;
	(lcd_data+67)->bit.bit_0 = 0;
	(lcd_data+67)->bit.bit_1 = 0;
	(lcd_data+68)->bit.bit_5 = 0;
	(lcd_data+67)->bit.bit_5 = 0;
	(lcd_data+68)->bit.bit_6 = 0;
	(lcd_data+67)->bit.bit_6 = 0;
	(lcd_data+67)->bit.bit_2 = 0;
	(lcd_data+67)->bit.bit_7 = 0;
	(lcd_data+68)->bit.bit_7 = 0;
	/********************************24***********************************/
	(lcd_data+70)->bit.bit_0 = 0;
	(lcd_data+70)->bit.bit_4 = 0;
	(lcd_data+70)->bit.bit_1 = 0;
	(lcd_data+70)->bit.bit_2 = 0;
	(lcd_data+70)->bit.bit_3 = 0;
	(lcd_data+69)->bit.bit_7 = 0;
	(lcd_data+68)->bit.bit_2 = 0;
	(lcd_data+68)->bit.bit_0 = 0;
	(lcd_data+69)->bit.bit_4 = 0;
	(lcd_data+69)->bit.bit_0 = 0;
	(lcd_data+69)->bit.bit_1 = 0;
	(lcd_data+70)->bit.bit_5 = 0;
	(lcd_data+69)->bit.bit_5 = 0;
	(lcd_data+70)->bit.bit_6 = 0;
	(lcd_data+69)->bit.bit_6 = 0;
	(lcd_data+69)->bit.bit_2 = 0;
	(lcd_data+69)->bit.bit_3 = 0;
	(lcd_data+70)->bit.bit_7 = 0;
	/********************************25***********************************/
	(lcd_data+71)->bit.bit_4 = 0;
	(lcd_data+72)->bit.bit_0 = 0;
	(lcd_data+73)->bit.bit_5 = 0;
	(lcd_data+73)->bit.bit_7 = 0;
	(lcd_data+72)->bit.bit_7 = 0;
	(lcd_data+71)->bit.bit_7 = 0;
	(lcd_data+71)->bit.bit_6 = 0;
	(lcd_data+71)->bit.bit_5 = 0;
	(lcd_data+71)->bit.bit_0 = 0;
	(lcd_data+72)->bit.bit_4 = 0;
	(lcd_data+72)->bit.bit_5 = 0;
	(lcd_data+72)->bit.bit_1 = 0;
	(lcd_data+71)->bit.bit_1 = 0;
	(lcd_data+72)->bit.bit_2 = 0;
	(lcd_data+71)->bit.bit_2 = 0;
	(lcd_data+72)->bit.bit_6 = 0;
	(lcd_data+71)->bit.bit_3 = 0;
	(lcd_data+72)->bit.bit_3 = 0;
	/********************************26***********************************/
	(lcd_data+75)->bit.bit_4 = 0;
	(lcd_data+74)->bit.bit_0 = 0;
	(lcd_data+75)->bit.bit_5 = 0;
	(lcd_data+75)->bit.bit_6 = 0;
	(lcd_data+75)->bit.bit_7 = 0;
	(lcd_data+73)->bit.bit_3 = 0;
	(lcd_data+73)->bit.bit_6 = 0;
	(lcd_data+73)->bit.bit_4 = 0;
	(lcd_data+73)->bit.bit_0 = 0;
	(lcd_data+74)->bit.bit_4 = 0;
	(lcd_data+74)->bit.bit_5 = 0;
	(lcd_data+74)->bit.bit_1 = 0;
	(lcd_data+73)->bit.bit_1 = 0;
	(lcd_data+74)->bit.bit_2 = 0;
	(lcd_data+73)->bit.bit_2 = 0;
	(lcd_data+74)->bit.bit_6 = 0;
	(lcd_data+74)->bit.bit_7 = 0;
	(lcd_data+74)->bit.bit_3 = 0;
	/********************************27***********************************/
	(lcd_data+75)->bit.bit_0 = 0;
	(lcd_data+77)->bit.bit_4 = 0;
	(lcd_data+77)->bit.bit_1 = 0;
	(lcd_data+77)->bit.bit_3 = 0;
	(lcd_data+76)->bit.bit_3 = 0;
	(lcd_data+75)->bit.bit_3 = 0;
	(lcd_data+75)->bit.bit_2 = 0;
	(lcd_data+75)->bit.bit_1 = 0;
	(lcd_data+76)->bit.bit_4 = 0;
	(lcd_data+76)->bit.bit_0 = 0;
	(lcd_data+76)->bit.bit_1 = 0;
	(lcd_data+77)->bit.bit_5 = 0;
	(lcd_data+76)->bit.bit_5 = 0;
	(lcd_data+77)->bit.bit_6 = 0;
	(lcd_data+76)->bit.bit_6 = 0;
	(lcd_data+76)->bit.bit_2 = 0;
	(lcd_data+76)->bit.bit_7 = 0;
	(lcd_data+77)->bit.bit_7 = 0;
	/********************************28***********************************/
	(lcd_data+79)->bit.bit_0 = 0;
	(lcd_data+79)->bit.bit_4 = 0;
	(lcd_data+79)->bit.bit_1 = 0;
	(lcd_data+79)->bit.bit_2 = 0;
	(lcd_data+79)->bit.bit_3 = 0;
	(lcd_data+78)->bit.bit_7 = 0;
	(lcd_data+77)->bit.bit_2 = 0;
	(lcd_data+77)->bit.bit_0 = 0;
	(lcd_data+78)->bit.bit_4 = 0;
	(lcd_data+78)->bit.bit_0 = 0;
	(lcd_data+78)->bit.bit_1 = 0;
	(lcd_data+79)->bit.bit_5 = 0;
	(lcd_data+78)->bit.bit_5 = 0;
	(lcd_data+79)->bit.bit_6 = 0;
	(lcd_data+78)->bit.bit_6 = 0;
	(lcd_data+78)->bit.bit_2 = 0;
	(lcd_data+78)->bit.bit_3 = 0;
	(lcd_data+79)->bit.bit_7 = 0;
	/********************************29***********************************/
	(lcd_data+84)->bit.bit_4 = 0;
	(lcd_data+85)->bit.bit_0 = 0;
	(lcd_data+86)->bit.bit_5 = 0;
	(lcd_data+86)->bit.bit_7 = 0;
	(lcd_data+85)->bit.bit_7 = 0;
	(lcd_data+84)->bit.bit_7 = 0;
	(lcd_data+84)->bit.bit_6 = 0;
	(lcd_data+84)->bit.bit_5 = 0;
	(lcd_data+84)->bit.bit_0 = 0;
	(lcd_data+85)->bit.bit_4 = 0;
	(lcd_data+85)->bit.bit_5 = 0;
	(lcd_data+85)->bit.bit_1 = 0;
	(lcd_data+84)->bit.bit_1 = 0;
	(lcd_data+85)->bit.bit_2 = 0;
	(lcd_data+84)->bit.bit_2 = 0;
	(lcd_data+85)->bit.bit_6 = 0;
	(lcd_data+84)->bit.bit_3 = 0;
	(lcd_data+85)->bit.bit_3 = 0;
	/********************************30***********************************/
	(lcd_data+88)->bit.bit_4 = 0;
	(lcd_data+87)->bit.bit_0 = 0;
	(lcd_data+88)->bit.bit_5 = 0;
	(lcd_data+88)->bit.bit_6 = 0;
	(lcd_data+88)->bit.bit_7 = 0;
	(lcd_data+86)->bit.bit_3 = 0;
	(lcd_data+86)->bit.bit_6 = 0;
	(lcd_data+86)->bit.bit_4 = 0;
	(lcd_data+86)->bit.bit_0 = 0;
	(lcd_data+87)->bit.bit_4 = 0;
	(lcd_data+87)->bit.bit_5 = 0;
	(lcd_data+87)->bit.bit_1 = 0;
	(lcd_data+86)->bit.bit_1 = 0;
	(lcd_data+87)->bit.bit_2 = 0;
	(lcd_data+86)->bit.bit_2 = 0;
	(lcd_data+87)->bit.bit_6 = 0;
	(lcd_data+87)->bit.bit_7 = 0;
	(lcd_data+87)->bit.bit_3 = 0;
	/********************************31***********************************/
	(lcd_data+88)->bit.bit_0 = 0;
	(lcd_data+90)->bit.bit_4 = 0;
	(lcd_data+90)->bit.bit_1 = 0;
	(lcd_data+90)->bit.bit_3 = 0;
	(lcd_data+89)->bit.bit_3 = 0;
	(lcd_data+88)->bit.bit_3 = 0;
	(lcd_data+88)->bit.bit_2 = 0;
	(lcd_data+88)->bit.bit_1 = 0;
	(lcd_data+89)->bit.bit_4 = 0;
	(lcd_data+89)->bit.bit_0 = 0;
	(lcd_data+89)->bit.bit_1 = 0;
	(lcd_data+90)->bit.bit_5 = 0;
	(lcd_data+89)->bit.bit_5 = 0;
	(lcd_data+90)->bit.bit_6 = 0;
	(lcd_data+89)->bit.bit_6 = 0;
	(lcd_data+89)->bit.bit_2 = 0;
	(lcd_data+89)->bit.bit_7 = 0;
	(lcd_data+90)->bit.bit_7 = 0;
	/*******************************32************************************/
	(lcd_data+92)->bit.bit_0  = 0;
	(lcd_data+92)->bit.bit_4  = 0;
	(lcd_data+92)->bit.bit_1  = 0;
	(lcd_data+92)->bit.bit_2  = 0;
	(lcd_data+92)->bit.bit_3  = 0;
	(lcd_data+91)->bit.bit_7  = 0;
	(lcd_data+90)->bit.bit_2  = 0;
	(lcd_data+90)->bit.bit_0  = 0;
	(lcd_data+91)->bit.bit_4  = 0;
	(lcd_data+91)->bit.bit_0  = 0;
	(lcd_data+91)->bit.bit_1  = 0;
	(lcd_data+92)->bit.bit_5  = 0;
	(lcd_data+91)->bit.bit_5  = 0;
	(lcd_data+92)->bit.bit_6  = 0;
	(lcd_data+91)->bit.bit_6  = 0;
	(lcd_data+91)->bit.bit_2  = 0;
	(lcd_data+91)->bit.bit_3  = 0;
	(lcd_data+92)->bit.bit_7  = 0;	
}

/***********************************************************************************************************************
* Function Name: disable_segments_charging_mode
* Description  : This function configures the segments that need to be unilluminated during charging mode.
* Arguments    : lcd_data
* Return Value : None
***********************************************************************************************************************/
void disable_segments_charging_mode(LCD_DATA_BUFF *lcd_data)
{
    (lcd_data+11)->bit.bit_0 = 0x0;//X0 BAT SOC
    (lcd_data+27)->bit.bit_7 = 0x0;//T34%
    (lcd_data+100)->bit.bit_3 = 0x0;//T35 KM
    (lcd_data+101)->bit.bit_4 = 0x0;//X12 DTE
    /*******************************************************************
    mode
    ********************************************************************/
    (lcd_data+9)->bit.bit_4 = 0x0;//Mode_Line
    (lcd_data+9)->bit.bit_5 = 0x0;//T2	
    (lcd_data+9)->bit.bit_6 = 0x0;//T3
    (lcd_data+9)->bit.bit_7 = 0x0;//T4	

    /*********************************************************************
     speed
    **********************************************************************/
    (lcd_data+31)->bit.bit_5 = 0x00;
    (lcd_data+31)->bit.bit_0 = 0x00;
    (lcd_data+31)->bit.bit_1 = 0x00;
    (lcd_data+31)->bit.bit_2 = 0x00;
    (lcd_data+31)->bit.bit_3 = 0x00;
    (lcd_data+31)->bit.bit_7 = 0x00;
    (lcd_data+30)->bit.bit_3 = 0x00;
    (lcd_data+30)->bit.bit_7 = 0x00;
    (lcd_data+30)->bit.bit_6 = 0x00;
    (lcd_data+30)->bit.bit_5 = 0x00;
    (lcd_data+30)->bit.bit_1 = 0x00;
    (lcd_data+30)->bit.bit_2 = 0x00;
    (lcd_data+31)->bit.bit_6 = 0x00;

    (lcd_data+29)->bit.bit_5 = 0x00;
    (lcd_data+30)->bit.bit_4 = 0x00;
    (lcd_data+29)->bit.bit_1 = 0x00;
    (lcd_data+29)->bit.bit_2 = 0x00;
    (lcd_data+29)->bit.bit_3 = 0x00;
    (lcd_data+29)->bit.bit_7 = 0x00;
    (lcd_data+28)->bit.bit_3 = 0x00;
    (lcd_data+28)->bit.bit_7 = 0x00;
    (lcd_data+28)->bit.bit_6 = 0x00;
    (lcd_data+28)->bit.bit_5 = 0x00;
    (lcd_data+28)->bit.bit_1 = 0x00;
    (lcd_data+28)->bit.bit_2 = 0x00;
    (lcd_data+29)->bit.bit_6 = 0x00;

    (lcd_data+27)->bit.bit_2 = 0x0;
    /********************************************************************
     soc
    *********************************************************************/	 
    (lcd_data+11)->bit.bit_0 = 0x0;//X0 BAT SOC
    (lcd_data+27)->bit.bit_7 = 0x0;

    (lcd_data+26)->bit.bit_0 = 0x0;
    (lcd_data+27)->bit.bit_4 = 0x0;
    (lcd_data+27)->bit.bit_6 = 0x0;
    (lcd_data+26)->bit.bit_3 = 0x0;
    (lcd_data+26)->bit.bit_2 = 0x0;
    (lcd_data+26)->bit.bit_1 = 0x0;
    (lcd_data+27)->bit.bit_5 = 0x0;

    (lcd_data+25)->bit.bit_0 = 0x00;
    (lcd_data+26)->bit.bit_5 = 0x00;
    (lcd_data+26)->bit.bit_7 = 0x00;
    (lcd_data+25)->bit.bit_3 = 0x00;
    (lcd_data+25)->bit.bit_2 = 0x00;
    (lcd_data+25)->bit.bit_1 = 0x00;
    (lcd_data+26)->bit.bit_6 = 0x00;

    (lcd_data+26)->bit.bit_4 = 0x0;
    /*********************************************************************
     Range
    **********************************************************************/
    (lcd_data+100)->bit.bit_3 = 0;//T35 KM
    (lcd_data+101)->bit.bit_4 = 0;//X12 DTE

    (lcd_data+100)->bit.bit_4 =  0;
    (lcd_data+100)->bit.bit_0 =  0;
    (lcd_data+100)->bit.bit_2 =  0;
    (lcd_data+100)->bit.bit_7 =  0;
    (lcd_data+100)->bit.bit_6 =  0;
    (lcd_data+100)->bit.bit_5 =  0;
    (lcd_data+100)->bit.bit_1 =  0;

    (lcd_data+99)->bit.bit_4 = 0x00;
    (lcd_data+99)->bit.bit_1 = 0x00;
    (lcd_data+99)->bit.bit_3 = 0x00;
    (lcd_data+99)->bit.bit_7 = 0x00;
    (lcd_data+99)->bit.bit_6 = 0x00;
    (lcd_data+99)->bit.bit_5 = 0x00;
    (lcd_data+99)->bit.bit_2 = 0x00;
    (lcd_data+99)->bit.bit_0 = 0x0;
    /***********************************************************************
    RTC
    ************************************************************************/
    (lcd_data+105)->bit.bit_4 = 0x0;//COL :
    (lcd_data+106)->bit.bit_4 = 0x0;//T10  //rtc line
    (lcd_data+104)->bit.bit_4 = 0x0;//PM  //PM
    (lcd_data+103)->bit.bit_7 = 0x0;//AM  //am	

    (lcd_data+103)->bit.bit_3 =  0x0;
    (lcd_data+103)->bit.bit_6 =  0x0;
    (lcd_data+103)->bit.bit_4 =  0x0;
    (lcd_data+103)->bit.bit_0 =  0x0;
    (lcd_data+103)->bit.bit_1 =  0x0;
    (lcd_data+103)->bit.bit_2 =  0x0;
    (lcd_data+103)->bit.bit_5 =  0x0;

    (lcd_data+104)->bit.bit_3 =  0x0;
    (lcd_data+104)->bit.bit_7 =  0x0;
    (lcd_data+104)->bit.bit_5 =  0x0;
    (lcd_data+104)->bit.bit_0 =  0x0;
    (lcd_data+104)->bit.bit_1 =  0x0;
    (lcd_data+104)->bit.bit_2 =  0x0;
    (lcd_data+104)->bit.bit_6 =  0x0;

    (lcd_data+105)->bit.bit_3 =  0x0;
    (lcd_data+105)->bit.bit_7 =  0x0;
    (lcd_data+105)->bit.bit_5 =  0x0;
    (lcd_data+105)->bit.bit_0 =  0x0;
    (lcd_data+105)->bit.bit_1 =  0x0;
    (lcd_data+105)->bit.bit_2 =  0x0;
    (lcd_data+105)->bit.bit_6 =  0x0;

    (lcd_data+106)->bit.bit_3 =  0x0;
    (lcd_data+106)->bit.bit_7 =  0x0;
    (lcd_data+106)->bit.bit_5 =  0x0;
    (lcd_data+106)->bit.bit_0 =  0x0;
    (lcd_data+106)->bit.bit_1 =  0x0;
    (lcd_data+106)->bit.bit_2 =  0x0;
    (lcd_data+106)->bit.bit_6 =  0x0;
    /***********************************************************************
    location dist
    ************************************************************************/
    (lcd_data+96)->bit.bit_7 = 0x0;//DOT1
    (lcd_data+98)->bit.bit_3 = 0x0;//KM	

    /********************************************10********************************************************/
    (lcd_data+98)->bit.bit_5 = 0x0;
    (lcd_data+98)->bit.bit_1 = 0x0;
    (lcd_data+98)->bit.bit_2 = 0x0;
    (lcd_data+98)->bit.bit_7 = 0x0;
    (lcd_data+97)->bit.bit_3 = 0x0;
    (lcd_data+97)->bit.bit_2 = 0x0;
    (lcd_data+98)->bit.bit_6 = 0x0;
    /***************************************9**********************************************************/
    (lcd_data+96)->bit.bit_1 = 0x0;
    (lcd_data+97)->bit.bit_5 = 0x0;
    (lcd_data+97)->bit.bit_6 = 0x0;
    (lcd_data+96)->bit.bit_3 = 0x0;
    (lcd_data+96)->bit.bit_6 = 0x0;
    (lcd_data+96)->bit.bit_5 = 0x0;
    (lcd_data+96)->bit.bit_2 = 0x0;
    /******************************************************8******************************************/
    (lcd_data+95)->bit.bit_5 = 0x0;
    (lcd_data+95)->bit.bit_2 = 0x0;
    (lcd_data+95)->bit.bit_3 = 0x0;
    (lcd_data+95)->bit.bit_7 = 0x0;
    (lcd_data+94)->bit.bit_3 = 0x0;
    (lcd_data+94)->bit.bit_2 = 0x0;
    (lcd_data+95)->bit.bit_6 = 0x0;
    /*************************************************7************************************************/
    (lcd_data+93)->bit.bit_1 = 0x0;
    (lcd_data+94)->bit.bit_6 = 0x0;
    (lcd_data+94)->bit.bit_7 = 0x0;
    (lcd_data+93)->bit.bit_3 = 0x0;
    (lcd_data+93)->bit.bit_7 = 0x0;
    (lcd_data+93)->bit.bit_6 = 0x0;
    (lcd_data+93)->bit.bit_2 = 0x0;
    /*********************************************************************
    odo meter
    **********************************************************************/
    (lcd_data+57)->bit.bit_4 = 0x0;
    (lcd_data+56)->bit.bit_7 = 0x0;

    /************************6segment**************************/
    (lcd_data+56)->bit.bit_0 = 0x0;
    (lcd_data+57)->bit.bit_5 = 0x0;
    (lcd_data+57)->bit.bit_7 = 0x0;
    (lcd_data+56)->bit.bit_3 = 0x0;
    (lcd_data+56)->bit.bit_2 = 0x0;
    (lcd_data+56)->bit.bit_1 = 0x0;
    (lcd_data+57)->bit.bit_6 = 0x0;
    /**********************************5segment****************************/
    (lcd_data+55)->bit.bit_0 = 0x0;
    (lcd_data+56)->bit.bit_4 = 0x0; 
    (lcd_data+56)->bit.bit_6 = 0x0;
    (lcd_data+55)->bit.bit_3 = 0x0;
    (lcd_data+55)->bit.bit_2 = 0x0;
    (lcd_data+55)->bit.bit_1 = 0x0;
    (lcd_data+56)->bit.bit_5 = 0x0;
    /**********************************4segment*****************************/
    (lcd_data+54)->bit.bit_0 = 0x0;	
    (lcd_data+55)->bit.bit_5 = 0x0;
    (lcd_data+55)->bit.bit_7 = 0x0;
    (lcd_data+54)->bit.bit_3 = 0x0;
    (lcd_data+54)->bit.bit_2 = 0x0;
    (lcd_data+54)->bit.bit_1 = 0x0;
    (lcd_data+55)->bit.bit_6 = 0x0;
    /*********************************3segment********************************/
    (lcd_data+53)->bit.bit_0 = 0x0;
    (lcd_data+54)->bit.bit_5 = 0x0;
    (lcd_data+54)->bit.bit_7 = 0x0;
    (lcd_data+53)->bit.bit_3 = 0x0;
    (lcd_data+53)->bit.bit_2 = 0x0;
    (lcd_data+53)->bit.bit_1 = 0x0;
    (lcd_data+54)->bit.bit_6 = 0x0;
    /*********************************3segment********************************/
    (lcd_data+52)->bit.bit_0 = 0x0;
    (lcd_data+53)->bit.bit_5 =0x0;
    (lcd_data+53)->bit.bit_7 = 0x0;
    (lcd_data+52)->bit.bit_3 = 0x0;
    (lcd_data+52)->bit.bit_2	= 0x0;
    (lcd_data+52)->bit.bit_1 = 0x0;
    (lcd_data+53)->bit.bit_6 = 0x0;
    /*********************************1segment********************************/
    (lcd_data+51)->bit.bit_0 = 0x0;
    (lcd_data+52)->bit.bit_5 = 0x0;
    (lcd_data+52)->bit.bit_7 = 0x0;
    (lcd_data+51)->bit.bit_3 = 0x0;
    (lcd_data+51)->bit.bit_2 = 0x0;
    (lcd_data+51)->bit.bit_1 = 0x0;
    (lcd_data+52)->bit.bit_6 = 0x0;
    /**********************************0segment*******************************/
    (lcd_data+50)->bit.bit_0 = 0x0;
    (lcd_data+51)->bit.bit_5 = 0x0;
    (lcd_data+51)->bit.bit_7 = 0x0;
    (lcd_data+50)->bit.bit_3 = 0x0;
    (lcd_data+50)->bit.bit_2 = 0x0;
    (lcd_data+50)->bit.bit_1 = 0x0;
    (lcd_data+51)->bit.bit_6 = 0x0;
    /**********************************************************************
    Trip meter
    ***********************************************************************/
    (lcd_data+82)->bit.bit_3 = 0x0;
    (lcd_data+80)->bit.bit_0 = 0x0;
    /***************************************3segment*********************************************/
    (lcd_data+83)->bit.bit_4 = 0x0;
    (lcd_data+83)->bit.bit_1 = 0x0;
    (lcd_data+83)->bit.bit_3 = 0x0;
    (lcd_data+83)->bit.bit_7 = 0x0;
    (lcd_data+83)->bit.bit_6 = 0x0;
    (lcd_data+83)->bit.bit_5 = 0x0;
    (lcd_data+83)->bit.bit_2 = 0x0;
    /****************************************2segment*******************************************/
    (lcd_data+82)->bit.bit_4 = 0x0;
    (lcd_data+82)->bit.bit_0 = 0x0;
    (lcd_data+82)->bit.bit_2 = 0x0;
    (lcd_data+82)->bit.bit_7 = 0x0;
    (lcd_data+82)->bit.bit_6 = 0x0;
    (lcd_data+82)->bit.bit_5 = 0x0;
    (lcd_data+82)->bit.bit_1 = 0x0;
    /************************************1segment****************************************************/
    (lcd_data+81)->bit.bit_4 = 0x0;
    (lcd_data+81)->bit.bit_1 = 0x0;
    (lcd_data+81)->bit.bit_3 = 0x0;
    (lcd_data+81)->bit.bit_7 = 0x0;
    (lcd_data+81)->bit.bit_6 = 0x0;
    (lcd_data+81)->bit.bit_5 = 0x0;
    (lcd_data+81)->bit.bit_2 = 0x0;
    /**************************************0segment***********************************************/
    (lcd_data+80)->bit.bit_4 = 0x0;
    (lcd_data+80)->bit.bit_1 = 0x0;
    (lcd_data+80)->bit.bit_3 = 0x0;
    (lcd_data+80)->bit.bit_7 = 0x0;
    (lcd_data+80)->bit.bit_6 = 0x0;
    (lcd_data+80)->bit.bit_5 = 0x0;
    (lcd_data+80)->bit.bit_2 = 0x0;
}


/***********************************************************************************************************************
* Function Name: battery_charging_telltale
* Description  : This function configures the segments/telltales that need to be illuminated in charging state.
* Arguments    : lcd_data, status of battery
* Return Value : None
***********************************************************************************************************************/
void battery_charging_telltale(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    if( status == ON)
	{		
		(lcd_data+29)->bit.bit_4 = 0x01;//T19 BATTERY
		(lcd_data+32)->bit.bit_5 = 0x01;//T29 %
		(lcd_data+32)->bit.bit_6 = 0x00;//T28 kmph
		(lcd_data+31)->bit.bit_4 = 0x00;//T22 SPEED
		(lcd_data+107)->bit.bit_7 = 0x1;//T7 chrging symbol
	}
	else
	{
		(lcd_data+29)->bit.bit_4 = 0x00;//T19 BATTERY
		(lcd_data+32)->bit.bit_5 = 0x00;//T29 %
		(lcd_data+32)->bit.bit_6 = 0x01;//T28 kmph
		(lcd_data+31)->bit.bit_4 = 0x01;//T22 SPEED
		(lcd_data+107)->bit.bit_7 = 0x0;//T7 chrging symbol
	}
}

void battery_chrg_Animation(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    if( status == ON)
	{
        (lcd_data+29)->bit.bit_4 = 0x01;//T19 BATTERY
        (lcd_data+32)->bit.bit_5 = 0x01;//T29 %
        (lcd_data+107)->bit.bit_7 = 0x1;//T7 chrging symbol
    }
}

/***********************************************************************************************************************
* Function Name: reverse_telltale
* Description  : This function configures the segments/telltales that need to be illuminated as the reverse mode.
* Arguments    : lcd_Data, status of reverse
* Return Value : None
***********************************************************************************************************************/
void reverse_telltale(LCD_DATA_BUFF *lcd_data, uint8_t reverse)
{
	if(reverse)
	{
		//(lcd_data+9)->bit.bit_0  = 0x1;//T5 TOP LINE
        //(lcd_data+28)->bit.bit_4 = 0x1;//T18 BOTTAM LINE
		(lcd_data+10)->bit.bit_4 = 0x1;//T17 REVERSE
	}
	else
	{
		(lcd_data+10)->bit.bit_4 = 0x0;//T17 REVERSE
	}
}

/***********************************************************************************************************************
* Function Name: right_indicator_telltile
* Description  : This function configures the segments/telltales that need to be illuminated as the right indicator.
* Arguments    : lcd_Data , status of indicator
* Return Value : None
***********************************************************************************************************************/
void right_indicator_telltile(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
	(lcd_data+107)->bit.bit_5 = status;
}

/***********************************************************************************************************************
* Function Name: left_indicator_telltile
* Description  : This function configures the segments/telltales that need to be illuminated as the left indicator.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void left_indicator_telltile(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
	(lcd_data+107)->bit.bit_3 = status;
}

/***********************************************************************************************************************
* Function Name: break_fluid_led_control
* Description  : This function configures the led that need to be illuminated as the brake fluid indicator.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void break_fluid_led_control(uint8_t status)
{
    BRAKE_FLUID_LED=status;
}

/***********************************************************************************************************************
* Function Name: parking_led_control
* Description  : This function configures the led that need to be illuminated as the parking indicator.
* Arguments    : status of parking
* Return Value : None
***********************************************************************************************************************/
void parking_led_control(uint8_t status)
{
    PARKING_LED=status;    
}

/***********************************************************************************************************************
* Function Name: ready_indication
* Description  : This function configures the segments that need to be illuminated for the ready indication
* Arguments    : lcd_data, status of ready symbol
* Return Value : None
***********************************************************************************************************************/
void ready_indication(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    (lcd_data+107)->bit.bit_1 = status;//T21
    (lcd_data+107)->bit.bit_2 = status;//T20	
}

/***********************************************************************************************************************
* Function Name: thermal_runaway_indication
* Description  : This function configures the segments that need to be illuminated for the thermal runaway indication.
* Arguments    : lcd_data, status of thermal runaway condition
* Return Value : None
***********************************************************************************************************************/
void thermal_runaway_indication(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
	
    if(status)
    {
	    //(lcd_data+9)->bit.bit_0  = 0x1;//T5 TOP LINE
        //(lcd_data+28)->bit.bit_4 = 0x1;//T18 BOTTAM LINE
        (lcd_data+9)->bit.bit_1  = 0x01;//T15 THERMAL
        
    }
    else
    {
        (lcd_data+9)->bit.bit_1 = 0x00;	
    }
}

/***********************************************************************************************************************
* Function Name: side_stand_indication
* Description  : This function configures the segments that need to be illuminated for the side stand.
* Arguments    : lcd_Data, status of side stand
* Return Value : None
***********************************************************************************************************************/
void side_stand_indication(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    if(status)
    {
        (lcd_data+10)->bit.bit_5     = 0x1;//T16 SIDESTAND
        //(lcd_data+9)->bit.bit_0      = 0x1;//T5 TOP LINE
        //(lcd_data+28)->bit.bit_4     = 0x1;//T18 BOTTAM LINE
    }
    else
    {
        (lcd_data+10)->bit.bit_5 = 0x0;	
    }
}
	

/***********************************************************************************************************************
* Function Name: throttle_on_indication
* Description  : This function configures the segments that need to be illuminated for the throttle.
* Arguments    : lcd_Data, status of throttle
* Return Value : None
***********************************************************************************************************************/
void throttle_on_indication(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    if(status)
    {
        (lcd_data+9)->bit.bit_2  = 0x1;//T14 THROTTLE
        //(lcd_data+9)->bit.bit_0  = 0x1;//T5 TOP LINE
        //(lcd_data+28)->bit.bit_4 = 0x1;//T18 BOTTAM LINE
    }
    else
    {
        (lcd_data+9)->bit.bit_2 = 0x0;
    }
}

/***********************************************************************************************************************
* Function Name: battery_on_indication
* Description  : This function configures the segments that need to be illuminated for the battery telltale.
* Arguments    : lcd_Data, status of battery telltale
* Return Value : None
***********************************************************************************************************************/
void battery_on_indication(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    if(status)
    {
        (lcd_data+10)->bit.bit_6 = 0x1;//T13 BATTERY
        //(lcd_data+9)->bit.bit_0 = 0x1;//T5 TOP LINE
        //(lcd_data+28)->bit.bit_4 = 0x1;//T18 BOTTAM LINE
    }
    else
    {
        (lcd_data+10)->bit.bit_6  = 0x0;
    }
}

/***********************************************************************************************************************
* Function Name: temp_on_indication
* Description  :This function configures the segments that need to be illuminated for the temperature telltale.
* Arguments    : lcd_Data, status of temperature symbol
* Return Value : None
***********************************************************************************************************************/
void temp_on_indication(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    if(status)
    {
        (lcd_data+9)->bit.bit_3 = 0x1;//T12 temp
       // (lcd_data+9)->bit.bit_0 = 0x1;//T5 TOP LINE
        //(lcd_data+28)->bit.bit_4 = 0x1;//T18 BOTTAM LINE
    }
    else
    {
        (lcd_data+9)->bit.bit_3 = 0x0;//T12 temp
    }
}

/***********************************************************************************************************************
* Function Name: service_on_indication
* Description  : This function configures the segments that need to be illuminated for the service telltale.
* Arguments    : lcd_Data, status of service indication telltale
* Return Value : None
***********************************************************************************************************************/
void service_on_indication(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    if(status)
    {
        (lcd_data+10)->bit.bit_7 = 0x1;//T11 SERIVCE
        //(lcd_data+9)->bit.bit_0 = 0x1;//T5 TOP LINE
        //(lcd_data+28)->bit.bit_4 = 0x1;//T18 BOTTAM LINE
    }
    else
    {
        (lcd_data+10)->bit.bit_7  = 0x0;
    }
}

/***********************************************************************************************************************
* Function Name: brake_on_indication
* Description  : 
* Arguments    : lcd_Data
* Return Value : None
***********************************************************************************************************************/
void brake_on_indication(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    (lcd_data+102)->bit.bit_2 = status;
}

/***********************************************************************************************************************
* Function Name: warning_indication
* Description  : 
* Arguments    : lcd_Data
* Return Value : None
***********************************************************************************************************************/
void warning_indication(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    (lcd_data+102)->bit.bit_1 = status;
}

void top_bottom_line(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    if(status)
    {
        (lcd_data+9)->bit.bit_0 = 0x1;//T5 TOP LINE
        (lcd_data+28)->bit.bit_4 = 0x1;//T18 BOTTAM LINE
    }
    else
    {
        (lcd_data+9)->bit.bit_0 = 0x0;//T5 TOP LINE
        (lcd_data+28)->bit.bit_4 = 0x0;//T18 BOTTAM LINE
    }
} 
/***********************************************************************************************************************
* Function Name: clear_all_error_indications
* Description  : 
* Arguments    : lcd_Data
* Return Value : None
***********************************************************************************************************************/
void clear_all_error_indications(LCD_DATA_BUFF *lcd_data)
{
    (lcd_data+9)->bit.bit_0  = 0x0;// TOP LINE
    (lcd_data+9)->bit.bit_1  = 0x00;// TEMP
    (lcd_data+28)->bit.bit_4 = 0x0;// BOTTAM LINE
    (lcd_data+10)->bit.bit_7 = 0x0;// SERIVCE
    (lcd_data+9)->bit.bit_1  = 0x0;// THERMAL
    (lcd_data+10)->bit.bit_6 = 0x0;// BATTERY
    (lcd_data+9)->bit.bit_2  = 0x0;// THROTTLE
    (lcd_data+10)->bit.bit_5 = 0x0;// SIDESTAND
}

/***********************************************************************************************************************
* Function Name: error_indication_txt_logic
* Description  : 
* Arguments    : lcd_Data
* Return Value : None
***********************************************************************************************************************/
void error_indication_txt_logic(uint8_t digit, uint8_t digit_pos, LCD_DATA_BUFF *lcd_data)
{
    
    switch (digit_pos)
    {
        case TXT_POS_1	:	(lcd_data+32)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+34)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); 
                            (lcd_data+34)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); 
                            (lcd_data+34)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); 
                            (lcd_data+33)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); 
                            (lcd_data+32)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); 
                            (lcd_data+32)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); 
                            (lcd_data+32)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); 
                            (lcd_data+33)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); 
                            (lcd_data+33)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); 
                            (lcd_data+33)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); 
                            (lcd_data+34)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); 
                            (lcd_data+33)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); 
                            (lcd_data+34)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); 
                            (lcd_data+33)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); 
                            (lcd_data+33)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); 
                            (lcd_data+33)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); 
                            (lcd_data+34)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); 
                            break;
        case TXT_POS_2	:	(lcd_data+36)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); 
                            (lcd_data+36)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); 
                            (lcd_data+36)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); 
                            (lcd_data+36)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); 
                            (lcd_data+36)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); 
                            (lcd_data+35)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); 
                            (lcd_data+34)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); 
                            (lcd_data+34)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); 
                            (lcd_data+35)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); 
                            (lcd_data+35)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); 
                            (lcd_data+35)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); 
                            (lcd_data+36)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); 
                            (lcd_data+35)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); 
                            (lcd_data+36)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); 
                            (lcd_data+35)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); 
                            (lcd_data+35)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); 
                            (lcd_data+35)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); 
                            (lcd_data+36)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); 
                            break;
        case TXT_POS_3	:	(lcd_data+37)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); 
                            (lcd_data+38)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); 
                            (lcd_data+39)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); 
                            (lcd_data+39)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); 
                            (lcd_data+38)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); 
                            (lcd_data+37)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); 
                            (lcd_data+37)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); 
                            (lcd_data+37)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); 
                            (lcd_data+37)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); 
                            (lcd_data+38)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); 
                            (lcd_data+38)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); 
                            (lcd_data+38)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); 
                            (lcd_data+37)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); 
                            (lcd_data+38)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); 
                            (lcd_data+37)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); 
                            (lcd_data+38)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); 
                            (lcd_data+37)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); 
                            (lcd_data+38)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); 
                            break;
        case TXT_POS_4	:	(lcd_data+41)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+40)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+41)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+41)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+41)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+39)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+39)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+39)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+39)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+40)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+40)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+40)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+39)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+40)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+39)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+40)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+40)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+40)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_5	:	(lcd_data+41)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+43)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+43)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+43)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+42)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+41)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+41)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+41)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+42)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+42)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+42)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+43)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+42)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+43)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+42)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+42)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+42)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+43)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R 
                            break;
        case TXT_POS_6	:	(lcd_data+45)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+45)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+45)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+45)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+45)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+44)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+43)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+43)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+44)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+44)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+44)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+45)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+44)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+45)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+44)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+44)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+44)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+45)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R	
                            break;
        case TXT_POS_7	:	(lcd_data+46)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+47)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+48)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+48)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+47)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+46)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+46)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+46)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+46)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+47)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+47)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+47)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+46)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+47)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+46)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+47)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+46)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+47)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_8	:	(lcd_data+50)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+49)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+50)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+50)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+50)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+48)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+48)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+48)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+48)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+49)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+49)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+49)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+48)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+49)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+48)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+49)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+49)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+49)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_9	:	(lcd_data+57)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+59)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+59)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+59)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+58)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+57)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+57)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+57)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+58)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+58)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+58)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+59)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+58)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+59)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+58)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+58)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+58)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+59)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_10	:	(lcd_data+61)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+61)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+61)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+61)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+61)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+60)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+59)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+59)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+60)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+60)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+60)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+61)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+60)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+61)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+60)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+60)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+60)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+61)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_11	:	(lcd_data+62)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+63)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+64)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+64)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+63)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+62)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+62)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+62)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+62)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+63)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+63)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+63)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+62)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+63)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+62)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+63)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+62)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+63)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_12	:	(lcd_data+66)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+65)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+66)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+66)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+66)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+64)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //
                            (lcd_data+64)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+64)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+64)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+65)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+65)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+65)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+64)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+65)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+64)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+65)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+65)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+65)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_13	:	(lcd_data+66)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+68)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+68)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+68)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+67)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+66)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+66)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+66)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+67)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+67)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+67)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+68)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+67)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+68)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+67)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+67)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+67)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+68)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_14	:	(lcd_data+70)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+70)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+70)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+70)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+70)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+69)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+68)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+68)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+69)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+69)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+69)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+70)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+69)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+70)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+69)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+69)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+69)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+70)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_15	:	(lcd_data+71)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+72)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+73)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+73)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+72)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+71)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+71)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+71)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+71)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+72)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+72)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+72)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+71)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+72)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+71)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+72)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+71)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+72)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_16	:	(lcd_data+75)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+74)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+75)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+75)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+75)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+73)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+73)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+73)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+73)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+74)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+74)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+74)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+73)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+74)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+73)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+74)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+74)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+74)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_17	:	(lcd_data+75)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+77)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+77)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+77)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+76)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+75)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+75)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+75)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+76)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+76)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+76)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+77)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+76)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+77)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+76)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+76)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+76)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+77)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_18	:	(lcd_data+79)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+79)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+79)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+79)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+79)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+78)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+77)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+77)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+78)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+78)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+78)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+79)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+78)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+79)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+78)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+78)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+78)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+79)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_19	:	(lcd_data+84)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); //A
                            (lcd_data+85)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); //B
                            (lcd_data+86)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); //C
                            (lcd_data+86)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); //D
                            (lcd_data+85)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); //E
                            (lcd_data+84)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); //F
                            (lcd_data+84)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); //G
                            (lcd_data+84)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); //H
                            (lcd_data+84)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); //I
                            (lcd_data+85)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); //J
                            (lcd_data+85)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); //K
                            (lcd_data+85)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); //L
                            (lcd_data+84)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); //M
                            (lcd_data+85)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); //N
                            (lcd_data+84)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); //O
                            (lcd_data+85)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); //P
                            (lcd_data+84)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); //Q
                            (lcd_data+85)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); //R
                            break;
        case TXT_POS_20	:	(lcd_data+88)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); 
                            (lcd_data+87)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); 
                            (lcd_data+88)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); 
                            (lcd_data+88)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); 
                            (lcd_data+88)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); 
                            (lcd_data+86)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); 
                            (lcd_data+86)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); 
                            (lcd_data+86)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); 
                            (lcd_data+86)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); 
                            (lcd_data+87)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); 
                            (lcd_data+87)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); 
                            (lcd_data+87)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); 
                            (lcd_data+86)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); 
                            (lcd_data+87)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); 
                            (lcd_data+86)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); 
                            (lcd_data+87)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); 
                            (lcd_data+87)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); 
                            (lcd_data+87)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); 
                            break;
        case TXT_POS_21	:	(lcd_data+88)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); 
                            (lcd_data+90)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); 
                            (lcd_data+90)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); 
                            (lcd_data+90)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); 
                            (lcd_data+89)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); 
                            (lcd_data+88)->bit.bit_3 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); 
                            (lcd_data+88)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); 
                            (lcd_data+88)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); 
                            (lcd_data+89)->bit.bit_4 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); 
                            (lcd_data+89)->bit.bit_0 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); 
                            (lcd_data+89)->bit.bit_1 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); 
                            (lcd_data+90)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); 
                            (lcd_data+89)->bit.bit_5 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); 
                            (lcd_data+90)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); 
                            (lcd_data+89)->bit.bit_6 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); 
                            (lcd_data+89)->bit.bit_2 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); 
                            (lcd_data+89)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); 
                            (lcd_data+90)->bit.bit_7 = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); 
                            break;
        case TXT_POS_22	:	(lcd_data+92)->bit.bit_0  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_A); 
                            (lcd_data+92)->bit.bit_4  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_B); 
                            (lcd_data+92)->bit.bit_1  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_C); 
                            (lcd_data+92)->bit.bit_2  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_D); 
                            (lcd_data+92)->bit.bit_3  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_E); 
                            (lcd_data+91)->bit.bit_7  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_F); 
                            (lcd_data+90)->bit.bit_2  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_G); 
                            (lcd_data+90)->bit.bit_0  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_H); 
                            (lcd_data+91)->bit.bit_4  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_I); 
                            (lcd_data+91)->bit.bit_0  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_J); 
                            (lcd_data+91)->bit.bit_1  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_K); 
                            (lcd_data+92)->bit.bit_5  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_L); 
                            (lcd_data+91)->bit.bit_5  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_M); 
                            (lcd_data+92)->bit.bit_6  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_N); 
                            (lcd_data+91)->bit.bit_6  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_O); 
                            (lcd_data+91)->bit.bit_2  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_P); 
                            (lcd_data+91)->bit.bit_3  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_Q); 
                            (lcd_data+92)->bit.bit_7  = ABC_GET_DISP_DATA_BIT(digit,SEGMENT_R); 
                            break;


        
        default:
            break;
    }
}

/***********************************************************************************************************************
* Function Name: error_indication_txt_to_segment_conversion
* Description  : 
* Arguments    : lcd_Data
* Return Value : None
***********************************************************************************************************************/
void error_indication_txt_to_segment_conversion(LCD_DATA_BUFF *lcd_data, char *str)
{
	uint8_t i;
    for(i=1;i<=MAX_TXT_POS;i++)
    {
        switch(*(str+i))
        {
            case ' ': error_indication_txt_logic(BLANK, i, lcd_data); break;
            case 'A': error_indication_txt_logic(TXT_A, i, lcd_data); break;
            case 'B': error_indication_txt_logic(TXT_B, i, lcd_data); break;
            case 'C': error_indication_txt_logic(TXT_C, i, lcd_data); break;
            case 'D': error_indication_txt_logic(TXT_D, i, lcd_data); break;
            case 'E': error_indication_txt_logic(TXT_E, i, lcd_data); break;
            case 'F': error_indication_txt_logic(TXT_F, i, lcd_data); break;
            case 'G': error_indication_txt_logic(TXT_G, i, lcd_data); break;
            case 'H': error_indication_txt_logic(TXT_H, i, lcd_data); break;
            case 'I': error_indication_txt_logic(TXT_I, i, lcd_data); break;
            case 'J': error_indication_txt_logic(TXT_J, i, lcd_data); break;
            case 'K': error_indication_txt_logic(TXT_K, i, lcd_data); break;
            case 'L': error_indication_txt_logic(TXT_L, i, lcd_data); break;
            case 'M': error_indication_txt_logic(TXT_M, i, lcd_data); break;
            case 'N': error_indication_txt_logic(TXT_N, i, lcd_data); break;
            case 'O': error_indication_txt_logic(TXT_O, i, lcd_data); break;
            case 'P': error_indication_txt_logic(TXT_P, i, lcd_data); break;
            case 'Q': error_indication_txt_logic(TXT_Q, i, lcd_data); break;
            case 'R': error_indication_txt_logic(TXT_R, i, lcd_data); break;
            case 'S': error_indication_txt_logic(TXT_S, i, lcd_data); break;
            case 'T': error_indication_txt_logic(TXT_T, i, lcd_data); break;
            case 'U': error_indication_txt_logic(TXT_U, i, lcd_data); break;
            case 'V': error_indication_txt_logic(TXT_V, i, lcd_data); break;
            case 'W': error_indication_txt_logic(TXT_W, i, lcd_data); break;
            case 'X': error_indication_txt_logic(TXT_X, i, lcd_data); break;
            case 'Y': error_indication_txt_logic(TXT_Y, i, lcd_data); break;
            case 'Z': error_indication_txt_logic(TXT_Z, i, lcd_data); break;
			case '0': error_indication_txt_logic(NUM_0, i, lcd_data); break;
            case '1': error_indication_txt_logic(NUM_1, i, lcd_data); break;
            case '2': error_indication_txt_logic(NUM_2, i, lcd_data); break;
            case '3': error_indication_txt_logic(NUM_3, i, lcd_data); break;
            case '4': error_indication_txt_logic(NUM_4, i, lcd_data); break;
            case '5': error_indication_txt_logic(NUM_5, i, lcd_data); break;
            case '6': error_indication_txt_logic(NUM_6, i, lcd_data); break;
            case '7': error_indication_txt_logic(NUM_7, i, lcd_data); break;
            case '8': error_indication_txt_logic(NUM_8, i, lcd_data); break;
            case '9': error_indication_txt_logic(NUM_9, i, lcd_data); break;
            case '+': error_indication_txt_logic(NUM_PLUS, i, lcd_data); break;
            case '-': error_indication_txt_logic(NUM_MINUS, i, lcd_data); break;
            case '*': error_indication_txt_logic(NUM_MULTIPLY, i, lcd_data); break;
            case '/': error_indication_txt_logic(NUM_DIVIDE, i, lcd_data); break;
            case '=': error_indication_txt_logic(NUM_EQUAL, i, lcd_data); break;
	    case '.': error_indication_txt_logic(NUM_DOT, i, lcd_data); break;
            
            
        }

    }
    
}


/***********************************************************************************************************************
* Function Name: error_indiction_text
* Description  : this function is to display the respective error in the alphanumeric area.
* Arguments    : lcd_data, error
* Return Value : None
***********************************************************************************************************************/
void error_indiction_text(LCD_DATA_BUFF *lcd_data, uint8_t error)
{
	switch(error)
	{	
        case MCU_ERROR_TXT : ///Battery full
            error_indication_txt_to_segment_conversion(lcd_data,"       MCU ERROR      ");
            break;        
        case MOTOR_ERROR_TXT : ///Battery full
            error_indication_txt_to_segment_conversion(lcd_data,"      MOTOR ERROR     ");
            break;
        case LIMP_MODE_HOME_TXT : ///Battery full
            error_indication_txt_to_segment_conversion(lcd_data,"     LIMP HOME MODE   ");
            break;
        case MCU_LOCKED_TXT : ///Battery full
            error_indication_txt_to_segment_conversion(lcd_data,"       MCU LOCKED     ");
            break;
        case BATTERY_FULL_TXT : ///Battery full
            error_indication_txt_to_segment_conversion(lcd_data,"      BATTERY FULL    ");
            break;
        case BATTERY_LOW_TXT : ///Battery full
            error_indication_txt_to_segment_conversion(lcd_data,"      BATTERY LOW     ");
            break;
        //case MCU_VALUE_ERROR_TXT : ///Battery full
        //    error_indication_txt_to_segment_conversion(lcd_data,"      SPEED ERROR     ");
        //    break;

        case CLEAR_TXT : ///Battery full
            error_indication_txt_to_segment_conversion(lcd_data,"                       ");
            break;
	}
}

void Animation_text(LCD_DATA_BUFF *lcd_data, char *str)
{
    error_indication_txt_to_segment_conversion(lcd_data,str);
}

/***********************************************************************************************************************
* Function Name: set_clear_error_text_display
* Description  : This function implements the functionality for setting or clearing the error.
* Arguments    : lcd_data, error, status
* Return Value : None
***********************************************************************************************************************/
void set_clear_error_text_display(LCD_DATA_BUFF *lcd_data, uint8_t error, uint8_t status)
{    
    switch(error)
    {
        case MCU_ERROR_TXT      : ERROR_BITS.BIT.BIT_MCU_ERROR=status;break;
        case MOTOR_ERROR_TXT    : ERROR_BITS.BIT.BIT_MOTOR_ERROR=status;break;
        case LIMP_MODE_HOME_TXT : ERROR_BITS.BIT.BIT_LIMP_MODE_HOME=status;break;
        case MCU_LOCKED_TXT     : ERROR_BITS.BIT.BIT_MCU_LOCKED=status;break;
        case BATTERY_FULL_TXT   : ERROR_BITS.BIT.BIT_BATTERY_FULL=status;break;
        case BATTERY_LOW_TXT    : ERROR_BITS.BIT.BIT_BATTERY_LOW=status;break;
        //case MCU_VALUE_ERROR_TXT    : ERROR_BITS.BIT.BIT_MCU_VALUE_ERROR=status;break;
       
    }
}

/***********************************************************************************************************************
* Function Name: error_indiction_text_display
* Description  : to dispaly error in alphanumeric area.
* Arguments    : lcd_Data
* Return Value : None
***********************************************************************************************************************/
void error_indiction_text_display(LCD_DATA_BUFF *lcd_data)
{
    static uint16_t count=0;
    static uint8_t pos=0;
    uint8_t i;
    for(i=pos;i<MAX_TXT_DISP_COUNT;i++)
    {
        if(CHECK_BIT(ERROR_BITS.BYTE,i))
        {
            error_indiction_text(lcd_data, i);
            pos=i;
            break;
        }
    }
    if(i==MAX_TXT_DISP_COUNT)
    {
        pos=0;
        error_indiction_text(lcd_data, CLEAR_TXT);
        for(i=pos;i<MAX_TXT_DISP_COUNT;i++)
        {
            if(CHECK_BIT(ERROR_BITS.BYTE,i))
            {
                error_indiction_text(lcd_data, i);
                pos=i;
                break;
            }
        }
    }
    count++;    
    if(count>=TXT_DISP_DURATION)
    {
        count=0; 
        pos++;
        if(pos>=MAX_TXT_DISP_COUNT)
        {
            pos=0;
        }        
    }
}

/***********************************************************************************************************************
* Function Name: vehicle_mode_indication
* Description  : segments to be lit for various modes of the vehicle.
* Arguments    : lcd_data, vehicle mode
* Return Value : None
***********************************************************************************************************************/
void vehicle_mode_indication(LCD_DATA_BUFF *lcd_data, uint8_t mode)
{
    switch(mode)
    {
        case ECO:       (lcd_data+9)->bit.bit_4 = ON;//Mode_Line
                        (lcd_data+9)->bit.bit_5 = ON;//T2
                        (lcd_data+9)->bit.bit_6 = OFF;//T2
                        (lcd_data+9)->bit.bit_7 = OFF;//T2
                        break;
        case CITY:      (lcd_data+9)->bit.bit_4 = ON;//Mode_Line
                        (lcd_data+9)->bit.bit_5 = OFF;//T2
                        (lcd_data+9)->bit.bit_6 = ON;//T2
                        (lcd_data+9)->bit.bit_7 = OFF;//T2
                        break;
        case PWR:       (lcd_data+9)->bit.bit_4 = ON;//Mode_Line
                        (lcd_data+9)->bit.bit_5 = OFF;//T2
                        (lcd_data+9)->bit.bit_6 = OFF;//T2
                        (lcd_data+9)->bit.bit_7 = ON;//T2
                        break;

        case ECO_PWR:   
                        (lcd_data+9)->bit.bit_4 = ON;//Mode_Line
                        (lcd_data+9)->bit.bit_5 = ON;//ECO
                        (lcd_data+9)->bit.bit_6 = OFF;//T2
                        (lcd_data+9)->bit.bit_7 = ON;//PWR
                        break;

        default:        (lcd_data+9)->bit.bit_4 = OFF;//Mode_Line                    
                        break;

    }
}

/***********************************************************************************************************************
* Function Name: navigation_direction
* Description  : This function implements the functionality for the Navigation direction.
* Arguments    : lcd_Data
* Return Value : None
***********************************************************************************************************************/
void navigation_direction(LCD_DATA_BUFF *lcd_data, uint8_t direction)
{
    (lcd_data+93)->bit.bit_4 = 0x0;//Y1
    (lcd_data+98)->bit.bit_0 = 0x0;//Y2
    (lcd_data+94)->bit.bit_4 = 0x0;//Y3
    (lcd_data+94)->bit.bit_5 = 0x0;//Y4
    (lcd_data+93)->bit.bit_5 = 0x0;//Y5
    (lcd_data+94)->bit.bit_1 = 0x0;//Y6
    (lcd_data+94)->bit.bit_0 = 0x0;//Y7
    (lcd_data+95)->bit.bit_0 = 0x0;//Y8
    (lcd_data+95)->bit.bit_1 = 0x0;//Y9
    (lcd_data+96)->bit.bit_0 = 0x0;//Y10 
    (lcd_data+97)->bit.bit_4 = 0x0;//Y11
    (lcd_data+98)->bit.bit_4 = 0x0;//Y12
    (lcd_data+97)->bit.bit_0 = 0x0;//Y13
    (lcd_data+97)->bit.bit_1 = 0x0;//Y14

	switch(direction)
	{
		case DIRECTION_1:
			(lcd_data+95)->bit.bit_1 = 0x1;//Y9
			(lcd_data+94)->bit.bit_0 = 0x1;//Y7 stright
            (lcd_data+95)->bit.bit_0 = 0x1;//Y8
			(lcd_data+96)->bit.bit_0 = 0x1;//Y10
			break;
		case DIRECTION_2:
			(lcd_data+95)->bit.bit_1 = 0x1;//Y9 Left
			(lcd_data+94)->bit.bit_1 = 0x1;//Y6
			(lcd_data+94)->bit.bit_5 = 0x1;//Y4
			(lcd_data+94)->bit.bit_4 = 0x1;//Y3
			break;
		case DIRECTION_3:
            (lcd_data+95)->bit.bit_1 = 0x1;//Y9 Right
			(lcd_data+97)->bit.bit_4 = 0x1;//Y11
            (lcd_data+98)->bit.bit_4 = 0x1;//Y12
            (lcd_data+97)->bit.bit_0 = 0x1;//Y13
			break;
		case DIRECTION_4:
			(lcd_data+95)->bit.bit_1 = 0x1;//Y9 Left U turn
			(lcd_data+94)->bit.bit_1 = 0x1;//Y6
			(lcd_data+94)->bit.bit_5 = 0x1;//Y4
			(lcd_data+93)->bit.bit_5 = 0x1;//Y5
		    break;
		case DIRECTION_5:
		    (lcd_data+95)->bit.bit_1 = 0x1;//Y9 Right U turn
			(lcd_data+97)->bit.bit_4 = 0x1;//Y11
			(lcd_data+97)->bit.bit_0 = 0x1;//Y13
			(lcd_data+97)->bit.bit_1 = 0x1;//Y14
			break;
		case DIRECTION_6:
		    (lcd_data+93)->bit.bit_4 = 0x1;//Y1 
			(lcd_data+95)->bit.bit_1 = 0x1;//Y9 Stright left
			(lcd_data+95)->bit.bit_0 = 0x1;//Y8
			break;
		case DIRECTION_7:
			(lcd_data+95)->bit.bit_1 = 0x1;//Y9 Stright right
			(lcd_data+95)->bit.bit_0 = 0x1;//Y8
			(lcd_data+98)->bit.bit_0 = 0x1;//Y2
            break;
	}
}

/***********************************************************************************************************************
* Function Name: range_bar_indication
* Description  : to lit the respective DTE bar.
* Arguments    : lcd_Data, bar, status
* Return Value : None
***********************************************************************************************************************/
void range_bar_indication(LCD_DATA_BUFF *lcd_data, uint8_t bar, uint8_t enable)
{

    (lcd_data+101)->bit.bit_5 = 0x0;//X13
    (lcd_data+101)->bit.bit_6 = 0x0;//X14
    (lcd_data+101)->bit.bit_7 = 0x0;//X15
    (lcd_data+101)->bit.bit_3 = 0x0;//X16
    (lcd_data+101)->bit.bit_2 = 0x0;//X17
    (lcd_data+101)->bit.bit_1 = 0x0;//X18
    (lcd_data+101)->bit.bit_0 = 0x0;//X19
    (lcd_data+102)->bit.bit_5 = 0x0;//X20
    (lcd_data+102)->bit.bit_6 = 0x0;//X21
    (lcd_data+102)->bit.bit_7 = 0x0;//X22

    if(enable == 1)
    {
        (lcd_data+102)->bit.bit_4 = 0x1;//X23 //LINE
        (lcd_data+101)->bit.bit_4 = 0x1;//X12 //dte


        switch(bar)
        {
            // case 0:
            //         (lcd_data+101)->bit.bit_5 = 0x0;//X13
            //         (lcd_data+101)->bit.bit_6 = 0x0;//X14
            //         (lcd_data+101)->bit.bit_7 = 0x0;//X15
            //         (lcd_data+101)->bit.bit_3 = 0x0;//X16
            //         (lcd_data+101)->bit.bit_2 = 0x0;//X17
            //         (lcd_data+101)->bit.bit_1 = 0x0;//X18
            //         (lcd_data+101)->bit.bit_0 = 0x0;//X19
            //         (lcd_data+102)->bit.bit_5 = 0x0;//X20
            //         (lcd_data+102)->bit.bit_6 = 0x0;//X21
            //         (lcd_data+102)->bit.bit_7 = 0x0;//X22
            //         break;
            case 1:
                    (lcd_data+101)->bit.bit_5 = 0x1;//X13
                    (lcd_data+101)->bit.bit_6 = 0x0;//X14
                    (lcd_data+101)->bit.bit_7 = 0x0;//X15
                    (lcd_data+101)->bit.bit_3 = 0x0;//X16
                    (lcd_data+101)->bit.bit_2 = 0x0;//X17
                    (lcd_data+101)->bit.bit_1 = 0x0;//X18
                    (lcd_data+101)->bit.bit_0 = 0x0;//X19
                    (lcd_data+102)->bit.bit_5 = 0x0;//X20
                    (lcd_data+102)->bit.bit_6 = 0x0;//X21
                    (lcd_data+102)->bit.bit_7 = 0x0;//X22
                    break;
            case 2:
                    (lcd_data+101)->bit.bit_5 = 0x1;//X13
                    (lcd_data+101)->bit.bit_6 = 0x1;//X14
                    (lcd_data+101)->bit.bit_7 = 0x0;//X15
                    (lcd_data+101)->bit.bit_3 = 0x0;//X16
                    (lcd_data+101)->bit.bit_2 = 0x0;//X17
                    (lcd_data+101)->bit.bit_1 = 0x0;//X18
                    (lcd_data+101)->bit.bit_0 = 0x0;//X19
                    (lcd_data+102)->bit.bit_5 = 0x0;//X20
                    (lcd_data+102)->bit.bit_6 = 0x0;//X21
                    (lcd_data+102)->bit.bit_7 = 0x0;//X22  
                    break;
            case 3:
                    (lcd_data+101)->bit.bit_5 = 0x1;//X13
                    (lcd_data+101)->bit.bit_6 = 0x1;//X14
                    (lcd_data+101)->bit.bit_7 = 0x1;//X15
                    (lcd_data+101)->bit.bit_3 = 0x0;//X16
                    (lcd_data+101)->bit.bit_2 = 0x0;//X17
                    (lcd_data+101)->bit.bit_1 = 0x0;//X18
                    (lcd_data+101)->bit.bit_0 = 0x0;//X19
                    (lcd_data+102)->bit.bit_5 = 0x0;//X20
                    (lcd_data+102)->bit.bit_6 = 0x0;//X21
                    (lcd_data+102)->bit.bit_7 = 0x0;//X22
                    break;
            case 4:
                    (lcd_data+101)->bit.bit_5 = 0x1;//X13
                    (lcd_data+101)->bit.bit_6 = 0x1;//X14
                    (lcd_data+101)->bit.bit_7 = 0x1;//X15
                    (lcd_data+101)->bit.bit_3 = 0x1;//X16
                    (lcd_data+101)->bit.bit_2 = 0x0;//X17
                    (lcd_data+101)->bit.bit_1 = 0x0;//X18
                    (lcd_data+101)->bit.bit_0 = 0x0;//X19
                    (lcd_data+102)->bit.bit_5 = 0x0;//X20
                    (lcd_data+102)->bit.bit_6 = 0x0;//X21
                    (lcd_data+102)->bit.bit_7 = 0x0;//X22
                    break;
            case 5:
                    (lcd_data+101)->bit.bit_5 = 0x1;//X13
                    (lcd_data+101)->bit.bit_6 = 0x1;//X14
                    (lcd_data+101)->bit.bit_7 = 0x1;//X15
                    (lcd_data+101)->bit.bit_3 = 0x1;//X16
                    (lcd_data+101)->bit.bit_2 = 0x1;//X17
                    (lcd_data+101)->bit.bit_1 = 0x0;//X18
                    (lcd_data+101)->bit.bit_0 = 0x0;//X19
                    (lcd_data+102)->bit.bit_5 = 0x0;//X20
                    (lcd_data+102)->bit.bit_6 = 0x0;//X21
                    (lcd_data+102)->bit.bit_7 = 0x0;//X22    
                    break;
            case 6:
                    (lcd_data+101)->bit.bit_5 = 0x1;//X13
                    (lcd_data+101)->bit.bit_6 = 0x1;//X14
                    (lcd_data+101)->bit.bit_7 = 0x1;//X15
                    (lcd_data+101)->bit.bit_3 = 0x1;//X16
                    (lcd_data+101)->bit.bit_2 = 0x1;//X17
                    (lcd_data+101)->bit.bit_1 = 0x1;//X18
                    (lcd_data+101)->bit.bit_0 = 0x0;//X19
                    (lcd_data+102)->bit.bit_5 = 0x0;//X20
                    (lcd_data+102)->bit.bit_6 = 0x0;//X21
                    (lcd_data+102)->bit.bit_7 = 0x0;//X22
                    break;
            case 7:
                    (lcd_data+101)->bit.bit_5 = 0x1;//X13
                    (lcd_data+101)->bit.bit_6 = 0x1;//X14
                    (lcd_data+101)->bit.bit_7 = 0x1;//X15
                    (lcd_data+101)->bit.bit_3 = 0x1;//X16
                    (lcd_data+101)->bit.bit_2 = 0x1;//X17
                    (lcd_data+101)->bit.bit_1 = 0x1;//X18
                    (lcd_data+101)->bit.bit_0 = 0x1;//X19
                    (lcd_data+102)->bit.bit_5 = 0x0;//X20
                    (lcd_data+102)->bit.bit_6 = 0x0;//X21
                    (lcd_data+102)->bit.bit_7 = 0x0;//X22  
                    break;
            case 8:
                    (lcd_data+101)->bit.bit_5 = 0x1;//X13
                    (lcd_data+101)->bit.bit_6 = 0x1;//X14
                    (lcd_data+101)->bit.bit_7 = 0x1;//X15
                    (lcd_data+101)->bit.bit_3 = 0x1;//X16
                    (lcd_data+101)->bit.bit_2 = 0x1;//X17
                    (lcd_data+101)->bit.bit_1 = 0x1;//X18
                    (lcd_data+101)->bit.bit_0 = 0x1;//X19
                    (lcd_data+102)->bit.bit_5 = 0x1;//X20
                    (lcd_data+102)->bit.bit_6 = 0x0;//X21
                    (lcd_data+102)->bit.bit_7 = 0x0;//X22	    
                    break;
            case 9:
                    (lcd_data+101)->bit.bit_5 = 0x1;//X13
                    (lcd_data+101)->bit.bit_6 = 0x1;//X14
                    (lcd_data+101)->bit.bit_7 = 0x1;//X15
                    (lcd_data+101)->bit.bit_3 = 0x1;//X16
                    (lcd_data+101)->bit.bit_2 = 0x1;//X17
                    (lcd_data+101)->bit.bit_1 = 0x1;//X18
                    (lcd_data+101)->bit.bit_0 = 0x1;//X19
                    (lcd_data+102)->bit.bit_5 = 0x1;//X20
                    (lcd_data+102)->bit.bit_6 = 0x1;//X21
                    (lcd_data+102)->bit.bit_7 = 0x0;//X22
                    break;
            case 10:
                    (lcd_data+101)->bit.bit_5 = 0x1;//X13
                    (lcd_data+101)->bit.bit_6 = 0x1;//X14
                    (lcd_data+101)->bit.bit_7 = 0x1;//X15
                    (lcd_data+101)->bit.bit_3 = 0x1;//X16
                    (lcd_data+101)->bit.bit_2 = 0x1;//X17
                    (lcd_data+101)->bit.bit_1 = 0x1;//X18
                    (lcd_data+101)->bit.bit_0 = 0x1;//X19
                    (lcd_data+102)->bit.bit_5 = 0x1;//X20
                    (lcd_data+102)->bit.bit_6 = 0x1;//X21
                    (lcd_data+102)->bit.bit_7 = 0x1;//X22
                    break;
        }
    }
    else if(enable == 0 )
    {
        (lcd_data+102)->bit.bit_4 = 0;//X23 //LINE
        (lcd_data+101)->bit.bit_4 = 0;//X12 //dte
    }

}

/***********************************************************************************************************************
* Function Name: soc_bar_indication
* Description  : This function implements the segments/ soc bars to be lit for respective SOC .
* Arguments    : lcd_Data, bar, enable
* Return Value : None
***********************************************************************************************************************/
void soc_bar_indication(LCD_DATA_BUFF *lcd_data, uint8_t bar, uint8_t enable)
{
    (lcd_data+11)->bit.bit_1 = 0x0;//X1
    (lcd_data+11)->bit.bit_2 = 0x0;//X2
    (lcd_data+11)->bit.bit_3 = 0x0;//X3
    (lcd_data+11)->bit.bit_7 = 0x0;//X4
    (lcd_data+11)->bit.bit_6 = 0x0;//X5
    (lcd_data+11)->bit.bit_5 = 0x0;//X6
    (lcd_data+11)->bit.bit_4 = 0x0;//X7
    (lcd_data+10)->bit.bit_1 = 0x0;//X8
    (lcd_data+10)->bit.bit_2 = 0x0;//X9
    (lcd_data+10)->bit.bit_3 = 0x0;//X10
    if(enable == 1)
    {
        (lcd_data+11)->bit.bit_0 = 0x1;//X0 BAT SOC
        (lcd_data+10)->bit.bit_0 = 0x1;//X11 SOC LINE
        switch(bar)
        {
            // case bar0:
            //             (lcd_data+11)->bit.bit_1 = 0x0;//X1
            //             (lcd_data+11)->bit.bit_2 = 0x0;//X2
            //             (lcd_data+11)->bit.bit_3 = 0x0;//X3
            //             (lcd_data+11)->bit.bit_7 = 0x0;//X4
            //             (lcd_data+11)->bit.bit_6 = 0x0;//X5
            //             (lcd_data+11)->bit.bit_5 = 0x0;//X6
            //             (lcd_data+11)->bit.bit_4 = 0x0;//X7
            //             (lcd_data+10)->bit.bit_1 = 0x0;//X8
            //             (lcd_data+10)->bit.bit_2 = 0x0;//X9
            //             (lcd_data+10)->bit.bit_3 = 0x0;//X10
            //             break;
            case 1:
                    (lcd_data+11)->bit.bit_1 = 0x1;//X1
                    (lcd_data+11)->bit.bit_2 = 0x0;//X2
                    (lcd_data+11)->bit.bit_3 = 0x0;//X3
                    (lcd_data+11)->bit.bit_7 = 0x0;//X4
                    (lcd_data+11)->bit.bit_6 = 0x0;//X5
                    (lcd_data+11)->bit.bit_5 = 0x0;//X6
                    (lcd_data+11)->bit.bit_4 = 0x0;//X7
                    (lcd_data+10)->bit.bit_1 = 0x0;//X8
                    (lcd_data+10)->bit.bit_2 = 0x0;//X9
                    (lcd_data+10)->bit.bit_3 = 0x0;//X10
                    break;
            case 2:
                    (lcd_data+11)->bit.bit_1 = 0x1;//X1
                    (lcd_data+11)->bit.bit_2 = 0x1;//X2
                    (lcd_data+11)->bit.bit_3 = 0x0;//X3
                    (lcd_data+11)->bit.bit_7 = 0x0;//X4
                    (lcd_data+11)->bit.bit_6 = 0x0;//X5
                    (lcd_data+11)->bit.bit_5 = 0x0;//X6
                    (lcd_data+11)->bit.bit_4 = 0x0;//X7
                    (lcd_data+10)->bit.bit_1 = 0x0;//X8
                    (lcd_data+10)->bit.bit_2 = 0x0;//X9
                    (lcd_data+10)->bit.bit_3 = 0x0;//X10	
                    break;
            case 3:
                    (lcd_data+11)->bit.bit_1 = 0x1;//X1
                    (lcd_data+11)->bit.bit_2 = 0x1;//X2
                    (lcd_data+11)->bit.bit_3 = 0x1;//X3
                    (lcd_data+11)->bit.bit_7 = 0x0;//X4
                    (lcd_data+11)->bit.bit_6 = 0x0;//X5
                    (lcd_data+11)->bit.bit_5 = 0x0;//X6
                    (lcd_data+11)->bit.bit_4 = 0x0;//X7
                    (lcd_data+10)->bit.bit_1 = 0x0;//X8
                    (lcd_data+10)->bit.bit_2 = 0x0;//X9
                    (lcd_data+10)->bit.bit_3 = 0x0;//X10
                    break;
            case 4:
                    (lcd_data+11)->bit.bit_1 = 0x1;//X1
                    (lcd_data+11)->bit.bit_2 = 0x1;//X2
                    (lcd_data+11)->bit.bit_3 = 0x1;//X3
                    (lcd_data+11)->bit.bit_7 = 0x1;//X4
                    (lcd_data+11)->bit.bit_6 = 0x0;//X5
                    (lcd_data+11)->bit.bit_5 = 0x0;//X6
                    (lcd_data+11)->bit.bit_4 = 0x0;//X7
                    (lcd_data+10)->bit.bit_1 = 0x0;//X8
                    (lcd_data+10)->bit.bit_2 = 0x0;//X9
                    (lcd_data+10)->bit.bit_3 = 0x0;//X10
                    break;
            case 5:
                    (lcd_data+11)->bit.bit_1 = 0x1;//X1
                    (lcd_data+11)->bit.bit_2 = 0x1;//X2
                    (lcd_data+11)->bit.bit_3 = 0x1;//X3
                    (lcd_data+11)->bit.bit_7 = 0x1;//X4
                    (lcd_data+11)->bit.bit_6 = 0x1;//X5
                    (lcd_data+11)->bit.bit_5 = 0x0;//X6
                    (lcd_data+11)->bit.bit_4 = 0x0;//X7
                    (lcd_data+10)->bit.bit_1 = 0x0;//X8
                    (lcd_data+10)->bit.bit_2 = 0x0;//X9
                    (lcd_data+10)->bit.bit_3 = 0x0;//X10
                    break;
            case 6:
                    (lcd_data+11)->bit.bit_1 = 0x1;//X1
                    (lcd_data+11)->bit.bit_2 = 0x1;//X2
                    (lcd_data+11)->bit.bit_3 = 0x1;//X3
                    (lcd_data+11)->bit.bit_7 = 0x1;//X4
                    (lcd_data+11)->bit.bit_6 = 0x1;//X5
                    (lcd_data+11)->bit.bit_5 = 0x1;//X6
                    (lcd_data+11)->bit.bit_4 = 0x0;//X7
                    (lcd_data+10)->bit.bit_1 = 0x0;//X8
                    (lcd_data+10)->bit.bit_2 = 0x0;//X9
                    (lcd_data+10)->bit.bit_3 = 0x0;//X10
                    break;
            case 7:
                    (lcd_data+11)->bit.bit_1 = 0x1;//X1
                    (lcd_data+11)->bit.bit_2 = 0x1;//X2
                    (lcd_data+11)->bit.bit_3 = 0x1;//X3
                    (lcd_data+11)->bit.bit_7 = 0x1;//X4
                    (lcd_data+11)->bit.bit_6 = 0x1;//X5
                    (lcd_data+11)->bit.bit_5 = 0x1;//X6
                    (lcd_data+11)->bit.bit_4 = 0x1;//X7
                    (lcd_data+10)->bit.bit_1 = 0x0;//X8
                    (lcd_data+10)->bit.bit_2 = 0x0;//X9
                    (lcd_data+10)->bit.bit_3 = 0x0;//X10
                    break;
            case 8:
                    (lcd_data+11)->bit.bit_1 = 0x1;//X1
                    (lcd_data+11)->bit.bit_2 = 0x1;//X2
                    (lcd_data+11)->bit.bit_3 = 0x1;//X3
                    (lcd_data+11)->bit.bit_7 = 0x1;//X4
                    (lcd_data+11)->bit.bit_6 = 0x1;//X5
                    (lcd_data+11)->bit.bit_5 = 0x1;//X6
                    (lcd_data+11)->bit.bit_4 = 0x1;//X7
                    (lcd_data+10)->bit.bit_1 = 0x1;//X8
                    (lcd_data+10)->bit.bit_2 = 0x0;//X9
                    (lcd_data+10)->bit.bit_3 = 0x0;//X10
                    break;
            case 9:
                    (lcd_data+11)->bit.bit_1 = 0x1;//X1
                    (lcd_data+11)->bit.bit_2 = 0x1;//X2
                    (lcd_data+11)->bit.bit_3 = 0x1;//X3
                    (lcd_data+11)->bit.bit_7 = 0x1;//X4
                    (lcd_data+11)->bit.bit_6 = 0x1;//X5
                    (lcd_data+11)->bit.bit_5 = 0x1;//X6
                    (lcd_data+11)->bit.bit_4 = 0x1;//X7
                    (lcd_data+10)->bit.bit_1 = 0x1;//X8
                    (lcd_data+10)->bit.bit_2 = 0x1;//X9
                    (lcd_data+10)->bit.bit_3 = 0x0;//X10
                    break;
            case 10:
                    (lcd_data+11)->bit.bit_1 = 0x1;//X1
                    (lcd_data+11)->bit.bit_2 = 0x1;//X2
                    (lcd_data+11)->bit.bit_3 = 0x1;//X3
                    (lcd_data+11)->bit.bit_7 = 0x1;//X4
                    (lcd_data+11)->bit.bit_6 = 0x1;//X5
                    (lcd_data+11)->bit.bit_5 = 0x1;//X6
                    (lcd_data+11)->bit.bit_4 = 0x1;//X7
                    (lcd_data+10)->bit.bit_1 = 0x1;//X8
                    (lcd_data+10)->bit.bit_2 = 0x1;//X9
                    (lcd_data+10)->bit.bit_3 = 0x1;//X10
                    break;
        }
    }
    else if(enable == 0)
    {
        (lcd_data+11)->bit.bit_0 = 0x0;//X0 BAT SOC
        (lcd_data+10)->bit.bit_0 = 0x0;//X11 SOC LINE
    }
}

/***********************************************************************************************************************
* Function Name: trip_display
* Description  : This function implements the segments to be lit for current trip value.
* Arguments    : lcd_Data, trip_disp
* Return Value : None
***********************************************************************************************************************/
void trip_display(LCD_DATA_BUFF *lcd_data, uint32_t trip_disp)
{
	uint8_t segment_1,segment_2,segment_3,segment_4;
	uint32_t temp;
	segment_1   = trip_disp%10;
	temp        = trip_disp/10;
	segment_2   = temp%10;
	temp        = temp/10;
	segment_3   = temp%10;
	temp        = temp/10;
	segment_4   = temp%10;
	
    (lcd_data+82)->bit.bit_3 = 0xff;//DOT3
    (lcd_data+80)->bit.bit_0 = 0xff;//T33 TRIP KM
    /***************************************3segment*********************************************/
    (lcd_data+83)->bit.bit_4 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_A); //a/
    (lcd_data+83)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_B); //b/
    (lcd_data+83)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_C); //c/
    (lcd_data+83)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_D); //d/
    (lcd_data+83)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_E); //e/
    (lcd_data+83)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_F); //f/
    (lcd_data+83)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_G); //g
    /****************************************2segment*******************************************/
    (lcd_data+82)->bit.bit_4 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_A); //a/
    (lcd_data+82)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_B); //b/
    (lcd_data+82)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_C); //c/
    (lcd_data+82)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_D); //d/
    (lcd_data+82)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_E); //e/
    (lcd_data+82)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_F); //f/
    (lcd_data+82)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_G); //g
    /************************************1segment****************************************************/
    (lcd_data+81)->bit.bit_4 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_A); //a/
    (lcd_data+81)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_B); //b/
    (lcd_data+81)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_C); //c/
    (lcd_data+81)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_D); //d/
    (lcd_data+81)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_E); //e/
    (lcd_data+81)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_F); //f/
    (lcd_data+81)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_G); //g
    /**************************************0segment***********************************************/
    (lcd_data+80)->bit.bit_4 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_A); //a/
    (lcd_data+80)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_B); //b/
    (lcd_data+80)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_C); //c/
    (lcd_data+80)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_D); //d/
    (lcd_data+80)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_E); //e/
    (lcd_data+80)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_F); //f/
    (lcd_data+80)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_G); //g

}

/***********************************************************************************************************************
* Function Name: init_io
* Description  : This function implements the init condition for i/p o/p pins.
* Arguments    : none
* Return Value : None
***********************************************************************************************************************/
void init_io(void)
{
	PM1_bit.no7 = 1;//Left_IND---------------(I/P)
	PM1_bit.no1 = 0;//LED_PARKING LAMB-------(O/P)
	PM3_bit.no7 = 0;//CAN Standby------------(O/P)
	PM7_bit.no5 = 0;//LED_LOW_BREAK OIL------(O/P)
	PM8_bit.no4 = 0;//PWM_Backlight----------(O/P)
	PM8_bit.no2 = 1;//Right_IND--------------(I/P)
	PM8_bit.no3 = 1;//Highbeam_IND-----------(I/P)
	PM9_bit.no2 = 1;//INPUT_Brake fluid_IN---(I/P)
	PM9_bit.no1 = 1;//INPUT_Parking _IND-----(I/P)
	PM9_bit.no0 = 1;//Hazard_IND-------------(I/P)
	PM8_bit.no4 = 0;//PWM_Backlight----------(O/P)
	PM8_bit.no5 = 0;

	P8_bit.no4  = 0;
	P8_bit.no5  = 0;

}

/***********************************************************************************************************************
* Function Name: odometer_display
* Description  : This function implements the functionality for the odometer.
* Arguments    : lcd_Data, odo_disp
* Return Value : None
***********************************************************************************************************************/
void odometer_display(LCD_DATA_BUFF *lcd_data, uint32_t odo_disp)
{
	uint8_t segment_1,segment_2,segment_3,segment_4,segment_5,segment_6,segment_7;
	uint32_t temp;
	segment_1  = odo_disp%10;
	temp      = odo_disp/10;
	segment_2  = temp%10;
	temp               = temp/10;
	segment_3  = temp%10;
	temp               = temp/10;
	segment_4  = temp%10;
	temp               = temp/10;
	segment_5  = temp%10;
	temp               = temp/10;
	segment_6  = temp%10;
	temp               = temp/10;
	segment_7  = temp%10;
	
	(lcd_data+57)->bit.bit_4 = 0xff;//T32_ODO
	(lcd_data+56)->bit.bit_7 = 0xff;//DOT2

	/************************6segment**************************/
	(lcd_data+56)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_A); //a/
	(lcd_data+57)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_B); //b/
	(lcd_data+57)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_C); //c/
	(lcd_data+56)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_D); //d/
	(lcd_data+56)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_E); //e/
	(lcd_data+56)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_F); //f/
	(lcd_data+57)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_G); //g/
	 /**********************************5segment****************************/
    (lcd_data+55)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_A); //a/
	(lcd_data+56)->bit.bit_4 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_B); //b/
	(lcd_data+56)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_C); //c/
	(lcd_data+55)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_D); //d/
	(lcd_data+55)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_E); //e/
	(lcd_data+55)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_F); //f/
	(lcd_data+56)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_G); //g
	 /**********************************4segment*****************************/
	(lcd_data+54)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_A); //a/	
	(lcd_data+55)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_B); //b/
	(lcd_data+55)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_C); //c/
	(lcd_data+54)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_D); //d/
	(lcd_data+54)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_E); //e/
	(lcd_data+54)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_F); //f/
	(lcd_data+55)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_G); //g
	 /*********************************3segment********************************/
	(lcd_data+53)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_A); //a/
	(lcd_data+54)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_B); //b/
	(lcd_data+54)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_C); //c/
	(lcd_data+53)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_D); //d/
	(lcd_data+53)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_E); //e/
	(lcd_data+53)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_F); //f/
	(lcd_data+54)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_G); //g
	 /*********************************3
      * segment********************************/
	(lcd_data+52)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_5,s_SEGMENT_A); //a/
	(lcd_data+53)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_5,s_SEGMENT_B); //b/
	(lcd_data+53)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_5,s_SEGMENT_C); //c/
	(lcd_data+52)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_5,s_SEGMENT_D); //d/
	(lcd_data+52)->bit.bit_2	= s_GET_DISP_DATA_BIT(segment_5,s_SEGMENT_E); //e/
	(lcd_data+52)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_5,s_SEGMENT_F); //f/
	(lcd_data+53)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_5,s_SEGMENT_G); //g
	 /*********************************1segment********************************/
    (lcd_data+51)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_6,s_SEGMENT_A); //a/
	(lcd_data+52)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_6,s_SEGMENT_B); //b/
	(lcd_data+52)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_6,s_SEGMENT_C); //c/
	(lcd_data+51)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_6,s_SEGMENT_D); //d/
	(lcd_data+51)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_6,s_SEGMENT_E); //e/
	(lcd_data+51)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_6,s_SEGMENT_F); //f/
	(lcd_data+52)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_6,s_SEGMENT_G); //g
	/**********************************0segment*******************************/
	(lcd_data+50)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_7,s_SEGMENT_A); //a/
	(lcd_data+51)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_7,s_SEGMENT_B); //b/
	(lcd_data+51)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_7,s_SEGMENT_C); //c/
	(lcd_data+50)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_7,s_SEGMENT_D); //d/
    (lcd_data+50)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_7,s_SEGMENT_E); //e/
	(lcd_data+50)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_7,s_SEGMENT_F); //f/
    (lcd_data+51)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_7,s_SEGMENT_G); //g
}

/***********************************************************************************************************************
* Function Name: navigation_distance_display
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void navigation_distance_display(LCD_DATA_BUFF *lcd_data, uint8_t kilometer, uint8_t meter)
{
	uint8_t segment_1,segment_2,segment_3,segment_4;
	uint8_t temp;
	segment_1  = meter%10;
	temp       = meter/10;
	segment_2  = temp%10;

	segment_3  = kilometer%10;
	temp               = kilometer/10;
	segment_4  = temp%10;

    (lcd_data+96)->bit.bit_7 = 0xff;//DOT1
	(lcd_data+98)->bit.bit_3 = 0xff;//KM
	
	/********************************************10********************************************************/
	(lcd_data+98)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_A); //a/
	(lcd_data+98)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_B); //b/
	(lcd_data+98)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_C); //c/
	(lcd_data+98)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_D); //d/
	(lcd_data+97)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_E); //e/
	(lcd_data+97)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_F); //f/
	(lcd_data+98)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_G); //g/
	/***************************************9**********************************************************/
	(lcd_data+96)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_A); //a/
	(lcd_data+97)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_B); //b/
	(lcd_data+97)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_C); //c/
	(lcd_data+96)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_D); //d/
	(lcd_data+96)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_E); //e/
	(lcd_data+96)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_F); //f/
	(lcd_data+96)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_G); //g/
	 /******************************************************8******************************************/
	(lcd_data+95)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_A); //a/
	(lcd_data+95)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_B); //b/
	(lcd_data+95)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_C); //c/
	(lcd_data+95)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_D); //d/
	(lcd_data+94)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_E); //e/
	(lcd_data+94)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_F); //f/
	(lcd_data+95)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_G); //g/
	/*************************************************7************************************************/
	(lcd_data+93)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_A); //a/
	(lcd_data+94)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_B); //b/
	(lcd_data+94)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_C); //c/
	(lcd_data+93)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_D); //d/
	(lcd_data+93)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_E); //e/
	(lcd_data+93)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_F); //f/
	(lcd_data+93)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_G); //g/

}

/***********************************************************************************************************************
* Function Name: rtc_display
* Description  : 
* Arguments    : lcd_data, rtc
* Return Value : None
***********************************************************************************************************************/
void rtc_display(LCD_DATA_BUFF *lcd_data, uint16_t rtc, uint8_t am_pm)
{
	uint16_t low_segments  = rtc%100;
	uint16_t high_segments = rtc/100;

	uint8_t segment_1 = low_segments%10;
	uint16_t temp     = low_segments/10;
	uint8_t segment_2 = temp%10;

	uint8_t segment_3 = high_segments%10;
	temp              = high_segments/10;
	uint8_t segment_4 = temp%10;

    (lcd_data+105)->bit.bit_4 = 0x1;//COL :
	(lcd_data+106)->bit.bit_4 = 0x1;//T10  //rtc line
    if(am_pm==1)
    {
        (lcd_data+104)->bit.bit_4 = 0x1;//PM  //PM
	    (lcd_data+103)->bit.bit_7 = 0x0;//AM  //am
    }
    else
    {
        (lcd_data+104)->bit.bit_4 = 0x0;//PM  //PM
	    (lcd_data+103)->bit.bit_7 = 0x1;//AM  //am
    }
/***************************************6segment*********************************************/
	(lcd_data+103)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_A); //a/
	(lcd_data+103)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_B); //b/
	(lcd_data+103)->bit.bit_4 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_C); //c/
	(lcd_data+103)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_D); //d/
	(lcd_data+103)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_E); //e/
	(lcd_data+103)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_F); //f/
	(lcd_data+103)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_G); //g
/****************************************5segment*******************************************/
	(lcd_data+104)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_A); //a/
    (lcd_data+104)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_B); //b/
	(lcd_data+104)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_C); //c/
	(lcd_data+104)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_D); //d/
	(lcd_data+104)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_E); //e/
	(lcd_data+104)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_F); //f/
	(lcd_data+104)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_G); //g
/************************************4segment****************************************************/
	(lcd_data+105)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_A); //a/
    (lcd_data+105)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_B); //b/
	(lcd_data+105)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_C); //c/
	(lcd_data+105)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_D); //d/
	(lcd_data+105)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_E); //e/
	(lcd_data+105)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_F); //f/
	(lcd_data+105)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_3,s_SEGMENT_G); //g
/**************************************2segment***********************************************/
	(lcd_data+106)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_A); //a/
	(lcd_data+106)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_B); //b/
	(lcd_data+106)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_C); //c/
	(lcd_data+106)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_D); //d/
	(lcd_data+106)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_E); //e/
	(lcd_data+106)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_F); //f/
	(lcd_data+106)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_4,s_SEGMENT_G); //g
}


/***********************************************************************************************************************
* Function Name: range_display
* Description  : 
* Arguments    : lcd_Data, range
* Return Value : None
***********************************************************************************************************************/
void range_display(LCD_DATA_BUFF *lcd_data, uint8_t range)
{
	
	uint8_t segment_1 = range%10;
	uint8_t temp      = range/10;
	uint8_t segment_2 = temp%10;
	uint8_t segment_3 = temp/10;

    (lcd_data+100)->bit.bit_3 = 0xff;//T35 KM
    (lcd_data+101)->bit.bit_4 = 0xff;//X12 DTE
    /*****************************segement3*********************************/
    (lcd_data+100)->bit.bit_4 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_A); //a/
    (lcd_data+100)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_B); //b/
    (lcd_data+100)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_C); //c/
    (lcd_data+100)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_D); //d/
    (lcd_data+100)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_E); //e/
    (lcd_data+100)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_F); //f/
    (lcd_data+100)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_G); //g/
    /********************************segment2******************************/
    if(range>9)
    {
        (lcd_data+99)->bit.bit_4 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_A); //a/
        (lcd_data+99)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_B); //b/
        (lcd_data+99)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_C); //c/
        (lcd_data+99)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_D); //d/
        (lcd_data+99)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_E); //e/
        (lcd_data+99)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_F); //f/
        (lcd_data+99)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_G); //g/
    }
    else
    {
        (lcd_data+99)->bit.bit_4 = 0x00;
        (lcd_data+99)->bit.bit_1 = 0x00;
        (lcd_data+99)->bit.bit_3 = 0x00;
        (lcd_data+99)->bit.bit_7 = 0x00;
        (lcd_data+99)->bit.bit_6 = 0x00;
        (lcd_data+99)->bit.bit_5 = 0x00;
        (lcd_data+99)->bit.bit_2 = 0x00;
    }
    /*****************************************segment1**************************/
    if(segment_3)
    {
        (lcd_data+99)->bit.bit_0 = 1; 
    }
    else
    {
        (lcd_data+99)->bit.bit_0 = 0;
    }
}

/***********************************************************************************************************************
* Function Name: soc_display
* Description  : This function configures the segments that need to be illuminated for the SOC%.
* Arguments    : lcd_Data, soc value
* Return Value : None
***********************************************************************************************************************/
void soc_display(LCD_DATA_BUFF *lcd_data, uint8_t soc)
{
	
	uint8_t segment_1 = soc%10;
	uint8_t temp      = soc/10;
	uint8_t segment_2 = temp%10;
	uint8_t segment_3 = temp/10;
    if(soc <= 100)
    {
        (lcd_data+11)->bit.bit_0 = 0x1;//X0 BAT SOC
        (lcd_data+27)->bit.bit_7 = 0x1;//T34%
        
        /*****************************segement3*********************************/
        (lcd_data+26)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_A); //a/
        (lcd_data+27)->bit.bit_4 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_B); //b/
        (lcd_data+27)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_C); //c/
        (lcd_data+26)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_D); //d/
        (lcd_data+26)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_E); //e/
        (lcd_data+26)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_F); //f/
        (lcd_data+27)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_1,s_SEGMENT_G); //g/
        /********************************segment2******************************/
        if(soc>9)
        {    
            (lcd_data+25)->bit.bit_0 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_A); //a/
            (lcd_data+26)->bit.bit_5 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_B); //b/
            (lcd_data+26)->bit.bit_7 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_C); //c/
            (lcd_data+25)->bit.bit_3 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_D); //d/
            (lcd_data+25)->bit.bit_2 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_E); //e/
            (lcd_data+25)->bit.bit_1 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_F); //f/
            (lcd_data+26)->bit.bit_6 = s_GET_DISP_DATA_BIT(segment_2,s_SEGMENT_G); //g/
        }
        else 
        {
            (lcd_data+25)->bit.bit_0 = 0x00;
            (lcd_data+26)->bit.bit_5 = 0x00;
            (lcd_data+26)->bit.bit_7 = 0x00;
            (lcd_data+25)->bit.bit_3 = 0x00;
            (lcd_data+25)->bit.bit_2 = 0x00;
            (lcd_data+25)->bit.bit_1 = 0x00;
            (lcd_data+26)->bit.bit_6 = 0x00;
        }

        /*****************************************segment1**************************/
        if(segment_3)
        {
            (lcd_data+26)->bit.bit_4 = 1; 
        }
        else
        {
            (lcd_data+26)->bit.bit_4 = 0;
        }
    }
    else
    {
        (lcd_data+11)->bit.bit_0 = 0;
        (lcd_data+27)->bit.bit_7 = 0;
        (lcd_data+26)->bit.bit_0 = 0;
        (lcd_data+27)->bit.bit_4 = 0;
        (lcd_data+27)->bit.bit_6 = 0;
        (lcd_data+26)->bit.bit_3 = 0;
        (lcd_data+26)->bit.bit_2 = 0;
        (lcd_data+26)->bit.bit_1 = 0;
        (lcd_data+27)->bit.bit_5 = 0;
        (lcd_data+25)->bit.bit_0 = 0;
        (lcd_data+26)->bit.bit_5 = 0;
        (lcd_data+26)->bit.bit_7 = 0;
        (lcd_data+25)->bit.bit_3 = 0;
        (lcd_data+25)->bit.bit_2 = 0;
        (lcd_data+25)->bit.bit_1 = 0;
        (lcd_data+26)->bit.bit_6 = 0;
        (lcd_data+26)->bit.bit_4 = 0;
    }
    
}

/***********************************************************************************************************************
* Function Name: highbeam_telltile
* Description  : This function configures the segments that need to be illuminated for the highbeam.
* Arguments    : lcd_Data, status of highbeam value
* Return Value : None
***********************************************************************************************************************/
void highbeam_telltile(LCD_DATA_BUFF *lcd_data, uint8_t highbeam)
{
    if(highbeam==1)
	{
		(lcd_data+107)->bit.bit_6 = 0x1;//T8
	}
	else if(highbeam==0)
	{
		(lcd_data+107)->bit.bit_6 = 0x0;//T8
	}
}

void alert_name_tag_warning(LCD_DATA_BUFF *lcd_data, uint8_t status)
{
    //(lcd_data+9)->bit.bit_0  = 0x0;// TOP LINE
    if(status == 1)
    {
        (lcd_data+32)->bit.bit_7 =1; 
    }
    else
    {
        (lcd_data+32)->bit.bit_7 =0; 
    }

}	
void clear_error_bits()
{
    ERROR_BITS.BYTE = 0;
}
