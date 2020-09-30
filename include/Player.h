#pragma once

#include "catch.hpp"
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Player {

  private:
    string name = "";
    int hand = 0;
    int newlyDrawnCard = 0;
    bool isWinner = false;
    bool started = false;
    bool exit = false;

  public: 
    void setName(string name);

    string getName();

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