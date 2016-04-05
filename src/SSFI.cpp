/*
 *
 *  File: SSFI.cpp
 *  Authors: Mikhail Strizhov
 *
 *  Date: Apr 5, 2016
 *
*/

// System
#include <iostream>
#include <iomanip>

// Shared

// Modules
#include <boost/program_options.hpp>
#include "SSFIManager.hpp"


int main(int argc, char* argv[])
{
  std::string directory;
  std::string extension;
  int words_num = 0;
  int thread_num = 0;

  namespace po = boost::program_options;
  po::options_description desc("Options");
  desc.add_options()
    ("help,h",    "Print usage")
    ("path,p",    po::value<std::string>(&directory)->default_value("."), "Directory to search for files.")
    ("ext,e",     po::value<std::string>(&extension)->default_value(".txt"), "File extension.")
    ("words,w",   po::value<int>(&words_num)->default_value(10), "The maximum number of words to display.")
    ("threads,t", po::value<int>(&thread_num)->default_value(10), "The number of threads to crawl directory.");
  po::variables_map vm; 

  po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
  if ( vm.count("help")  ) 
  { 
    std::cout << "Super Simple File Indexer " << std::endl << desc << std::endl; 
    return 0; 
  }
  po::notify(vm);
  
  // Make manager and results
  SSFIManager ctr;
  std::multimap<int, std::string, wc_comparator> results;

  // Set path
  ctr.SetRootPath(directory);

  // Set extension
  ctr.SetFileExtension(extension);

  // Set max num threads
  ctr.SetMaxThreads(thread_num);

  // Get result
  ctr.GetWordCounts(results);

  // Print results
  auto item = results.begin();
  while((item != results.end()) && --words_num)
  {
    std::cout << item->second << "\t" << item->first << std::endl;
    ++item;
  }

  return 0;
}

