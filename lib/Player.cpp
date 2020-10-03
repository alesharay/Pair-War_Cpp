#include "Player.h"

using namespace std;

Player::Player(Deck &cards, int ID) : card_deck(cards), id(ID) { }

void Player::setHand(int card) {
  hand = card;
  printf("----PLAYER %d:\nHAND %d\n", id, hand);
  fprintf(pFile, "PLAYER %d: hand %d\n", id, hand);

}

void Player::accessDeck() {
  drawCard();
  displayHand();
  printHandToFile();
  compareCards();

  turn++; // inc turn so next player may use the deck
  if( turn > NUM_THREADS ) {
    turn = 1;      // if player3 went, move to player1
  }
   
  pthread_cond_broadcast(&condition_var); // broadcast that deck is available
}

void Player::displayHand() {
  printf("----PLAYER %d:\nHAND %d %d\n", id, hand, newlyDrawnCard);
}

void Player::printHandToFile() {
  fprintf(pFile, "PLAYER %d: hand %d %d\n", id, hand, newlyDrawnCard);
}

void Player::drawCard() {
  newlyDrawnCard = card_deck.pop();
  fprintf(pFile, "PLAYER %d: draws %d \n", id, newlyDrawnCard); 
}

void Player::discard( int card ) {
  card_deck.push(card);
  fprintf(pFile, "PLAYER %d: discards %d \n", id, card);   
}

void Player::compareCards( ) {
  if( hand == newlyDrawnCard ) {
    printf("WIN yes\n");      
    fprintf(pFile, "PLAYER %d: wins\n", id);
    win = true;
    pthread_cond_signal(&cond_win1); // signal dealer to exit           
  } else {
    printf("Win no\n");
    if( rand() % 2 ) {
      discard( newlyDrawnCard );  
    } else {
      int temp = hand;
      hand = newlyDrawnCard;
      discard( temp ); 
    }
    card_deck.showDeck();
  }
}

void Player::resetHand() {
  hand = -1;
}

void Player::run() {

     while( win == 0 ){
      int locked = pthread_mutex_lock(&mutex_useDeck); // lock the deck ...............  

        //  while( id != turn && win == 0 ){ // make players wait for their turn
         while( id != turn && win == 0 ){ // make players wait for their turn
            pthread_cond_wait(&condition_var, &mutex_useDeck); 
         }
         if( win == 0 ){   
           if(turn == id ) {
             pId = id;
             accessDeck();
           }
         } 
      pthread_mutex_unlock(&mutex_useDeck); // unlock the deck ...........
      // if( id > 3 ) id = 0; ++;        
   }
   // leave the player thread
   fprintf(pFile, "PLAYER %d: exits round\n", id); 
   
   pthread_exit(NULL);  
}