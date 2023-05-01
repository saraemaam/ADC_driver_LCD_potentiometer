/*****************************************************************
 * Module      : LCD module
 * File name   : lcd.c
 * Description : Lcd driver to implement configurable LCD driver to
 *              work with any lcd
 * Author      : Sarah
 ****************************************************************/

#include "gpio.h"
#include "lcd.h"
#include "common_macros.h"
#include<util/delay.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Description:
 * Initialize LCD :
 * 1.by setting up the direction using GPIO driver
 * 2.set up LCD data bit mode 8bit or 4bit mode
 * */
void LCD_init(void)
{
	/* Configure the direction for RS and E pins as output pins */
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);

	/* LCD Power ON delay always > 15ms */
	_delay_ms(20);

#if (LCD_DATA_BITS_MODE == 4)

	/* Configure 4 pins in the data port as output pins */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == 8)

	/* Configure the data port as output port */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);

	_delay_ms(20);		/* LCD Power ON delay always > 15ms */

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif

	/* cursor off */
	LCD_sendCommand(LCD_CURSOR_OFF);
	/* clear LCD at the beginning */
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/*
 * Description: send required commands to the LCD
 */
void LCD_sendCommand (uint8 command)
{
	/*Clear RS pin (to write command)*/
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	/* delay for processing Tas = 50ns */
	_delay_ms(1);
	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	/*in 4 Bit mode we have to send the command MSB 4 bits then LSB 4 bits */
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);
	/*send the LSB 4 bits command*/
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);

#elif (LCD_DATA_BITS_MODE == 8)
	/*Send the command directly*/
	GPIO_writePort(LCD_DATA_PORT_ID,command);
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);

#endif

}

/*
 * Description:
 * display specific characters to the screen
 */
void LCD_displayCharacter(uint8 data)
{
	/*Set RS pin (to write data)*/
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	/* delay for processing Tas = 50ns */
	_delay_ms(1);
	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	/*in 4 Bit mode we have to send the data MSB 4 bits then LSB 4 bits */
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID,GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT (data,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT (data,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT (data,7));

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);
	/*send the LSB 4 bits of data*/
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,3));

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);

#elif (LCD_DATA_BITS_MODE == 8)
	/*Send the command directly*/
	GPIO_writePort(LCD_DATA_PORT_ID,data);
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);

#endif

}
/*
 * Description:
 * Display string to the screen
 *
 */
void LCD_displayString(const uint8 *Str)
{

	uint8 i = 0;

	while (Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}

}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col)
{

	uint8 Lcd_memory_address;
	switch(row)
	{
	case 0:
		Lcd_memory_address = col;
		break;
	case 1:
		Lcd_memory_address = col + 0x40;
		break;
	case 2:
		Lcd_memory_address = col + 0x10;
		break;
	case 3:
		Lcd_memory_address = col + 0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand( Lcd_memory_address | LCD_SET_CURSOR_LOCATION);

}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str){

	LCD_moveCursor(row,col);
	LCD_displayString(Str);

}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data)
{
	/* String to hold the ascii result */
	char buff[16];
	/* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	itoa(data,buff,10);
	/* Display the string */
	LCD_displayString(buff);

}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	/* Clear screen */
	LCD_sendCommand(LCD_CLEAR_COMMAND);

}




