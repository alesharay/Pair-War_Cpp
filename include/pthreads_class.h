#include "globals.h"

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class pthreads_class {
  
  public:
    pthreads_class();
    virtual ~pthreads_class();
    bool start_thread();
    void wait();

  protected:
    virtual void run() = 0;

  private:
    static void * run_helper(void * This);
    pthread_t thread;
    
};