#pragma once

#include "globals.h"

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

using namespace std;

class Deck {

  public:
    void loadDeck();

    void shuffleCards();

    int size();

    void push(int card);

    int pop();

    int get(int index);

    void set(int index, int card); 

    void showDeck();

  private:

    int tableCards[52];

};