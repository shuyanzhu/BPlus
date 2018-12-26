//
// Created by eureka on 18-12-25.
//

#ifndef BPLUS_MTBPT_H
#define BPLUS_MTBPT_H

#include <pthread.h>
#include "BPT.h"

template <typename T>
class MTBPT : public BPT<T>
{
  private:
    pthread_rwlock_t rwlock;

  public:
    MTBPT(int order = 3)
        : BPT<T>(order)
    {
        // rwlock = new pthread_rwlock_t;
        pthread_rwlock_init(&rwlock, NULL);
    }
    ~MTBPT()
    {
        pthread_rwlock_destroy(&rwlock);
        // delete rwlock;
    }
    BPTNode<T> *search(const T &e)
    {
        pthread_rwlock_wrlock(&rwlock);
        BPTNode<T> *ret = BPT<T>::search(e);
        pthread_rwlock_unlock(&rwlock);
        return ret;
    }
    bool insert(const T &e)
    {
        pthread_rwlock_wrlock(&rwlock);
        bool ret = BPT<T>::insert(e);
        pthread_rwlock_unlock(&rwlock);
        return ret;
    }
    bool remove(const T &e)
    {
        pthread_rwlock_wrlock(&rwlock);
        bool ret = BPT<T>::remove(e);
        pthread_rwlock_unlock(&rwlock);
        return ret;
    }
};
#endif // BPLUS_MTBPT_H
