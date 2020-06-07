#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "snakeSrc.h"
#include "print.h"

static const char Hline = (char)205;
static const char Vline = (char)186;
static const char RTCornerline = (char)187;
static const char RBCornerline = (char)188;
static const char LTCornerline = (char)201;
static const char LBCornerline = (char)200;
static const char block = (char)'O';

const uint32_t vertSpeed = 31000000;
const uint32_t horzSpeed = 18000000;

static uint16_t X1 = 0;
static uint16_t X2 = 0;
static uint16_t Y1 = 0;
static uint16_t Y2 = 0;

static void Delay(char);
static bool SnakeAddNode(doublyLinkedList_Typedef* list);
static void SnakeUpdate(doublyLinkedList_Typedef* list, char* statickeyPress);
static bool SnakeLimitCheck(char direction, Coord_Typedef* axisData);
       void SnakeMove(doublyLinkedList_Typedef* node, bool firstCall);
static bool SnakeDrawNonBlocking(doublyLinkedList_Typedef* list, bool eraseTheLast);
static bool SnakeDrawBlocking(doublyLinkedList_Typedef* list, bool eraseTheLast);
static void SnakeClearArea(uint16_t XStart, uint16_t XStop, uint16_t YStart, uint16_t YStop);
static char SnakeDirectionHandler(char keyPress);
static void SnakeframeCreation(uint8_t xOrigin, uint8_t yOrigin, uint8_t xLength, uint8_t yLength);
static void WriteListData_TestCode(doublyLinkedList_Typedef* node);
static void increaseYaxis_TestCode(doublyLinkedList_Typedef* list);


