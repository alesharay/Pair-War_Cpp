#include "Dealer.h"

using namespace std;

Dealer::Dealer(Deck &cards, Player &player_1, Player &player_2, Player &player_3) : card_deck(cards), player1(player_1), player2(player_2), player3(player_3) {}

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

void Dealer::accessDeck() {
  shuffleCards();
  dealCards();

  pthread_cond_broadcast(&condition_var); // inform that deck is available
}

void Dealer::shuffleCards() {
  fprintf(pFile, "DEALER: shuffle\n"); // shuffle the deck

  // int size = card_deck.size();
  for( int i = 0; i < NUM_CARDS; ++i ) {
    int randomIndex = rand() % NUM_CARDS;
    int temp = card_deck.get( i ); 
    card_deck.set( i, card_deck.get(randomIndex) );
    card_deck.set( randomIndex, temp );
  }

  card_deck.showDeck();
}

void Dealer::dealCards() {
  fprintf(pFile, "DEALER: deal\n");      // deal the cards
  printf("DEALER: deal\n");      // deal the cards

  if( turn == 1) { 
    player1.setHand( card_deck.pop() );
    printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player1.getID(), player1.getHand());
    printf("\n\n\n");

    player2.setHand( card_deck.pop() );
     printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player2.getID(), player2.getHand());
    printf("\n\n\n");

    player3.setHand( card_deck.pop() ); 
    printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player3.getID(), player3.getHand());
    printf("\n\n\n");

  } else if( turn == 2 ) {
    player2.setHand( card_deck.pop() );
    printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player2.getID(), player2.getHand());
    printf("\n\n\n");

    player3.setHand( card_deck.pop() ); 
    printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player3.getID(), player3.getHand());
    printf("\n\n\n");

    player1.setHand( card_deck.pop() );
    printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player1.getID(), player1.getHand());
    printf("\n\n\n");

  } else {
    player3.setHand( card_deck.pop() ); 
    printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player3.getID(), player3.getHand());
    printf("\n\n\n"); 

    player1.setHand( card_deck.pop() );
    printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player1.getID(), player1.getHand());
    printf("\n\n\n");
    
    player2.setHand( card_deck.pop() );
    printf("\n\n\n");
    printf("DEAL CARDS --- PLAYER %d: hand %d\n", player2.getID(), player2.getHand());
    printf("\n\n\n");
  }

}