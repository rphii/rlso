#!/bin/bash
powerpc64-unknown-linux-gnu-gcc *.c
qemu-ppc64 -L /usr/powerpc64-unknown-linux-gnu/ ./a.out

