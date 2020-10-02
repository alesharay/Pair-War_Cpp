#include "Dealer.h"

using namespace std;

Dealer::Dealer(){}

Dealer::Dealer(Player &player1, Player &player2, Player &player3) {
  this->player1 = player1;
  this->player1 = player2;
  this->player1 = player3;
}

void Dealer::dealCards(Deck &cards) {
  player1.setHand( cards.pop() );
  player2.setHand( cards.pop() );
  player3.setHand( cards.pop() ); 
}

void Dealer::shuffleCards(Deck &cards) {
        
    int size = cards.size();
    for( int i = 0; i < size-1; ++i ) {
      int randomIndex = rand() % size;
      int temp = cards.get( i ); 
      cards.set( i, cards.get(randomIndex) );
      cards.set( randomIndex, temp );
  }
}

void Player::accessDeck(Deck &cards) {
  shuffleCards(cards);
  deal(cards);
}

void* Dealer::run(void *arg, Deck &cards) {
   pId = 0;       // identify the dealer as player 0
   turn = 0;           // set/reset turn val to indicate it's the dealer's turn 
   hand dealerHand;    // dealer gets a NULL hand
   useTheDeck(pId, dealerHand); // let the dealer use the deck
   
   accessDeck(cards);

   // leave the dealer thread
   pthread_mutex_lock(&mutex_dealerExit);  // lock the exit ............
      while( !win ){
         pthread_cond_wait(&cond_win1, &mutex_dealerExit);
      }      
   pthread_mutex_unlock(&mutex_dealerExit); // unlock the exit .........
   fprintf(pFile, "DEALER: exits round\n");  

   pthread_exit(NULL);  
}