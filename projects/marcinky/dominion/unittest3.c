/**********************************************************************
 ** Program: unittest3.c
 ** Author: Yvonne Marcinko
 ** Date: 5/05/2019
 ** Description: Unit test for dominion.c smithy implementation 
 **		from modified assignment 2 code. Simple test checks that 
 **		hand increases by 3. Include the following lines in makefile:
 **		unittest3: unittest3.c dominion.o rngs.o
 **			gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() 
{
	int newCards = 3;	//expect hand to increase by 3 
	int handpos = 0; 
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;

	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, council_room, steward};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST: Testing in Refactored Function --------------
	printf("\n  TEST: Refactored Function\n");
	printf("      (very slow, but works)\n");
	printf("  *Known bug should cause the number of card\n");
	printf("   increase in hand count to be incorrect.\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// call card in refactored function
	caseSmithy(thisPlayer, &testG, handpos);

	// print expectations
	printf("	hand count = %d, expected = %d\n", 
		testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	printf("	actions    = %d, expected = %d\n", 
		testG.numActions, G.numActions); //smithy is an action, so expect 1

	// assert statements
	printf("\n");
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);
	assert(testG.numActions == G.numActions);
	
	// print success if test passed
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
