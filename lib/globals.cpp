#include "globals.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

// <<<<<<<< THREAD GLOBALS >>>>>>>>
 pthread_mutex_t mutex_deck_availability_to_player = PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t cond_deck_availability = PTHREAD_COND_INITIALIZER;
 pthread_mutex_t mutex_deck_availability_to_dealer = PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t cond_winner_found = PTHREAD_COND_INITIALIZER;

// <<<<<<<< GAME GLOBALS >>>>>>>>
 FILE * log_file;
 int seed = 0;
 int which_player = 1;
 int current_round = 1;
 bool winner_found = false;