#include "LeakSearch.h"

#include <algorithm>
#include <iostream>


bool comp(SpLeak a,SpLeak b) {
  return *a < *b;
}

LeakRecords::LeakRecords(unsigned int size)
    : size_(size)
{
}

void LeakRecords::Add(SpLeak leak) {
  if ( (!leaks_.empty()) && ((*leaks_.rbegin())->GetLeakSize() < leak->GetLeakSize()) ) {
    cout << "Found potential leak: ";
    leak->Print();
  }
  if (leaks_.size() < size_) {
    leaks_.insert(leak);
    //cout << "[Added] " << *leak;
  }
  else {
    const size_t min = (*leaks_.begin())->GetLeakSize();
    if ( min < leak->GetLeakSize() ) {
      leaks_.erase(leaks_.begin());
      leaks_.insert(leak);
      //cout << "[Added] " << *leak;
    }
  }
}

//void LeakRecords::Print(ostream& s) const {
//  cout << "--- LEAKS ---" << endl;

//  for (auto it=leaks_.rbegin(); it!=leaks_.rend() ; ++it)
//    **it;
//}

void LeakRecords::Print(ostream& s) const {
  cout << "--- LEAKS ---" << endl;

  for (auto it=leaks_.rbegin(); it!=leaks_.rend() ; ++it)
    (*it)->Print();
}

ostream& operator<< (ostream& s, LeakRecords& ls) {
  ls.Print(s);
  return s;
}

