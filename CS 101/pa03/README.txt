Gavin Chen ghchen 1492980
5/17/17
cs101 pa01

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


This program builds off of pa01 and 02. It parses an input file, creates the graph adt similar to pa01. So far only my DFS works. To run it, simply call make to compile the binary file, then run it as ./graph02 <flags> <input file>. The makefile also includes a clean utility that will delete the binary file. The DFS algorithim functions as described in the text, visiting all white nodes, and recursivly diving down connected componenets until all nodes are black. For this assignment I created a data struct called graph that held the adj list of the verticies, the info array, the finishing time stack, as well as the number of nodes in the graph. The info array was a 2D array with that stored info as [vertex][info]. It held the color, discovery time, finishing time, and predececor/root for each node in indicies 0, 1, 2, and 3 respectivly.

I wasn't able to get the SCC component of the assignment working for graphs with more than at least 16 verticies (eg test2.in). For graphs with small numbers of verticies the algorithim works alright, however when I input test2.in there is an error in making the transposed graph. In my code I create another graph struct to hold the transposed data. The error occurs when trying to calloc memory for the transposed data. Before calling calloc the stack is as it should be, however after calling calloc(1,1) the data in the stack is modified after the 6th indicie. It replaces most of the values with 0, and when dfsphase2 begins it tries to access the -1 indicie (-1 to offset the verticies begining on 1 instead of 0), and results in a segmentation fault. It looks like the calloc function is overiding the data with memory values. I tried to store the stack values in a seperate array to pass them into the new transposed graph, but I am unable to call calloc. The function is somehow overiding the data in the struct, and I was unable to resolve the issue. The error is in line 66 of my dfstrace1.c file.


