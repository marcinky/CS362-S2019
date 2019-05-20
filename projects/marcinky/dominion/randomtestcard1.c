/**********************************************************************
 ** Program: randomtestcard1.c
 ** Author: Yvonne Marcinko
 ** Date: 5/19/2019
 ** Description: random test for dominion.c village implementation 
 **		from assignment 3. Expected behavior: +1 card, +2 actions
 *********************************************************************/

#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define TESTCARD "village"
#define MAX_RT 200
#define MAX_SD 100
#define PEEPS 4

void printFail()
{
	printf("\n >>>>>  [%s card] TEST FAILED <<<<<\n\n", TESTCARD);
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
	int numPlayers, a, i, seed;
	int newCards = 1;	
	int usedCard = 2;

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
	{	//randomize players  
		numPlayers = (rand() % PEEPS + 1);

		printf("\n %s Run#%d numPlayers: %d", TESTCARD, a, numPlayers);

		//initialize game state 
		initializeGame(numPlayers, k, seed, &G);

		//copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
	
		//call card in function
		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

		//check actions executed
		printf("\n action count %d, expected %d\n",
			testG.numActions, 
			G.numActions);

		if(testG.numActions != G.numActions)
		{
			printFail();
		}
	
		//check hand count
		printf(" hand count %d, expected %d\n",
			testG.handCount[thisPlayer] - usedCard - newCards, 
			G.handCount[thisPlayer] + newCards);

		if(testG.handCount[thisPlayer] - usedCard - newCards != 
			G.handCount[thisPlayer] + newCards)
		{
			printFail();
		}

		//check discard count
		printf(" discard count %d, expected %d\n",
			testG.discardCount[thisPlayer],
			G.discardCount[thisPlayer] + newCards);

		if(testG.discardCount[thisPlayer] != 
			G.discardCount[thisPlayer] + newCards)
		{
			printFail();
		}

		a++;
	}

	//print success if test passed
	printf("\n >>>>> Random Testing PASSED for: %s <<<<<\n\n", TESTCARD);

	return 0;
}
