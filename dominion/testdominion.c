/*
 *seed as argument
 *random numbe rof players (2-4)
 *random set of kingdom cards
 *AI playing dominion
 */

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"

// Define function not listed in dominion.h to suppress compiler warnings
int getCost(int card);

/**
 * Fills a deck with a random set of 10 unique cards (may not all be valid)
 */
void randomCards(int* deck) {
	int i;
	for(i = 0; i < 10; i++) {
		int randCard = rand() % (treasure_map + 1);

		// Make sure card is unique
		int deckAlreadyContains = 0;
		int j;
		for(j = 0; j < i; j++) {
			if(deck[j] == randCard) {
				deckAlreadyContains = 1;
				break;
			}
		}

		//If not, try again
		if(deckAlreadyContains) {
			i--;
			continue;
		}

		deck[i] = randCard;
	}
}

/**
 * Finds a random card that the player is able to purchase (supply > 0 and coins >= cost)
 * @return the index in the supply array (i.e. the card's value)
 */
int randomAffordableCard(struct gameState *g) {
	int affordableCards[treasure_map + 1];
	int affordableCardsCount = 0;
	int i;
	for(i= 0; i <= treasure_map; i++) {
		// If card is affordable and supply > 0, add it to array
		if(g->supplyCount[i] > 0 && getCost(i) <= g->coins) {
			affordableCards[affordableCardsCount++] = i;
		}
	}

	// Couldn't find any cards to buy
	if(affordableCardsCount == 0) {
		return -1;
	}

	int randCard = rand() % affordableCardsCount;
	return affordableCards[randCard];
}

/**
 * Finds a random action card in the player's hand. Ignores all cards whose index in
 * the player's hand is contained within the ignore array.
 * @return the index in the player's hand of an action card
 */
int randomActionCard(struct gameState *g, int* ignore, int ignorec) {
	int playableCards[numHandCards(g)];
	int playableCardsCount = 0;
	int i;
	for(i = 0; i < numHandCards(g); i++) {
		if(handCard(i, g) >= adventurer) {
			// Check if we're supposed to ignore this one
			int ignoreCard = 0;
			int j;
			for(j = 0; j < ignorec; j++)
				if(ignore[j] == i)
					ignoreCard = 1;

			// If not, add it to playable cards array
			if(!ignoreCard) {
				printf("Card %d is playable, it's %d\n", i, handCard(i, g));
				playableCards[playableCardsCount++] = i;
			}
		}
	}

	// Couldn't find a card to play
	if(playableCardsCount == 0) {
		return -1;
	}

	int randCard = rand() % playableCardsCount;
	return playableCards[randCard];
}

/**
 * Given that the player is about to play card at cardIndex, this function
 * will attempt to fill the choices array with 3 valid choices.
 * @return 0 if successful, -1 if valid choices are not found
 */
