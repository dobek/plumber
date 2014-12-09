#pragma once

#include "LeakRecords.h"
#include <iostream>

using namespace std;

class LeakSearch {
public:
  LeakSearch(const void* /* mem */, size_t /* memSize */,size_t recordsNumber = 10);

  size_t SearchForLeaks(size_t minPatternLength=5 /* bytes */);

  LeakRecords& GetLeakRecords();
  void PrintLeakRecords(ostream& s=cout);

private:
  LeakRecords records_;
  const unsigned char *mem_;
  size_t memSize_;
};


