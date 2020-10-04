// #include "Player.h"  
#include "Dealer.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         // for writing to the log 
#include <iostream>


Deck cards;
Player player1( cards, 1 ), player2( cards, 2 ), player3( cards, 3 );
Dealer dealer( cards, player1, player2, player3 );

// <<<<<<<< function prototypes >>>>>>>>
void play_round();
void reset_hands();

// <<<<<<<< main >>>>>>>> 
int main(int argc, char *argv[]){

  log_file = fopen("log.txt", "a"); // open the log file 
  seed = atoi( argv[1] );
  srand(seed);

   while( current_round <= NUMBER_OF_ROUNDS ) {
      winner_found = false;                // reset the win flag 
      play_round();                // launch a round
      current_round++;                 // inc the round counter to next round
   }
   
   fclose(log_file);                 // close the log file
   exit(EXIT_SUCCESS);
} // end main

// <<<<<<<< play_round >>>>>>>>
void play_round(){ // launch dealer and player threads for the current round
  cards.load_deck();               // populate the card deck
  reset_hands();

  if( current_round == 1) which_player = 1;
  if( current_round == 2) which_player = 2;
  if( current_round == 3) which_player = 3;

  printf("\n<<<<<<<<<<<< ROUND: %d >>>>>>>>>>>>\n", current_round);
  fprintf(log_file, "\n<<<<<<<<<<<< ROUND: %d >>>>>>>>>>>>\n", current_round);


  // create dealer thread
  dealer.start_thread();

  // create player threads
  player1.start_thread(); 
  player2.start_thread(); 
  player3.start_thread();

  // join threads so that function waits until all threads complete
  dealer.wait();

  player1.wait(); 
  player2.wait(); 
  player3.wait();

} // end play_round

// <<<<<<<< reset_hands >>>>>>>>
void reset_hands() {
  player1.reset_hand();
  player2.reset_hand();
  player3.reset_hand();
} // end reset_hands()