int randomChoices(int cardIndex, int *choices, struct gameState *g) {
	int card = handCard(cardIndex, g);
	switch(card) {
		case feast: /* choice1 is supply # of card gained) */
		{
			int possibleCards[treasure_map + 1];
			int possibleCardsCount = 0;
			int i;
			for(i = 0; i <= treasure_map; i++) {
				if(getCost(i) <= 5 && g->supplyCount[i] > 0) {
					possibleCards[possibleCardsCount++] = i;
				}
			}

			if(possibleCardsCount == 0)
				return -1;

			choices[0] = possibleCards[rand() % possibleCardsCount];
			choices[1] = -1;
			choices[2] = -1;
			break;
		}

		case mine: /* choice1 is hand# of money to trash, choice2 is supply# of
	    money to put in hand */
	    {
	    	int possibleCards[numHandCards(g)];
			int possibleCardsCount = 0;
		int i;
		for(i = 0; i < numHandCards(g); i++) {
	    		if(handCard(i, g) < copper || handCard(i, g) > gold)
	    			continue;
	    		possibleCards[possibleCardsCount++] = i;
	    	}

	    	if(possibleCardsCount == 0)
	    		return -1;

	    	int toTrash = possibleCards[rand() % possibleCardsCount];
	    	int trashCardValue = getCost(handCard(toTrash, g));

	    	int treasure[3] = {copper, silver, gold};
	    	int possibleToAdd[3];
	    	int possibleToAddCount = 0;
		for(i = 0; i < 3; i++) {
	    		if(g->supplyCount[treasure[i]] > 0 && getCost(treasure[i]) <= trashCardValue + 3)
	    			possibleToAdd[possibleToAddCount++] = i;
	    	}

	    	if(possibleToAddCount == 0)
	    		return -1;

	    	int toAdd = possibleToAdd[rand() % possibleToAddCount];

	    	choices[0] = toTrash;
	    	choices[1] = toAdd;
	    	choices[2] = -1;

	    	break;
	    }

		case remodel: /* choice1 is hand# of card to remodel, choice2 is supply# */
	    {
	    	int randomHandPositions[numHandCards(g)];
			int randomHandPositionsCount = 0;
			int i;
			for(i = 0; i < numHandCards(g); i++) {
				if(i != cardIndex)
					randomHandPositions[randomHandPositionsCount++] = i;
			}

			if(randomHandPositionsCount == 0)
				return -1;

			int handPos = randomHandPositions[rand() % randomHandPositionsCount];
			int cardCost = getCost(handCard(handPos, g));

			int randomSupplyCards[treasure_map + 1];
			int randomSupplyCardCount = 0;
			for(i = 0; i <= treasure_map; i++) {
				if(g->supplyCount[i] > 0 && getCost(i) <= cardCost + 2)
					randomSupplyCards[randomSupplyCardCount++] = i;
			}

			if(randomSupplyCardCount == 0)
				return -1;

			int newCard = randomSupplyCards[rand() % randomSupplyCardCount];

	    	choices[0] = handPos;
	    	choices[1] = newCard;
	    	choices[2] = -1;
	    	break;
	    }

		case baron: /* choice1: boolean for discard of estate */
	    {
	    	int haveEstate = 0;
		int i;
	    	for(i = 0; i < numHandCards(g); i++) {
	    		if(handCard(i, g) == estate) {
	    			haveEstate = 1;
	    			break;
	    		}
	    	}

	    	choices[0] = haveEstate ? rand() % 2 : 0;
	    	choices[1] = -1;
	    	choices[2] = -1;
			break;
	    }

		case minion: /* choice1:  1 = +2 coin, 2 = redraw */
		{
			int which = rand() % 2;
			int other = which == 0 ? 1 : 0;
	    	choices[which] = 1;
	    	choices[other] = 0;
	    	choices[2] = -1;
			break;
		}

		case steward: /* choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) */
		{
			choices[0] = rand() % 3 + 1;
			choices[1] = -1;
			choices[2] = -1;

			if(choices[0] == 3) {
				if(numHandCards(g) < 3) {
					choices[0] = rand() % 2 + 1;
					break;
				}

				int randomHandPositions[2];
				int randomHandPositionsCount = 0;
				while(randomHandPositionsCount < 2) {
					int i = rand() % numHandCards(g);
					if(i == cardIndex)
						continue;
					randomHandPositions[randomHandPositionsCount++] = i;
				}

				choices[1] = randomHandPositions[0];
				choices[2] = randomHandPositions[1];
			}
			break;
		}

		case ambassador: /* choice1 = hand#, choice2 = number to return to supply */
		{
			int randomHandPositions[numHandCards(g)];
			int randomHandPositionsCount = 0;
			int i;
			for(i = 0; i < numHandCards(g); i++) {
				if(i != cardIndex)
					randomHandPositions[randomHandPositionsCount++] = i;
			}

			if(randomHandPositionsCount == 0)
				return -1;

			int handPos = randomHandPositions[rand() % randomHandPositionsCount];

			int cardCount = 0;
		//	int i;
			for(i = 0; i < numHandCards(g); i++) {
				if(handCard(i, g) == handCard(handPos, g))
					cardCount++;
			}

			choices[0] = handPos;
			choices[1] = cardCount > 1 ? (rand() % 2 + 1) : 1;
			choices[2] = -1;

			break;
		}

		case embargo: /* choice1 = supply# */
		{
			choices[0] = rand() % (treasure_map + 1);
			choices[1] = -1;
			choices[2] = -1;
			break;
		}

		case salvager: /* choice1 = hand# to trash */
		{
			int randomHandPositions[numHandCards(g)];
			int randomHandPositionsCount = 0;
			int i;
			for(i = 0; i < numHandCards(g); i++) {
				if(i != cardIndex)
					randomHandPositions[randomHandPositionsCount++] = i;
			}

			if(randomHandPositionsCount == 0)
				return -1;

			choices[0] = randomHandPositions[rand() % randomHandPositionsCount];
			choices[1] = -1;
			choices[2] = -1;
			break;
		}

		default:
			choices[0] = -1;
			choices[1] = -1;
			choices[2] = -1;
			break;
	}

	return 0;
}

