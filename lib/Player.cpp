#include "Player.h"

using namespace std;

// <<<<<<<< Constructor >>>>>>>>
Player::Player( Deck &cards, int ID ) : card_deck( cards ), id( ID ) { } // end constructor

// <<<<<<<< run >>>>>>>>
void Player::run() {
  while( !winner_found ) {
    int locked = pthread_mutex_lock( &mutex_deck_availability_to_player );

    while( id != which_player && winner_found == 0 ) { pthread_cond_wait( &cond_deck_availability, &mutex_deck_availability_to_player ); }

    if( !winner_found ) {   
      if( which_player == id ) {
        access_deck();
        which_player++;
        if( which_player > NUMBER_OF_THREADS ) { which_player = 1; }
      }
    } 
    pthread_mutex_unlock( &mutex_deck_availability_to_player ); // unlock the deck ...........
  }

  fprintf( log_file, "PLAYER %d: exits round\n", id ); 
  pthread_exit( NULL );  
} // end run

// <<<<<<<< access_deck >>>>>>>>
void Player::access_deck() {
  draw_card();
  compare_cards();  
  pthread_cond_broadcast( &cond_deck_availability );
} // access_deck

// <<<<<<<< draw_card >>>>>>>>
void Player::draw_card() {
  fprintf( log_file, "PLAYER %d: hand %d \n", id, hand ); 
  newly_drawn_card = card_deck.pop();
  fprintf( log_file, "PLAYER %d: draws %d \n", id, newly_drawn_card ); 
} // end draw_card

// <<<<<<<< discard_card >>>>>>>>
void Player::discard_card( int card ) {
  card_deck.push( card );
  fprintf( log_file, "PLAYER %d: discards %d \n", id, card );
  fprintf( log_file, "PLAYER %d: hand %d \n", id, hand );
} // end discard_card

// <<<<<<<< compare_cards >>>>>>>>
void Player::compare_cards() {
  if( hand == newly_drawn_card ) {
    fprintf( log_file, "PLAYER %d: hand %d %d\n", id, hand, newly_drawn_card );
    fprintf( log_file, "PLAYER %d: wins\n", id );
    winner_found = true;
    won = true;
    pthread_cond_signal( &cond_winner_found ); 
  } else {
    if( rand() % 2 ) { discard_card( newly_drawn_card ); } 
    else {
      int temp = hand;
      hand = newly_drawn_card;
      discard_card( temp ); 
    }

    card_deck.print_deck();
  }
} // end compare_cards

// <<<<<<<< set_hand >>>>>>>>
void Player::set_hand( int card ) { hand = card; } // end set_hand

// <<<<<<<< get_hand >>>>>>>>
int Player::get_hand() { return hand; } // end get_hand

// <<<<<<<< get_newlyDrawnCard >>>>>>>>
int Player::get_newlyDrawnCard() { return newly_drawn_card; } // end get_newlyDrawnCard

// <<<<<<<< set_ID >>>>>>>>
void Player::set_ID( int ID ) { id = ID; } // end set_ID

// <<<<<<<< get_ID >>>>>>>>
int Player::get_ID() { return id; } // end get_ID

// <<<<<<<< won_game >>>>>>>>
bool Player::won_game() { return won; } // end won_game

// <<<<<<<< reset_hand >>>>>>>>
void Player::reset_hand() { hand = -1; } // end reset_hand