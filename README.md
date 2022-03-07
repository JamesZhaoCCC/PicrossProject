# Picross Generator and Solver

Composed of PicrossGen and PicrossSolver

## How to run 
g++ PicrossGen.cpp or g++ PicrossSolver.cpp

./PicrossGen or ./PicrossSolver

## Picross Generator
PicrossGen.h
PicrossGen.cpp

Create a new file (ruleFile) containing the rule for a M by N picross puzzle
by taking in user input for row and column

Process: Randomly fills a grid of M by N size with 1s or 0s. Afterwards, calculate the row and column rules by counting the individual runs and store them in a matrix.

Example Rule File:
Row :( 1 )( 1 )( 2 )
Column :( 1 )( 1 )( 2 )

## Picross Solver
PicrossSolver.h
PicrossSolver.cpp

Requires exRuleFile. Parses through exRuleFile and outputs the answer for the rule in the terminal
Inefficient, brute force solves up to 6 by 6. Anything more requires too much time.

Process: Uses cartesian product. Depth-First Search and Backtracking.

Time Complexity of O(V + E)


## Background
Picross or Nonograms is a logic puzzle in the form of a grid and you are given a set of numbers lining the rows and columns of the grid.
The sets of numbers indicate whether a spot on the grid would be filled in, the length it will extend to without interruption,
how many lines are contained in the row or column, and the order of those lines within that row or column.
