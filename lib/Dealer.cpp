#include "Dealer.h"

using namespace std;

// <<<<<<<< constructor >>>>>>>>
Dealer::Dealer(Deck &cards, Player &player_1, Player &player_2, Player &player_3) : card_deck(cards), player1(player_1), player2(player_2), player3(player_3) {} // end constructor

// <<<<<<<< run >>>>>>>>
void Dealer::run() {
   
  access_deck();

  pthread_mutex_lock(&mutex_deck_availability_to_dealer);  // lock the deck to the dealer
      while( !winner_found ) {
         pthread_cond_wait(&cond_winner_found, &mutex_deck_availability_to_dealer);
      }      
  pthread_mutex_unlock(&mutex_deck_availability_to_dealer); // unlock the deck to the dealer
   
   fprintf(log_file, "DEALER: exits round\n");  

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
  fprintf(log_file, "DEALER: shuffle\n"); // shuffle the deck

  // int size = card_deck.size();
  for( int i = 0; i < NUMBER_OF_CARDS; ++i ) {
    int randomIndex = rand() % NUMBER_OF_CARDS;
    int temp = card_deck.get( i ); 
    card_deck.set( i, card_deck.get(randomIndex) );
    card_deck.set( randomIndex, temp );
  }

  card_deck.show_deck();
} // end shuffle_deck

// <<<<<<<< deal_cards >>>>>>>>
void Dealer::deal_cards() {
  fprintf(log_file, "DEALER: deal\n");      
  printf("DEALER: deal\n"); 

  if( which_player == 1) { 
    player1.set_hand( card_deck.pop() );
    printf("--- PLAYER %d: hand %d\n", player1.get_ID(), player1.get_hand());
    player2.set_hand( card_deck.pop() );
    printf("--- PLAYER %d: hand %d\n", player2.get_ID(), player2.get_hand());
    player3.set_hand( card_deck.pop() ); 
    printf("--- PLAYER %d: hand %d\n", player3.get_ID(), player3.get_hand());

  } else if( which_player == 2 ) {
    player2.set_hand( card_deck.pop() );
    printf("--- PLAYER %d: hand %d\n", player2.get_ID(), player2.get_hand());
    player3.set_hand( card_deck.pop() ); 
    printf("--- PLAYER %d: hand %d\n", player3.get_ID(), player3.get_hand());
    player1.set_hand( card_deck.pop() );
    printf("--- PLAYER %d: hand %d\n", player1.get_ID(), player1.get_hand());

  } else {
    player3.set_hand( card_deck.pop() ); 
    printf("--- PLAYER %d: hand %d\n", player3.get_ID(), player3.get_hand());
    player1.set_hand( card_deck.pop() );
    printf("--- PLAYER %d: hand %d\n", player1.get_ID(), player1.get_hand());    
    player2.set_hand( card_deck.pop() );
    printf("--- PLAYER %d: hand %d\n", player2.get_ID(), player2.get_hand());
  }
} // end deal_cards