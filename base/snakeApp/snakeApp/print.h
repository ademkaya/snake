/*
 * File:   printf.h
 * Author: Adem
 *
 * Started on Jun , 2020, 22:22 PM
 */

#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdint.h>
#include <stdbool.h>
//#include <windows.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif


	void printCharOnSpesificLocation(uint16_t X, uint16_t Y, char chr);
	void printStringOnSpesificLocation(uint16_t X, uint16_t Y, char* str);
	char NonBlockingKeyPressDetection(void);
	char BlockingkeyPressDetection(void);
	void clearScreen(void);
	bool getChar_(char* ch);


#ifdef __cplusplus
}
#endif	/* __PRINT_H__ */
#endif