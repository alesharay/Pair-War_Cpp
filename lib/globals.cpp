#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         
#include <iostream>

#include "globals.h"

#define NUM_THREADS 3      // number of player threads 
#define NUM_CARDS 52       // number of cards

// global variables ============================================================
// THREAD g-vars:
 pthread_mutex_t mutex_useDeck = PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
 pthread_mutex_t mutex_dealerExit = PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t cond_win1 = PTHREAD_COND_INITIALIZER;
 pthread_t playerThreads[NUM_THREADS];
 pthread_t dealerThread;

// OTHER g-vars:
 FILE * pFile;              // point to ext file for the log
 int roundNum = 1;          // keep track of which round it is
 int numberOfRounds = 3;    // select how many rounds to play
 int some_value = 1;        // TESTING ONLYxxxxxxxxxxxxxxxxxxxxxxx  
 int turn = 0;              // keep track of whose turn it is
 //int const NUM_CARDS = 52;  // number of cards in the deck 
 int seed = 0;              // the seed for rand() passed from command line   
 bool win = false;          // flag to indicate a player has won
 long pId = 0;              // identify the player