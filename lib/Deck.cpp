#include "Deck.h"

using namespace std;

// <<<<<<<< constrcutor >>>>>>>>
Deck::Deck() { load_deck(); } // end constructor

// <<<<<<<< load_deck >>>>>>>>
void Deck::load_deck() {
  for( int i = 0; i < 4; ++i ) {
    for ( int j = 0; j < 13; ++j ) {
      tableCards[ (i*13)+j ] = j+1;
    }
  }
} // load_deck

// <<<<<<<< size >>>>>>>>
int Deck::size() { return NUMBER_OF_CARDS; } // end size

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

  for( int i = 0; i < (NUMBER_OF_CARDS-1); ++i ) { tableCards[i] = tableCards[i+1]; }
  tableCards[ (NUMBER_OF_CARDS-1) ] = -1;
  return card;
} // end pop

// <<<<<<<< get >>>>>>>>
int Deck::get( int index ) { return tableCards[index]; } // end get

// <<<<<<<< set >>>>>>>>
void Deck::set( int index, int card ) { tableCards[index] = card; } // end set

// <<<<<<<< display_deck >>>>>>>>
void Deck::display_deck() {
  printf( "DECK: " );
  bool emptySlotFound = false; 
  for( int i = 0; i < NUMBER_OF_CARDS; i++ ) {
    if( tableCards[i] == -1 || i >= NUMBER_OF_CARDS ) {
      emptySlotFound = true;
      printf( "\n" );
      break;
    } else { printf( "%d ", tableCards[i] ); }
  }

  if( !emptySlotFound ) { printf( "\n" ); }
} // end display_deck

// <<<<<<<< print_deck >>>>>>>>
void Deck::print_deck() {
  fprintf( log_file, "DECK: " );

  bool emptySlotFound = false;
  for( int i = 0; i < NUMBER_OF_CARDS; i++ ) {
    if( tableCards[i] == -1 || i >= NUMBER_OF_CARDS ) {
      emptySlotFound = true;
      fprintf( log_file, "\n" );
      break;
    } else { fprintf( log_file, "%d ", tableCards[i] ); }
  }

  if( !emptySlotFound ) { fprintf(log_file, "\n"); } 
}// end print_deck