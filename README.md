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

Example Rule File:
Row :( 1 )( 1 )( 2 )
Column :( 1 )( 1 )( 2 )

## Picross Solver
PicrossSolver.h
PicrossSolver.cpp

Requires exRuleFile. Parses through exRuleFile and outputs the answer for the rule in the terminal
