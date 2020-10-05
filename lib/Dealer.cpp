#include "Dealer.h"

using namespace std;

// <<<<<<<< constructor >>>>>>>>
Dealer::Dealer(Deck &cards, Player &player_1, Player &player_2, Player &player_3) : 
  card_deck(cards), player1(player_1), player2(player_2), player3(player_3) {} // end constructor

// <<<<<<<< run >>>>>>>>
void Dealer::run() {
  access_deck();

  pthread_mutex_lock( &mutex_deck_availability_to_dealer );
  while( !winner_found ) { pthread_cond_wait( &cond_winner_found, &mutex_deck_availability_to_dealer ); }      
  pthread_mutex_unlock( &mutex_deck_availability_to_dealer );
  
  pthread_exit( NULL );
} // end run

// <<<<<<<< access_deck >>>>>>>>
void Dealer::access_deck() {
  shuffle_deck();
  deal_cards();

  pthread_cond_broadcast( &cond_deck_availability );
} // end access_deck

// <<<<<<<< shufflfe_deck >>>>>>>>
void Dealer::shuffle_deck() {
  fprintf(log_file, "DEALER: shuffle\n"); 

  for( int i = 0; i < NUMBER_OF_CARDS; ++i ) {
    int randomIndex = rand() % NUMBER_OF_CARDS;
    int temp = card_deck.get( i ); 
    card_deck.set( i, card_deck.get(randomIndex) );
    card_deck.set( randomIndex, temp );
  }

  card_deck.print_deck();
} // end shuffle_deck

// <<<<<<<< deal_cards >>>>>>>>
void Dealer::deal_cards() {
  if( which_player == 1 ) { 
    player1.set_hand( card_deck.pop() );
    player2.set_hand( card_deck.pop() );
    player3.set_hand( card_deck.pop() ); 

  } else if( which_player == 2 ) {
    player2.set_hand( card_deck.pop() );
    player3.set_hand( card_deck.pop() ); 
    player1.set_hand( card_deck.pop() );

  } else {
    player3.set_hand( card_deck.pop() ); 
    player1.set_hand( card_deck.pop() );
    player2.set_hand( card_deck.pop() );
  }
} // end deal_cards