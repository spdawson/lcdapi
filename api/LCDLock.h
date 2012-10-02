#ifndef _LCD_LOCK_H_
#define _LCD_LOCK_H_

#include "LCDMutex.h"

#include <pthread.h>

/** \class LCDLock LCDLock.h "api/LCDLock.h"
 *  \brief A class to lock mutexes.
 *  \ingroup main
 *  This class is used to lock some mutexes and be sure that they will
 *   be unlocked, even if an exception occurs.
 */
class LCDLock
{
 private:
  LCDMutex *_lcdMutex;
  ::pthread_mutex_t *_posixMutex;
  bool _useLCD;

 public:    
  /**
   * \brief Constructor locking an LCD mutex.
   *
   * This constructor locks the LCD mutex and stores it.
  */
  LCDLock(LCDMutex *mutex)
  {
    _lcdMutex = mutex;
    ::pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, 0);
    _lcdMutex->lock();
    _useLCD = true;
  }
  /**
   * \brief Constructor locking a Posix mutex.
   *
   * This constructor locks the Posix mutex and stores it.
  */
  LCDLock(::pthread_mutex_t *mutex)
  {
    _posixMutex = mutex;
    ::pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, 0);
    ::pthread_mutex_lock(_posixMutex);
    _useLCD = false;
  }

  /**
   * \brief Destructor unlocking the mutex.
   *
   * This destructor unlocks the mutex.
  */
  ~LCDLock()
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
};

#endif
