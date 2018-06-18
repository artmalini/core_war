#!/bin/bash

echo "\n---------------------- [Cleaning Trash and Temp Files] ---------------------- \n"

rm -rf _*
rm -rf __*
rm -rf *.c~

rm -rf */_*
rm -rf */*.c~

rm -rf */*/_*
rm -rf */*/*.c~

rm -rf */*/*/_*
rm -rf */*/*/*.c~

echo "\n---------------------- [Compile CoreWar-ASM] ---------------------- \n"
make
echo "\n---------------------- [TEST of My - ASSEMBLER] ---------------------- \n"
./asm vmakahon.s

echo "\n---------------------- [TEST of Custom - ASSEMBLER] ---------------------- \n"
./resourses/asm vmakahon.s