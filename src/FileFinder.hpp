/*
 *
 *  File: FileFinder.hpp
 *  Authors: Mikhail Strizhov
 *
 *  Date: Apr 5, 2016
 *
*/

#ifndef _FILEFINDER_H
#define _FILEFINDER_H

// System

// Shared
#include "site_defaults.hpp"

// Module
#include <boost/shared_ptr.hpp>

class ThreadManager;

class FileFinder
{
  public:
    FileFinder(boost::shared_ptr<ThreadManager> p_oThreadManager);
    virtual ~FileFinder();

    // Find all paths for a given directory
    void Find(fs::path p_oDir, std::list<fs::path>& p_lSubPaths, std::string p_sExt="*");

  private:
    bool ExtMatch(const fs::path p_oTest);
    void LocateFiles(fs::path p_oDir, std::list<fs::path>& p_lSubPaths, bool p_bThreadEnabled);

    boost::shared_ptr<ThreadManager> m_oThreadManager;
    std::string	m_sExt;
};
#endif

