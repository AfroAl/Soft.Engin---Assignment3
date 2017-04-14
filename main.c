#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "crossfireOperations.h"
#define MAX_PLAY 6
#define MAX_SLOTS 7

int main(void)
{
    enum playerType playerType[4];
    int row, col, boardSize, playSize, playNum;
    srand(time(NULL));
    int i=0, a, b, j, c, d, e;
    int currDist, reqDist, Attack[MAX_PLAY];

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

        if(slots[a][b].place[a][b] != 0)
        {
            slots[a][b].place[a][b] = (i*10)+(slots[a][b].place[a][b]);
        }
        else
        {
            slots[a][b].place[a][b] = i;
        }
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

    for(i=0;i<7;i++)
    {   
        for(j=0;j<7;j++)
        {   
            explored[i][j] = false;  
        }   
    }

    //--------------------------------------------------------------------------------------

    // Sets Capabilities of each archtype
    for(i=0;i<playSize;i++)
    {
        if(players[i].Type == 0)
        {
            players[i].Smarts = 70 + rand()%31;
            players[i].Strength = 1 + rand()%50;
            players[i].Magic = 51 + rand()%30;
            players[i].Luck = 60 + rand()%41;
            players[i].Dex = 1 + rand()%100;      
        }
        else if(players[i].Type == 1)
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
        else if(players[i].Type == 3)
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
        else if(players[i].Type == 2)
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
            printf("\n");

            //Player wants to move
            if(ans == 'M' || ans =='m')
            {
                printf("\n");
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

                if(slots[a][b].terrainType == 1)
                {
                    printf("Current position: Level ground. No status change at this terrain. \n");
                }
                else if(slots[a][b].terrainType == 2)
                {
                    printf("Current position: Hill. Now changing stats....\n");
        
                    if(players[playNum].Dex < 50)
                    {
                        players[playNum].Strength -= 10;
                    }
                    else if(players[playNum].Dex >= 60)
                    {
                        players[playNum].Strength +=10;
                    }

                    if(players[playNum].Strength < 0)
                    {
                        players[playNum].Strength = 0;
                    }
                    if(players[playNum].Strength > 100)
                    {
                        players[playNum].Strength = 100;
                    }
                }
                else if(slots[a][b].terrainType == 3)
                {
                    printf("Current position: City. Now changing stats....\n");
                    
                    if(players[playNum].Smarts > 60)
                    {
                        players[playNum].Magic += 10;
                    }
                    else if(players[playNum].Smarts <= 60)
                    {
                        players[playNum].Dex -= 10;
                    }

                    if(players[playNum].Magic > 100)
                    {
                        players[playNum].Magic = 100;
                    }
                    if(players[playNum].Dex < 0)
                    {
                        players[playNum].Dex = 0;
                    }
                }
            }
            else if(ans == 'A' || ans == 'a')
            {
                for(a=0;a<boardSize;a++)
                {
                    for(b=0;b<boardSize;b++)
                    {
                        if(slots[a][b].place[a][b] == playNum+1)
                        {
                            row = a;
                            col = b;
                        }
                    }
                }
                for(a=0;a<boardSize;a++)
                {
                    for(b=0;b<boardSize;b++)
                    {
                        printf("%d ", slots[a][b].place[a][b]);
                    }
                    printf("\n");
                }
                printf("\n");

                printf("Would you like do near attack(N) or distant attack(D) or magic attack(M)?");
                char atk;
                fflush(stdin);
                scanf("%c", &atk);
                
                if(atk == 'N' || atk == 'n')
                {
                    reqDist = 1;
                    currSlot = reachDesiredElement(row,col,upLeft);

                    foundSlots = malloc(16 * sizeof(struct slot));

                    if(currSlot != NULL)
                    {
                        findSlots(reqDist, 0, currSlot, foundSlots, &count, explored);
                    }

                    j=0;
                    for(i=0;i<count;i++)
                    {
                        c = i+1;
                        for(a=0;a<boardSize;a++)
                        {
                            for(b=0;b<boardSize;b++)
                            {
                                if((a == foundSlots[i].row) && (b == foundSlots[i].column) && (slots[a][b].place[a][b] == c))
                                {
                                    Attack[j] = slots[a][b].place[a][b];
                                    j++;
                                }
                            }
                        }
                    }

                    c=0;
                    for(i=0;i<=j;i++)
                    {
                        if(Attack[i] == 0)
                        {
                            c++;
                        }
                    }

                    if(c==j)
                    {
                        printf("There are no enemies close enough this round.\n");
                    }
                    else
                    {
                        printf("You can attack player(s) \n");
                        for(i=0;i<j-1;i++)
                        {
                            printf("%d, ", Attack[i]);
                        }
                        printf("%d. Which one? ", Attack[i]);
                        int defend;
                        scanf("%d", &defend);
                    
                        if(players[defend-1].Strength <= 70)
                        {
                            printf("Your opponent has less than or equal to 70 Strength points.\n");
                            printf("You overcame them and they took damage.\n");
                            players[defend-1].lifePoints -= 0.5*(players[defend-1].Strength);
                        }
                        else if(players[defend-1].Strength > 70)
                        {
                            printf("Your opponent has greater than 70 Strength points.\n");
                            printf("They fought back and you took damage.\n");
                            players[playNum].lifePoints -= 0.3*(players[playNum].Strength);
                        }
                    }
                }  
                else if(atk == 'D' || atk == 'd')
                {
                    count = 0;
                    for(i=0;i<playSize;i++)
                    {
                        Attack[i] = 0;
                    }
                    for(i=0;i<7;i++)
                    {   
                        for(j=0;j<7;j++)
                        {      
                            explored[i][j] = false;  
                        }   
                    }
                    for(i=2;i<5;i++)
                    {
                        reqDist = i;
                        currSlot = reachDesiredElement(row,col,upLeft);

                        foundSlots = malloc(49 * sizeof(struct slot));

                        if(currSlot != NULL)
                        {
                            findSlots(reqDist, 0, currSlot, foundSlots, &count, explored);
                        }
                    }

                    j=0;
                    for(i=0;i<count;i++)
                    {
                        c = i+1;
                        for(a=0;a<boardSize;a++)
                        {
                            for(b=0;b<boardSize;b++)
                            {
                                if((a == foundSlots[i].row) && (b == foundSlots[i].column) && (slots[a][b].place[a][b] == c))
                                {
                                    Attack[j] = slots[a][b].place[a][b];
                                    j++;
                                }
                            }
                        }
                    }
                    printf("%d\n", j);
                    for(i=0;i<=j;i++)
                    {
                        printf("%d ", Attack[i]);
                    }

                    c=0;
                    for(i=0;i<j;i++)
                    {
                        if(Attack[i] == 0)
                        {
                            c++;
                        }
                    }

                    if(c==j)
                    {
                        printf("There are no enemies close enough this round.\n");
                    }
                    else
                    {
                        printf("You can attack player(s) \n");
                        for(i=0;i<j-1;i++)
                        {
                            printf("%d, ", Attack[i]);
                        }
                        printf("%d. Which one? ", Attack[i]);
                        int defend;
                        scanf("%d", &defend);

                        if(players[defend-1].Dex >= players[playNum].Dex)
                        {
                            printf("Your opponent has more dexterity point than you.\n");
                            printf("They took 0 damage.\n");
                        }
                        else if(players[playNum].Dex > players[defend-1].Dex)
                        {
                            printf("Your opponent has less dexterity point than you.\n");
                            printf("They took damage.\n");
                            players[defend-1].lifePoints -= 0.3*(players[playNum].Strength);
                        }
                    }
                }
                else if(atk == 'M' || atk == 'm')
                {    
                    printf("You can attack any player. Enter a player number: ");
                    int defend;
                    scanf("%d", &defend);

                    if(players[playNum].Smarts + players[playNum].Magic > 150)
                    {
                        printf("MAGIC ATTACK!!\n");
                        printf("%d\n", players[defend-1].lifePoints);
                        players[defend-1].lifePoints = players[defend-1].lifePoints - ((0.5*(players[playNum].Magic)) + (0.2*(players[playNum].Smarts)));
                        printf("%d\n", players[defend-1].lifePoints);
                    }
                    else
                    {
                        printf("Your energy wasn't enough and your spell failed.\n");
                    }
                }
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
                        else if(slots[a][b].place[a][b] >= 10)
                        {
                            int choice1 = (slots[a][b].place[a][b])/10;
                            int choice2 = (slots[a][b].place[a][b])%10;

                            if(playNum == choice1)
                            {
                                slots[a][b].place[a][b] = choice2;
                            }
                            else if(playNum == choice2)
                            {
                                slots[a][b].place[a][b] = choice1;
                            }

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