#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         
#include <iostream>

#include "globals.h"

#define NUM_THREADS 3      // number of player threads 
#define NUM_CARDS 52       // number of cards

// THREAD GLOBALS
 pthread_mutex_t mutex_deck_availability_to_player = PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t cond_deck_availability = PTHREAD_COND_INITIALIZER;
 pthread_mutex_t mutex_deck_availability_to_dealer = PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t cond_winner_found = PTHREAD_COND_INITIALIZER;

// OTHER GLOBALS
 FILE * pFile;              // point to ext file for the log
 int roundNum = 1;          // keep track of which round it is
 int numberOfRounds = 3;    // select how many rounds to play
 int turn = 0;              // keep track of whose turn it is
 int seed = 0;              // the seed for rand() passed from command line   
 bool win = false;          // flag to indicate a player has won