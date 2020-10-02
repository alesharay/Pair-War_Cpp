#pragma once

#include "globals.h"
#include "Deck.h"
#include "pthreads_Class.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         // for writing to the log 
#include <iostream>



using namespace std;

class Player : public pthreads_Class {
  public:
    Player();

    Player(string name);

    void setHand(int card); 

    void accessDeck(Deck &cards);

    void displayHand();

    void printHandToFile();

    void drawCard(Deck &cards);

    void discard(Deck &cards, int card);

    void compareCards(Deck &cards);

    void run();

  private:
    string name;
    int hand = -1;
    int newlyDrawnCard = -1;
    bool started = false; 
};