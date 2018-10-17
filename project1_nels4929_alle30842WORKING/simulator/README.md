James Allender
Mitchell Nelson
CISC-340 
Project 01 part 2
README

simulator.c - This file is the C source code for our machine code simulator

Makefile - This is a makefile to be used with Make to build our project

multiply.as - this is a asembly instruction file that multiplys the 2 numbers specified in the file on the mcand and mplier .fill lines

Test Files:
	test1.ac/mc Profesor provided test file. Tests looping via beq (in part tests sucessfull sign extension of a negetive number), lw, add, noop, labels (designating lines and in offsets), and halt.
	test2.ac/mc Tests nand spicificly, and re-test other commands
	test3.ac/mc Tests sw spicificly, and re-test other commands
	test4.ac/mc Tests jalr in increse by 1 and skip farther spicificly, and re-test other commands
	test5.ac/ma Tests storing into a large value of memory and load from that location into a reg to confirm storing and recal, and re-test other commands