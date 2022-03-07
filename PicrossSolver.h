/* 
James Zhao
2/22/2022

Header file for PicrossSolver.cpp. Contains printRule and prinVector.
*/

#include <iostream>
#include <vector>
#include <fstream>

void printRule(std::vector<std::vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        std::cout << "( ";
        for (int j = 0; j < matrix[i].size(); j++) {
            // std::cout << "Element at num[" << i << "][" << j << "]: ";
            std::cout << matrix[i][j]<<" ";
        }
        std::cout << ')';
    }
    std::cout << '\n';
}

void printVector(std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

void printMatrix(std::vector<std::vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            // std::cout << "Element at num[" << i << "][" << j << "]: ";
            std::cout << matrix[i][j]<<" ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

std::vector<std::vector<int>> makeRowRule(std::vector<std::vector<int>> matrix, int row, int col) {
    std::vector<std::vector<int>> rowRule;
    bool zeros = true;
    int countRow = 0;

    for (int i = 0; i < row; i++) {
        std::vector<int> rowNums;
        for (int j = 0; j < col; j++) {
            if(matrix[i][j] == 1) {
                zeros = false;
                countRow++;
                continue;
            }
            if(matrix[i][j] == 0) {
                // add countRow into rowNums
                if(countRow > 0) {
                    // std::cout << countRow;
                    rowNums.push_back(countRow);
                }
                countRow = 0;
                continue;
            }
        }
        if(countRow > 0) {
            //std::cout << countRow;
            rowNums.push_back(countRow);
        }
        if(zeros == true) {
            //std::cout << '0';
            rowNums.push_back(0);
        }
        else {
            zeros = true;
        }
        //std::cout << " Row Done " << '\n';
        rowRule.push_back(rowNums);
        countRow = 0;
    }
    return rowRule;
}

std::vector<std::vector<int>> makeColRule(std::vector<std::vector<int>> matrix, int row, int col) {
    std::vector<std::vector<int>> colRule;
    bool zeros = true;
    int countCol = 0;

        for (int i = 0; i < col; i++) {
            std::vector<int> colNums;

            for (int j = 0; j < row; j++) {
                if(matrix[j][i] == 1) {
                    zeros = false;
                    countCol++;
                    continue;
                }
                if(matrix[j][i] == 0) {
                    // add countRow into rowNums
                    if(countCol > 0) {
                        // std::cout << countCol;
                        colNums.push_back(countCol);
                    }
                    countCol = 0;
                    continue;
                }
            }
            if(countCol > 0) {
                //std::cout << countCol;
                colNums.push_back(countCol);
            }
            if(zeros == true) {
                //std::cout << '0';
                colNums.push_back(0);
            }
            else {
                zeros = true;
            }
        //std::cout << " Column Done " << '\n';
        colRule.push_back(colNums);
        countCol = 0;
    }
    return colRule;
}
