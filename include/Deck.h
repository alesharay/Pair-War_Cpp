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

    Deck();

    void loadDeck();

    void shuffleCards();

    int size();

    void push(int card);

    int pop();

    int get(int i);

    void set(int i, int card);

    void showDeck();

  private:

    int tableCards[52];

};