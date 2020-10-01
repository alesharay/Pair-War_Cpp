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