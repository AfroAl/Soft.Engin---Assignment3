#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "crossfireOperations.h"
#define MAX_PLAY 6
#define MAX_SLOTS 7

int main(void)
{
    enum playerType playerType[4];
    int row, col, boardSize, playSize, playNum;
    srand(time(NULL));
    int i=0, a, b, j;

    struct slots *currslots1 = NULL;
    struct slots *foundslots;
    bool explored[BOARD_SIZE][BOARD_SIZE];
    int count=0;

    struct slot *upLeft;
    struct slot *upRight;
    struct slot *downLeft;
    struct slot *downRight;

    struct player players[MAX_PLAY];
    struct player x[MAX_PLAY][MAX_PLAY];


    printf("Please enter the number of players (Max 6): ");
    scanf("%d", &playSize);

    if(playSize>6 && playSize<2)
    {
        printf("Please restart the program with between 2 and 6 players.\n");
        exit(0);
    }


    printf("Each player next must enter their name & choose an archtype.\n");
    printf("Human(0), Ogre(1), Wizard(2), Elf(3)\n");

    while(i<playSize)
    {
        scanf("%s %d", players[i].Name , &(players[i].Type));
        i++;
    }

    //-------------------------------------------------------------------------------------

    boardSize = getBoardSize();

    createBoard(BOARD_SIZE, &upLeft, &upRight, &downLeft, &downRight);

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

    //Gives each slots a random slots type
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

    int quitCheck[playSize], quit=0, liveCheck = playSize, skip=0;

    for(i=0;i<playSize;i++)
    {
        quitCheck[i] = -1;
    }

    while(liveCheck > 1)
    {
        for(playNum=0;playNum<playSize;playNum++)
        {
            for(a=0;a<playSize;a++)
            {
                if(quitCheck[a] == playNum)
                {
                    goto SKIP;
                }
            }

            char ans;
            printf("\n");
            printf("Player %d's Turn:\n", playNum+1);
            printf("Would you like to move(M), attack(A) a player or quit(Q) the game?\n");
            scanf(" %c", &ans);

            //Player wants to move
            if(ans == 'M' || ans =='m')
            {

                for(a=0;a<boardSize;a++)
                {
                    for(b=0;b<boardSize;b++)
                    {
                        printf("%d ", slots[a][b].place[a][b]);
                    }
                    printf("\n");
                }
                for(a=0;a<boardSize;a++)
                {
                    for(b=0;b<boardSize;b++)
                    {
                        if(slots[a][b].place[a][b] == playNum+1)
                        {
                            goto MOVE;
                        }
                    }
                }

                MOVE : movePlayer(a, b, slots[a][b].place);
            }
            else if(ans == 'A' || ans == 'a')
            {

            }
            else if(ans == 'Q' || ans == 'q')
            {
                for(a=0;a<boardSize;a++)
                {
                    for(b=0;b<boardSize;b++)
                    {
                        if(slots[a][b].place[a][b] == playNum+1)
                        {
                            slots[a][b].place[a][b] = 0;
                            liveCheck--;
                            quitCheck[playNum] = playNum;
                        }
                    }
                }
            }
            else
            {
                printf("You have forfeited your turn.\n");
            }

            SKIP : skip++;
        }
    }

    if(liveCheck == 1)
    {
        printf("There is only one player left.\n");
    }
    else if(liveCheck == 0)
    {
        printf("All players decided to quit.\n");
    }
    
    //Prints out Player stats
    printf("\n");
    printf("The final totals of all players\n");
    for(i=0;i<playSize;i++)
    {
        printf("%s ", players[i].Name);

        switch(players[i].Type)
        {
            case 0: printf("(Human, "); break;
            case 1: printf("(Ogre, "); break;
            case 2: printf("(Wizard, "); break;
            case 3: printf("(Elf, "); break;
        }

        printf("%d)\n", players[i].lifePoints);
    }

    return 0;
}