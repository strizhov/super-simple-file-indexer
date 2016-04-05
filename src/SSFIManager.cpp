/*
 *
 *  File: SSFIManager.cpp
 *  Authors: Mikhail Strizhov
 *
 *  Date: Apr 5, 2016
 *
*/

// System

// Shared
#include "site_defaults.hpp"

// Module
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "WordCount.hpp"
#include "FileFinder.hpp"
#include "ThreadManager.hpp"
#include "SSFIManager.hpp"

class SSFIManager::Impl
{
  public:
    Impl(boost::shared_ptr<ThreadManager> p_oThreadManager)
	: m_sExt(".txt"), 
	  m_sPath("."), 
	  m_oWordCounter(p_oThreadManager), 
	  m_oFileFinder(p_oThreadManager), 
	  m_pThreadManager(p_oThreadManager)
    { }

    virtual ~Impl()
    { }

    void SetFileExtension(const std::string& p_sExt)
    {
      m_sExt = p_sExt;
    }
		
    void SetRootPath(const std::string& p_sPath)
    {
      m_sPath = p_sPath;
    }
		
    void SetMaxThreads(const size_t& p_iMaxThread) 
    {
      m_pThreadManager->SetMaxThreads(p_iMaxThread);
    }
		
    const std::string& GetFileExtension()
    { 
      return m_sExt;
    }
		
    const std::string GetRootPath() 
    {
      return fs::canonical(m_sPath).string();
    }
		
    size_t GetMaxThreads()
    {
      return m_pThreadManager->GetMaxThreads();
    }
		
    void GetFileList(std::list<fs::path>& p_lPaths)
    {
       m_oFileFinder.Find(m_sPath, p_lPaths, m_sExt);
    }

    void GetWordCounts(std::list<fs::path>& p_lPaths, std::multimap<int, std::string, wc_comparator>& p_mResults)
    {
      // Two main execution methods
      m_oWordCounter.CountWords(p_lPaths);
      m_oWordCounter.GetTotals(p_mResults);
    }

    private:
      std::string m_sExt;
      fs::path      m_sPath;
      WordCount     m_oWordCounter;
      FileFinder    m_oFileFinder;
      boost::shared_ptr<ThreadManager> m_pThreadManager;
};

SSFIManager::SSFIManager()
{
  boost::shared_ptr<ThreadManager> l_pThreadManager = boost::make_shared<ThreadManager>();
  p_oImpl = boost::make_shared<Impl>(l_pThreadManager);
}

SSFIManager::~SSFIManager()
{
}

bool SSFIManager::GetWordCounts(std::multimap<int, std::string, wc_comparator>& p_mResults)
{
  std::list<fs::path> paths;
  p_oImpl->GetFileList(paths);
  p_oImpl->GetWordCounts(paths, p_mResults);

  return true;
}

bool SSFIManager::SetRootPath(const std::string& p_sPath)
{
  if (p_sPath.empty())
  {
    std::cerr << "Given path is empty.\n";
	return false;
  }

  p_oImpl->SetRootPath(p_sPath);
  return true;
}

const std::string SSFIManager::GetRootPath()
{
	return p_oImpl->GetRootPath();
}

bool SSFIManager::SetFileExtension(const std::string& p_sExt)
{  
  if (p_sExt.empty())
  {
    std::cerr << "File extension is empty.\n";
	return false;
  }
	
  p_oImpl->SetFileExtension(p_sExt);
  return true;
}

const std::string& SSFIManager::GetFileExtension()
{
	return p_oImpl->GetFileExtension();
}

bool SSFIManager::SetMaxThreads(const size_t& p_iMaxThread)
{
  if (p_iMaxThread < 1)
  {
    std::cerr << "Thread number is less that 1.\n";
	return false;
  }

  p_oImpl->SetMaxThreads(p_iMaxThread);
  return true;
}

size_t SSFIManager::GetMaxThreads()
{
	return p_oImpl->GetMaxThreads();
}
