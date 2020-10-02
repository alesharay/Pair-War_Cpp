// library links ===============================================================
// #include "Player.h"
#include "Dealer.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         // for writing to the log 
#include <iostream>

struct hand{               // a hand container for each player 
   int card1, card2;
};

hand hand1, hand2, hand3;  // hands for the players 
Deck cards;
Player player1( "PLAYER 1" ), player2( "PLAYER 2" ), player3( "PLAYER 3" );
Dealer dealer(cards, player1, player2, player3);


// function prototypes =========================================================
void *dealer_thread(void *arg);
void *player_threads(void *playerId);
void useTheDeck(long, hand);
void randSeed();
void dealCards(); //-------------------dealCards()
void playRound();
void parseArgs(char *[]);

// main ========================================================================
int main(int argc, char *argv[]){

   pFile = fopen("log.txt", "a"); // open the log file 
   parseArgs(argv);               // parse args from console   
   randSeed();                    // seed rand() with arg from command line

   while( roundNum <= numberOfRounds ){
      playRound();                // launch a round
      roundNum++;                 // inc the round counter to next round
      win = false;                // reset the win flag 
   }
   
   fclose(pFile);                 // close the log file
   exit(EXIT_SUCCESS);
} // end main


// function declarations ======================================================
void parseArgs(char *argv[]){ // set seed to val from the command line
   seed = atoi( argv[1] );
} // end function

void randSeed(){ // seed rand() using arg x from the command line    
   srand(seed);
} // end function

void playRound(){ // launch dealer and player threads for the current round
  cards.loadDeck();               // populate the card deck

  printf("\n<<<<<<<<<<<< ROUND: %d >>>>>>>>>>>>\n", roundNum);
  fprintf(pFile, "\n<<<<<<<<<<<< ROUND: %d >>>>>>>>>>>>\n", roundNum);

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

   pId = 0;       // identify the dealer as player 0
  //  long pId = 0;       // identify the dealer as player 0
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

  //  pId = (long)playerId;
   long pId = (long)playerId;
   
   // assign hands to players based on which round is being played   
   hand thisHand;
   if( roundNum == 1 ){
      if( pId == 1 ) thisHand = hand1; 
      else if( pId == 2 ) thisHand = hand2;
      else thisHand = hand3;
   } 
   else if( roundNum == 2 ){
      if( pId == 2 ) thisHand = hand2; 
      else if( pId == 2 ) thisHand = hand3;
      else thisHand = hand1;
   }    
   else if( roundNum == 3 ){
      if( pId == 3 ) thisHand = hand3; 
      else if( pId == 1 ) thisHand = hand1;
      else thisHand = hand2;
   }   
   
   while( !win ){
      pthread_mutex_lock(&mutex_useDeck); // lock the deck ...............  
         while( pId != turn && !win ){ // make players wait for their turn
            pthread_cond_wait(&condition_var, &mutex_useDeck); 
         }
         if( !win ){   
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
      fprintf(pFile, "DEALER: shuffle\n"); dealer.shuffleCards(cards); // shuffle the deck
      cards.showDeck();

      fprintf(pFile, "DEALER: deal\n"); dealCards();      // deal the cards
   }    
   else{ // player uses the deck................................................
   
      // show hand
      fprintf(pFile, "PLAYER %ld: hand %d \n", pId, thisHand.card1);
      
      // draw a card

      thisHand.card2 = cards.pop();

      fprintf(pFile, "PLAYER %ld: draws %d \n", pId,thisHand.card2); 
      
      // show hand     
      printf("----PLAYER %ld:\nHAND %d %d\n",pId, thisHand.card1, thisHand.card2);
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

         // randomly select discard and put it back in the deck
         if( rand()%2 ){
            fprintf(pFile, "PLAYER %ld: discards %d \n", pId, thisHand.card1);   

            cards.push(thisHand.card1);
            thisHand.card1 = thisHand.card2; // set card1 to remaining card value
         }     
         else{
            fprintf(pFile, "PLAYER %ld: discards %d \n", pId, thisHand.card2);             
            cards.push(thisHand.card2);
         }   
      }      
   }  
   turn ++; // inc turn so next player may use the deck
   if( turn > NUM_THREADS ) {
     turn = 1;      // if player3 went, move to player1
     cards.showDeck();
   }
   
   pthread_cond_broadcast(&condition_var); // broadcast that deck is available
} // end function

void dealCards(){ // the dealer deals one card into each hand
  hand1.card1 = cards.pop();      
  hand2.card1 = cards.pop();      
  hand3.card1 = cards.pop();      
} // end function