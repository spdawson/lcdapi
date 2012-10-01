#include "LCDMutex.h"

#include <pthread.h>

using namespace std;

LCDMutex::LCDMutex()
{
  ::pthread_mutex_init(&_mutex, 0);
  _owner = (::pthread_t)-1;
}

LCDMutex::~LCDMutex()
{
  ::pthread_mutex_destroy(&_mutex);
}

void LCDMutex::lock()
{
  if (_owner != ::pthread_self())
  {
    ::pthread_mutex_lock(&_mutex);
    _owner = ::pthread_self();
  }
}

void LCDMutex::unlock()
{
  _owner = (::pthread_t)-1;
  ::pthread_mutex_unlock(&_mutex);
}
