/*******************************************************************************
*   course:       CS4328 
*   project:      Project 2 - Pair War 
*   programmer:   Stacy Bridges
*   due:          12/03/2015  
*   submitted:    12/05/2015
*   description:  Pair War Card Game
*******************************************************************************/


// library links ===============================================================
#include "Deck.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         // for writing to the log 
#include <iostream>

// // global variables ============================================================
// // THREAD g-vars:
// pthread_mutex_t mutex_useDeck = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
// pthread_mutex_t mutex_dealerExit = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t cond_win1 = PTHREAD_COND_INITIALIZER;
// pthread_t playerThreads[NUM_THREADS];
// pthread_t dealerThread;

// // OTHER g-vars:
// FILE * pFile;              // point to ext file for the log
// int roundNum = 1;          // keep track of which round it is
// int numberOfRounds = 3;    // select how many rounds to play
// int some_value = 1;        // TESTING ONLYxxxxxxxxxxxxxxxxxxxxxxx  
// int turn = 0;              // keep track of whose turn it is
// const int NUM_CARDS = 52;  // number of cards in the deck 
// int deck[NUM_CARDS];       // a card deck for shuffling and dealing
// int *topOfDeck;            // point to top of deck
// int *bottomOfDeck;         // point to bottom of deck
// int seed = 0;              // the seed for rand() passed from command line   
// bool win = false;          // flag to indicate a player has won
struct hand{               // a hand container for each player 
   int card1, card2;
};
hand hand1, hand2, hand3;  // hands for the players 
Deck cards;


// function prototypes =========================================================
void *dealer_thread(void *arg);
void *player_threads(void *playerId);
void useTheDeck(long, hand);
void randSeed();
void buildDeck(); //-------------------loadDeck()
void shuffleDeck(); //-----------------shuffleCards()
void dealCards(); //-------------------dealCards()
void playRound();
void parseArgs(char *[]);
void printDeck();


// main ========================================================================
int main(int argc, char *argv[]){

   pFile = fopen("log.txt", "a"); // open the log file 
   parseArgs(argv);               // parse args from console   
   randSeed();                    // seed rand() with arg from command line
   buildDeck();                   // populate the card deck
  // cards.loadDeck();               // populate the card deck

   while( roundNum <= 
          numberOfRounds ){
      playRound();                // launch a round
      roundNum++;                 // inc the round counter to next round
      win = false;                // reset the win flag 
   }
   
   fclose(pFile);                 // close the log file
   exit(EXIT_SUCCESS);
} // end main


// function declarations =======================================================

void parseArgs(char *argv[]){ // set seed to val from the command line
   seed = atoi( argv[1] );
} // end function


void randSeed(){ // seed rand() using arg x from the command line    
   srand(seed);
} // end function


void buildDeck(){ // put 4 of each card value into deck[] where range is 0-12
   int cardVal = 0, numInSuit = 4, card = 0;
   while( (card < NUM_CARDS) && 
          (cardVal < (NUM_CARDS/numInSuit)) ){
      for( int i = 0; i < numInSuit; i++ ){
         deck[card] = cardVal;
         card++;
      }
      cardVal++;
   }    
   topOfDeck = deck;          // point to top of deck
   bottomOfDeck = deck + 51;  // point to bottom of deck
} // end function


void playRound(){ // launch dealer and player threads for the current round

   printf("ROUND: %d ................\n", roundNum);
   fprintf(pFile, "ROUND: %d ................\n", roundNum);

   // create dealer thread
   int retD = pthread_create(&dealerThread, NULL, &dealer_thread, NULL);

   // create player threads
   int retP;
   for( long i = 1; i <= NUM_THREADS; i++ ){
      retP = pthread_create(&playerThreads[i], NULL, &player_threads, (void *)i);
   }

   // join threads so that function waits until all threads complete
   pthread_join(dealerThread, NULL); 

   for( int j = 0; j < 3; j++ ){
      pthread_join(playerThreads[j], NULL); 
   }

} // end function


void *dealer_thread(void *arg){ // this function is for the dealer thread

   long pId = 0;       // identify the dealer as player 0
   turn = 0;           // set/reset turn val to indicate it's the dealer's turn 
   hand dealerHand;    // dealer gets a NULL hand
   useTheDeck(pId, dealerHand); // let the dealer use the deck
   

   // leave the dealer thread
   pthread_mutex_lock(&mutex_dealerExit);  // lock the exit ............
      while( !win ){
         pthread_cond_wait(&cond_win1, &mutex_dealerExit);
      }      
   pthread_mutex_unlock(&mutex_dealerExit); // unlock the exit .........
   fprintf(pFile, "DEALER: exits round\n");  

   pthread_exit(NULL);
} // end function


