/*
 *
 *  File: ThreadManager.hpp
 *  Authors: Mikhail Strizhov
 *
 *  Date: Apr 5, 2016
 *
*/

#ifndef _THREADMANAGER_H
#define _THREADMANAGER_H

// System

// Shared

// Module

class ThreadManager
{
  public:
    ThreadManager();
    virtual ~ThreadManager();

    size_t GetActive();
    size_t CheckIn();
    size_t CheckOut();

    void   SetMaxThreads(size_t p_szMaxThreads);
    size_t GetMaxThreads();

  private:
    size_t m_szMaxThreads;
    size_t m_szActiveThreads;
    boost::mutex  m_oThreadManagerLock;
};
#endif 

