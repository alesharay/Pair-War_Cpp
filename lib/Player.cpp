#include "Player.h"

using namespace std;

// <<<<<<<< Constructor >>>>>>>>
Player::Player(Deck &cards, int ID) : card_deck(cards), id(ID) { } // end constructor

// <<<<<<<< run >>>>>>>>
void Player::run() {

/*printf("\n\n\n");
  printf("PLAYER %d: hand %d\n", id, hand);
  printf("\n\n\n"); */

     while( !winner_found ){
      int locked = pthread_mutex_lock(&mutex_deck_availability_to_player); // lock the deck

         while( id != which_player && winner_found == 0 ){ // make players wait for their turn
            pthread_cond_wait(&cond_deck_availability, &mutex_deck_availability_to_player); 
         }
         if( !winner_found ){   
           if( which_player == id ) {
             access_deck();
           }
         } 
      pthread_mutex_unlock(&mutex_deck_availability_to_player); // unlock the deck ...........
      // if( id > 3 ) id = 0; ++;        
   }
   // leave the player thread
   fprintf(log_file, "PLAYER %d: exits round\n", id); 
   
   pthread_exit(NULL);  
} // end run

// <<<<<<<< access_deck >>>>>>>>
void Player::access_deck() {
  draw_card();
  printf("----PLAYER %d:\nHAND %d %d\n", id, hand, newlyDrawnCard);
  compare_cards();

  which_player++; // inc turn so next player may use the deck
  if( which_player > NUMBER_OF_THREADS ) {
    which_player = 1;      // if player3 went, move to player1
  }
   
  pthread_cond_broadcast(&cond_deck_availability); // broadcast that deck is available
} // access_deck

// <<<<<<<< draw_card >>>>>>>>
void Player::draw_card() {
  fprintf(log_file, "PLAYER %d: hand %d \n", id, hand); 
  newlyDrawnCard = card_deck.pop();
  fprintf(log_file, "PLAYER %d: draws %d \n", id, newlyDrawnCard); 
} // end draw_card

// <<<<<<<< discard_card >>>>>>>>
void Player::discard_card( int card ) {
  card_deck.push(card);
  fprintf(log_file, "PLAYER %d: discards %d \n", id, card);   
} // end discard_card

// <<<<<<<< compare_cards >>>>>>>>
void Player::compare_cards( ) {
  if( hand == newlyDrawnCard ) {
    printf("WIN yes\n");      
    fprintf(log_file, "PLAYER %d: wins\n", id);
    winner_found = true;
    pthread_cond_signal(&cond_winner_found); // signal dealer to exit           
  } else {
    printf("Win no\n");
    if( rand() % 2 ) {
      discard_card( newlyDrawnCard );  
    } else {
      int temp = hand;
      hand = newlyDrawnCard;
      discard_card( temp ); 
    }
    card_deck.show_deck();
  }
} // end compare_cards

// <<<<<<<< set_hand >>>>>>>>
void Player::set_hand(int card) { hand = card; } // end set_hand

// <<<<<<<< get_hand >>>>>>>>
int Player::get_hand() { return hand; } // end get_hand

// <<<<<<<< set_ID >>>>>>>>
void Player::set_ID(int ID) { id = ID; } // end set_ID

// <<<<<<<< get_ID >>>>>>>>
int Player::get_ID() { return id; } // end get_ID

// <<<<<<<< reset_hand >>>>>>>>
void Player::reset_hand() {
  hand = -1;
} // end reset_hand