#pragma once

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

#include "Deck.h"

using namespace std;

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

// <<<<<<<< SHUFFLECARDS >>>>>>>>
void Deck::shuffleCards() {
  for( int i = 0; i < size()-1; ++i ) {
    int randomIndex = rand() % size();
    int temp = tableCards[i];
    tableCards[i] = tableCards[randomIndex];
    tableCards[randomIndex] = temp;
  }
} // end shuffleCards

// <<<<<<<< PUSH >>>>>>>>
void Deck::push(int card) {
  tableCards[size()-1] = card;
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
int Deck::get(int index) {
  return tableCards[index];
} // end get

// <<<<<<<< SET >>>>>>>>
void Deck::set(int index, int card) {
  tableCards[index] = card;
} // end set

// <<<<<<<< SHOWDECK >>>>>>>>
void Deck::showDeck() {
  printf("DECK: ");
  fprintf(pFile, "DECK: ");   

  for( int i = 0; i < size(); ++i) {
    if( tableCards[i] == -1 ) {
      printf("\n");
      fprintf(pFile, "\n");
      break;
    } else {
      printf( "%d ", tableCards[i] );
      fprintf( pFile, "%d ", tableCards[i] );
    }
  }
} // end showDeck