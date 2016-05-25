CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

unittest1:  unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

randtesta: randomtestadventurer.c dominion.o rngs.o
	gcc -o randtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)

randtestc1: randomtestcard1.c dominion.o rngs.o
	gcc -o randtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)

randtestc2: randomtestcard2.c dominion.o rngs.o
	gcc -o randtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)

randtestex: extrarandomtest.c dominion.o rngs.o
	gcc -o extrarandomtest extrarandomtest.c -g dominion.o rngs.o $(CFLAGS)

testdominion: testdominion.c dominion.o rngs.o
	gcc -o testdominion testdominion.c -g dominion.o rngs.o $(CFLAGS)

buildtests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

unittestresults.out: buildtests playdom
	./unittest1 >> unittestresults.out
	echo "GCOV AFTER 1 TEST" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./unittest2 >> unittestresults.out
	echo "GCOV AFTER 2 TESTS" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./unittest3 >> unittestresults.out
	echo "GCOV AFTER 3 TESTS" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./unittest4 >> unittestresults.out
	echo "GCOV AFTER 4 TESTS" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./cardtest1 >> unittestresults.out
	echo "GCOV AFTER 5 TESTS" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./cardtest2 >> unittestresults.out
	echo "GCOV AFTER 6 TESTS" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./cardtest3 >> unittestresults.out
	echo "GCOV AFTER 7 TESTS" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./cardtest4 >> unittestresults.out
	echo "GCOV AFTER 8 TESTS" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./playdom 2 >> unittestresults.out
	echo "GCOV AFTER PLAYING A GAME" >> unittestresults.out
	gcov dominion.c >> unittestresults.out

randcardtests: randtesta randtestc1 randtestc2 randtestex
	./randtestadventurer 42 >> randomtestadventurer.out
	echo "GCOV OF RANDOM TESTING: ADVENTURER" >> randomtestadventurer.out
	gcov -f randomtestadventurer.c >> randomtestadventurer.out
	echo "GCOV OF DOMINION" >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	./randtestcard1  42>> randomtestcard1.out
	echo "GCOV OF RANDOM TESTING: CUTPURSE" >> randomtestcard1.out
	gcov -f randomtestcard1.c >> randomtestcard1.out
	echo "GCOV OF DOMINION" >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	./randtestcard2 42 >> randomtestcard2.out
	echo "GCOV OF RANDOM TESTING: SMITHY" >> randomtestcard2.out
	gcov -f randomtestcard2.c >> randomtestcard2.out
	echo "GCOV OF DOMINION" >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	echo "GCOV OF RANDOM TESTING: BARON" >> extrarandomtest.out
	./extrarandomtest 42 >> extrarandomtest.out
	gcov -f extrarandomtest.c >> extrarandomtest.out
	echo "GCOV OF DOMINION" >> extrarandomtest.out
	gcov dominion.c >> extrarandomtest.out

testdominion.out: testdominion
	./testdominion 42 > testdominion.out


all: playdom player

clean:
	rm -f *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randtestadventurer randtestcard1 extrarandomtest randtestcard2 player.exe testInit testInit.exe *.out *.gcov *.gcda *.gcno *.so *.a *.dSYM
