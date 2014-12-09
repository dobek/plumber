#include "LeakSearch.h"

#include <iostream>
#include <string.h>

using namespace std;


void LeakSearch_Selftest_1() {
  const int N=100;
  unsigned char tab[N];

  for (int i=0;i<N;++i)
    tab[i]=i+100;

  const unsigned char pat[] = {1,2,3,4,5,6,7};
  memcpy(tab+10,pat,sizeof(pat));
  memcpy(tab+30,pat,sizeof(pat));
  memcpy(tab+50,pat,sizeof(pat));

  LeakSearch ls(tab,N,4);

  ls.SearchForLeaks(3);

  ls.PrintLeakRecords();

  cout << "DONE" << endl;

}

