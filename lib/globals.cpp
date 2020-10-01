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
 int *topOfDeck;            // point to top of deck
 int *bottomOfDeck;         // point to bottom of deck
 int seed = 0;              // the seed for rand() passed from command line   
 bool win = false;          // flag to indicate a player has won
 long pId = 0;              // identify the player




//  void useTheDeck(hand thisHand){
// // void useTheDeck(long pId, hand thisHand){
//    if( pId == 0 ){ // dealer uses the deck......................................   
//       fprintf(pFile, "DEALER: shuffle\n"); cards.shuffleCards(); // shuffle the deck    

//       fprintf(pFile, "DEALER: deal\n"); dealCards();      // deal the cards
//    }    
//    else{ // player uses the deck................................................
   
//       // show hand
//       fprintf(pFile, "PLAYER %ld: hand %d \n", pId, thisHand.card1);
      
//       // draw a card

//       thisHand.card2 = cards.pop();

//       fprintf(pFile, "PLAYER %ld: draws %d \n", pId,thisHand.card2); 
      
//       // show hand     
//       printf("PLAYER %ld:\nHAND %d %d\n",pId, thisHand.card1, thisHand.card2);
//       fprintf(pFile, "PLAYER %ld: hand %d %d\n", pId, thisHand.card1, thisHand.card2);        
            
//       // compare the cards
//       if( thisHand.card1 == thisHand.card2 ){
//          // if the cards match, then declare a winner            
//          printf("WIN yes\n");      
//          fprintf(pFile, "PLAYER %ld: wins\n", pId);
//          win = true;   
//          pthread_cond_signal(&cond_win1); // signal dealer to exit           
//       }
//       else{
//          // if the cards don't match, then discard a card            
//          printf("WIN no\n");    

//          // randomly select discard and put it back in the deck
//          if( rand()%2 ){
//             fprintf(pFile, "PLAYER %ld: discards %d \n", pId, thisHand.card1);   

//             cards.push(thisHand.card1);
//             thisHand.card1 = thisHand.card2; // set card1 to remaining card value
//          }     
//          else{
//             fprintf(pFile, "PLAYER %ld: discards %d \n", pId, thisHand.card2);             
//             cards.push(thisHand.card2);
//          }   
//          // print the contents of the deck
//         cards.showDeck();                
//       }      
//    }  
//    turn ++; // inc turn so next player may use the deck
//    if( turn > NUM_THREADS ) turn = 1;      // if player3 went, move to player1
//    pthread_cond_broadcast(&condition_var); // broadcast that deck is available
// } // end function