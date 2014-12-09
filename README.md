plumber HOWTO
=======

./dump.sh pid

It will dump memory blocks of pid process to files.

cat /proc/pid/maps

Check for [heap] and find dumped file which corresponds to it. Rename it to core.

Compile all files (ignore *_Selftest.*).  Run binary in the same directory as core file.

As the result, you will get the list of Leaks (size, repeated pattern length and pattern itself)
