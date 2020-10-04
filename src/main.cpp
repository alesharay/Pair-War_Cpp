// library links ===============================================================
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

// function prototypes =========================================================
void playRound();
void resetHands();

// <<<<<<<< main >>>>>>>> 
int main(int argc, char *argv[]){

  pFile = fopen("log.txt", "a"); // open the log file 
  seed = atoi( argv[1] );
  srand(seed);

   while( roundNum <= numberOfRounds ){
      win = false;                // reset the win flag 
      playRound();                // launch a round
      roundNum++;                 // inc the round counter to next round
   }
   
   fclose(pFile);                 // close the log file
   exit(EXIT_SUCCESS);
} // end main

// <<<<<<<< playRound >>>>>>>>
void playRound(){ // launch dealer and player threads for the current round
  cards.loadDeck();               // populate the card deck
  resetHands();

  if( roundNum == 1) turn = 1;
  if( roundNum == 2) turn = 2;
  if( roundNum == 3) turn = 3;

  printf("\n<<<<<<<<<<<< ROUND: %d >>>>>>>>>>>>\n", roundNum);
  fprintf(pFile, "\n<<<<<<<<<<<< ROUND: %d >>>>>>>>>>>>\n", roundNum);


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

} // end playRound

// <<<<<<<< resetHands >>>>>>>>
void resetHands() {
  player1.reset_hand();
  player2.reset_hand();
  player3.reset_hand();
} // end resetHands()