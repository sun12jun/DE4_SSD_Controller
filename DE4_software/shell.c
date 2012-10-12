/*
 * shell.c
 *
 *  Created on: 2012. 9. 24.
 *      Author: ydj
 */

#include <stdio.h>
#include <string.h>
//#include <altera_avalon_jtag_uart_regs.h>
#include <io.h>
#include "includes.h"
#include "shell.h"
#include "my_ctype.h"
#include "alt_ucosii_simple_error_check.h"

/*	semaphore declaration	*/

/*-----------------------------------------------------------*/
void task_shell(void *parg)
{
	INT16U num, i;
	char cChar, command[100], string[6][16], *token[6];

	for(i=0;i<6;i++) token[i]=string[i];

	viewlogo();
	printf("DE4_SSD > ");

	i = 0;
	for(;;)
	{
		cChar = getc(stdin);

		if(cChar >= 0)
		{
			if(cChar == CHAR_LF)
			{
				command[i++] = '\0';
				num = GetToken(token, command);

				if(num > 0) 
					Interpreter(token, num);
				else
					viewlogo();

				printf("DE4_SSD > ");
				i=0;
			}
			else
			{
				printf("%c", cChar);
				command[i++] = cChar;
			}
		}

		OSTimeDlyHMSM(0, 0, 0, 5);
	}
}

//-------------------------------------------------------------------------------
void viewlogo()
{
	printf("\n");
	printf("***************************************************\n");
	printf("*                        DE4_SSD                  *\n");
	printf("***************************************************\n");
}


//-------------------------------------------------------------------------------
INT16U GetToken(INT8S **token, INT8S *string)
{
	INT16U si=0, di=0, num=0;
	INT8S temp;

	while((temp=string[si++])!='\0'){
		if(temp==CHAR_SPACE | temp==CHAR_TAB){
			*(*(token+num)+di)='\0';
			num++;
			di=0;
		}else{
			*(*(token+num)+di++)=temp;
		}
	}
	*(*(token+num)+di)='\0';
	num++;

	return num;
}

void Interpreter(INT8S **token, INT16U num)
{
//	INT32U param[5];

	if(!strcmp(token[0],"") && num==1)
	{
		viewlogo();
	}
	else if(!strcmp(token[0],"info") && num==1)
	{
		get_info();
	}
	else
		printf("\nInvalid Command\n");
}
//-------------------------------------------------------------------------------

void IntToStr(INT8S *str, INT32S value, INT32S radix)
{
	INT8S DigitMap[]="0123456789abcdef", tmpChar;
	INT32S a, len;

	INT8S *start=str;
	INT32S quotient=value;

	do{
		*str=DigitMap[(INT32S)(quotient%radix)];
		str++;
		quotient/=radix;
	}while(quotient);

	*str='\0';
	str=start;
	len=strlen(str);

	for(a=0;a<len/2;a++){
		tmpChar=str[a];
		str[a]=str[len-1-a];
		str[len-1-a]=tmpChar;
	}
}
//-------------------------------------------------------------------------------

INT32U StrToInt(INT8S *str, INT32U radix)
{
	INT32U result = 0,value;

	radix = 10;
	if (*str == '0') {
		str++;
		if ((*str == 'x') && isxdigit(str[1])) {
			radix = 16;
			str++;
		}
		else{
			radix = 10;
		}
	}

	while ( isxdigit(*str) && (value = isdigit(*str)? *str-'0' : (islower(*str)? toupper(*str) : *str)-'A'+10) < radix )
	{
		result = result*radix + value;
		str++;
	}

	return result;
}

void get_info()
{
	printf("\n");
	printf("***************************\n");
	printf("* SSD controller using FPGA\n");
	printf("* Core : Nios2             \n");
	printf("* Mem  : DDR2              \n");
	printf("***************************\n");
}

void mem_display(INT32U BaseAddr)
{
	volatile INT32U* piBase;
	volatile INT8U* pcBase;
	INT8U i, j;
	INT8U md[64];

	piBase = (volatile INT32U*)(BaseAddr);
	pcBase = (volatile INT8U*)(BaseAddr);

	if(BaseAddr & 0x3 != 0)
	{
		printf("\nPlease address align by word size");
		return;
	}

	for(i = 0; i < 16; i++)
	{
		printf("\n%08lx: %08lx %08lx %08lx %08lx    ", piBase, *piBase, *(piBase+1), *(piBase+2), *(piBase+3)); // 4 byte display(integer)
		piBase += 4;

		for(j = 0; j < 16; j++) // 4 byte display(ascii)
		{
			printf((isprint(*(pcBase)) && (*(pcBase) < 0x80))? *(pcBase) : '.');
			pcBase++;
		}
	}	 
}

/*
void task_shell(void *parg)
{
	char cChar;
	int i;
	INT8U err;

	i = 0;

	ViewLogo2();

	jtag_uart_tx_str("\nDE4_SSD > ");

	for(;;)
	{
		cChar = jtag_uart_rx_byte();
		if(cChar >= 0)
		{
			if(cChar == CHAR_CR)
			{
				ViewLogo2();

				jtag_uart_tx_str("\nDE4_SSD_CR > ");
				i=0;
			}
			else
			{
				jtag_uart_tx_byte(cChar);
				i++;
			}
		}
		//OSTimeDlyHMSM(0, 0, 0, 5);
	}
}

void ViewLogo2()
{
	jtag_uart_tx_str("\n");
	jtag_uart_tx_str("***************************************************\n");
	jtag_uart_tx_str("*                        DE4_SSD                  *\n");
	jtag_uart_tx_str("***************************************************\n");
}

 */
