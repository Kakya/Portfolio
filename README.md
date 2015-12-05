# Portfolio
This is the collection of low-level programming work I have done in both C and X86_64 Assembly.

mm, mdriver, and memory are together a simulation of the C library malloc, free, and realloc functions using doubly linked lists.
Together, they allow a user to allocate, free, and reallocate memory as much as they want within the size of the Heap.
bits is a series of bitwise integer puzzles completed.
Project1 implements a program that solves the n-Queens problem whose objective is to place n queens on a n × n chess board: no two queens are allowed to be in the same row, column, or a diagonal for n = 4, ..., 20. 
Project2 implements singly linked lists in C to shuffle a deck of cards.
Image, Embed and Extract refer to a project that successfully hides a document inside a pgm file, using the final unused bit in the .pgm file and then succesfully extracting it out.
Deck is more manipulations of a deck of cards using a singly-linked list.
Abundant, caller, long_sqrt, and quintuple are written in x86_64 Assembly and are simple functions. Abundant returns whether the given input is an abundant number or not. Quintuple simply returns five times the input, long_sqrt returns the largest value whose square is not greater than the input. Caller simply calls quintuple.