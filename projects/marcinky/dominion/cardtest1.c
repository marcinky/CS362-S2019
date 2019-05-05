/**********************************************************************
 ** Program: cardtest1.c
 ** Author: Yvonne Marcinko
 ** Date: 5/05/2019
 ** Description: Unit test for dominion.c adventurer implementation 
 **		Include the following lines in the makefile:
 **		cardtest1: cardtest1.c dominion.o rngs.o
 **			gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() 
{
	int newCards = 2;	//expect hand to increase by 2
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;

	struct gameState G, testG;
	int k[10] = {council_room, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, steward};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST: Testing in cardEffect --------------
	printf("\n	TEST: Testing in cardEffect\n");
	printf("  *Known bug will cause deck count to\n");
	printf("   be 1 less than expected.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call card in cardEffect function
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	// print expectations
	printf("	hand count = %d, expected = %d\n", 
		testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	printf("	deck count = %d, expected = %d\n", 
		testG.deckCount[thisPlayer] + newCards, G.deckCount[thisPlayer] - newCards);
	printf("	actions    = %d, expected = %d\n", testG.numActions, G.numActions);

	// assert statements
	printf("\n");
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - newCards);
	assert(testG.deckCount[thisPlayer] + newCards ==  G.deckCount[thisPlayer] + newCards);
	assert(testG.numActions == G.numActions);

	// print success if test passed
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


