#include "pthreads_Class.h"

pthreads_Class::pthreads_Class() {}

pthreads_Class::~pthreads_Class() {}

bool pthreads_Class::start_thread() {
  return (pthread_create(&_thread, NULL, run_helper, this) == 0);
}

void pthreads_Class::wait() {
  (void) pthread_join(_thread, NULL);
}

void * pthreads_Class::run_helper(void * This) {
  ((pthreads_Class *)This)->run(); 
  return NULL;
}