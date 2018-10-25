// DracView.c ... DracView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "DracView.h"
// #include "Map.h" ... if you decide to use the Map ADT

struct dracView {
    //PUT IN OWN IMPLEMENTATION
    Round round;
    int score;
    int health[NUM_PLAYERS];
    LocationID currentLocation[NUM_PLAYERS];
    LocationID trail[NUM_PLAYERS][TRAIL_SIZE]; 
	LocationID trapLocations[TRAIL_SIZE];
	LocationID imVampLocation;                                                             //I add trap and vampire

};


// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[])                            //I write a new one 
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    DracView dracView = malloc(sizeof(struct dracView));
    Gameview state = newGameView(pastPlays, messages);
    //just need to set the values in the struct
    dracView->round = state->round;
    dracView->score = state->score;
    //health points
    PlayerID num = PLAYER_LORD_GODALMING;
    while(num <= PLAYER_DRACULA) {
        dracView->health[num]= state[num];
        num++;
    }
    //everyone's trail
    PlayerID huntID = PLAYER_LORD_GODALMING;
    int m = 0;
    while(huntID <= PLAYER_DRACULA) {
	m = 0;
	while(m < TRAIL_SIZE) {
		dracView->trail[huntID][m] = state[huntID][m];
		m++;
        }
	huntID++; 
    }

    //trap locations
    int n = 0;
	while(n < TRAIL_SIZE) {
		dracView->trapLocations[n] = state[n];
       	n++;
    }
    
    //vamp location
    dracView->imVampLocation = state->imVampLocation;
	 
    return dracView;
}

//Finished
// Frees all memory previously allocated for the DracView toBeDeleted
void disposeDracView(DracView toBeDeleted)
{
    free(toBeDeleted);
}


//// Functions to return simple information about the current state of the game

//Finished
// Get the current round
Round giveMeTheRound(DracView currentView)
{
    return currentView->round;                                  //DracView is a ptr, it should be currentView->round I think
}

//Finished
// Get the current score
int giveMeTheScore(DracView currentView)
{
    return currentView->score;								    //->score
}

//Finished
// Get the current health points for a given player
int howHealthyIs(DracView currentView, PlayerID player)
{
	if(currentView->health[player] < 0) {
        currentView->health[player] = 0;                         //ensure blood is in the interval 0....4
    } else if(currentView->health[player] > 4) {                 //maybe unnecessary
		currentView->health[player] = 4;
	}  
	
    return currentView->health[player];
}

// May be UNKNOWN_LOCATION if the player has not had a turn yet
//   (ie at the beginning of the game when the round is 0)
// Always returns an exact location
//   (assumes that the pastPlays string contains full Dracula
//    locations since Dracula always knows where he's been)
//Finished
// Get the current location id of a given player
LocationID whereIs(DracView currentView, PlayerID player)
{    																			

	return currentView->currentLocation[player];
}

//Finished
// Get the most recent move of a given player
void lastMove(DracView currentView, PlayerID player,
              LocationID *start, LocationID *end)
{
    //LILAC
    Round currR = currentView->round;
    LocationID from = currentView->trail[player][TRAIL_SIZE-2];
    LocationID to = currentView->trail[player][TRAIL_SIZE-1];
  
   	start[currR] = from;
   	end[currR] = to;
    
    return;
}

//Finished
// Find out what minions are placed at the specified location
void whatsThere(DracView currentView, LocationID where,
                int *numTraps, int *numVamps)
{
    //LILAC
    int n = 0;
    if(places[where].type == SEA || where = NOWHERE) {                                 //place[].type  ?right
	numTraps[where] = 0;
        numVamps[where] = 0;
    } else {
	while(n < TRAIL_SIZE) {
	    if(currentView->trapLocations[n] == where) {
		numTraps[where]++; 
	    }
            n++;
        }
        if(currentView->imVampLocation == where) {
	    numVamps[where]++;
	}
    }

    return;
}


//// Functions that return information about the history of the game
//Finished
// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
                    LocationID trail[TRAIL_SIZE])
{
    int i;
    for (i = 0, i < TRAIL_SIZE, i++){
        
        trail[i] = currentView->trail[player][i];
    }
}


//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
// Don't include hospital or anywhere reachable by rail
//Can't move to anywhere in his trail (use above function)
LocationID *whereCanIgo(DracView currentView, int *numLocations, int road, int sea)
{
    LocationID possibleMoves[numLocations[0]];
    possibleMoves[0] = currentView->currentLocation[4]; //putting dracula's current location in array
    if(road == TRUE){
        //places reachable by road
    }
    if(sea == TRUE){
        //places reachable by sea
    }
    return possibleMoves;
}


// What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{
    //SAME AS HUNTERVIEW SO KENDRICK
    return NULL;
}
