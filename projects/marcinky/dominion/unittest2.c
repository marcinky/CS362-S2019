/**********************************************************************
 ** Program: unittest2.c
 ** Author: Yvonne Marcinko
 ** Date: 5/05/2019
 ** Description: Unit test for dominion.c council_room implementation 
 **		from modified assignment 2 code. Simple test looks for an 
 **		increase of 4 cards to hand, and an additional buy.
 **		Include the following lines in the makefile:
 **		unittest2: unittest2.c dominion.o rngs.o
 **			gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// Custom Assert MACRO so that .gcda is generated 
//(program needs to execute to completion)
#define STR(x) #x
#define MY_ASSERT(x)if(!(x)){printf(" >>>>>  TEST FAILED  <<<<<\n  item: (%s)\n  function: %s\n  file: %s\n  line: %d\n\n", STR(x),__PRETTY_FUNCTION__,__FILE__,__LINE__);}else{printf(" >>>>>  TEST PASSED  <<<<<\n  item: (%s)\n\n", STR(x));}

#define TESTCARD "council_room"

int main() 
{
	int newCards = 4;	//expect to gain 4 cards
	int buy = 1; //expect 1 additional buy
	int handpos = 0; 
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int nextPlayer = 1;
	int discarded = 1;//expect to discard the card after play

	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, steward};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST: Refactored Function --------------
	printf("\n	TEST 2: Refactored Function\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// call card in cardEffect function
	caseCouncil(thisPlayer, &testG, handpos);

	// print expectations
	printf("	hand count = %d, expected = %d\n", 
		testG.handCount[thisPlayer], 
		G.handCount[thisPlayer] + newCards - discarded);
	printf("	deck count = %d, expected = %d\n", 
		testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	printf("	buy count  = %d, expected = %d\n", 
		testG.numBuys, G.numBuys + buy);

	// next player
	printf("\n	Next Player\n");

	// print expectations
	printf("	hand count = %d, expected = %d\n", 
		testG.handCount[nextPlayer], G.handCount[nextPlayer] + 1);
	printf("	deck count = %d, expected = %d\n", 
		testG.deckCount[nextPlayer], G.deckCount[nextPlayer] - 1);

	// assert statements
	printf("\n");
	MY_ASSERT(testG.handCount[thisPlayer] == 
		G.handCount[thisPlayer] + newCards - discarded);
	MY_ASSERT(testG.deckCount[thisPlayer] == 
		G.deckCount[thisPlayer] - newCards);
	MY_ASSERT(testG.numBuys == G.numBuys + buy);
	MY_ASSERT(testG.handCount[nextPlayer] == G.handCount[nextPlayer] + 1);
	MY_ASSERT(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - 1);
	
	// print success if test passed
	printf("\n >>>>> Testing complete for: %s <<<<<\n\n", TESTCARD);

	return 0;
}
