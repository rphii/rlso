#!/bin/bash
powerpc64-unknown-linux-gnu-gcc ../src/*.c $1
qemu-ppc64 -L /usr/powerpc64-unknown-linux-gnu/ ./a.out

