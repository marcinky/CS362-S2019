CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c 
	gcc -o testme -g testme.c $(CFLAGS)

#execute file and run gcov
testresults: testme	
	-./testme 
	gcov -b testme 

all: testme testresults

clean: rm -f *.o *.gcov *.gcda *.gcno 
