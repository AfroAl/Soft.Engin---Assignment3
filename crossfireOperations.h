#define CROSSFIREOPERATIONS_H_
#ifndef CROSSFIREOPERATIONS_H_

#endif /* CROSSFIREOPERATIONS_H_ */

#define BOARD_SIZE 7
#define REQ_DISTANCE 3

typedef int bool;
enum { false, true };

struct slot
{
	int row;
	int column;
	int terrainType;
	int place[BOARD_SIZE][BOARD_SIZE];
	int tmp;
	int tmpR, tmpC;
	int colMinus1, rowMinus1, rowPlus1, colPlus1;

	struct slot *left;
	struct slot *right;
	struct slot *up;
	struct slot *down;
}slots[BOARD_SIZE][BOARD_SIZE];

enum playerType {human, ogre, wizard, elf};

struct player
{
	char Name[20];
	enum playerType Type;
	int lifePoints;
	int Dex, Smarts, Strength, Magic, Luck;
};


int getBoardSize();

void movePlayer(int a, int b, int place[BOARD_SIZE][BOARD_SIZE]);

struct slot *  reachDesiredElement(int row, int column, struct slot * initialSlot);

void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);

void findSlots(int reqDist, int currDist,  struct slot * currSlot, struct slot * foundSlots, int * count,  bool explored[7][7]);