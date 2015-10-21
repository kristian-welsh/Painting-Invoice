@ echo off
del program.exe
gcc -std=iso9899:199409 -pedantic-errors -Wno-long-long -Wno-write-strings program.c
mv a.exe program.exe
