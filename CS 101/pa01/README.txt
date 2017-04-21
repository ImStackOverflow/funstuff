Gavin Chen ghchen 1492980
4/20/17
cs101 pa01

I have read and understood the Academic Misconduct Policy for
    Undergraduates, the related sections 102.01-102.016 and 105.15 of the
    UC Santa Cruz Student Policies and Regulations Handbook,
    and the related sections of the class syllabus.
-Gavin Chen

I wrote this assignment using only permitted sources
       that do not require citation, according to the syllabus.

This program creates a graph by implementing a array of pointers ADT.
Each element in the array coresponds to a graph node of the same value,
and holds a pointer that points to a struct that holds an int array of vertecies
that vertex is connected to, as well as the size and capacity of the data array.
The program works with use of the calloc and realloc functions to create 
nodes and arrays. The input file is the standard file, and if any of the inputs are 
formated incorrectly the program will end with an error message about the format.
There is a memory leak with the calloc function used to make the nodes as well as a memory
leak with the calloc that created the array of pointers. The leak associated with making
nodes is constant and leaks 32 bytes of memory, while the second leak is a function 
of the number of nodes.