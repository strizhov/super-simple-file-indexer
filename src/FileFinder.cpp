/*
 *
 *  File: FileFinder.cpp
 *  Authors: Mikhail Strizhov
 *
 *  Date: Apr 5, 2016
 *
*/

// System
#include <iostream>

// Shared

// Module
#include <boost/thread.hpp>
#include "FileFinder.hpp"
#include "ThreadManager.hpp"

FileFinder::FileFinder(boost::shared_ptr<ThreadManager> p_oThreadManager)
: m_oThreadManager(p_oThreadManager)
{
}

FileFinder::~FileFinder()
{ 
}
	
void FileFinder::Find(fs::path p_oDir, std::list<fs::path> & p_lSubPaths, std::string p_sExt)
{
  m_sExt = p_sExt;
  LocateFiles(p_oDir, p_lSubPaths, false);
}

void FileFinder::LocateFiles(fs::path p_oDir, std::list<fs::path>& p_lSubPaths, bool p_bThreadEnabled)
{
  // Create list of child paths
  std::list<std::list<fs::path>> child_paths;

  if (fs::exists(p_oDir) && fs::is_directory(p_oDir))
  {
    // Do scan with thread group
    boost::thread_group threads;
    fs::directory_iterator end_iter;
    for (fs::directory_iterator dir_iter(p_oDir); dir_iter != end_iter; ++dir_iter)
    {
      if (fs::is_regular_file(dir_iter->status()) )
  	{
  	  if (ExtMatch(dir_iter->path()))
  	    p_lSubPaths.push_back(dir_iter->path());
  	} 
  	else if (fs::is_directory(dir_iter->status()))
  	{
  	  std::list<fs::path> child;
  	  child_paths.push_back(child);
        
  	  // Check threads
  	  if (m_oThreadManager->CheckOut())
  	    threads.create_thread(boost::bind(&FileFinder::LocateFiles, this, dir_iter->path(), boost::ref(child_paths.back()), true));
  	  else
  	    LocateFiles(dir_iter->path(), boost::ref(child_paths.back()), false);
      }
  	else
  	{
  	  std::cerr << "Skipping: " << dir_iter->path() << std::endl;
  	}
    }
    
    // Wait for all threads
    threads.join_all();
    
    // Merge whats left
    if (child_paths.size())
    {
  	for (auto& path : child_paths)
  	  p_lSubPaths.merge(path);
    }
  }
  
  if (p_bThreadEnabled)
    m_oThreadManager->CheckIn();
}

bool FileFinder::ExtMatch(const fs::path p_oTest)
{
  if (m_sExt == "*")
    return(true);
  else if (m_sExt == p_oTest.extension())
    return(true);
  else
    return(false);
}
