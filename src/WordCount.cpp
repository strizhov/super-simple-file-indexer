/*
 *
 *  File: WordCount.cpp
 *  Authors: Mikhail Strizhov
 *
 *  Date: Apr 5, 2016
 *
*/

// System
#include <fstream>

// Shared

// Module
#include <boost/algorithm/string.hpp>   
#include <boost/make_shared.hpp>
#include "WordCount.hpp"

WordCount::WordCount(boost::shared_ptr<ThreadManager> p_oThreadManager)
: m_oThreadManager(p_oThreadManager)
{
}

WordCount::~WordCount()
{
}

// Count words based on multiple paths in input
void WordCount::CountWords(const std::list<fs::path>& p_lPaths)
{
  for (auto& path : p_lPaths)
    AddFileContents(path);
}

// Count words for a single path in input
void WordCount::CountWords(const boost::filesystem::path& p_oPath)
{
  AddFileContents(p_oPath);
}

// Generate results
void WordCount::GetTotals(std::multimap<int, std::string, wc_comparator>& p_mResults)
{
  if (p_mResults.empty() != 0)
	p_mResults.clear();

  // Wait for completion
  WaitForCompletion();

  // Lock	
  boost::mutex::scoped_lock lock(m_oWordCounterMutex);

  // Convert from string ordered map to a map sorted by count
  for (auto& item : m_oFrequency)
	  p_mResults.insert(std::make_pair(item.second, item.first));	  
}

// Add content from file
void WordCount::AddFileContents(const boost::filesystem::path& p_oPath)
{
  // Check for threads
  if (m_oThreadManager->CheckOut())
  {
    // Swawn a thread with function object that includes path and thread boolean
    m_oWordCounterThreads.create_thread(boost::bind(&WordCount::Crawl, this, p_oPath, true));
  }
  else 
  {
    Crawl(p_oPath, false);
  }
}

// Wait until threads are done
void WordCount::WaitForCompletion()
{
  m_oWordCounterThreads.join_all();
}

// Crawl the content of file, extract words and count frequency
void WordCount::Crawl(const boost::filesystem::path& p_oPath, bool p_bThreadEnabled)
{
  std::ifstream word_file;
  std::locale locality("C");

  // Open file
  word_file.open(p_oPath.string().c_str());
  if (word_file)
  {
    std::map<std::string, int> file_wc;
	std::string line;
 
    // Read each line
    while (std::getline(word_file, line))
    {
	  auto end=line.end();
	  auto itr=line.begin();
	  auto word_start=line.end();
	
      // Convert line to lower case
	  boost::algorithm::to_lower(line);

	  while (itr != end)
	  {
        if (*itr < 0 || (!std::isalnum(*itr, locality) && *itr != '_'))
		{
		  if (word_start != end)
		  {
		    ++file_wc[std::string(word_start, itr)];
		  }
		  word_start = end;
		}
		else if (word_start == end)
		{
		  word_start = itr;
		}
		++itr;
	  }
	  if (word_start != end)
	  {
	    ++file_wc[std::string(word_start, itr)];
	  }
    }

	// Close file
	word_file.close();
	
	// Now for each word frequency, update main stats
	boost::mutex::scoped_lock lock (m_oWordCounterMutex);
	for (auto& wc_freq : file_wc)
	  m_oFrequency[wc_freq.first] += wc_freq.second;
  }
  else
  {
    std::cerr << "Failed to read: " << p_oPath.string()  << std::endl;
  }
  
  if (p_bThreadEnabled)
  {
    m_oThreadManager->CheckIn();
  }
}


