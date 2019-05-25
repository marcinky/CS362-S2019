/**********************************************************************
 ** Program: cardtest3.c
 ** Author: Yvonne Marcinko
 ** Date: 5/05/2019
 ** Description: Unit test for dominion.c great hall implementation. 
 **		This will look for an increase of 1 card and 1 action.
 **		Include the following lines in the makefile:
 **		cardtest3: cardtest3.c dominion.o rngs.o
 **			gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
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

#define TESTCARD "great_hall"

int main() {
	int newCards = 1; // expecting to increase by 1 card
	int actions = 1;  // expecting to increase by 1 action
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};
			
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST: Testing in cardEffect  --------------
	printf("  TEST: Expecting to gain 1 card to hand count and 1 action.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	// print expectations
	printf("	hand count = %d, expected = %d\n", testG.handCount[thisPlayer], 
		G.handCount[thisPlayer] + newCards);
	printf("	deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], 
		G.deckCount[thisPlayer] - newCards);
	printf("	actions    = %d, expected = %d\n", testG.numActions, 
		G.numActions + actions);
	printf("	discarded  = %d, expected = %d\n", testG.discardCount[thisPlayer],
		G.discardCount[thisPlayer] + 1);

	// assert statements
	printf("\n");
	MY_ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);
	MY_ASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
	MY_ASSERT(testG.numActions == G.numActions);
	MY_ASSERT(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]+1);

	// print success if tests passed
	printf("\n >>>>> Testing complete for: %s <<<<<\n\n", TESTCARD);

	return 0;
}


