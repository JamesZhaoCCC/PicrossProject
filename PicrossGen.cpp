/* 
James Zhao
2/2/2022

Create a Picross puzzle by getting the desired row and column 
and then outputting the rule of the picross puzzle in the form of a file.
*/


#include <time.h>
#include <limits>
#include "PicrossGen.h"

//generate a matrix at random to represent a nonogram(picross) puzzle
//return row and column as matrices to show ruleset of puzzle
int main() {
    std::vector<std::vector<int>> num;

    // generate numbers from a different seed based on time it is run to make numbers more random
    srand(time(nullptr));

    int row, col;

    //input validation - must be positive, non-zero, integer
    while(std::cout << "Number of Rows (must be positive and greater than 0)\n" && (!(std::cin >> row)|| row < 0)) {
        std::cout << "Not a positive integer. Enter a positive integer for rows.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while(std::cout << "Number of Columns (must be positive and greater than 0)\n" && (!(std::cin >> col)|| col < 0)) {
        std::cout << "Not a positive integer. Enter a positive integer for columns.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    fillMatrix(num, row, col);
    //printMatrix(num);

    makeRuleFile(num, row, col);

    return 0;
}