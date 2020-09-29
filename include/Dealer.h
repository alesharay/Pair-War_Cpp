#pragma once

#include "catch.hpp"
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Dealer {

  private:

  public:
    bool doneDealing;

    void shuffleCards();

    void dealCards();

    // replace with whatever the c++ version should be
    void run();
};