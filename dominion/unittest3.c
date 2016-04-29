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
  
	g.supplyCount[province] = 10;
	int gamestatus = isGameOver(&g);
        myassert(gamestatus == 0, "game not over");

	g.supplyCount[province] ==0;
	gamestatus = isGameOver(&g);
	myassert(gamestatus == 1,"game over");
 

	checkasserts();
	return 0;
}
