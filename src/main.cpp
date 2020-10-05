#include "Dealer.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

Deck cards;
Player player1( cards, 1 ), player2( cards, 2 ), player3( cards, 3 );
Dealer dealer( cards, player1, player2, player3 );

// <<<<<<<< function prototypes >>>>>>>>
void play_round();
void display_result();
void reset_hands();
void set_seed( char *argv[] );

// <<<<<<<< main >>>>>>>> 
int main( int argc, char *argv[] ){

  log_file = fopen( "Log_File.txt", "w+" );
  set_seed(argv);

  for( current_round; current_round <= NUMBER_OF_ROUNDS; current_round++ ) {
    winner_found = false;
    play_round();
  }

  fclose(log_file);
  exit(EXIT_SUCCESS);
} // end main

// <<<<<<<< set_seed >>>>>>>>
void set_seed( char *argv[] ) {
  try { 
    seed = atoi( argv[1] );
    if( seed < 1000000 ) seed += 1000000;
    srand(seed);
  } catch( const exception& e) {
    printf( "Invalid seed entered... Please try again" );
  }
} // end set_seed

// <<<<<<<< play_round >>>>>>>>
void play_round(){
  cards.load_deck();
  reset_hands();

  if( current_round == 1 ) which_player = 1;
  if( current_round == 2 ) which_player = 2;
  if( current_round == 3 ) which_player = 3;

  printf("\n<<<<<<<<<<<< ROUND: %d >>>>>>>>>>>>\n", current_round);
  fprintf(log_file, "\n<<<<<<<<<<<< ROUND: %d >>>>>>>>>>>>\n", current_round);

  // create dealer thread
  dealer.start_thread();

  // create player threads
  player1.start_thread(); 
  player2.start_thread(); 
  player3.start_thread();

  // join dealer threads
  dealer.wait();

  // join player threads
  player1.wait(); 
  player2.wait(); 
  player3.wait();

  display_result();
} // end play_round

// <<<<<<<< display_result >>>>>>>>
void display_result() {
  int winner = player1.won_game() ? 1 : player2.won_game() ? 2 : 3;

  switch(winner) {
    case 1:
      printf("PLAYER %d:\nHAND %d %d\nWIN yes\n", 1, player1.get_hand(), player1.get_newlyDrawnCard());
      printf("PLAYER %d:\nHAND %d\nWIN no\n", 2, player2.get_hand());
      printf("PLAYER %d:\nHAND %d\nWIN no\n", 3, player3.get_hand());
      break;
    case 2:
      printf("PLAYER %d:\nHAND %d\nWIN no\n", 1, player1.get_hand());
      printf("PLAYER %d:\nHAND %d %d\nWIN yes\n", 2, player2.get_hand(), player2.get_newlyDrawnCard());
      printf("PLAYER %d:\nHAND %d\nWIN no\n", 3, player3.get_hand());    
      break;
    case 3:
      printf("PLAYER %d:\nHAND %d\nWIN no\n", 1, player1.get_hand());
      printf("PLAYER %d:\nHAND %d\nWIN no\n", 2, player2.get_hand());  
      printf("PLAYER %d:\nHAND %d %d\nWIN yes\n", 3, player3.get_hand(), player3.get_newlyDrawnCard());
      break;
    default:
      break;
  }  
  cards.display_deck();
} // end display_result

// <<<<<<<< reset_hands >>>>>>>>
void reset_hands() {
  player1.reset_hand();
  player2.reset_hand();
  player3.reset_hand();
} // end reset_hands()