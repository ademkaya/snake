﻿// snakeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>
#include <math.h>
#include <conio.h>
#include "doublyLinkedList.h"

//#include <thread>

typedef struct Coord {
    uint16_t X;
    uint16_t Y;
}Coord_Typedef;

static const uint8_t X1 = 10;
static const uint8_t Y1 = 10;
static const uint8_t X2 = 40;
static const uint8_t Y2 = 40;

static const char Hline = (char)205;
static const char Vline = (char)186;
static const char RTCornerline = (char)187;
static const char RBCornerline = (char)188;
static const char LTCornerline = (char)201;
static const char LBCornerline = (char)200;
static const char block        = (char)'O';

static void AddSnakeNode(doublyLinkedList_Typedef* list);
static bool snakeDrawBlocking(doublyLinkedList_Typedef* list, bool eraseTheLast);
static bool snakeDrawNonBlocking(doublyLinkedList_Typedef* list, bool eraseTheLast);
static void UpdateSnake(doublyLinkedList_Typedef* list, char* statickeyPress);
static void frameCreation(uint8_t xOrigin, uint8_t yOrigin, uint8_t xLength, uint8_t yLength);
static char DirectionHandler(void);
static char BlockingkeyPressDetection(void);
static void increaseYaxisTest(doublyLinkedList_Typedef* list);

static bool limitCheck(char direction, Coord_Typedef* axisData);
void move(doublyLinkedList_Typedef* node,bool);
static void WriteListData_TestCode(doublyLinkedList_Typedef* list);
void clearArea(uint16_t XStart, uint16_t XStop, uint16_t YStart, uint16_t YStop);
static void printStringOnSpesificLocation(uint16_t X, uint16_t Y, char* str);
static void printCharOnSpesificLocation(uint16_t X, uint16_t Y, char chr);
static void clearScreen(void);
static bool getChar_(char* ch);
static void Delay(void);


Coord_Typedef c1;
Coord_Typedef c2;
Coord_Typedef c3;
Coord_Typedef c4;
Coord_Typedef c5;
Coord_Typedef c6;

doublyLinkedList_Typedef* list;
int main()
{
    
    frameCreation(X1, Y1, X2 - X1, Y2 - Y1);

    c1.X = X1+10;
    c1.Y = Y1+1;
    c2.X = X1 + 9;
    c2.Y = c1.Y;
    c3.X = X1 + 8;
    c3.Y = c1.Y;
    c4.X = X1 + 7;
    c4.Y = c1.Y;
    c5.X = X1 + 6;
    c5.Y = c1.Y;
    c6.X = X1 + 5;
    c6.Y = c1.Y;

    AddNode(&list, &c1); 
    AddNode(&list, &c2); 
    AddNode(&list, &c3); 
    AddNode(&list, &c4); 
    AddNode(&list, &c5); 
    AddNode(&list, &c6); 

    //headNode = list.Functions.AddMainNode(&c1);
    //           list.Functions.AddSibling(headNode, &c2);
    //           list.Functions.AddSibling(headNode, &c3);
    //           list.Functions.AddSibling(headNode, &c4);
    //           list.Functions.AddSibling(headNode, &c5);
    //           list.Functions.AddSibling(headNode, &c6);

    uint32_t f = 0;
    bool add = false;
    char keyPress = NULL;
    bool refresh = false;
    while (true) {
        if (_kbhit())
        {
            keyPress = BlockingkeyPressDetection();
        }        
        
        // clearArea(X1 + 1, X2 - 1, Y1 + 1, Y2 - 1);
        //WriteListData_TestCode(&list);

        UpdateSnake(list, &keyPress);              
        Delay();
        snakeDrawBlocking(list,true);

        // increaseYaxisTest(&list);
        // clearArea(X1 + 1, X2 - 1, Y1 + 1, Y2 - 1);
    }


    
}


static bool AddSnakeNode(doublyLinkedList_Typedef* list) {
    bool retVal = true;
    doublyLinkedList_Typedef* node = list;
    AddNode(&list, NULL);

    while (node->data) {
        node = node->right;
    }

    node->data = calloc(1, sizeof(Coord_Typedef));

    if (!(node->data))
        retVal = false;
    else
        memcpy(node->data, node->left->data, sizeof(Coord_Typedef));

    return retVal;
}

static void Delay(void) {
    for (uint32_t a = 0; a < 15500000; a++) {
        ;
    }
}
static void increaseYaxisTest(doublyLinkedList_Typedef* list) {
    doublyLinkedList_Typedef* node = list;
    while (node) {
        ((Coord_Typedef*)(node->data))->Y += 1;
        node = node->right;
    }
}

