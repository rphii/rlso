#!/bin/bash
gcc *.c -fsanitize=address -ggdb3 -rdynamic -Og && ./a.out 
