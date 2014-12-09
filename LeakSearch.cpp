#include "LeakSearch.h"

#include <iostream>
#include <vector>
#include <string.h>


using namespace std;

LeakSearch::LeakSearch(const void* mem, size_t memSize, size_t recordsNumber)
    : records_(recordsNumber+1)
    , memSize_(memSize)
{
  mem_ = static_cast<const unsigned char*>(mem);
}

size_t LeakSearch::SearchForLeaks(size_t minPatternLength) {
  vector<SpLeak> store;
  array<TOccurrences,256> map;

  //Init occ with leaks for 1 byte pattern (i.e. one char)
  for (size_t i=0; i < memSize_ ; ++i)
    map[mem_[i]].push_back(i);

  for (int i=0 ; i<256 ; ++i)
    if ( map[i].size() > 1 ) {
      //todo std::move
      store.push_back(make_shared<Leak>(map[i],1));
    }


  while (!store.empty()) {
    SpLeak leak = store.back();
    store.pop_back();
    const TOccurrences &occs = leak->GetOccurrences();
    const size_t offset = leak->GetPatternLength();

    for (int i=0; i < 256; ++i)
      map[i].clear();

    for (auto occ=occs.begin(); occ!=occs.end() ; ++occ)
      if ( *occ + offset < memSize_)
        map[mem_[*occ + offset]].push_back(*occ);

    for (int i=0; i < 256; ++i)
      if (map[i].size() > 1) {
        //todo: std:move for TOccurrences
        SpLeak nLeak(new Leak(map[i],offset+1));
        store.push_back(nLeak);
        if (minPatternLength <= offset+1)
          records_.Add(nLeak);
      }
  }

  return 0; //todo return max leak
}

LeakRecords& LeakSearch::GetLeakRecords() {
  return records_;
}

void LeakSearch::PrintLeakRecords(ostream& s) {
  records_.Print(s);
}

