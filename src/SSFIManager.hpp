/*
 *
 *  File: SSFIManager.hpp
 *  Authors: Mikhail Strizhov
 *
 *  Date: Apr 5, 2016
 *
*/

// System

// Shared
#include "site_defaults.hpp"

// Module
#include "boost/shared_ptr.hpp"

class SSFIManager
{
  public:
    SSFIManager();
    virtual ~SSFIManager();

    bool SetRootPath(const std::string& p_sPath);
    const std::string GetRootPath();
    
    bool SetFileExtension(const std::string& p_sExt);
    const std::string& GetFileExtension();
    
    bool SetMaxThreads(const size_t& p_iMaxThread);
    size_t GetMaxThreads();

    bool GetWordCounts(std::multimap<int, std::string, wc_comparator>& p_mResults);

  protected:
    class Impl;

  private:
    boost::shared_ptr<Impl> p_oImpl;
};

