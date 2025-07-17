#!/bin/bash
args="../src/*.c $1 -O3 -DNDEBUG -march=native -mfpmath=sse -fno-semantic-interposition -ffp-contract=fast"
printf " \033[94m*\033[0m GCC RUN\n"
gcc ${args} -flto=auto -fgraphite-identity && ./a.out 
gcc ${args} && ./a.out 
printf " \033[94m*\033[0m CLANG RUN\n"
clang ${args} && ./a.out 
clang ${args} -flto=thin && ./a.out 

