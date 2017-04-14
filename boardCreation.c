#include <stdio.h>
#include <stdlib.h>
#include "crossfireOperations.h"

void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight)
{
	struct slot ** board = malloc(boardSize * sizeof(struct slot *));


	for(int i =0; i< boardSize; i++)
	{
		board[i] = malloc(boardSize * sizeof(struct slot));

		for(int j=0;j < boardSize; j++)
		{
			board[i][j].row = i;
			board[i][j].column = j;
		}
	}

	for(int i =1; i< boardSize-1; i++)
	{
		for(int j=1;j < boardSize-1; j++)
		{
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].down = &board[i+1][j];
			board[i][j].left = &board[i][j-1];
		}
	}

	for(int j = 1; j < boardSize -1; j++)
	{
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];
		board[0][j].up = NULL;

		board[boardSize - 1][j].right = &board[boardSize - 1][j+1];
		board[boardSize -1][j].left = &board[boardSize - 1][j-1];
		board[boardSize - 1][j].up = &board[boardSize - 2][j];
		board[boardSize - 1][j].down = NULL;
	}

	for(int i = 1; i < boardSize -1; i++)
	{
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i-1][0];
		board[i][0].down = &board[i+1][0];
		board[i][0].left = NULL;

		board[i][boardSize-1].left = &board[i][boardSize-2];
		board[i][boardSize -1].up = &board[i -1][boardSize-1];
		board[i][boardSize -1].down = &board[i+1][boardSize -1];
		board[i][boardSize -1].right = NULL;
	}


		board[0][0].right = &board[0][1];
		board[0][0].down = &board[1][0];

		board[0][boardSize-1].left = &board[0][boardSize-2];
		board[0][boardSize -1].down = &board[1][boardSize -1];

		board[boardSize -1][0].right = &board[boardSize -1][1];
		board[boardSize -1][0].up = &board[boardSize -2][0];

		board[boardSize - 1][boardSize-1].up = &board[boardSize-2][boardSize-1];
		board[boardSize - 1][boardSize -1].left = &board[boardSize -1][boardSize -2];

		*upLeft = &board[0][0];
		*upRight = &board[0][boardSize -1];
		*downLeft = &board[boardSize -1][0];
		*downRight = &board[boardSize -1][boardSize -1];
	}

struct slot * reachDesiredElement(int row, int column, struct slot * initialSlot)
{
	bool found = false;
	struct slot * currentSlot = initialSlot;

	while(found == false)
	{
		if(currentSlot->row > row)
		{
			currentSlot = currentSlot->up;
		}

		if(currentSlot->row < row)
		{
			currentSlot = currentSlot->down;
		}

		if(currentSlot->column > column)
		{
			currentSlot = currentSlot->left;
		}

		if(currentSlot->column < column)
		{
			currentSlot = currentSlot->right;
		}

		if(currentSlot->column == column && currentSlot->row == row)
		{
			found = true;
		}

	}

	return currentSlot;
}

void findSlots(int reqDist, int currDist,  struct slot * currSlot, struct slot * foundSlots, int * count,  bool explored[BOARD_SIZE][BOARD_SIZE])
{
	if(currDist == reqDist)
	{
		if(explored[currSlot->row][currSlot->column] == false)
		{
			*(foundSlots + *count) = *currSlot;
			(*count)++;
			explored[currSlot->row][currSlot->column] = true;
		}
	}
	else
	{
		if(currSlot->up != NULL)
		{
			findSlots(reqDist, currDist +1,  currSlot->up, foundSlots, count, explored);
		}
		if(currSlot->right != NULL)
		{
			findSlots(reqDist, currDist +1,  currSlot->right, foundSlots, count, explored);
		}
		if(currSlot->down != NULL)
		{
			findSlots(reqDist, currDist +1,  currSlot->down, foundSlots, count, explored);
		}
		if(currSlot->left != NULL)
		{
			findSlots(reqDist, currDist +1,  currSlot->left, foundSlots, count, explored);
		}

	}
}