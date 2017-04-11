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
	}
	else
	{
		return boardSize;
	}
}

void getDesiredElement(int boardSize, int * row, int * col)
{
	printf("Your current position is : (%d, %d)\n", *row, *col);
	printf("Please enter the column and the row of the desired slot \n");
	printf("Note that size of the board is %d\n", boardSize);

	int tmpR;
	int tmpC;
		do {
			printf("Row: ");
			scanf("%d", row);
			printf("%d\n", *row);
			if(row < 0 && *row >= boardSize)
				printf("Error: Incorrect row dimension\n");
		} while(*row < 0 && *row >= boardSize);

		do {
			printf("Column: ");
			scanf("%d", col);
			printf("%d\n", *col);
			if(*col < 0 && *col >= boardSize)
				printf("Error: Incorrect column dimension\n");
		} while(*col < 0 && *col >= boardSize);
}