// DracView.c ... DracView ADT implementation
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "DracView.h"
#include "Map.h" //... if you decide to use the Map ADT


static void getTrap(char *pastPlays, LocationID *trap);
static LocationID getVamp(char *pastPlays);

struct dracView {
    //PUT IN OWN IMPLEMENTATION
    GameView state;
    LocationID trapLocations[TRAIL_SIZE];
    LocationID imVampLocation;                                                             // add trap and vampire

};


// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[])                            // write a new one 
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    DracView dracView = malloc(sizeof(struct dracView));
    dracView->state = newGameView(pastPlays, messages);
    //just need to set the values in the struct
    //trap locations
    getTrap(pastPlays, dracView->trapLocations);
    
    //vamp location
    dracView->imVampLocation = getVamp(pastPlays) ;
	 
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
    return getRound(currentView->state);                                  //DracView is a ptr, it should be currentView->round I think
}

//Finished
// Get the current score
int giveMeTheScore(DracView currentView)
{
    return getScore(currentView->state);								    //->score
}

//Finished
// Get the current health points for a given player
int howHealthyIs(DracView currentView, PlayerID player)
{	
    return getHealth(currentView->state,player);
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

	return getLocation(currentView->state,player);
}

//Finished
// Get the most recent move of a given player
void lastMove(DracView currentView, PlayerID player,
              LocationID *start, LocationID *end)
{
    //LILAC
    Round currR = getRound(currentView->state);
    LocationID trail[TRAIL_SIZE];
    getHistory(currentView->state,player,trail);
    LocationID from = trail[1];
    LocationID to = trail[0];
  
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
    *numTraps = 0;
    *numVamps = 0;
    int i = 0;
    while(i <= 5) {
	if(currentView->trapLocations[i] == where) { *numTraps = *numTraps +1;}
        i++;
    }
    if(i == 5) *numTraps = 0;
    if(currentView->imVampLocation == where) {*numVamps = *numVamps+1;}
    else{*numVamps = 0;}
    return;
}


//// Functions that return information about the history of the game
//Finished
// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
                    LocationID trail[TRAIL_SIZE])
{
     return getHistory(currentView->state, player, trail);
}

/*

//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
// Don't include hospital or anywhere reachable by rail
//Can't move to anywhere in his trail (use above function)
LocationID *whereCanIgo(DracView currentView, int *numLocations, int road, int sea)
{
    LocationID currLocation = currentView->currentLocation[4];
    LocationID possibleMoves[numLocations[0]];
    
    Map map = newMap();
    VList curr = map->connections[currLocation];
    
    possibleMoves[0] = currLocation; //putting dracula's current location in array
    
    while(curr != NULL){ //tranverse thru all adjacent locations
        int in_trail = FALSE;
        int doub_back = FALSE;
        int count = 1;
        int i = 0;
        int a;
        int ok = FALSE;
        int k;
        for(k = 0; k < TRAIL_SIZE; k++){
            a = trail[4][k];
            for(i = 0; i<TRAIL_SIZE; i++){
                if(trail[4][i] == curr->v){ //testing if curr location is in trail
                    in_trail = TRUE;
                }
                if(a == trail[4][i]){ // testing if double back occurs
                    doub_back = TRUE;
                }
            }
        }
        
        if(in_trail == FALSE || in_trail == TRUE && doub_back = FALSE){ //if curr location is not in trail or if it is in trail
            ok = TRUE;
        }
        
        if(curr->type == RAIL || curr->v == ST_JOSEPH_AND_ST_MARYS){ //dracula cant travel by rail and cant got to the hospital
            ok = FALSE;
        }
        
        if(ok == TRUE){
            possibleMoves[count] = curr->v;
            count++;
        }
        curr = curr->next;
    }
    return possibleMoves;
}


// What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{
    if (player == PLAYER_DRACULA){
        return whereCanIgo(currentView, numLocations, road, sea);
    } else {
        return connectedLocations(currentView->state, numLocations, whereIs(currentView, player), player, giveMeTheRound(currentView), road, rail, sea);
    }
    return NULL;
}



*/
static void getTrap(char *pastPlays, LocationID *trap) {
	int i;
        for (i = 0; i < strlen(pastPlays); i += 8){
            	char * play = (char *) malloc(9);
		strncpy(play, pastPlays+i, 8);
        	if (play[0] == 'D'){
            		if(play[3] == 'T'){
				char pos[2];
				pos[0] = play[1];
				pos[1] = play[2]; 
				int j = 5;
				while(j > 0){					
					trap[j] = trap[j-1];
					j--;
				}
				trap[0] = abbrevToID(pos);
             		}
		}
        free(play);
    	}
    
}

static LocationID getVamp(char *pastPlays) {
 	int i;
	LocationID vamp;
    	for (i = 0; i < strlen(pastPlays); i += 8){
        	char * play = (char *) malloc(9);
		strncpy(play, pastPlays+i, 8);
        	if (play[0] == 'D'){
        	    	if(play[4] == 'V') {
				char pos[2];
				pos[0] = play[1];
				pos[1] = play[2]; 
                		vamp = abbrevToID(pos);
            		}
        	}
		free(play);
    }
	return vamp;
}
