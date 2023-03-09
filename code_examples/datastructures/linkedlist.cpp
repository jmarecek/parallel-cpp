//********************************************************
// The following code example is taken from the book
//  C++20 - The Complete Guide
//  by Nicolai M. Josuttis (www.josuttis.com)
//  http://www.cppstd20.com
//
// The code is licensed under a
//  Creative Commons Attribution 4.0 International License
//  http://creativecommons.org/licenses/by/4.0/
//********************************************************


#include <iostream>
#include <thread>
#include <memory>               // includes <atomic> now
using namespace std::literals;  // for duration literals

include "linkedlist.h"

int main()
{
  AtomicList<std::string> alist;

  // populate list with elements from 10 threads:
  {
    std::vector<std::jthread> threads;
    for (int i = 0; i < 100; ++i) {
      threads.push_back(std::jthread{[&, i]{
                                       for (auto s : {"hi", "hey", "ho", "last"}) {
                                         alist.insert(std::to_string(i) + s);
                                         std::this_thread::sleep_for(5ns);
                                       }
                                     }});
    }
  } // wait for all threads to finish

  alist.print();   // print resulting list
}
