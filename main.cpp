#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


#include "Leak_Selftest.h"
#include "LeakRecords_Selftest.h"
#include "LeakSearch.h"

using namespace std;


int main()
{
    cout << "Duplicate finder" << endl;
    const char* file="core";

    struct stat filestatus;
    stat( file, &filestatus );
    const size_t N = filestatus.st_size;

    int i;
    int fd;
    void *map;

    fd = open(file, O_RDONLY);
    if (fd == -1) {
      perror("Error opening file for reading");
      exit(EXIT_FAILURE);
    }

    map = mmap(0, N, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
      close(fd);
      perror("Error mmapping the file");
      exit(EXIT_FAILURE);
    }


    LeakSearch ls(map,N);
    Leak::SetMemBuffer(static_cast<unsigned char*>(map));

    ls.SearchForLeaks();

    ls.PrintLeakRecords();


    if (munmap(map, N) == -1) {
      perror("Error un-mmapping the file");
    }
    close(fd);

    return 0;
}

