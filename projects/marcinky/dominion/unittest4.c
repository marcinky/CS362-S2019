/**********************************************************************
 ** Program: unittest4.c
 ** Author: Yvonne Marcinko
 ** Date: 5/05/2019
 ** Description: Unit test for dominion.c village implementation 
 **		from modified assignment 2 code. Simple test looks for
 **		expected action increase by 2 and hand increase by 1.
 **		Include the following lines in the makefile:
 **		unittest4: unittest4.c dominion.o rngs.o
 **			gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() 
{
	int newCards = 1;	//expect hand to increase by 1 
	int held = 1; //village card in hand
	int handpos = 0; 
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int discarded = 1;
	int actions = 2; //expect action to increase by 2
	int shuffledCards = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, steward};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST: Testing in Refactored Function --------------
	printf("\n	TEST: Refactored Function\n");
	printf("  *Known bug should cause the handcount to\n");
	printf("   be 1 more than expected because of extra\n");
	printf("   draw, and should no discards when 1 is\n");
	printf("   expected.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call card in refactored function
	caseVillage(thisPlayer, &testG, handpos);

	// print expectations
	printf("	hand count = %d, expected = %d\n", 
		testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	printf("	deck count = %d, expected = %d\n", 
		testG.deckCount[thisPlayer], 
		G.deckCount[thisPlayer] - newCards - held + shuffledCards);
	printf("	discarded  = %d, expected = %d\n", 
		testG.discardCount[thisPlayer], 
		G.discardCount[thisPlayer] + discarded);
	printf("	actions    = %d, expected = %d\n", 
		testG.numActions, G.numActions + actions); //village is an action card

	// assert statements
	printf("\n");
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);
	assert(testG.deckCount[thisPlayer] == 
		G.deckCount[thisPlayer] - discarded + shuffledCards);
	assert(testG.discardCount[thisPlayer] == 
		G.discardCount[thisPlayer] + discarded);
	assert(testG.numActions == G.numActions + actions);
	
	// print success if test passed
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
