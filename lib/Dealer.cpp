#include "Dealer.h"

using namespace std;

Dealer::Dealer(Deck &cards, Player &player_1, Player &player_2, Player &player_3) : card_deck(cards), player1(player_1), player2(player_2), player3(player_3) {}

void Dealer::shuffleCards() {
  int size = card_deck.size();
  for( int i = 0; i < size-1; ++i ) {
    int randomIndex = rand() % size;
    int temp = card_deck.get( i ); 
    card_deck.set( i, card_deck.get(randomIndex) );
    card_deck.set( randomIndex, temp );
  }

  fprintf(pFile, "DEALER: shuffle\n"); // shuffle the deck
  card_deck.showDeck();
}

void Dealer::dealCards() {
  player1.setHand( card_deck.pop() );
  player2.setHand( card_deck.pop() );
  player3.setHand( card_deck.pop() ); 

  fprintf(pFile, "DEALER: deal\n");      // deal the cards
}

void Dealer::accessDeck() {
  shuffleCards();
  dealCards();

  pthread_cond_broadcast(&condition_var); // broadcast that deck is available
}

void Dealer::run() {
   pId = 0;       // identify the dealer as player 0
   
   accessDeck();

   // leave the dealer thread
   pthread_mutex_lock(&mutex_dealerExit);  // lock the exit ............
      while( !win ) {
         pthread_cond_wait(&cond_win1, &mutex_dealerExit);
      }      
   pthread_mutex_unlock(&mutex_dealerExit); // unlock the exit .........
   
   fprintf(pFile, "DEALER: exits round\n");  

   pthread_exit(NULL);  
}