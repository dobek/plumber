#include "Leak.h"

#include <iostream>

Leak::Leak(const TOccurrences& occur,unsigned int patternLength) {
  occurrences_ = occur;
  patternLength_ = patternLength;
  UpdateLeakSize();
}

const TOccurrences& Leak::GetOccurrences() const {
  return occurrences_;
}

unsigned int Leak::GetLeakSize() const {
  return leakSize_;
}

unsigned int Leak::GetPatternLength() const {
  return patternLength_;
}

void Leak::UpdateLeakSize() {
  //How much memory is wasted for the repeating pattern
  leakSize_ = 0;

  if (occurrences_.size() < 2)
    return;

  size_t overlapSafe = occurrences_[0] + patternLength_;
  for (auto it = occurrences_.begin() + 1 ; it != occurrences_.end() ; ++it )
  if ( overlapSafe < *it ) {
    leakSize_ += patternLength_;
    overlapSafe = *it + patternLength_;
  }
}

void Leak::Print() const {
  const TOccurrences& o = occurrences_;
  cout << "Leak Size: " << GetLeakSize()
       << ", Pattern Length: " << GetPatternLength()
       << " Pattern: ";
  if (mem_)
    for (const unsigned char* p=mem_+o[0]; p != mem_ + o[0] + patternLength_; ++p )
      cout << *p;
  cout << endl;
}

unsigned char* Leak::mem_ = nullptr;

void Leak::SetMemBuffer(unsigned char *mem) {
  mem_ = mem;
}

bool operator< (const Leak& a, const Leak& b) {
  return (a.GetLeakSize() < b.GetLeakSize());
}

bool operator< (const SpLeak a, const SpLeak b) {
  if (b == nullptr)
    return false;
  if (a == nullptr)
    return true;
  return (a->GetLeakSize() < b->GetLeakSize());
}

ostream& operator<< (ostream& s, const Leak& l) {
  const TOccurrences& o = l.GetOccurrences();
  s << "Leak Size: " << l.GetLeakSize()
    << ", Pattern Length: " << l.GetPatternLength()
    << ", Occurrences: " << o.front();
  for (auto it=o.begin()+1; it!=o.end() ; ++it)
    s << ", " << *it;
  s << endl;
  return s;
}
