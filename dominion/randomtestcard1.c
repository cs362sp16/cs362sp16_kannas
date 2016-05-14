#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TESTS 12

//This randomly tests Adventurer

int main(int argc,char *argv[]) {

	printf("Random testing of #1 cards\n");
	int num_test = 100;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
	int i,player;

	for(i=0;i<100;++i)
	{

		//get the random number generation going
		int seed;
		seed = rand();

		player = rand()%4;		//randomly assigned
		struct gameState g;		//get a new game
		
		initializeGame(player,k,seed,&g);	
	
		//allocate the hand an the deck for the player
		for(i=0;i<player;++i)
		{
			//rand within the modulous
			g.deckCount[i] = rand()%MAX_DECK;
			g.handCount[i] = rand()%MAX_HAND;	

		}

		int r = cardEffect(smithy,1,1,1,&g,1,0);
	}
	
	printf("done\n");
	 return 0;
} 