void *player_threads(void *playerId){ // this function is for player threads

   long pId = (long)playerId;
   
   // assign hands to players based on which round is being played   
   hand thisHand;
   if( roundNum == 1 ){
      if( pId == 1 ) thisHand = hand1; 
      else if( pId == 2 ) thisHand = hand2;
      else thisHand = hand3;
   } 
   else if( roundNum == 2 ){
      if( pId == 2 ) thisHand = hand1; 
      else if( pId == 3 ) thisHand = hand2;
      else thisHand = hand3;
   }    
   else if( roundNum == 3 ){
      if( pId == 3 ) thisHand = hand1; 
      else if( pId == 1 ) thisHand = hand2;
      else thisHand = hand3;
   }   
   
   while( win == 0 ){
      pthread_mutex_lock(&mutex_useDeck); // lock the deck ...............  
         while( pId != turn && win == 0 ){ // make players wait for their turn
            pthread_cond_wait(&condition_var, &mutex_useDeck); 
         }
         if( win == 0 ){   
            useTheDeck(pId, thisHand); // let players use the deck
         }         
      pthread_mutex_unlock(&mutex_useDeck); // unlock the deck ...........
   }
   // leave the player thread
   fprintf(pFile, "PLAYER %ld: exits round\n", pId); 

   pthread_exit(NULL);   
} // end function


void useTheDeck(long pId, hand thisHand){
   if( pId == 0 ){ // dealer uses the deck......................................   
      fprintf(pFile, "DEALER: shuffle\n"); shuffleDeck(); // shuffle the deck    

      // fprintf(pFile, "DEALER: shuffle\n"); cards.shuffleCards(); // shuffle the deck    

      fprintf(pFile, "DEALER: deal\n"); dealCards();      // deal the cards
   }    
   else{ // player uses the deck................................................
   
      // show hand
      fprintf(pFile, "PLAYER %ld: hand %d \n", pId, thisHand.card1);
      
      // draw a card
      thisHand.card2 = *topOfDeck, 
      topOfDeck = topOfDeck + 1;

      // thisHand.card2 = cards.pop();

      fprintf(pFile, "PLAYER %ld: draws %d \n", pId,thisHand.card2); 
      
      // show hand     
      printf("HAND %d %d\n", thisHand.card1, thisHand.card2);
      fprintf(pFile, "PLAYER %ld: hand %d %d\n", pId, thisHand.card1, thisHand.card2);        
            
      // compare the cards
      if( thisHand.card1 == thisHand.card2 ){
         // if the cards match, then declare a winner            
         printf("WIN yes\n");      
         fprintf(pFile, "PLAYER %ld: wins\n", pId);
         win = true;   
         pthread_cond_signal(&cond_win1); // signal dealer to exit           
      }
      else{
         // if the cards don't match, then discard a card            
         printf("WIN no\n");    
         // shift cards in deck to make room for discard

         topOfDeck = topOfDeck - 1;       
         int *ptr = topOfDeck;
         while( ptr != bottomOfDeck ){
            *ptr = *(ptr + 1);
            ptr = ptr + 1;      
         }         

         // randomly select discard and put it back in the deck
         int discard = rand()%2;
         if( discard == 0 ){
            fprintf(pFile, "PLAYER %ld: discards %d \n", pId, thisHand.card1);   
            *bottomOfDeck = thisHand.card1;  // put card back in deck
            thisHand.card1 = thisHand.card2; // set card1 to remaining card value
         }     
         else{
            fprintf(pFile, "PLAYER %ld: discards %d \n", pId, thisHand.card2);             
            *bottomOfDeck = thisHand.card2;
         }   
         // print the contents of the deck
         printDeck();                 
      }      
   }  
   turn ++; // inc turn so next player may use the deck
   if( turn > NUM_THREADS ) turn = 1;      // if player3 went, move to player1
   pthread_cond_broadcast(&condition_var); // broadcast that deck is available
} // end function


void shuffleDeck(){ // dealer swaps current card w/ rand card til all shuffled
   for( int i = 0; i < (NUM_CARDS - 1); i++ ){
      int randPos = i + (rand() % (NUM_CARDS - i));  
      int temp = deck[i];
      deck[i] = deck[randPos]; 
      deck[randPos] = temp;
   }
} // end function


void dealCards(){ // the dealer deals one card into each hand
   hand1.card1 = *topOfDeck; topOfDeck = topOfDeck + 1; 
   hand2.card1 = *topOfDeck; topOfDeck = topOfDeck + 1;  
   hand3.card1 = *topOfDeck; topOfDeck = topOfDeck + 1;   


  // hand1.card1 = cards.pop();      
  // hand2.card1 = cards.pop();      
  // hand3.card1 = cards.pop();      
} // end function


void printDeck(){ // print deck to console and to log
   printf("DECK: ");
   fprintf(pFile, "DECK: ");    
   int *ptr = topOfDeck;
   while( ptr != bottomOfDeck ){
      printf("%d ", *ptr);
      fprintf(pFile, "%d ", *ptr);
      ptr++;
      if( ptr == bottomOfDeck ){
         printf("%d \n", *ptr);
         fprintf(pFile, "%d \n", *ptr);     
      }      
   }
}
