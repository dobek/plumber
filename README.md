plumber HOWTO
=======

./dump.sh pid

It will dump memory blocks of pid process to files.

cat /proc/pid/maps

Check for [heap] and find dumped file which corresponds to it. Rename it to core.

Compile all files (ignore *_Selftest.*).  Run binary in the same directory as core file.

As the result, you will get the sorted list of Leaks (size, repeated pattern length and pattern itself)

E.g.

A[BCD]EF[BCD]GHIJK[BCD]LMNO - BCD is treated a leak.
- leak size = 6 ( 2 x 3 ,  we assume that the first instance is not leak )
- leak pattern length = 3
- leak pattern: BCD
