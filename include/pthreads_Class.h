#include "globals.h"

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class pthreads_Class {
  
  public:
    pthreads_Class();

    virtual ~pthreads_Class();

    bool start_thread();

    void wait();

  protected:
    virtual void run() = 0;

  private:
    static void * run_helper(void * This);

    pthread_t thread;
};