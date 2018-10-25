

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h"

// #include "Map.h" ... if you decide to use the Map ADT

struct gameView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    int score;
    int health[NUM_PLAYERS];
    Round round;
    PlayerID currentPlayer;
    LocationID currentLocation[NUM_PLAYERS];
    LocationID trail[NUM_PLAYERS][TRAIL_SIZE];
    LocationID trapLocations[TRAIL_SIZE];
    LocationID imVampLocation;    
};   



static void wipeTrails(GameView g){
    int i = 0;
    int j = 0;
    for (i = 0;i < NUM_PLAYERS; i++){
        for (j = 0; j < TRAIL_SIZE; j++){
            g->trail[i][j] = UNKNOWN_LOCATION;
        }
        g->currentLocation[i] = UNKNOWN_LOCATION;
    }
}



static void putMoveIntoTrail(GameView g, PlayerID p, LocationID l){
    // Shift all elements right by 1
    printf("Putting move into trail: ");
    int i = 0;
    for (i = 4; i >= 0; i--){
        g->trail[p][i+1] = g->trail[p][i];
        printf("shifting: %d ",g->trail[p][i]);
    }
    g->trail[p][0] = l;
    printf(" \n");
}



static void handleHunters(GameView g, char * play, PlayerID player){
    int i;
    for (i = 3; i < 7; i++){
        switch (play[i]){
            // Trap, hunter loses 2 points
            case 'T': g->health[player] -= LIFE_LOSS_TRAP_ENCOUNTER; break;
            // Immature vampire destryoted, nothing happens
            case 'V': break;
            // Dracula encountered
            case 'D': 
                printf("Player current health is %d\n", g->health[player]);
                g->health[player] -= LIFE_LOSS_DRACULA_ENCOUNTER;
                printf("Player health after encounter is: %d\n", g->health[player]);
                g->health[PLAYER_DRACULA] -= LIFE_LOSS_HUNTER_ENCOUNTER;
        }
    }

    char * location = (char *) malloc(3);
    strncpy(location, play+1, 2);
    int locationNum = abbrevToID(location);
    g->currentLocation[player] = locationNum;
    printf("LOCATION IS: %d set value is %d\n", locationNum, g->currentLocation[player]);
    if (locationNum == g->trail[player][0]){
        g->health[player] += LIFE_GAIN_REST;
    }

    if (g->health[player] > 9){
        g->health[player] = 9;
    }
    putMoveIntoTrail(g, player, locationNum);
}


static void handleDrac(GameView g, char * play){
    char * location = (char *) malloc(3);
    strncpy(location, play+1, 2);
    int locationNum;
    printf("DRAC location is %s\n", location);
    printf("Result of strcmp is %d\n", strcmp(location, "C?"));
    if (strcmp(location, "C?") == 0){
        locationNum = CITY_UNKNOWN;
    } else if (strcmp(location, "S?") == 0){
        locationNum = SEA_UNKNOWN;
        g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
    } else if (strcmp(location, "TP") == 0){
        locationNum = TELEPORT;
    } else if (strcmp(location, "HI") == 0){
        locationNum = HIDE;
    } else if (strcmp(location, "D1") == 0){
        locationNum = DOUBLE_BACK_1;
        if (g->trail[PLAYER_DRACULA][0] == SEA_UNKNOWN){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }
        if (g->trail[PLAYER_DRACULA][0] < 70 && isSea(g->trail[PLAYER_DRACULA][0])){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }
    } else if (strcmp(location, "D2") == 0){
        locationNum = DOUBLE_BACK_2;
        if (g->trail[PLAYER_DRACULA][1] == SEA_UNKNOWN){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }
        if (g->trail[PLAYER_DRACULA][1] < 70 && isSea(g->trail[PLAYER_DRACULA][1])){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }

    } else if (strcmp(location, "D3") == 0){
        locationNum = DOUBLE_BACK_3;
        if (g->trail[PLAYER_DRACULA][2] == SEA_UNKNOWN){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }
        if (g->trail[PLAYER_DRACULA][2] < 70 && isSea(g->trail[PLAYER_DRACULA][2])){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }
    } else if (strcmp(location, "D4") == 0){
        locationNum = DOUBLE_BACK_4;
        if (g->trail[PLAYER_DRACULA][3] == SEA_UNKNOWN){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }
        if (g->trail[PLAYER_DRACULA][3] < 70 && isSea(g->trail[PLAYER_DRACULA][3])){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }
    } else if (strcmp(location, "D5") == 0){
        locationNum = DOUBLE_BACK_5;
        if (g->trail[PLAYER_DRACULA][4] == SEA_UNKNOWN){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }
        if (g->trail[PLAYER_DRACULA][4] < 70 && isSea(g->trail[PLAYER_DRACULA][4])){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }
    } else {
        locationNum = abbrevToID(location);
        if (isSea(locationNum)){
            g->health[PLAYER_DRACULA] -= LIFE_LOSS_SEA;
        }
    }
    g->currentLocation[PLAYER_DRACULA] = locationNum;
    putMoveIntoTrail(g, PLAYER_DRACULA, locationNum);


    if (play[6] == 'V'){
        g->score -= SCORE_LOSS_VAMPIRE_MATURES;
    }
    if (locationNum == TELEPORT && g->health[PLAYER_DRACULA] > 0){
        g->health[PLAYER_DRACULA] += LIFE_GAIN_CASTLE_DRACULA;
    }
    if (g->health[PLAYER_DRACULA] > 40){
        g->health[PLAYER_DRACULA] = 40;
    }
    g->score -= SCORE_LOSS_DRACULA_TURN;
}



