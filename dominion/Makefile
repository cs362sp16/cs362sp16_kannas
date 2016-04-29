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
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)


unittest: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o 
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest:
	@gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	
	@gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	
	@gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	
	@gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	


unittestresults:
		./unittest1 1 &> unittestresults.out
		echo "GCOV AFTER 1 TEST" >> unittestresults.out
		gcov dominion.c >> unittestresults.out
		./unittest2 1 >> unittestresults.out
		echo "GCOV AFTER 2 TEST" >> unittestresults.out
		gcov dominion.c >> unittestresults.out
		./unittest3 1 >> unittestresults.out
		echo "GCOV AFTER 3 TEST" >> unittestresults.out
		gcov dominion.c >> unittestresults.out
		./unittest4 1 >> unittestresults.out
		echo "GCOV AFTER 4 TEST" >> unittestresults.out
		gcov dominion.c >> unittestresults.out
		./cardtest1 1 >> unittestresults.out
		echo "GCOV AFTER 1 CARDTEST" >> unittestresults.out
		gcov dominion.c >> unittestresults.out
		./cardtest2 1 >> unittestresults.out
		echo "GCOV AFTER 2 CARDTEST" >> unittestresults.out
		gcov dominion.c >> unittestresults.out
		./cardtest3 1 >> unittestresults.out
		echo "GCOV AFTER 3 CARDTEST" >> unittestresults.out
		gcov dominion.c >> unittestresults.out
		./cardtest4 1 >> unittestresults.out
		echo "GCOV AFTER 4 CARDTEST" >> unittestresults.out
		gcov dominion.c >> unittestresults.out


all: playdom player unittest cardtest unittestresults


clean:
	rm -f *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM
