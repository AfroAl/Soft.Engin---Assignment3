#ifndef CROSSFIREOPERATIONS_H_
#define CROSSFIREOPERATIONS_H_

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

	struct slot *left;
	struct slot *right;
	struct slot *up;
	struct slot *down;
};

enum playerType {human, ogre, wizard, elf};

struct player
{
	char Name[20];
	enum playerType Type;
	int lifePoints;
	int Dex, Smarts, Strength, Magic, Luck;
};


int getBoardSize();

void getDesiredElement(int maxsize, int * row, int * col);

void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);

struct slot *  reachDesiredElement(int row, int column, struct slot * initialSlot);

void findSlots(int reqDist, int currDist,  struct slot * currSlot, struct slot * foundSlots, int * count,  bool explored[7][7]);