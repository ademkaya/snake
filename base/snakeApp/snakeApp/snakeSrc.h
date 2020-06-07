/*
 * File:   snakeSrc.h
 * Author: Adem
 *
 * Started on Jun , 2020, 6:11 PM
 */

#ifndef __SNAKESOURCE_H__
#define __SNAKESOURCE_H__

#include <stdlib.h>
#include <stdint.h>
#include "doublyLinkedList.h"


#ifdef __cplusplus
extern "C" {
#endif


	typedef struct Coord {
		uint16_t X;
		uint16_t Y;
	}Coord_Typedef;

	typedef struct snake {
		void (*Delay)							(char);
		bool (*SnakeAddNode)					(doublyLinkedList_Typedef* list);
		void (*SnakeUpdate)						(doublyLinkedList_Typedef* list, char statickeyPress);
		bool (*SnakeLimitCheck)					(char direction, Coord_Typedef* axisData);
		void (*SnakeMove)						(doublyLinkedList_Typedef* node, bool firstCall);
		bool (*SnakeDrawNonBlocking)			(doublyLinkedList_Typedef* list, bool eraseTheLast);
		bool (*SnakeDrawBlocking)				(doublyLinkedList_Typedef* list, bool eraseTheLast);
		void (*SnakeClearArea)					(uint16_t XStart, uint16_t XStop, uint16_t YStart, uint16_t YStop);
		char (*SnakeDirectionHandler)			(char keyPress);
		void (*SnakeframeCreation)				(uint8_t xOrigin, uint8_t yOrigin, uint8_t xLength, uint8_t yLength);
		void (*WriteListData_TestCode)			(doublyLinkedList_Typedef* node);
		void (*increaseYaxis_TestCode)			(doublyLinkedList_Typedef* list);

		void (*printStringOnSpesificLocation)	(uint16_t X, uint16_t Y, char* str);
		void (*printCharOnSpesificLocation)		(uint16_t X, uint16_t Y, char chr);
		char (*BlockingkeyPressDetection)		(void);
	}snake_typedef;


	bool InitializeSnakePtr(snake_typedef** ptr, uint32_t XLow, uint32_t XHigh, uint32_t YLow, uint32_t YHigh);



#ifdef __cplusplus
}
#endif
#endif /* __SNAKESOURCE_H__ */