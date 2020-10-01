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

    void showDeck();

  private:

    int tableCards[52];

};