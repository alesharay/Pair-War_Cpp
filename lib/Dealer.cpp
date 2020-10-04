#include "Dealer.h"

using namespace std;

// <<<<<<<< constructor >>>>>>>>
Dealer::Dealer(Deck &cards, Player &player_1, Player &player_2, Player &player_3) : card_deck(cards), player1(player_1), player2(player_2), player3(player_3) {} // end constructor

// <<<<<<<< run >>>>>>>>
void Dealer::run() {
   
  access_deck();

  pthread_mutex_lock(&mutex_deck_availability_to_dealer);  // lock the deck to the dealer
      while( !win ) {
         pthread_cond_wait(&cond_winner_found, &mutex_deck_availability_to_dealer);
      }      
  pthread_mutex_unlock(&mutex_deck_availability_to_dealer); // unlock the deck to the dealer
   
   fprintf(pFile, "DEALER: exits round\n");  

   pthread_exit(NULL);  
} // end run

// <<<<<<<< access_deck >>>>>>>>
void Dealer::access_deck() {
  shuffle_deck();
  deal_cards();

  pthread_cond_broadcast(&cond_deck_availability); // inform that deck is available
} // end access_deck

// <<<<<<<< shufflfe_deck >>>>>>>>
void Dealer::shuffle_deck() {
  fprintf(pFile, "DEALER: shuffle\n"); // shuffle the deck

  // int size = card_deck.size();
  for( int i = 0; i < NUM_CARDS; ++i ) {
    int randomIndex = rand() % NUM_CARDS;
    int temp = card_deck.get( i ); 
    card_deck.set( i, card_deck.get(randomIndex) );
    card_deck.set( randomIndex, temp );
  }

  card_deck.showDeck();
} // end shuffle_deck

// <<<<<<<< deal_cards >>>>>>>>
void Dealer::deal_cards() {
  fprintf(pFile, "DEALER: deal\n");      // deal the cards
  printf("DEALER: deal\n");      // deal the cards

  if( turn == 1) { 
    player1.set_hand( card_deck.pop() );
    // printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player1.get_ID(), player1.get_hand());
    // printf("\n\n\n");

    player2.set_hand( card_deck.pop() );
    // printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player2.get_ID(), player2.get_hand());
    // printf("\n\n\n");

    player3.set_hand( card_deck.pop() ); 
    // printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player3.get_ID(), player3.get_hand());
    // printf("\n\n\n");

  } else if( turn == 2 ) {
    player2.set_hand( card_deck.pop() );
    // printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player2.get_ID(), player2.get_hand());
    // printf("\n\n\n");

    player3.set_hand( card_deck.pop() ); 
    // printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player3.get_ID(), player3.get_hand());
    // printf("\n\n\n");

    player1.set_hand( card_deck.pop() );
    // printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player1.get_ID(), player1.get_hand());
    // printf("\n\n\n");

  } else {
    player3.set_hand( card_deck.pop() ); 
    // printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player3.get_ID(), player3.get_hand());
    // printf("\n\n\n"); 

    player1.set_hand( card_deck.pop() );
    // printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player1.get_ID(), player1.get_hand());
    // printf("\n\n\n");
    
    player2.set_hand( card_deck.pop() );
    // printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player2.get_ID(), player2.get_hand());
    // printf("\n\n\n");
  }
} // end deal_cards