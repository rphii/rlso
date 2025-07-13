#!/bin/bash
args="../src/*.c $1 -O3 -DNDEBUG -march=native"
printf " \033[94m*\033[0m GCC RUN\n"
gcc ${args} -flto=auto && ./a.out 
printf " \033[94m*\033[0m CLANG RUN\n"
clang ${args} -flto=thin && ./a.out 

