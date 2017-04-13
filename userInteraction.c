#include <stdio.h>
#include <stdlib.h>
#include "crossfireOperations.h"

int getBoardSize()
{
	int boardSize;
	printf("Please enter the required size of the board (7): \n");
	scanf("%d", &boardSize);

	if(boardSize != 7)
	{
		printf("Please restart and enter the correct board size.\n");
		exit(0);
	}
	else
	{
		return boardSize;
	}
}

void movePlayer(int a, int b, int place[BOARD_SIZE][BOARD_SIZE])
{
    int row = a;
    int col = b;
	printf("Your current position is : (%d, %d)\n", row, col);

	int moveChoice;
    if((col == 0) && (row == 0))
    {
        printf("You can only move down(0) or right(1): ");
        scanf("%d", &moveChoice);

        if(moveChoice==0)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a+1][b].place[a+1][b];
            slots[a+1][b].place[a+1][b] = slots[a][b].tmp;
        }
        else if (moveChoice==1)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b+1].place[a][b+1];
            slots[a][b+1].place[a][b+1] = slots[a][b].tmp;
        }
        else
        {
            printf("You have just forfeited your turn.\n");
        }
    }
    else if((col > 0) && (col < 6) && (row == 0))
    {
        printf("You can move left(0), down(1) or right(2): ");
        scanf("%d", &moveChoice);

        if(moveChoice==0)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b-1].place[a][b-1];
            slots[a][b-1].place[a][b-1] = slots[a][b].tmp;
        }
        else if(moveChoice==1)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a+1][b].place[a+1][b];
            slots[a+1][b].place[a+1][b] = slots[a][b].tmp;
        }
        else if(moveChoice==2)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b+1].place[a][b+1];
            slots[a][b+1].place[a][b+1] = slots[a][b].tmp;
        }
        else
        {
            printf("You have just forfeited your turn.\n");
        }
    }
    else if((col == 6) && (row == 0))
    {
        printf("You can only move left(0) or down(1): ");
        scanf("%d", &moveChoice);

        if(moveChoice==0)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b-1].place[a][b-1];
            slots[a][b-1].place[a][b-1] = slots[a][b].tmp;
        }
        else if(moveChoice==1)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a+1][b].place[a+1][b];
            slots[a+1][b].place[a+1][b] = slots[a][b].tmp;
        }
        else
        {
            printf("You have just forfeited your turn.\n");
        }
    }
    else if((col == 6) && (row > 0) && (row < 6))
    {
        printf("You can move up(0), left(1) or down(2): ");
        scanf("%d", &moveChoice);

        if(moveChoice==0)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a-1][b].place[a-1][b];
            slots[a-1][b].place[a-1][b] = slots[a][b].tmp; 
        }
        else if(moveChoice==1)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b-1].place[a][b-1];
            slots[a][b-1].place[a][b-1] = slots[a][b].tmp;
        }
        else if(moveChoice==2)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a+1][b].place[a+1][b];
            slots[a+1][b].place[a+1][b] = slots[a][b].tmp;
        }
        else
        {
            printf("You have just forfeited your turn.\n");
        }
    }
    else if((col == 6) && (row == 6))
    {
        printf("You can only move up(0) or left(1): ");
        scanf("%d", &moveChoice);

        if(moveChoice==0)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a-1][b].place[a-1][b];
            slots[a-1][b].place[a-1][b] = slots[a][b].tmp;
        }
        else if(moveChoice==1)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b-1].place[a][b-1];
            slots[a][b-1].place[a][b-1] = slots[a][b].tmp;
        }
        else
        {
            printf("You have just forfeited your turn.\n");
        }
    }
    else if((col > 0) && (col < 6) && (row == 6))
    {
        printf("You can move left(0), up(1) or right(2): ");
        scanf("%d", &moveChoice);

        if(moveChoice==0)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b-1].place[a][b-1];
            slots[a][b-1].place[a][b-1] = slots[a][b].tmp;
        }
        else if(moveChoice==1)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a-1][b].place[a-1][b];
            slots[a-1][b].place[a-1][b] = slots[a][b].tmp;
        }
        else if(moveChoice==2)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b+1].place[a][b+1];
            slots[a][b+1].place[a][b+1] = slots[a][b].tmp;
        }
        else
        {
            printf("You have just forfeited your turn.\n");
        }
    }
    else if((col == 0) && (row == 6))
    {
        printf("You can only move up(0) or right(1): ");
        scanf("%d", &moveChoice);

        if(moveChoice==0)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a-1][b].place[a-1][b];
            slots[a-1][b].place[a-1][b] = slots[a][b].tmp;
        }
        else if(moveChoice==1)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b+1].place[a][b+1];
            slots[a][b+1].place[a][b+1] = slots[a][b].tmp;
        }
        else
        {
            printf("You have just forfeited your turn.\n");
        }
    }
    else if((col == 0) && (row > 0) && (row < 6))
    {
        printf("You can move up(0), right(1) or down(2): ");
        scanf("%d", &moveChoice);

        if(moveChoice==0)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a-1][b].place[a-1][b];
            slots[a-1][b].place[a-1][b] = slots[a][b].tmp;
        }
        else if(moveChoice==1)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b+1].place[a][b+1];
            slots[a][b+1].place[a][b+1] = slots[a][b].tmp;
        }
        else if(moveChoice==2)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a+1][b].place[a+1][b];
            slots[a+1][b].place[a+1][b] = slots[a][b].tmp;
        }
        else
        {
            printf("You have just forfeited your turn.\n");
        }
    }
    else if((col > 0) && (col < 6) && (row < 6) && (row > 0))
    {
        printf("You can move up(0), down(1), left(2) or right(3): ");
        scanf("%d", &moveChoice);

        if(moveChoice==0)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a-1][b].place[a-1][b];
            slots[a-1][b].place[a-1][b] = slots[a][b].tmp;
        }
        else if(moveChoice==1)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a+1][b].place[a+1][b];
            slots[a+1][b].place[a+1][b] = slots[a][b].tmp;
        }
        else if(moveChoice==2)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b-1].place[a][b-1];
            slots[a][b-1].place[a][b-1] = slots[a][b].tmp;
        }
        else if(moveChoice==3)
        {
            slots[a][b].tmp = slots[a][b].place[a][b];
            slots[a][b].place[a][b] = slots[a][b+1].place[a][b+1];
            slots[a][b+1].place[a][b+1] = slots[a][b].tmp;
        }
        else
        {
            printf("You have just forfeited your turn.\n");
        }
    }
}