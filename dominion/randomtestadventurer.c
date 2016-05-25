#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TESTS 12

//This randomly tests Adventurer

int main(int argc,char *argv[]) {

	int handnum,num_test,decknum;
	int seed = atoi(argv[1]);
	printf("Random testing of #2 cards\n");
	num_test = 100;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
	int i,player;	
	struct gameState g;		//get a new game
	player = 0;

	for(i=0;i<100;++i)
	{

		//get the random number generation going
	
		initializeGame(2,k,seed,&g);	
	
		//allocate the hand an the deck for the player
			//rand within the modulous
			g.deckCount[i] = rand()%MAX_DECK;
			g.handCount[i] = rand()%MAX_HAND;	

			handnum = g.handCount[player];
			decknum = g.deckCount[player];

			addCardToHand(player,7,&g);
			playCard(handnum,0,0,0,&g);
	}
	
	 return 0;
}
