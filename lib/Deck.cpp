#include "Deck.h"

using namespace std;
Deck::Deck() {
  loadDeck();
}

// <<<<<<<< LOADDECK >>>>>>>>
void Deck::loadDeck() {
  for(int i = 0; i < 4; ++i) {
    for (int j = 0; j < 13; ++j) {
      tableCards[(i*13)+j] = j+1;
    }
  }
} // loadDeck

// <<<<<<<< SIZE >>>>>>>>
int Deck::size() {
  return sizeof(tableCards)/sizeof(tableCards[0]);
} // end size

// <<<<<<<< PUSH >>>>>>>>
void Deck::push( int card ) {
  for( int i = 0, deck_size; size(); ++i ) {
    if( tableCards[i] == -1 ) { 
      tableCards[i] = card;
      break;
    }
  }
} // end push

// <<<<<<<< POP >>>>>>>>
int Deck::pop() {
  int card = tableCards[0];

  for( int i = 0; i < size()-1; ++i ) {
    tableCards[i] = tableCards[i+1];
  }
  tableCards[size()-1] = -1;

  return card;
} // end pop

// <<<<<<<< GET >>>>>>>>
int Deck::get( int index ) {
  return tableCards[index];
} // end get

// <<<<<<<< SET >>>>>>>>
void Deck::set( int index, int card ) {
  tableCards[index] = card;
} // end set

// <<<<<<<< SHOWDECK >>>>>>>>
void Deck::showDeck() {
  printf("DECK: ");
  fprintf(pFile, "DECK: ");   

  bool emptySlotFound = false; 
  for( int i = 0, deck_size = size(); i < deck_size; ++i) {
    if( tableCards[i] == -1 || i >= deck_size) {
      emptySlotFound = true;
      printf("\n");
      fprintf(pFile, "\n");
      break;
    } else {
      printf( "%d ", tableCards[i] );
      fprintf( pFile, "%d ", tableCards[i] );
    }
  }

  if( !emptySlotFound ) { 
    printf("\n");
    fprintf(pFile, "\n");
  } // end showDeck
}