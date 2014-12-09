#include "Leak.h"

#include <iostream>


void test1() {
  TOccurrences occ;
//  occ.reserve(1000);

  for (int i=0; i<10 ; ++i)
      occ.push_back(i);

  Leak leak(occ,3);

  cout << "Leak size: " << leak.GetLeakSize() << endl;
}
