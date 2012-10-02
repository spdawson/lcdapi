#include "LCDLock.h"

#include "LCDMutex.h"

namespace lcdapi {

LCDLock::LCDLock(LCDMutex *mutex)
  : _lcdMutex(mutex), _posixMutex(NULL), _useLCD(true)
{
  ::pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, 0);
  _lcdMutex->lock();
}

LCDLock::LCDLock(::pthread_mutex_t *mutex)
  : _lcdMutex(NULL), _posixMutex(mutex), _useLCD(false)
{
  ::pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, 0);
  ::pthread_mutex_lock(_posixMutex);
}

LCDLock::~LCDLock()
{
  if (_useLCD)
  {
    _lcdMutex->unlock();
  }
  else
  {
    ::pthread_mutex_unlock(_posixMutex);
  }
  ::pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0);
}

} // end of lcdapi namespace
