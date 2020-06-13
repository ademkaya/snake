// snakeApp.c : This file contains the 'main' function. Program execution begins and ends there.
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
Coord_Typedef nodeStartCoord1;

snake_typedef* snake;
doublyLinkedList_Typedef* list;
Coord_Typedef lastPtr           = {0,0};
int main()
{
    InitializeSnakePtr(&snake, X1, X2, Y1, Y2);
    snake->SnakeframeCreation(X1, Y1, X2 - X1, Y2 - Y1);
    nodeStartCoord1 = *(snake->RandomPointCreate(list, false));
    baitCoord = *(snake->RandomPointCreate(list, true));

    AddNode(&list, &nodeStartCoord1);

    snake->SnakeDrawBlocking(list, false);

    char keyPress = 0;

    while (true) {

        keyPress = NonBlockingKeyPressDetection();

        snake->CalcEraseTheLast(list, false);                            /* gets the end coordinate of the snake */

        snake->SnakeUpdate(list, keyPress);
        snake->Delay(keyPress);
        snake->SnakeDrawBlocking(list, false);

        if (snake->IsSelfHit()) {
            ;//comes here.
        }

        if (snake->IsBaitEaten(list, &baitCoord)) {
            snake->SnakeAddNode(list);
            baitCoord = *(snake->RandomPointCreate(list, true));
        }

        if (!snake->IsWallHit()) {
            snake->CalcEraseTheLast(list, true);                        /* erase the last coordinate ,which get previously, from the screen */
        } else {
            ;// comes here.
        }

    }

}
 /*
     To Do: 
        *   Don't create random points on the points of snake   - done
        *   eats out the last point???                          - corrected
        *   Detect self hit                                     - done
        *   Detect wall hit                                     - done
        *   multiple threads to exclude delay                   - ...
        *   score will be added                                 - ...
 */
