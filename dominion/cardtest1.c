#include "dominion.h"
#include <stdio.h>

int failed = 0;

int myassert(int b,char* msg) {
  if (b == 0) {
    printf("FAILED ASSERTION: %s\n",msg);
    failed = 1;
  }
}

void checkasserts() {
  if (!failed) {
    printf ("TEST SUCCESSFULLY COMPLETED.\n");
  }
}

int main() {
  struct gameState g;

  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};

  int r = initializeGame(2, k, 5, &g);

	//intialize
	g.hand[0][0] = smithy;
	g.whoseTurn = 0;

		//play and then see what happens
	
	int i = g.outpostPlayed;

	playCard(0,0,0,0,&g);

	//check after
	int u = g.outpostPlayed;
	myassert(u == i+1,"increased by one");
  	checkasserts();

	return 0;
}
