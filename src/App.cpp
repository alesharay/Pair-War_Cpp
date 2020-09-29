#include <iostream>
#include <vector>
#include "Dealer.h"
#include "Player.h"
#include "Deck.h"

using namespace std;

class App {
  public:
    static Dealer dealer;

    void sayHello() {
      cout << "Hello, World!" << endl;
    }
};

int main() {
  App app;

  app.sayHello();

  return 0;
}