/**********************************************************************
 ** Program: randomtestcard2.c
 ** Author: Yvonne Marcinko
 ** Date: 5/19/2019
 ** Description: Random test for dominion.c council room implementation.
 **		Expected behavior: +4 card, +1 buy, other player +1 card 
 *********************************************************************/

#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define TESTCARD "council_room"
#define MAX_RT 20000
#define MAX_SD 100
#define PEEPS 4

void printFail()
{
	printf("\n >>>>> [%s card] TEST FAILED <<<<<\n\n", TESTCARD);
	exit(200);
}


int main() 
{
	//set rand
	srand(time(NULL));
	
	//variables
	int choice1=1, choice2=1, choice3=1;
	int handpos = 0;
	int bonus = 0;
	int thisPlayer = 0;
	int nextPlayer = 0;
	int numPlayers, a, i, seed;
	int newCards = 4;	//expect to gain 4 cards
	int opNewCards = 1; //other player draws one card
	int discarded = 1;//expect to discard the card after play

	//create gamestate 
	struct gameState G, testG;

	//each player starts with 10 cards
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy, council_room};

	// -------------------- BEGIN RANDOM TEST -------------------- // 
	printf("\n---------- Begin Random Test for Card: %s ----------\n", TESTCARD);
	
	seed = rand();
	a = 0;

	for(i = 0; i < MAX_RT + 1; i++)
	{	//randomize values 
		numPlayers = (rand() % PEEPS + 1);

		printf("\n %s Run#%d numPlayers: %d", TESTCARD, a, numPlayers);

		//initialize game state 
		initializeGame(numPlayers, k, seed, &G);

		//copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
	
		//call card in function
		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

		//check number of buys executed 
		printf("\n #buys count %d, expected %d\n", 
			testG.numBuys - opNewCards, 
			G.numBuys);

		if(testG.numBuys - opNewCards != G.numBuys)
		{
			printFail();
		}
	
		//check hand count for current player
		printf(" hand count %d, expected %d\n",
			testG.handCount[thisPlayer] - discarded, 
			G.handCount[thisPlayer] + newCards - discarded);

		if(testG.handCount[thisPlayer] - discarded != 
			G.handCount[thisPlayer] + newCards - discarded)
		{
			printFail();
		}

		//check hand count for next player
		printf(" next player hand count = %d, expected = %d\n", 
			testG.handCount[nextPlayer] - newCards, 
			G.handCount[nextPlayer]);
	
		if(testG.handCount[nextPlayer] - newCards != G.handCount[nextPlayer])
		{
			printFail();
		}

		a++;
	}

	//print success if test passed
	printf("\n >>>>> Random Testing PASSED for: %s <<<<<\n\n", TESTCARD);

	return 0;
}
