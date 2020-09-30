#include <iostream>
#include <vector>
#include "Dealer.h"
#include "Player.h"
#include "Deck.h"

using namespace std;

int main(int argc, char *argv[]) {
  int seed = atoi(argv[1]);
  srand(seed); 
  // using $(($(date +%s%N)/1000000)) as the seed allows for the time in milliseconds to be the call that way it is always different

  cout << endl << "Random value: " << (rand() % 18)+1 << endl << endl;

  return 0;
}