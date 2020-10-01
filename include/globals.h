#pragma once

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         
#include <iostream>

#define NUM_THREADS 3      // number of player threads 
#define NUM_CARDS 52       // number of cards

// global variables ============================================================
// THREAD g-vars:
extern pthread_mutex_t mutex_useDeck;
extern pthread_cond_t condition_var;
extern pthread_mutex_t mutex_dealerExit;
extern pthread_cond_t cond_win1;
extern pthread_t playerThreads[NUM_THREADS];
extern pthread_t dealerThread;

// OTHER g-vars:
extern FILE * pFile;              // point to ext file for the log
extern int roundNum;          // keep track of which round it is
extern int numberOfRounds;    // select how many rounds to play
extern int some_value;        // TESTING ONLYxxxxxxxxxxxxxxxxxxxxxxx  
extern int turn;              // keep track of whose turn it is
extern int deck[NUM_CARDS];       // a card deck for shuffling and dealing
extern int *topOfDeck;            // point to top of deck
extern int *bottomOfDeck;         // point to bottom of deck
extern int seed;              // the seed for rand() passed from command line   
extern bool win;          // flag to indicate a player has won
