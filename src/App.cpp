#include <iostream>
#include <vector>
#include "Dealer.h"
#include "Player.h"
#include "Deck.h"

using namespace std;

Dealer dealer;
Deck cards;
Player player1;
Player player2;
Player player3;
bool winnerFound = false;
int seed = 0;
vector<Player> players;

int getRandom();


int main(int argc, char *argv[]) {
  seed = atoi(argv[1]);
   
  // using $(($(date +%s%N)/1000000)) as the seed allows for the time in milliseconds to be the call that way it is always different

  player1.setName("PLAYER 1");
  player1.setName("PLAYER 2");
  player1.setName("PLAYER 3");

  players.push_back(player1);
  players.push_back(player2);
  players.push_back(player3);

  cout << endl << "Random value: " << getRandom() << endl << endl;

  return 0;
}

int getRandom() {
  srand(seed);
  return (rand() % 18) + 1;
}