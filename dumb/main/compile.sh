#!/bin/bash
gcc write-bootloader.c -o write-bootloader
./write-bootloader
rm write-bootloader
gcc dumb864x01.c -o build -lX11
