/*
 *
 *  File: WordCount.hpp
 *  Authors: Mikhail Strizhov
 *
 *  Date: Apr 5, 2016
 *
*/

#ifndef _WORDCOUNT_H
#define _WORDCOUNT_H

// System

// Shared
#include "site_defaults.hpp"

// Module
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "ThreadManager.hpp"

class WordCount
{
  public:
    WordCount(boost::shared_ptr<ThreadManager> p_oThreadManager);
    virtual ~WordCount();
		
    // Count words for a one path	
    void CountWords(const boost::filesystem::path& p_oPath);

    // Count words for multiple paths
    void CountWords(const std::list<fs::path>& p_lPaths);

    // Get results
    void GetTotals(std::multimap<int, std::string, wc_comparator>& p_mResults);
 
  private:
    void AddFileContents(const boost::filesystem::path& p_oPath);
    void WaitForCompletion();
    void Crawl(const boost::filesystem::path& p_oPath, bool p_bThreadEnabled);

    boost::mutex m_oWordCounterMutex;
    std::map<std::string, int> m_oFrequency;
    boost::thread_group	m_oWordCounterThreads;
    boost::shared_ptr<ThreadManager> m_oThreadManager;
};
#endif 
