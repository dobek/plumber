#pragma once

#include <vector>
#include <memory>

using namespace std;

typedef  vector<size_t>  TOccurrences;

class Leak {
public:
  Leak(const TOccurrences& /* occur */,unsigned int /* patternLength */);

  const TOccurrences& GetOccurrences() const;
  unsigned int GetLeakSize() const;
  unsigned int GetPatternLength() const;

  void Print() const;
  static void SetMemBuffer(unsigned char *mem);

private:
  TOccurrences  occurrences_;
  unsigned long leakSize_;
  unsigned int  patternLength_;

  static unsigned char *mem_;

  void UpdateLeakSize();
};

typedef shared_ptr<Leak> SpLeak;

bool operator< (const Leak&, const Leak&);
bool operator< (const SpLeak, const SpLeak);

ostream& operator<< (ostream&,const Leak&);
