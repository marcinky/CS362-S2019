/**********************************************************************
 ** Program: cardtest4.c
 ** Author: Yvonne Marcinko
 ** Date: 5/05/2019
 ** Description: Unit test for dominion.c minion implementation 
 **		Include the following lines in the makefile:
 **		cardtest4: cardtest4.c dominion.o rngs.o
 **			gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
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

#define TESTCARD "minion"

int main() 
{
	int newCards = 0;
	int discarded = 1;
	int xtraCoins = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	//int nextPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, great_hall, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1 = +2 coins --------------
	printf("TEST 1: choice1 = 1 = +2 coins\n");

	// copy the game state to a test case
	choice1 = 1;
	choice2 = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 0;
	xtraCoins = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], 
		G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], 
		G.deckCount[thisPlayer] - newCards);
	printf("coin count = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

	// assert statements
	printf("\n");
	MY_ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	MY_ASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
	MY_ASSERT(testG.coins == G.coins + xtraCoins);

	// ----------- TEST 2: choice2  = +4 cards --------------
	printf("\nTEST 2: choice2  = +4 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 1;
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);

	// print expectations
	newCards = 4;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], 
		G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], 
		G.deckCount[thisPlayer] - newCards);
	printf("coin count = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

/* useless since I can't figure out how to trigger choice2
	// Check if next player discards
	printf("hand count = %d, expected = %d\n", testG.handCount[nextPlayer], 
		G.handCount[nextPlayer]);
	printf("discarded  = %d, expected = %d\n", testG.discardCount[nextPlayer], 
		G.discardCount[nextPlayer] +1);
*/
	// assert statements
	printf("\n");
	MY_ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	MY_ASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
	MY_ASSERT(testG.coins == G.coins + xtraCoins);

	// print success if test passed
	printf("\n >>>>> Testing complete for: %s <<<<<\n\n", TESTCARD);

	return 0;
}
