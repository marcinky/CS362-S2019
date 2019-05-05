/**********************************************************************
 ** Program: cardtest2.c
 ** Author: Yvonne Marcinko
 ** Date: 5/05/2019
 ** Description: Unit test for dominion.c smithy implementation 
 **		Include the following lines in the makefile:
 **		cardtest2: cardtest2.c dominion.o rngs.o
 **			gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
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
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;

	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, council_room, steward};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Testing in cardEffect --------------
	printf("\n  TEST 1: Testing in cardEffect\n");
	printf("        (very slow, but works)\n");
	printf("  *Tests to ensure the function discards.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call card in cardEffect function
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	// print expectations
	printf("	hand count = %d, expected = %d\n", 
		testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	printf("	discarded  = %d, expected = %d\n", 
		testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1); //expect 1 discard
	printf("	actions    = %d, expected = %d\n", testG.numActions, G.numActions);

	// assert statements
	printf("\n");
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
	assert(testG.numActions == G.numActions);

	// print success if test passed
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


