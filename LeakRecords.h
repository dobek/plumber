#pragma once

#include <set>
#include <iostream>

#include "Leak.h"

using namespace std;

class LeakRecords {
public:
  LeakRecords(unsigned int size = 10);

  void Add(SpLeak);
  void Print(ostream&) const;

private:
  class Compare
  {
  public:
    bool operator() (const SpLeak l, const SpLeak r)
    {
      return *l < *r;
    }
  };
  set<SpLeak,Compare> leaks_;
  unsigned int size_;
};

ostream& operator<< (ostream&,LeakRecords&);
