#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>


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
	printf("testing the updateCoin function\n\n");  
	
	struct gameState g;

  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};

  int r = initializeGame(2, k, 5, &g);

  int catch = upDateCoins(0,&g,0);
  
  myassert(0,"The number of updated coins is the same");

  catch = upDateCoins(5,&g, 4);
 myassert(4,"There should be four more coins");
  
  checkasserts();
	return 0;
}
