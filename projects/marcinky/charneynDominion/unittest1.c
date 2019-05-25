/**********************************************************************
 ** Program: unittest1.c
 ** Author: Yvonne Marcinko
 ** Date: 5/05/2019
 ** Description: Unit test for dominion.c adventurer implementation 
 **		from modified assignment 2 code. Expect when function complete
 **		handcount will increase by 2.
 **		Include the following lines in the makefile:
 **		unittest1: unittest1.c dominion.o rngs.o
 **			gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
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

#define TESTCARD "adventurer"

int main() 
{
	int newCards = 2;	//expect hand to increase by 2
	int handpos = 0; 
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int temphand[MAX_HAND];

	struct gameState G, testG;
	int k[10] = {council_room, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, steward};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST: Refactored Function --------------
	printf("\n	TEST: Refactored Function\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call card in refactored function
	adventurerRefactor(&testG);

	// print expectations
	printf("	hand count = %d, expected = %d\n", 
		testG.handCount[thisPlayer], 
		G.handCount[thisPlayer] + newCards);
	printf("	deck count = %d, expected = %d\n", 
		testG.deckCount[thisPlayer] + newCards, 
		G.deckCount[thisPlayer] - newCards);

	// assert statements
	printf("\n");
	MY_ASSERT(testG.handCount[thisPlayer] - newCards ==
		G.handCount[thisPlayer] + newCards);
	MY_ASSERT(testG.deckCount[thisPlayer] + newCards ==
		G.deckCount[thisPlayer] - newCards);

	// print success if test passed
	printf("\n >>>>> Testing complete for: %s <<<<<\n\n", TESTCARD);

	return 0;
}
