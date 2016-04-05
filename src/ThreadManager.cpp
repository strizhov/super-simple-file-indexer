/*
 *
 *  File: ThreadManager.cpp
 *  Authors: Mikhail Strizhov
 *
 *  Date: Apr 5, 2016
 *
*/

// System

// Shared
#include "site_defaults.hpp"

// Module
#include <boost/thread.hpp>
#include "ThreadManager.hpp"

ThreadManager::ThreadManager()
: m_szMaxThreads(MAX_THREADS),
  m_szActiveThreads(0)
{}

ThreadManager::~ThreadManager()
{}

size_t ThreadManager::GetActive()
{
  boost::mutex::scoped_lock lock(m_oThreadManagerLock);
  return m_szActiveThreads;
}

size_t ThreadManager::CheckIn()
{
  boost::mutex::scoped_lock lock(m_oThreadManagerLock);
  m_szActiveThreads--;
  return m_szActiveThreads;
}

size_t ThreadManager::CheckOut()
{
  boost::mutex::scoped_lock lock(m_oThreadManagerLock);
  if (m_szActiveThreads < m_szMaxThreads)
  {
    m_szActiveThreads++;
	return m_szActiveThreads;
  }
  else
    return 0;
}

void ThreadManager::SetMaxThreads(size_t p_szMaxThreads)
{
  m_szMaxThreads = p_szMaxThreads;
}

size_t ThreadManager::GetMaxThreads()
{
  return m_szMaxThreads;
}
