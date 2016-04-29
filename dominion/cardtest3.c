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
			
	int card;	
	int cardcount = cardEffect(1,0,0,0,&g);
	int hand = numHandCards(&g);
	int total = cardcount+hand;

	if(total == numHandCards(&g)+2)
		printf("everything passed!\n");

	else
		printf("fail\n");
	return 0;
}
