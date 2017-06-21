Gavin Chen ghchen 1492980
5/17/17
cs101 pa03

I have read and understood the Academic Misconduct Policy for
    Undergraduates, the related sections 102.01-102.016 and 105.15 of the
    UC Santa Cruz Student Policies and Regulations Handbook,
    and the related sections of the class syllabus.
-Gavin Chen

I wrote this assignment using only permitted sources
       that do not require citation, according to the syllabus.


submitted files:
dfstrace1.c
dfstrace1.h
intVec.c
intVec.h
loadGraph.c
loadGraph.h
Makefile
Readme
scc03.c
test1.in
test2.in
test3.in
test4.in
test5.in


This program builds off of pa01 and 02. It parses an input file, creates the graph adt similar to pa01.
To run it, simply call make to compile the binary file, then run it as ./graph02 <flags> <input file>. 
The makefile also includes a clean utility that will delete the binary file. 
The DFS algorithim functions as described in the text, visiting all white nodes, and recursivly diving down connected componenets until all nodes are black while also adding them to the finishing time stack. 
The program then calls DFS2 and visits all the nodes in the order specified by the finishing time stack (first in last out).
For this assignment I created a data struct called graph that held the adj list of the verticies, the info array, the finishing time stack, as well as the number of nodes in the graph. 
The info array was a 2D array with that stored info as [vertex][info]. 
It held the color, discovery time, finishing time, and predececor/root for each node in indicies 0, 1, 2, and 3 respectivly.

test1.in tests the creation of the adjVec and the transpose/print adj matrix functions, and also tests the dfs algorithim for a simple case. 
test2.in tests scalability and ensures the realloc and other dynamic size functions work. 
test3.in tests for a tree with 2 different SCC's and is a more in depth test of the algorithim.
test4.in tests weighted edge input.

done
