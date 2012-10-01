#ifndef _LCD_MUTEX_H_
#define _LCD_MUTEX_H_

#include <pthread.h>

/** \class LCDMutex LCDMutex.h "api/LCDMutex.h"
 *  \brief A class implementing mutexes.
 *  \ingroup main
 *  This class is used to create some recursive mutexes.
 *   If a thread has already locked it, it won't be blocked by
 *   another lock.
 */
class LCDMutex
{
 private:
  ::pthread_mutex_t _mutex;
  ::pthread_t _owner;
 public:
  /**
   * \brief Default constructor.
   *
   * This constructor initializes the mutex.
  */
  LCDMutex();
  /**
   * \brief Destructor.
   *
   * This destructor destroys he mutex.
  */
  ~LCDMutex();
  /**
   * \brief Lock the mutex.
   *
   * This method is used to lock the mutex. It will have an effect
   *  only if it is not already locked by the same thread.
  */
  void lock();
  /**
   * \brief Unlock the mutex.
   *
   * This method will release the mutex so another thread can acquire it.
  */
  void unlock();

};

#endif
