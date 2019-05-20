CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

# ------ Tests for assignment 4 ------
randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

#>>>>>> .out files <<<<<<<#
randomtestresults: randomtestcard1 randomtestadventurer randomtestcard2
	-./randomtestadventurer &> randomtestresults.out
	-./randomtestcard1 >> randomtestresults.out
	-./randomtestcard2 >> randomtestresults.out
	gcov -b randomtestadventurer.c >> randomtestresults.out
	gcov -b randomtestcard1.c >> randomtestresults.out
	gcov -b randomtestcard2.c >> randomtestresults.out

randomtestrun: randomtestcard1 randomtestadventurer randomtestcard2
	-./randomtestadventurer 
	-./randomtestcard1 		
	-./randomtestcard2 	
	gcov -b randomtestadventurer.c
	gcov -b randomtestcard1.c 
	gcov -b randomtestcard2.c 

# ------ End for assignment 4 ------

#testDrawCard: testDrawCard.c dominion.o rngs.o
#	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

#badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
#	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

#testBuyCard: testDrawCard.c dominion.o rngs.o
#	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

#testAll: dominion.o testSuite.c
#	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

#runtests: testDrawCard 
#	./testDrawCard &> unittestresult.out
#	gcov dominion.c >> unittestresult.out
#	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player randomtestresults randomtestrun

clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestadventurer randomtestcard1 randomtestcard2
