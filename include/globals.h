// #pragma once

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         
#include <iostream>

#define NUM_THREADS 3      // number of player threads 
#define NUM_CARDS 52       // number of cards

// global variables ============================================================
// THREAD g-vars:
extern pthread_mutex_t mutex_deck_availability_to_player;
extern pthread_cond_t cond_deck_availability;
extern pthread_mutex_t mutex_deck_availability_to_dealer;
extern pthread_cond_t cond_winner_found;

// OTHER g-vars:
extern FILE * pFile;              // point to ext file for the log
extern int roundNum;          // keep track of which round it is
extern int numberOfRounds;    // select how many rounds to play
extern int turn;              // keep track of whose turn it is
extern int seed;              // the seed for rand() passed from command line   
extern bool win;          // flag to indicate a player has won