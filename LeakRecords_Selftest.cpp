#include "LeakRecords_Selftest.h"
#include "LeakRecords.h"
#include <iostream>

using namespace std;

void LeakRecords_Selftest1() {
  TOccurrences o {1, 4, 6};
  o.reserve(1000);
  SpLeak spLeak(new Leak(o,3));

  LeakRecords records;
  records.Add(spLeak);


  o[0] = 0;
  o[1] = 7;
  o[2] = 19;
  o.push_back(27);

  spLeak = make_shared<Leak>(o,4);
  records.Add(spLeak);


  o[0] = 0;
  o[1] = 7;
  o[2] = 19;
  o[3] = 24;
  o.push_back(27);

  spLeak = make_shared<Leak>(o,2);
  records.Add(spLeak);

  cout << records;
  cout << "LeakRecords_Selftest1 - done" << endl;
}