// updates the coordinates relative the button press if there is any.
static void UpdateSnake(doublyLinkedList_Typedef* list, char* statickeyPress) {
    static char direction = 'D';

    *statickeyPress = toupper(*statickeyPress);

    // *****    direction assign
    if (*statickeyPress) {
        bool assign = false;
        if ((*statickeyPress == 'W') && (direction != 'S')) {
            assign = true;
        }
        if ((*statickeyPress == 'S') && (direction != 'W')) {
            assign = true;
        }
        if ((*statickeyPress == 'A') && (direction != 'D')) {
            assign = true;
        }
        if ((*statickeyPress == 'D') && (direction != 'A')) {
            assign = true;
        }
        if (assign) {
            direction = *statickeyPress;
        }
    }

    //limit check
    if (!limitCheck(direction, (Coord_Typedef*)(list->data))) {

        if (direction == 'W') {

            move(list, true);                         // update the list
            ((Coord_Typedef*)(list->data))->Y -= 1;   // update the head      

        }
        else if (direction == 'S') {

            move(list, true);                         // update the list
            ((Coord_Typedef*)(list->data))->Y += 1;   // update the head

        }
        else if (direction == 'A') {

            move(list, true);                         // update the list
            ((Coord_Typedef*)(list->data))->X -= 1;   // update the head

        }
        else if (direction == 'D') {

            move(list, true);                         // update the list
            ((Coord_Typedef*)(list->data))->X += 1;   // update the head
        }

    }

    *statickeyPress = 0;  // consume the value.
}

static bool limitCheck(char direction,Coord_Typedef* axisData) {
    bool retVal = false;
    if ((direction == 'W') && (axisData->Y == Y1+1)) {
        retVal = true;
    }
    else if ((direction == 'S') && (axisData->Y == Y2-1)) {
        retVal = true;
    }
    else if ((direction == 'D') && (axisData->X == X2-1)) {
        retVal = true;
    }
    else if ((direction == 'A') && (axisData->X == X1+1)) {
        retVal = true;
    }
    return retVal;
}

/* listhead stays untouched */
void move(doublyLinkedList_Typedef* node,bool firstCall) {
    static bool lastPtr = NULL;
    if (firstCall)
        lastPtr = false;

    if (node->right) {
        move(node->right, false);
    } else {
        memcpy(node->data, node->left->data, sizeof(Coord_Typedef));
        lastPtr = true;
        return;
    }
    if ((lastPtr) && (node->left)) {
        memcpy(node->data, node->left->data, sizeof(Coord_Typedef));
    }

}
static void WriteListData_TestCode(doublyLinkedList_Typedef* node) {
    unsigned int g = 0;

    while (node) {
        printf("%d    X: %d - Y:%d \n", g++, ((Coord_Typedef*)(node->data))->X, ((Coord_Typedef*)(node->data))->Y);
        node = node->right;
    }
    printf("-----------------------------\n");
}
/*    Draws only linkedlist  in non blocking fashion   */
static bool snakeDrawNonBlocking(doublyLinkedList_Typedef* list,bool eraseTheLast) {
   static doublyLinkedList_Typedef* node = NULL;

   if (node == NULL) {
       node = list;
   }

   printCharOnSpesificLocation(((Coord_Typedef*)(node)->data)->X, ((Coord_Typedef*)(node)->data)->Y, block);


   if (!(node->right) && (eraseTheLast)) {
       printCharOnSpesificLocation(((Coord_Typedef*)(node)->data)->X, ((Coord_Typedef*)(node)->data)->Y, 0);
   }

   node = node->right;

   if (!node)
       return true;

  return false;
}

/*    Draws only linkedlist  in blocking fashion   */
static bool snakeDrawBlocking(doublyLinkedList_Typedef* list,bool eraseTheLast) {

    doublyLinkedList_Typedef* node = NULL;
    
    // initialize...
    if (!node) {
        node = list;
    }

    // draw..
    while (node) {
        // processes
        printCharOnSpesificLocation(((Coord_Typedef*)(node)->data)->X, ((Coord_Typedef*)(node)->data)->Y, block);

        if (!(node->right) && (eraseTheLast)) {
            printCharOnSpesificLocation(((Coord_Typedef*)(node)->data)->X, ((Coord_Typedef*)(node)->data)->Y, 0);
        }

        node = node->right;
    }

    return true;
}

/*    Clear the inside area    */
void clearArea(uint16_t XStart, uint16_t XStop, uint16_t YStart, uint16_t YStop) {
    uint16_t xtemp = 0;
    uint16_t ytemp = 0;
    for (xtemp = XStart; xtemp < XStop; xtemp++) {
        for (ytemp = YStart; ytemp < YStop; ytemp++) {
            printCharOnSpesificLocation(xtemp, ytemp, 0);
        }
    }
     
}


