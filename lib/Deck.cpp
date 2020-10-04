#include "Deck.h"

using namespace std;
Deck::Deck() {
  load_deck();
}

// <<<<<<<< load_deck >>>>>>>>
void Deck::load_deck() {
  for(int i = 0; i < 4; ++i) {
    for (int j = 0; j < 13; ++j) {
      tableCards[(i*13)+j] = j+1;
    }
  }
} // load_deck

// <<<<<<<< size >>>>>>>>
int Deck::size() {
  return sizeof(tableCards)/sizeof(tableCards[0]);
} // end size

// <<<<<<<< push >>>>>>>>
void Deck::push( int card ) {
  for( int i = 0, deck_size; size(); ++i ) {
    if( tableCards[i] == -1 ) { 
      tableCards[i] = card;
      break;
    }
  }
} // end push

// <<<<<<<< pop >>>>>>>>
int Deck::pop() {
  int card = tableCards[0];

  for( int i = 0; i < size()-1; ++i ) {
    tableCards[i] = tableCards[i+1];
  }
  tableCards[size()-1] = -1;

  return card;
} // end pop

// <<<<<<<< get >>>>>>>>
int Deck::get( int index ) {
  return tableCards[index];
} // end get

// <<<<<<<< set >>>>>>>>
void Deck::set( int index, int card ) {
  tableCards[index] = card;
} // end set

// <<<<<<<< show_deck >>>>>>>>
void Deck::show_deck() {
  printf("DECK: ");
  fprintf(log_file, "DECK: ");   

  bool emptySlotFound = false; 
  for( int i = 0, deck_size = size(); i < deck_size; ++i) {
    if( tableCards[i] == -1 || i >= deck_size) {
      emptySlotFound = true;
      printf("\n");
      fprintf(log_file, "\n");
      break;
    } else {
      printf( "%d ", tableCards[i] );
      fprintf( log_file, "%d ", tableCards[i] );
    }
  }

  if( !emptySlotFound ) { 
    printf("\n");
    fprintf(log_file, "\n");
  } // end show_deck
}