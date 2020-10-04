#include "pthreads_class.h"

// <<<<<<<< constructor >>>>>>>>
pthreads_class::pthreads_class() {} // end constructor

// <<<<<<<< destructor >>>>>>>>
pthreads_class::~pthreads_class() {} // end destructor

// <<<<<<<< start_thread >>>>>>>>
bool pthreads_class::start_thread() {
  return (pthread_create(&thread, NULL, run_helper, this) == 0);
} // end start_thread

// <<<<<<<< wait >>>>>>>>
void pthreads_class::wait() {
  (void) pthread_join(thread, NULL);
} // end wait

// <<<<<<<< run_helper >>>>>>>>
void * pthreads_class::run_helper(void * This) {
  ((pthreads_class *)This)->run(); 
  return NULL;
} // end run_helper