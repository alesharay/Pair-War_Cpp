#include "Player.h"

using namespace std;

// <<<<<<<< Constructor >>>>>>>>
Player::Player(Deck &cards, int ID) : card_deck(cards), id(ID) { } // end constructor

// <<<<<<<< run >>>>>>>>
void Player::run() {

/*printf("\n\n\n");
  printf("PLAYER %d: hand %d\n", id, hand);
  printf("\n\n\n"); */

     while( !win ){
      int locked = pthread_mutex_lock(&mutex_deck_availability_to_player); // lock the deck

         while( id != turn && win == 0 ){ // make players wait for their turn
            pthread_cond_wait(&cond_deck_availability, &mutex_deck_availability_to_player); 
         }
         if( !win ){   
           if( turn == id ) {
             access_deck();
           }
         } 
      pthread_mutex_unlock(&mutex_deck_availability_to_player); // unlock the deck ...........
      // if( id > 3 ) id = 0; ++;        
   }
   // leave the player thread
   fprintf(pFile, "PLAYER %d: exits round\n", id); 
   
   pthread_exit(NULL);  
} // end run

// <<<<<<<< accessDeck >>>>>>>>
void Player::access_deck() {
  draw_card();
  printf("----PLAYER %d:\nHAND %d %d\n", id, hand, newlyDrawnCard);
  compare_cards();

  turn++; // inc turn so next player may use the deck
  if( turn > NUM_THREADS ) {
    turn = 1;      // if player3 went, move to player1
  }
   
  pthread_cond_broadcast(&cond_deck_availability); // broadcast that deck is available
} // accessDeck

// <<<<<<<< drawCard >>>>>>>>
void Player::draw_card() {
  fprintf(pFile, "PLAYER %d: hand %d \n", id, hand); 
  newlyDrawnCard = card_deck.pop();
  fprintf(pFile, "PLAYER %d: draws %d \n", id, newlyDrawnCard); 
} // end drawCard

// <<<<<<<< discardCard >>>>>>>>
void Player::discard_card( int card ) {
  card_deck.push(card);
  fprintf(pFile, "PLAYER %d: discards %d \n", id, card);   
} // end discardCard

// <<<<<<<< compareCards >>>>>>>>
void Player::compare_cards( ) {
  if( hand == newlyDrawnCard ) {
    printf("WIN yes\n");      
    fprintf(pFile, "PLAYER %d: wins\n", id);
    win = true;
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
    card_deck.showDeck();
  }
} // end compareCards

// <<<<<<<< setHand >>>>>>>>
void Player::set_hand(int card) { hand = card; } // end setHand

// <<<<<<<< resetHand >>>>>>>>
int Player::get_hand() { return hand; } // end getHand

// <<<<<<<< resetHand >>>>>>>>
void Player::set_ID(int ID) { id = ID; } // end setID

// <<<<<<<< resetHand >>>>>>>>
int Player::get_ID() { return id; } // end getID

// <<<<<<<< resetHand >>>>>>>>
void Player::reset_hand() {
  hand = -1;
} // end resetHand