void printState(struct gameState *g) {
	printf("test: Game state");
	int i;
	for(i = 0; i < g->numPlayers; i++) {
		printf("  test: Deck counts for player %d: %d %d %d\n", i + 1, g->handCount[i], g->deckCount[i], g->discardCount[i]);
	}
//	int i;
	for(i = 0; i <= treasure_map; i++) {
		printf("  test: Supply could for %d: %d\n", i, g->supplyCount[i]);
	}
}



int main(int argc,char ** argv)
{
	//initialize game state and pointer to game struct and other variables
	int random;
	int playerTurn;	

//	int cardstack[26] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo,outpost, salvager, sea_hag, treasure_map};


	//need at least 2 players
	if(argc == 2)
	{
		random = atoi(argv[1]);	//random gets assigned the the second command line argument
	}
	else
	{
		printf("sytax for dominion is: ./testdominion <random seed>\n");
		return -1;
	}
	srand(random);
	
	//create array of 10 populate with locations
//	int player = floor(Random()*3+2);		//4-2+1 = 3 (range 2-4)
//	int seed = floor(Random()*100);
//	int i;
	//do this once - for loop useless
	int i;
	for(i = 0; i < 1; i++) {
		// Get random kingdom cards
		int kingdomCards[10];
		randomCards(kingdomCards);	//call function

		int randPlayers = rand() % 3 + 2;	//4-2+1
		struct gameState g;
		initializeGame(randPlayers, kingdomCards, rand(), &g);

		//play game	- while the game isn't over
		while(!isGameOver(&g)) {

			//cards we didn't play
			int error[MAX_HAND];
			int errorCount = 0;

			//as long as you have options
			while(g.numActions > 0 && numHandCards(&g) > 0) {
				//get a card
				int card = randomActionCard(&g, error, errorCount);

				if(card == -1)
					break;

				//try to get a random card
				int choices[3];
				if(randomChoices(card, choices, &g)) {
					error[errorCount++] = card;
					continue;
				}


				// Play the card, see if we were successful
				if(playCard(card, choices[0], choices[1], choices[2], &g) > -1) {
					printf("playing card %d\n", handCard(card, &g));
					errorCount = 0;
				} else {
					//there was an error
					error[errorCount++] = card;
					printf("couldn't play card at index %d which had data: %d)\n", card, handCard(card, &g));
				}
			}

			//treasure cards
			int i;
			for(i = 0; i < numHandCards(&g); i++) {
				if((handCard(i, &g) == copper || handCard(i, &g) == silver || handCard(i, &g) == gold) && rand() % 3 < 2) {
					printf("treasure card\n");
					playCard(i, -1, -1, -1, &g);
				}
			}

			//buy random
			while(g.numBuys > 0) {
				int card = randomAffordableCard(&g);
				if(card == -1)
					break;
				printf("buying card\n");
				buyCard(card, &g);
			}

			printf("turn is over\n");
			endTurn(&g);

			printState(&g);
		}
		printf("Game is over\n");

		int winners[MAX_PLAYERS];
		getWinners(winners, &g);

		printf("Results:\n");
		for(i = 0; i < g.numPlayers; i++) {
			printf("  test: Score for player %d: %d. Winner? %d\n", i + 1, scoreFor(i, &g), winners[i]);
		}
	}

}
