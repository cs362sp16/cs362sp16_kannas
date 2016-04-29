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
  struct gameState g;

  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};

  int r = initializeGame(2, k, 5, &g);

  int deck = fullDeckCount(2,copper,&g);
  myassert(deck == 7,"7 copper");


  deck = fullDeckCount(1,estate,&g);
  myassert(deck == 3,"3 estates");

  checkasserts();
  return 0;
}
