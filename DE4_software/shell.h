/*
 * shell.h
 *
 *  Created on: 2012. 9. 24.
 *      Author: ydj
 */

#ifndef SHELL_H_
#define SHELL_H_

//#include "includes.h"

#define	CHAR_LF          10
#define CHAR_CR          13
#define CHAR_ESC         27
#define CHAR_BACKSPACE   8
#define CHAR_TAB         9
#define CHAR_SPACE       32

#define CHAR_UP			 65
#define CHAR_DOWN		 66
#define CHAR_RIGHT		 67
#define CHAR_LEFT		 68
//#define COMMAND_STACK_SIZE 8

void task_shell(void *);


void viewlogo();
void get_info();
//void ViewLogo2();

INT16U GetToken(INT8S **token, INT8S *string);
void Interpreter(INT8S **token, INT16U num);
void IntToStr(INT8S *str, INT32S value, INT32S radix);
INT32U StrToInt(INT8S *str, INT32U radix);

#endif /* SHELL_H_ */
