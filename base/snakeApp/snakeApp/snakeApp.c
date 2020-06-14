// snakeApp.c : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "print.h"
#include "snakeSrc.h"
#include "doublyLinkedList.h"

//#include <thread>

static const uint8_t X1 = 2;
static const uint8_t Y1 = 1;
static const uint8_t X2 = 80;
static const uint8_t Y2 = 40;
static Coord_Typedef scoreStrCoord = { 0,0 };
static Coord_Typedef BaitStrCoord = { 0,0 };

Coord_Typedef baitCoord;
Coord_Typedef nodeStartCoord1;

snake_typedef* snake;
doublyLinkedList_Typedef* list;
Coord_Typedef lastPtr           = {0,0};

static uint16_t baitsEaten = 0;
static uint32_t Score = 0;
static void ScoreBoardUpdate(Coord_Typedef* ScoreStrCoord, Coord_Typedef* BaitStrCoord, uint16_t baitsEaten, uint32_t score);       // will be moved in snakeSrc.c
int main()
{

    scoreStrCoord.X = X2 + 2;
    scoreStrCoord.Y = Y1 + 1;
    BaitStrCoord.X = scoreStrCoord.X;
    BaitStrCoord.Y = scoreStrCoord.Y + 2;

    InitializeSnakePtr(&snake, X1, X2, Y1, Y2);
    snake->SnakeframeCreation(X1, Y1, X2 - X1, Y2 - Y1);
    // score screen
    snake->SnakeframeCreation(X2+1, Y1, 20, 5);

    snake->printStringOnSpesificLocation(scoreStrCoord.X, scoreStrCoord.Y, (char*)&"Score : ");
    snake->printStringOnSpesificLocation(BaitStrCoord.X, BaitStrCoord.Y, (char*)&"Bait : ");

    nodeStartCoord1 = *(snake->RandomPointCreate(list, false));
    baitCoord       = *(snake->RandomPointCreate(list, true));

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
            ; // game finish flag comes here.
        }

        if (snake->IsBaitEaten(list, &baitCoord)) {
            snake->SnakeAddNode(list);
            baitCoord = *(snake->RandomPointCreate(list, true));

            if (!snake->IsWallHit() && !snake->IsSelfHit()) {
                baitsEaten += 1;
                Score += 1;
            }

        } else {
            if (!snake->IsWallHit() && !snake->IsSelfHit())
                Score += 1;
        }

        if (!snake->IsWallHit()) {
            snake->CalcEraseTheLast(list, true);                        /* erase the last coordinate ,which get previously, from the screen */
        } else {
            ;   // game finish flag comes here.
        }

        if (!snake->IsWallHit()&& !snake->IsSelfHit())
            ScoreBoardUpdate(&scoreStrCoord,&BaitStrCoord,baitsEaten,Score);
    }

}
static void ScoreBoardUpdate(Coord_Typedef* ScoreStrCoord, Coord_Typedef* BaitStrCoord, uint16_t baitsEaten, uint32_t score) {
    char chrscore[10];
    char chrbait[5];
    snprintf(chrscore, 10, "%d", score);
    snprintf(chrbait, 5, "%d", baitsEaten);

    snake->printStringOnSpesificLocation(ScoreStrCoord->X+8, ScoreStrCoord->Y, &chrscore[0]);
    snake->printStringOnSpesificLocation(BaitStrCoord->X+7, BaitStrCoord->Y, &chrbait[0]);
}

 /*
     To Do: 
        *   Don't create random points on the points of snake   - done
        *   eats out the last point???                          - done
        *   Detect self hit                                     - done
        *   Detect wall hit                                     - done
        *   multiple threads to exclude delay                   - ...
        *   score will be added                                 - done
        *   end of game because of collision                    - ...
        *   successfully completed game detection               - ...
        *   sometimes bait doesnt come up even tough there is enough place - ... inspect
        *   portability issue will be considered                - ...
 */