static char DirectionHandler(void) {
    char keyPress = BlockingkeyPressDetection();
    char retVal = NULL;
    if ((keyPress == 'A') || (keyPress == 'a')) {
        //printCharOnSpesificLocation(X1, Y1, 'A');
        retVal = 'A';
    }
    else if ((keyPress == 'W') || (keyPress == 'w')) {
        //printCharOnSpesificLocation(X1, Y1, 'W');
        retVal = 'W';
    }
    else if ((keyPress == 'D') || (keyPress == 'd')) {
        //printCharOnSpesificLocation(X1, Y1, 'D');
        retVal = 'D';
    }
    else if ((keyPress == 'S') || (keyPress == 's')) {
        //printCharOnSpesificLocation(X1, Y1, 'S');
        retVal = 'S';
    }
    return retVal;
}
static void frameCreation(uint8_t xOrigin, uint8_t yOrigin, uint8_t xLength, uint8_t yLength) {

    // xLength *= 2; //to equalize the image   ... will be activate later on

    printCharOnSpesificLocation(xOrigin, yOrigin, LTCornerline);
    printCharOnSpesificLocation(xOrigin+ xLength, yOrigin, RTCornerline);

    printCharOnSpesificLocation(xOrigin, yOrigin+ yLength, LBCornerline);
    printCharOnSpesificLocation(xOrigin + xLength, yOrigin+ yLength, RBCornerline);


    for (uint8_t x = 1; x < xLength; x++) {
        printCharOnSpesificLocation(xOrigin+x, yOrigin, Hline);
        printCharOnSpesificLocation(xOrigin+x, yOrigin+ yLength, Hline);
    }
    for (uint8_t y = 1; y < yLength; y++) {
        printCharOnSpesificLocation(xOrigin, yOrigin+y, Vline);
        printCharOnSpesificLocation(xOrigin+ xLength, yOrigin+y, Vline);
    }

}
static void printStringOnSpesificLocation(uint16_t X, uint16_t Y, char* str) {
    printf("\337\33[%d;%dH%s\338", Y, X, str);
}
static void printCharOnSpesificLocation(uint16_t X, uint16_t Y, char chr) {
    printf("\337\33[%d;%dH%c\338", Y, X, chr);
}
static char BlockingkeyPressDetection(void)
{
    static char ch = 0;
    getChar_(&ch);
    return(ch);
}

static bool getChar_(char* ch)
{
    bool    ret = false;

    HANDLE  stdIn = GetStdHandle(STD_INPUT_HANDLE);

    DWORD   saveMode;
    GetConsoleMode(stdIn, &saveMode);
    SetConsoleMode(stdIn, ENABLE_PROCESSED_INPUT);

    if (WaitForSingleObject(stdIn, INFINITE) == WAIT_OBJECT_0)
    {
        DWORD num;
        ReadConsole(stdIn, ch, 1, &num, NULL);

        if (num == 1) ret = true;
    }

    SetConsoleMode(stdIn, saveMode);

    return(ret);
}
static void clearScreen(void) {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}



#if false
// updates the coordinates relative the button press if there is any.
static void UpdateSnake(LinkedList_Typedef* list, char* statickeyPress) {
    /* not implemented yet.*/
    static char direction = 'D';
    static char pre_direction;
    static node_Typedef* node = NULL;

    // *****    node assign
    if (!node) {
        node = list->ListHead;
    }

    // *****    direction assign
    if (*statickeyPress) {
        bool assign = false;
        if ((*statickeyPress == 'W') && (pre_direction != 'S')) {
            assign = true;
        }
        if ((*statickeyPress == 'S') && (pre_direction != 'W')) {
            assign = true;
        }
        if ((*statickeyPress == 'A') && (pre_direction != 'D')) {
            assign = true;
        }
        if ((*statickeyPress == 'D') && (pre_direction != 'A')) {
            assign = true;
        }
        if (assign) {
            direction = *statickeyPress;
        }
    }


    if (direction == 'W') {

        if (node == list->ListHead)
            ((Coord_Typedef*)(node->data))->Y -= 1;
        else
            ((Coord_Typedef*)(node->right->data))->Y = (((Coord_Typedef*)(node->left->data))->Y) + 1;

    }
    else if (direction == 'S') {

        if (node == list->ListHead)
            ((Coord_Typedef*)(node->data))->Y += 1;
        else
            ((Coord_Typedef*)(node->right->data))->Y = (((Coord_Typedef*)(node->left->data))->Y) - 1;

    }
    else if (direction == 'A') {

        if (node == list->ListHead)
            ((Coord_Typedef*)(node->data))->X -= 1;
        else
            ((Coord_Typedef*)(node->right->data))->X = (((Coord_Typedef*)(node->left->data))->X) + 1;

    }
    else if (direction == 'D') {

        if (node == list->ListHead)
            ((Coord_Typedef*)(node->data))->X += 1;
        else
            ((Coord_Typedef*)(node->right->data))->X = (((Coord_Typedef*)(node->left->data))->X) - 1;
    }


    node = node->right;
    pre_direction = direction;
    *statickeyPress = 0;  // consume the value.
}
#endif