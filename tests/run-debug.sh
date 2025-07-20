#!/bin/bash
args="../src/*.c $1 -fsanitize=address -ggdb3 -rdynamic -Og -lrphiic"
printf " \033[94m*\033[0m GCC RUN\n"
gcc ${args} && ./a.out 
printf " \033[94m*\033[0m CLANG RUN\n"
clang ${args} && ./a.out 
printf " \033[94m*\033[0m TCC RUN\n"
tcc ${args} && ./a.out 

