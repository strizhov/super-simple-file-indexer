/*
 *
 *  File: site_defaults.hpp
 *  Authors: Mikhail Strizhov
 *
 *  Date: Apr 5, 2016
 *
*/

#ifndef _SITEDEFAULTS_H
#define _SITEDEFAULTS_H

#include <map>
#include <list>
#include <boost/filesystem.hpp>

#ifndef MAX_THREADS
#define MAX_THREADS 10
#endif 

namespace fs = boost::filesystem;

// Comparator for multimap
struct wc_comparator : public std::binary_function<int, std::string, bool>
{
  
  bool operator() (const int& a, const int& b) const
  { 
    return (a > b); 
  }
  
  bool operator() (const std::string& a, const std::string& b) const
  {
    return (a < b);
  }
};
	
#endif  

