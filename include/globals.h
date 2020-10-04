#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         
#include <iostream>

#define NUMBER_OF_CARDS 52
#define NUMBER_OF_ROUNDS 3
#define NUMBER_OF_THREADS 3

// <<<<<<<< THREAD GLOBALS >>>>>>>>
extern pthread_mutex_t mutex_deck_availability_to_player;
extern pthread_cond_t cond_deck_availability;
extern pthread_mutex_t mutex_deck_availability_to_dealer;
extern pthread_cond_t cond_winner_found;

// <<<<<<<< GAME GLOBALS >>>>>>>>
extern FILE * log_file;
extern int seed;
extern int which_player;
extern int current_round;
extern bool winner_found;