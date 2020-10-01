#include "Player.h"

using namespace std;

Player::Player() {}

Player::Player(Deck &cards, string name) {
  this->cards = cards;
  this->name = name;
}

void* Player::run(void *playerId) {

    pId = (long)playerId;
    Player currentPlayer(cards, "");

    if( roundNum == 1) {

    } else if( roundNum == 2) {

    } else if( roundNum == 3 ) {

    } 

     while( win == 0 ){
      pthread_mutex_lock(&mutex_useDeck); // lock the deck ...............  
         while( pId != turn && win == 0 ){ // make players wait for their turn
            pthread_cond_wait(&condition_var, &mutex_useDeck); 
         }
         if( win == 0 ){   
            // useTheDeck(pId, thisHand); // let players use the deck
            accessDeck();
         }         
      pthread_mutex_unlock(&mutex_useDeck); // unlock the deck ...........
   }
   // leave the player thread
   fprintf(pFile, "PLAYER %ld: exits round\n", pId); 

   pthread_exit(NULL);  
}

void Player::setHand(int card) {
  hand = card;
  printf("PLAYER %d:\nHAND %d\n", pId, hand);
  fprintf(pFile, "PLAYER %ld: hand %d\n", pId, hand);
}

void Player::accessDeck() {
  drawCard();
  displayHand();
  printHandToFile();
  compareCards();
}

void Player::displayHand() {
  printf("PLAYER %ld:\nHAND %d %d\n", pId, hand, newlyDrawnCard);
}

void Player::printHandToFile() {
  fprintf(pFile, "PLAYER %ld: hand %d %d\n", pId, hand, newlyDrawnCard);
}

void Player::drawCard() {
  newlyDrawnCard = cards.pop();
  fprintf(pFile, "PLAYER %ld: draws %d \n", pId, newlyDrawnCard); 
}

void Player::discard(int card) {
  cards.push(card);
  fprintf(pFile, "PLAYER %ld: discards %d \n", pId, card);   
}

void Player::compareCards() {
  if( hand == newlyDrawnCard ) {
    printf("WIN yes\n");      
    fprintf(pFile, "PLAYER %ld: wins\n", pId);
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
    cards.showDeck();
  }
}