static PlayerID determinePlayer(GameView g, char * play){
    PlayerID playerID;
    switch (play[0]){
        case 'G': playerID = PLAYER_LORD_GODALMING; break;
        case 'S': playerID = PLAYER_DR_SEWARD; break;
        case 'H': playerID = PLAYER_VAN_HELSING; break;
        case 'M': playerID = PLAYER_MINA_HARKER; break;
        case 'D': playerID = PLAYER_DRACULA; 
            g->round++;
            break;



    }
    g->currentPlayer = playerID + 1;
    if (playerID == PLAYER_DRACULA){
        g->currentPlayer = PLAYER_LORD_GODALMING;
    }
    return playerID;

}



static void parsePastPlays(GameView g, char * move){
    int i = 0;
    for (i = 0; i < strlen(move); i += 8){
        char * play = (char *) malloc(9);
        strncpy(play, move+i, 8);
        PlayerID player = determinePlayer(g, play);
        if (play[0] != 'D'){
            printf("HANDING HUNTER %d\n", player);
            handleHunters(g, play, player);
        } else {
            printf("HANDLING DRAC %d\n", player);
            handleDrac(g, play);
        }
        free(play);
    }
}



// Checks if a location has already been listed as connected

static int inArray(LocationID *array, int arrayLength, LocationID place)
{
    int i = 0;
    while (i < arrayLength) {
        if (array[i] == place)
            return 1;
        else
            i++;
    }

    return 0;

}



// Finds rail connections allowed by rules

static int railSearch(Map map, LocationID *railConnections, LocationID origin, int maxDepth)

{

	railConnections[0] = origin;

    int nRailLocations = 1;

    int checked = 0;

    int depth, prevRailLocations;

	int i;

    for (depth = 1; depth <= maxDepth; depth++){

		prevRailLocations = nRailLocations;

    	    while (checked < prevRailLocations) {

/*		    while (n != NULL) {

		        if (n->type == RAIL) {

		            if (!inArray(railConnections, nRailLocations, n->v)) {

		            	railConnections[nRailLocations] = n->v;

		            	nRailLocations++;

		            }

		        }

		        n = n->next;

		    } 

*/

			for (i = MIN_MAP_LOCATION; i < MAX_MAP_LOCATION; i++) {

				if (connectionExists(map, railConnections[checked], i, RAIL)) {

					if (!inArray(railConnections, nRailLocations, i)) {

						railConnections[nRailLocations] = i;

						nRailLocations++;

					}

				}

			}

		    checked++;

		}   

    }

    return nRailLocations;

} 



// Creates a new GameView to summarise the current state of the game

