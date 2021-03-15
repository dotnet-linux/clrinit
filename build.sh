#!/bin/bash

mkdir -p build
gcc -fno-asynchronous-unwind-tables -fno-ident -s -Os -nostdlib -static -lgcc -o build/init main.c

