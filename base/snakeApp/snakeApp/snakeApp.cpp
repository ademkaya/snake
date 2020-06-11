// snakeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <conio.h>

#include "print.h"
#include "snakeSrc.h"
#include "doublyLinkedList.h"

//#include <thread>

static const uint8_t X1 = 2;
static const uint8_t Y1 = 1;
static const uint8_t X2 = 40;
static const uint8_t Y2 = 20;

Coord_Typedef baitCoord;
Coord_Typedef nodeStartCoord;

snake_typedef* snake;
doublyLinkedList_Typedef* list;
int main()
{
    InitializeSnakePtr(&snake,X1,X2,Y1,Y2);
    snake->SnakeframeCreation(X1, Y1, X2 - X1, Y2 - Y1);
    nodeStartCoord = *(snake->RandomPointCreate(list,false));
    baitCoord      = *(snake->RandomPointCreate(list,true));
    
    AddNode(&list, &nodeStartCoord);




    char keyPress = NULL;
    bool baitIsEaten = false;
    while (true) {
     
        keyPress = NonBlockingKeyPressDetection();


        snake->SnakeUpdate(list, keyPress);              
        snake->Delay(keyPress);
        snake->SnakeDrawBlocking(list,true);
        if (snake->IsBaitEaten(list, &baitCoord)){
            snake->SnakeAddNode(list);
            baitCoord = *(snake->RandomPointCreate(list,true));
        }

    }


    
}
 /*
     To Do: 
        *   Don't create random points on the points of snake -- done
        *   Detect self hit
        *   Detect wall hit
        *   multiple threads to exclude delay ...
 */


        //  clearArea(X1 + 1, X2 - 1, Y1 + 1, Y2 - 1);
        //  WriteListData_TestCode(&list);
        //  increaseYaxisTest(&list);
        //  clearArea(X1 + 1, X2 - 1, Y1 + 1, Y2 - 1);


