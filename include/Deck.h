#include "globals.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

class Deck {

  public:
    Deck();
    void load_deck();
    int size();
    void push( int card );
    int pop();
    int get( int i );
    void set( int i, int card );
    void display_deck();
    void print_deck();

  private:
    int tableCards[ NUMBER_OF_CARDS ];
    
};