bool InitializeSnakePtr(snake_typedef** ptr,uint32_t XLow,uint32_t XHigh, uint32_t YLow, uint32_t YHigh) {
    bool retVal = true;

    *ptr = calloc(1, sizeof(snake_typedef));
    if (!(*ptr))
        retVal = false;

    if (retVal){
        (*ptr)->Delay = &Delay;        
        (*ptr)->SnakeAddNode = &SnakeAddNode;
        (*ptr)->SnakeClearArea = &SnakeClearArea;
        (*ptr)->SnakeDirectionHandler = &SnakeDirectionHandler;
        (*ptr)->SnakeDrawBlocking = &SnakeDrawBlocking;
        (*ptr)->SnakeDrawNonBlocking = &SnakeDrawNonBlocking;
        (*ptr)->SnakeframeCreation = &SnakeframeCreation;
        (*ptr)->SnakeLimitCheck = &SnakeLimitCheck;
        (*ptr)->SnakeMove = &SnakeMove;
        (*ptr)->SnakeUpdate = &SnakeUpdate;
        (*ptr)->WriteListData_TestCode = &WriteListData_TestCode;
        (*ptr)->increaseYaxis_TestCode = &increaseYaxis_TestCode;

        X1 = XLow;
        X2 = XHigh;
        Y1 = YLow;
        Y2 = YHigh;
    }
    return retVal;
}
/*Adds node on the last end of the linkedlist*/
static bool SnakeAddNode(doublyLinkedList_Typedef* list) {
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
static void Delay(char keyPress) {
    static char lastKey = 'D';
    uint32_t a = 0;
    if ((lastKey == 'A') || (lastKey == 'D')) {
        for (a = 0; a < horzSpeed; a++) {
            ;
        }
    }
    if ((lastKey == 'S') || (lastKey == 'W')) {
        for (a = 0; a < vertSpeed; a++) {
            ;
        }
    }

    if (keyPress!=0)
        lastKey = toupper(keyPress);
}
static void SnakeUpdate(doublyLinkedList_Typedef* list, char statickeyPress) {
    static char direction = 'D';

    statickeyPress = toupper(statickeyPress);

    // *****    direction assign
    if (statickeyPress) {
        bool assign = false;
        if ((statickeyPress == 'W') && (direction != 'S')) {
            assign = true;
        }
        if ((statickeyPress == 'S') && (direction != 'W')) {
            assign = true;
        }
        if ((statickeyPress == 'A') && (direction != 'D')) {
            assign = true;
        }
        if ((statickeyPress == 'D') && (direction != 'A')) {
            assign = true;
        }
        if (assign) {
            direction = statickeyPress;
        }
    }

    //limit check
    if (!SnakeLimitCheck(direction, (Coord_Typedef*)(list->data))) {

        if (direction == 'W') {

            SnakeMove(list, true);                    // update the list
            ((Coord_Typedef*)(list->data))->Y -= 1;   // update the head      

        }
        else if (direction == 'S') {

            SnakeMove(list, true);                    // update the list
            ((Coord_Typedef*)(list->data))->Y += 1;   // update the head

        }
        else if (direction == 'A') {

            SnakeMove(list, true);                    // update the list
            ((Coord_Typedef*)(list->data))->X -= 1;   // update the head

        }
        else if (direction == 'D') {

            SnakeMove(list, true);                    // update the list
            ((Coord_Typedef*)(list->data))->X += 1;   // update the head
        }

    }
    // there is no need to zero the keypress, it is going to clear in next turn if nothing detected.
}
static bool SnakeLimitCheck(char direction, Coord_Typedef* axisData) {
    bool retVal = false;
    if ((direction == 'W') && (axisData->Y == Y1 + 1)) {
        retVal = true;
    }
    else if ((direction == 'S') && (axisData->Y == Y2 - 1)) {
        retVal = true;
    }
    else if ((direction == 'D') && (axisData->X == X2 - 1)) {
        retVal = true;
    }
    else if ((direction == 'A') && (axisData->X == X1 + 1)) {
        retVal = true;
    }
    return retVal;
}
/*recursive*/
void SnakeMove(doublyLinkedList_Typedef* node, bool firstCall) {
    static bool lastPtr;

    if (firstCall)
        lastPtr = false;

    if (node->right) {
        SnakeMove(node->right, false);
    }
    else {
        memcpy(node->data, node->left->data, sizeof(Coord_Typedef));
        lastPtr = true;
        return;
    }
    if ((lastPtr) && (node->left)) {
        memcpy(node->data, node->left->data, sizeof(Coord_Typedef));
    }

}
static bool SnakeDrawNonBlocking(doublyLinkedList_Typedef* list, bool eraseTheLast) {
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
static bool SnakeDrawBlocking(doublyLinkedList_Typedef* list, bool eraseTheLast) {

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
static void SnakeClearArea(uint16_t XStart, uint16_t XStop, uint16_t YStart, uint16_t YStop) {
    uint16_t xtemp = 0;
    uint16_t ytemp = 0;
    for (xtemp = XStart; xtemp < XStop; xtemp++) {
        for (ytemp = YStart; ytemp < YStop; ytemp++) {
            printCharOnSpesificLocation(xtemp, ytemp, 0);
        }
    }

}
static char SnakeDirectionHandler(char keyPress) {
    char retVal = 0;
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
static void SnakeframeCreation(uint8_t xOrigin, uint8_t yOrigin, uint8_t xLength, uint8_t yLength) {
    // xLength *= 2; //to equalize the image   ... will be activate later on

    printCharOnSpesificLocation(xOrigin, yOrigin, LTCornerline);
    printCharOnSpesificLocation(xOrigin + xLength, yOrigin, RTCornerline);

    printCharOnSpesificLocation(xOrigin, yOrigin + yLength, LBCornerline);
    printCharOnSpesificLocation(xOrigin + xLength, yOrigin + yLength, RBCornerline);


    for (uint8_t x = 1; x < xLength; x++) {
        printCharOnSpesificLocation(xOrigin + x, yOrigin, Hline);
        printCharOnSpesificLocation(xOrigin + x, yOrigin + yLength, Hline);
    }
    for (uint8_t y = 1; y < yLength; y++) {
        printCharOnSpesificLocation(xOrigin, yOrigin + y, Vline);
        printCharOnSpesificLocation(xOrigin + xLength, yOrigin + y, Vline);
    }
}

/* ---- TEST CODE ---- */
static void WriteListData_TestCode(doublyLinkedList_Typedef* node) {
    unsigned int g = 0;

    while (node) {
        printf("%d    X: %d - Y:%d \n", g++, ((Coord_Typedef*)(node->data))->X, ((Coord_Typedef*)(node->data))->Y);
        node = node->right;
    }
    printf("-----------------------------\n");
}
/* ---- TEST CODE ---- */
static void increaseYaxis_TestCode(doublyLinkedList_Typedef* list) {
    doublyLinkedList_Typedef* node = list;
    while (node) {
        ((Coord_Typedef*)(node->data))->Y += 1;
        node = node->right;
    }
}