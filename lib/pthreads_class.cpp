#include "pthreads_class.h"

pthreads_class::pthreads_class() {}

pthreads_class::~pthreads_class() {}

bool pthreads_class::start_thread() {
  return (pthread_create(&thread, NULL, run_helper, this) == 0);
}

void pthreads_class::wait() {
  (void) pthread_join(thread, NULL);
}

void * pthreads_class::run_helper(void * This) {
  ((pthreads_class *)This)->run(); 
  return NULL;
}