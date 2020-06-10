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

Coord_Typedef c1;
Coord_Typedef c2;
Coord_Typedef c3;
Coord_Typedef c4;
Coord_Typedef c5;
Coord_Typedef c6;

Coord_Typedef* baitCoord;

snake_typedef* snake;
doublyLinkedList_Typedef* list;
int main()
{
    InitializeSnakePtr(&snake,X1,X2,Y1,Y2);
    snake->SnakeframeCreation(X1, Y1, X2 - X1, Y2 - Y1);
    baitCoord = snake->RandomPointCreate();



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



    char keyPress = NULL;
    bool baitIsEaten = false;
    while (true) {
     
        keyPress = NonBlockingKeyPressDetection();


        snake->SnakeUpdate(list, keyPress);              
        snake->Delay(keyPress);
        snake->SnakeDrawBlocking(list,true);
        if (snake->IsBaitEaten(list, baitCoord)){
            snake->SnakeAddNode(list);
            baitCoord = snake->RandomPointCreate();
        }

    }


    
}
 /*
     To Do: 
        *   Don't create random points on the points of snake
        *   Detect self hit
        *   Detect wall hit
        *   multiple threads to exclude delay ...
 */


        //  clearArea(X1 + 1, X2 - 1, Y1 + 1, Y2 - 1);
        //  WriteListData_TestCode(&list);
        //  increaseYaxisTest(&list);
        //  clearArea(X1 + 1, X2 - 1, Y1 + 1, Y2 - 1);


