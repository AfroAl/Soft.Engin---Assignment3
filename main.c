#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "crossfireOperations.h"
#define MAX_PLAY 6
#define MAX_SLOT 7

int main(void)
{
    enum playerType playerType[4];
    int row, column, boardSize, playSize;
    srand(time(NULL));
    int i=0, a, b, j;

    struct slot *currSlot = NULL;
    struct slot *foundSlots;
    bool explored[BOARD_SIZE][BOARD_SIZE];
    int count=0;

    struct slot *upLeft;
    struct slot *upRight;
    struct slot *downLeft;
    struct slot *downRight;

    struct player players[MAX_PLAY];
    struct player x[MAX_PLAY][MAX_PLAY];

    struct slot slots[MAX_SLOT][MAX_SLOT];


    printf("Please enter the number of players (Max 6): ");
    scanf("%d", &playSize);

    if(playSize>6 && playSize<2)
    {
        printf("Please restart the program with between 2 and 6 players.\n");
        exit(0);
    }

    printf("Each player next must choose an archtype.\n");
    printf("Human(0), Ogre(1), Wizard(2), Elf(3)\n");

    while(i<playSize)
    {
        scanf("%s %d", players[i].Name , &(players[i].Type));
        i++;
    }

    //-------------------------------------------------------------------------------------

    boardSize = getBoardSize();

    createBoard(BOARD_SIZE,&upLeft, &upRight, &downLeft, &downRight);

    for(i=0;i<boardSize;i++)
    {
        for(j=0;j<boardSize;j++)
        {
            slots[i][j].place[i][j] = 0;
        }
    }

    i=1;
    while(i<=playSize)
    {
        a = rand()%boardSize;
        b = rand()%boardSize;

        slots[a][b].place[a][b] = i;
        i++;
    }

    printf("\n");

    //Gives each slot a random slot type
    for(i=0;i<boardSize;i++)
    {
        for(j=0;j<boardSize;j++)
        {
            slots[i][j].terrainType=rand() % 3 + 1;
        }
    }

    // Sets all lifepoints to 100
    for(i=0;i<playSize;i++)
    {
        players[i].lifePoints = 100;
    }

    //--------------------------------------------------------------------------------------

    // Sets Capabilities of each archtype
    for(i=0;i<playSize;i++)
    {
        if(players[i].Type == playerType[0])
        {
            players[i].Smarts = 70 + rand()%31;
            players[i].Strength = 1 + rand()%50;
            players[i].Magic = 51 + rand()%30;
            players[i].Luck = 60 + rand()%41;
            players[i].Dex = 1 + rand()%100;      
        }
        else if(players[i].Type == playerType[1])
        {
            int total=0;
            while(total<300)
            {
                players[i].Smarts = 1 + rand()%100;
                players[i].Strength = 1 + rand()%100;
                players[i].Magic = 1 + rand()%100;
                players[i].Luck = 1 + rand()%100;
                players[i].Dex = 1 + rand()%100;

                total = players[i].Smarts + players[i].Strength + players[i].Magic + players[i].Luck + players[i].Dex;
            }
        }
        else if(players[i].Type == playerType[2])
        {
            int sum=0;
            while(sum<=50)
            {
                players[i].Smarts = rand()%21;
                players[i].Strength = 80 + rand()%21;
                players[i].Magic = 0;
                players[i].Luck = rand()%101;
                players[i].Dex = 80 + rand()%21;

                sum = players[i].Smarts + players[i].Luck;
            } 
        }
        else if(players[i].Type == playerType[4])
        {
            players[i].Smarts = 90 + rand()%11;
            players[i].Strength = 1 + rand()%20;
            players[i].Magic = 80 + rand()%21;
            players[i].Luck = 50 + rand()%51;
            players[i].Dex = 1 + rand()%100;
        }
    }

    //-----------------------------------------------------------------------------------------

    int quitCheck[playSize], liveCheck=playSize, quit=0;

    for(i=0;i<playSize;i++)
    {
        quitCheck[i] = -1;
    }

    while(liveCheck != 1 && quit != playSize)
    {
        for(int playNum=0;playNum<playSize;playNum++)
        {
            for(a=0;a<playSize;a++)
            {
                if(quitCheck[a] == playNum)
                {
                    printf("DURP\n");
                }
            }

            char ans;
            printf("\n");
            printf("Player %d's Turn:\n", playNum+1);
            printf("Would you like to move(M), attack(A) a player or quit(Q) the game?\n");
            scanf(" %c", &ans);

            //Player wants to move
            if(ans == 'M')
            {
                for(a=0;a<boardSize;a++)
                {
                    for(b=0;b<boardSize;b++)
                    {
                        if(slots[a][b].place[a][b] == playNum+1)
                        {
                            row = a;
                            column = b;
                        }
                    }
                }

                getDesiredElement(BOARD_SIZE, &row,&column);

                if(row >= BOARD_SIZE/2)
                {
                    if(column >= BOARD_SIZE/2)
                    {
                        currSlot = reachDesiredElement(row,column,downRight);
                    } 
                    else
                    {
                        currSlot = reachDesiredElement(row,column,downLeft);
                    }
                }
                else
                {
                    if(column >= BOARD_SIZE/2)
                    {  
                        currSlot = reachDesiredElement(row,column, upRight);
                    }
                    else
                    {
                        currSlot = reachDesiredElement(row,column,upLeft);
                    }
                }
                    /*int moveChoice;
                    if(((currSlot->column) == 0) && ((currSlot->row) == 0))
                    {
                        printf("You can only move down(0) or right(1): ");
                        scanf("%d", &moveChoice);

                        if(moveChoice==0)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowPlus1;
                            currSlot->rowPlus1 = currSlot->tmpR;
                        }
                        else if (moveChoice==1)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colPlus1;
                            currSlot->colPlus1 = currSlot->tmpC;
                        }
                        else
                        {
                            printf("You have just forfeited your turn.\n");
                        }
                    }
                    else if(((currSlot->column) > 0) && (currSlot->column < 6) && ((currSlot->row) == 0))
                    {
                        printf("You can move left(0), down(1) or right(2): ");
                        scanf("%d", &moveChoice);

                        if(moveChoice==0)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colMinus1;
                            currSlot->colMinus1 = currSlot->tmpC;
                        }
                        else if(moveChoice==1)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowPlus1;
                            currSlot->rowPlus1 = currSlot->tmpR;
                        }
                        else if(moveChoice==2)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colPlus1;
                            currSlot->colPlus1 = currSlot->tmpC;
                        }
                        else
                        {
                            printf("You have just forfeited your turn.\n");
                        }
                    }
                    else if(((currSlot->column) == 6) && ((currSlot->row) == 0))
                    {
                        printf("You can only move left(0) or down(1): ");
                        scanf("%d", &moveChoice);

                        if(moveChoice==0)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colMinus1;
                            currSlot->colMinus1 = currSlot->tmpC;
                        }
                        else if(moveChoice==1)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowPlus1;
                            currSlot->rowPlus1 = currSlot->tmpR;
                        }
                        else
                        {
                            printf("You have just forfeited your turn.\n");
                        }
                    }
                    else if(((currSlot->column) == 6) && ((currSlot->row) > 0) && ((currSlot->row) < 6))
                    {
                        printf("You can move up(0), left(1) or down(2): ");
                        scanf("%d", &moveChoice);

                        if(moveChoice==0)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowMinus1;
                            currSlot->rowMinus1 = currSlot->tmpR; 
                        }
                        else if(moveChoice==1)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colMinus1;
                            currSlot->colMinus1 = currSlot->tmpC;
                        }
                        else if(moveChoice==2)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowPlus1;
                            currSlot->rowPlus1 = currSlot->tmpR;
                        }
                        else
                        {
                            printf("You have just forfeited your turn.\n");
                        }
                    }
                    else if(((currSlot->column) == 6) && ((currSlot->row) == 6))
                    {
                        printf("You can only move up(0) or left(1): ");
                        scanf("%d", &moveChoice);

                        if(moveChoice==0)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowMinus1;
                            currSlot->rowMinus1 = currSlot->tmpR;
                        }
                        else if(moveChoice==1)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colMinus1;
                            currSlot->colMinus1 = currSlot->tmpC;
                        }
                        else
                        {
                            printf("You have just forfeited your turn.\n");
                        }
                    }
                    else if(((currSlot->column) > 0) && ((currSlot->column < 6) && (currSlot->row) == 6))
                    {
                        printf("You can move left(0), up(1) or right(2): ");
                        scanf("%d", &moveChoice);

                        if(moveChoice==0)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colMinus1;
                            currSlot->colMinus1 = currSlot->tmpC;
                        }
                        else if(moveChoice==1)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowMinus1;
                            currSlot->rowMinus1 = currSlot->tmpR;
                        }
                        else if(moveChoice==2)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colPlus1;
                            currSlot->colPlus1 = currSlot->tmpC;
                        }
                        else
                        {
                            printf("You have just forfeited your turn.\n");
                        }
                    }
                    else if(((currSlot->column) == 0) && ((currSlot->row) == 6))
                    {
                        printf("You can only move up(0) or right(1): ");
                        scanf("%d", &moveChoice);

                        if(moveChoice==0)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowMinus1;
                            currSlot->rowMinus1 = currSlot->tmpR;
                        }
                        else if(moveChoice==1)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colPlus1;
                            currSlot->colPlus1 = currSlot->tmpC;
                        }
                        else
                        {
                            printf("You have just forfeited your turn.\n");
                        }
                    }
                    else if(((currSlot->column) == 0) && ((currSlot->row) > 0) && ((currSlot->row) < 6))
                    {
                        printf("You can move up(0), right(1) or down(2): ");
                        scanf("%d", &moveChoice);

                        if(moveChoice==0)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowMinus1;
                            currSlot->rowMinus1 = currSlot->tmpR;
                        }
                        else if(moveChoice==1)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colPlus1;
                            currSlot->colPlus1 = currSlot->tmpC;
                        }
                        else if(moveChoice==2)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowPlus1;
                            currSlot->rowPlus1 = currSlot->tmpR;
                        }
                        else
                        {
                            printf("You have just forfeited your turn.\n");
                        }
                    }
                    else if(((currSlot->column) > 0) && ((currSlot->column) < 6) && ((currSlot->row) < 6) && (currSlot->row) > 0)
                    {
                        printf("You can move up(0), down(1), left(2) or right(3): ");
                        scanf("%d", &moveChoice);

                        if(moveChoice==0)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowMinus1;
                            currSlot->rowMinus1 = currSlot->tmpR;
                        }
                        else if(moveChoice==1)
                        {
                            currSlot->tmpR = currSlot->row;
                            currSlot->row = currSlot->rowPlus1;
                            currSlot->rowPlus1 = currSlot->tmpR;
                        }
                        else if(moveChoice==2)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colPlus1;
                            currSlot->colPlus1 = currSlot->tmpC;
                        }
                        else if(moveChoice==3)
                        {
                            currSlot->tmpC = currSlot->column;
                            currSlot->column = currSlot->colMinus1;
                            currSlot->colMinus1 = currSlot->tmpC;
                        }
                        else
                        {
                            printf("You have just forfeited your turn.\n");
                        }
                    }*/
            }
            else if(ans == 'A')
            {

            }
            else if(ans == 'Q')
            {
                for(a=0;a<boardSize;a++)
                {
                    for(b=0;b<boardSize;b++)
                    {
                        if(slots[a][b].place[a][b] == playNum+1)
                        {
                            slots[a][b].place[a][b] = 0;
                            quit++;
                            quitCheck[i+1] = playNum+1;
                        }
                    }
                }
            }
        }
    }


    //---------------------------------------------------------------------------------------
    //ATTACK?????
    /*getDesiredElement(BOARD_SIZE, &row,&column);

    if(row >= BOARD_SIZE/2)
    {
        if(column >= BOARD_SIZE/2)
        {
            currSlot = reachDesiredElement(row,column,downRight);
        } 
        else
        {
            currSlot = reachDesiredElement(row,column,downLeft);
        }
    }
    else
    {
        if(column >= BOARD_SIZE/2)
        {
            currSlot = reachDesiredElement(row,column, upRight);
        }
        else
        {
            currSlot = reachDesiredElement(row,column,upLeft);
        }
    }*/

    //-----------------------------------------------------------------------------------
    //ATTACK FINE PLAYER
   /* for(int i=0; i<BOARD_SIZE; i++)
    {
        for(int j=0; j<BOARD_SIZE;j++)
        {
            explored[i][j] = false;
        }
    }

    foundSlots = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(struct slot ));
    printf("\n\nFunction findSlotsinvoked:\n");

    if(currSlot!= NULL)
    {
        findSlots(REQ_DISTANCE, 0, currSlot, foundSlots, &count, explored);

        for(int i=0; i<count; i++)
        {
            printf("(%d, %d)-> ",foundSlots[i].row, foundSlots[i].column);
        }
    }*/
    return 0;
}