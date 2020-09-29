#pragma once

#include "catch.hpp"
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Player {

  private:
    string nane;
    int hand;
    int newlyDrawnCard;
    bool isWinner;
    bool started;
    bool exit;

  public: 
    bool hasStarted();

    void setStartedRound(bool started);

    string setHand(int card);

    string drawCard();

    string discardCard();

    string compareCards();

    string roundOver();

    bool hasExited();

    void screenDisplay();

    void resetHand();

    // replace with whatever the c++ version should be
    void run();
};