GameView newGameView(char *pastPlays, PlayerMessage messages[])

{

    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION

    GameView gameView = malloc(sizeof(struct gameView));

    PlayerID player;

    wipeTrails(gameView);

    gameView->round = 0; 

    gameView->score = GAME_START_SCORE;

    gameView->currentPlayer = PLAYER_LORD_GODALMING;



    //LocationID pastLocation[NUM_PLAYERS];

    for (player = PLAYER_LORD_GODALMING; player <= PLAYER_MINA_HARKER; player++){

        gameView->health[player] = GAME_START_HUNTER_LIFE_POINTS;

    }



    gameView->health[PLAYER_DRACULA] = GAME_START_BLOOD_POINTS;

    parsePastPlays(gameView, pastPlays);

    return gameView;

}

     

     

// Frees all memory previously allocated for the GameView toBeDeleted

void disposeGameView(GameView toBeDeleted)

{

    free(toBeDeleted);

}





//// Functions to return simple information about the current state of the game



// Get the current round

Round getRound(GameView currentView)

{

    return currentView->round;

}



// Get the id of current player - ie whose turn is it?

PlayerID getCurrentPlayer(GameView currentView)

{

    return currentView->currentPlayer;

}



// Get the current score

int getScore(GameView currentView)

{

    return currentView->score;

}



// Get the current health points for a given player

int getHealth(GameView currentView, PlayerID player)

{

    return currentView->health[player];

}



// Get the current location id of a given player

LocationID getLocation(GameView currentView, PlayerID player)

{

    printf("Retrieveing locaiton for: %d\n", player);

    printf ("Location of %d is %d\n", player, currentView->currentLocation[player]);

    return currentView->currentLocation[player];

}



//// Functions that return information about the history of the game



// Fills the trail array with the location ids of the last 6 turns

void getHistory(GameView currentView, PlayerID player,

                            LocationID trail[TRAIL_SIZE])

{

    printf("Writing to trail: ");

    int i = 0;

    for (i = 0; i < TRAIL_SIZE; i++){

        trail[i] = currentView->trail[player][i];

        printf("%d ",currentView->trail[player][i]);

    }

    printf(" \n");

}



//// Functions that query the map to find information about connectivity



// Returns an array of LocationIDs for all directly connected locations



LocationID *connectedLocations(GameView currentView, int *numLocations,

                               LocationID from, PlayerID player, Round round,

                               int road, int rail, int sea)

{

    int numL;

    LocationID *locations = malloc(NUM_MAP_LOCATIONS * sizeof(LocationID));

    if (round == 0) {

        for (numL = 0; numL < NUM_MAP_LOCATIONS; numL++)

            locations[numL] = numL;

        if (player == PLAYER_DRACULA) {

            locations[ST_JOSEPH_AND_ST_MARYS] = MAX_MAP_LOCATION;

            numL--;

        }

    } else {

        locations[0] = from;

        numL = 1;

        Map map = newMap();

		int i;

        if (road) {

			for (i = MIN_MAP_LOCATION; i < MAX_MAP_LOCATION; i++) {

				if (connectionExists(map, from, i, ROAD)) {

					locations[numL] = i;

					numL++;

				}

			}

		}

        if (sea) {

			for (i = MIN_MAP_LOCATION; i < MAX_MAP_LOCATION; i++) {

				if (connectionExists(map, from, i, BOAT) && (!inArray(locations, numL, i))) {

					locations[numL] = i;

					numL++;

				}

			}

		}

        int railDistance = round % 4;

        if (rail && (player != PLAYER_DRACULA) && (railDistance != 0)) {

            LocationID *tmp = malloc(NUM_MAP_LOCATIONS * sizeof(LocationID));

            int nRailConnections = 0;

            nRailConnections = railSearch(map, tmp, from, railDistance);

            for (i = 0; i < nRailConnections; i++) {

            	if (!inArray(locations, numL, tmp[i])) {

            		locations[numL] = i;

            		numL++;

            	} 

            }

            free(tmp);

        }

        disposeMap(map);

    }

    *numLocations = numL;

    return locations;

}
