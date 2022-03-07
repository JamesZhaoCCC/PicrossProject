/* 
James Zhao
2/17/2022

Solve a Picross puzzle by reading the rule through a file

File is in the form of Rule followed by column below.

Answer will be output through a file in grid format.
*/

#include <algorithm>
#include <string>
#include <sstream>
#include "PicrossSolver.h"

//Takes in a string and uses stringstream to parse the string and output only the integers contained in the string
//*BUG* Generates matrices that are one extra in beginning. Must be deleted outside function. If done inside, it deletes twice. *BUG*
void parseRuleFile(std::string str, std::vector<std::vector<int>> &row, std::vector<std::vector<int>> &col)
{
    std::stringstream ss;   
    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    std::string dir, temp;
    int found;
    std::vector<int> v;
    /* first store the rule direction, row or column */
    ss >> dir;
    while (ss >> temp) {
        
        /* extracting word by word from stream */
        //std::cout << dir << " " << temp << '\n'; 
        if(dir == "Row") { 
            if(isdigit(temp[0])) {
                v.push_back(atoi(temp.c_str()));
            } 
            else {
                row.push_back(v);
                v.clear();
            }
        }
        if(dir == "Column") {
            if(isdigit(temp[0])) {
                v.push_back(atoi(temp.c_str()));
            } 
            else {
                col.push_back(v);
                v.clear();
            }
        }

    }
    // std::cout << row.size();
}

//Check input matrix with the rules to make sure the puzzle is solved
//Used by solving functions to check if the solution is correct
//method: find rule of input matrix and compare with correct rule matrices
bool check(std::vector<std::vector<int>> matrix, std::vector<std::vector<int>> row, std::vector<std::vector<int>> col) {
    if(makeRowRule(matrix, matrix.size(), matrix[0].size()) == row && makeColRule(matrix, matrix.size(), matrix[0].size()) == col) {
        std::cout << "True\n";
        return true;
    }
    // printRule(makeRowRule(matrix, matrix.size(), matrix[0].size()));
    // printRule(row);
    // if(makeRowRule(matrix, matrix.size(), matrix[0].size()) == row) {
    //     std::cout << "True\n";
    //     return true;
    // }
    else {
        std::cout << "False\n";
        return false;
    }
}

//return a solution that obeys rowRule, unfinished
//rules are in form a matrices
// ***BUG - ForceRule only works with 5x5 matrices
std::vector<std::vector<int>> ForceRule(std::vector<std::vector<int>> &row) {  
    std::vector<int> v(row.size(), 0);
    std::vector<std::vector<int>> ans(row.size(), v);

    std::vector<std::vector<int>> rowCopy = row;

    for (int i = 0; i < rowCopy.size(); i++) {
        //std::cout << "( ";
        std::vector<int> v;
        for (int j = 0; j < rowCopy[i].size(); j++) {
            // std::cout << row[i][j]<<" ";
            // totalRow += row[i][j];
            while(rowCopy[i][j] != 0) {
                v.push_back(1);
                rowCopy[i][j] -= 1;
            }
            // v.push_back(0);
        }
        while(v.size() != row.size()) {
                v.push_back(0);
        }
        ans[i] = v;
        //std::cout << '\n';
    }
    // force row to match
    // printMatrix(ans);

    // do {
    //     printMatrix(ans);
    //     //check(ans, row, col);
    //     //std::cout << '\n';
    // } while ( std::next_permutation(ans[num].begin(),ans[num].end()) );   
    //std::cout  << ans[0].size();
    //printVector(temp);
    //printMatrix(ans);
    //comb(ans[0]);


    return ans;
}

//https://www.geeksforgeeks.org/distinct-permutations-string-set-2/
//find all unique permutations of a string via recursion
//MODS: maintains order according to rowRule
void permute(int i, std::string s, std::vector<std::string> &perm, std::vector<int> row)
{
    // base case
    if (i == (s.length() - 1)) {
        //check for right permutation
        std::vector<int> compare;
        int total1s = 0;
        bool zeros = true;
        // std::cout << s[0]-48 << " ";
        if(s[0]-48 == 1) total1s ++;
        for(int i = 0; i < s.length(); i++) {
                
            if (s[i]-48 != 1 && s[i+1]-48 == 1) total1s ++;

            else if (s[i]-48 == 1 && s[i+1]-48 == 1) total1s ++;

            else if (s[i]-48 == 1 && s[i+1]-48 != 1) {
                compare.push_back(total1s);
                total1s = 0;
            }
            if(s[i]-48 == 1) zeros = false;
        }
        //
        if(zeros) {
            perm.push_back(s);
        }

        // *** (FIXED) BUG - some comparisons are not showing ***
        if(row == compare) {
            perm.push_back(s);
            return;
        }
        else return;

        // perm.push_back(s);
        // return;
    }
   
    char prev = '*';
   
    // loop from j = 1 to length of string
    for (int j = i; j < s.length(); j++) {
        std::string temp = s;
        if (j > i && temp[i] == temp[j])
            continue;
        if (prev != '*' && prev == s[j]) {
            continue;
        }
       
        // swap the elements
        std::swap(temp[i], temp[j]);
        prev = s[j];
       
        // recursion call
        permute(i + 1, temp, perm, row);
    }
}

bool checkCol(std::vector<std::string> s, std::vector<std::vector<int>> col) {

    std::vector<std::vector<int>> v; //vector<string> s converted to vector<vector<int>> v
    int numCol = 0;
    for(int i = 0, x = 0; i < s.size(); i++) { //look through vector
        //std::cout << s[i] << "\n";
        std::vector<int> vec;
        for(int j = 0; j < s[i].length(); j++) { //look through string
            vec.push_back(s[i][j]-48);
        }
        v.push_back(vec);
        numCol++;
    }

    //printMatrix(v); // print s(converted to v)
    std::vector<std::vector<int>> compare;

    for(int i = 0; i < v.size(); i++) {
        int x = 0;
        std::vector<int> total1s;
        for(int j = 0; j < v[i].size(); j++) {
            if(v[j][i] == 1 && total1s.empty()) {
                total1s.push_back(1);
            }
            else if (v[j][i] == 0 && !total1s.empty()) {
                total1s.push_back(0);
            }
            else if (v[j][i] == 1 && !total1s.empty()) {
                total1s.back() += 1;
            }
            // std::cout<<v[j][i] << " ";
        }
        total1s.erase(std::remove(total1s.begin(), total1s.end(), 0), total1s.end());
        if(total1s.empty()) total1s.push_back(0);
        compare.push_back(total1s);
        // std::cout << '\n';
    }
    
    //printRule(compare);
    //printRule(col);

    if(compare == col) {
        printMatrix(v);
        std::cout << "You've Done it\n";
        return true;
    }
    else {
        // std::cout << "You Have Failed\n";
        return false;
    }
}

//create input vector for cartesian product
// ***BUG - vector of 0s is not created
std::vector<std::vector<std::string>> createCombine(std::vector<std::vector<int>> &ans, std::vector<std::vector<int>> &row) {  
    std::vector<std::vector<std::string>> combine; // hold all combinations of the c
    std::vector<std::string> c; //ans matrix converted to vector of strings, c
    // printMatrix(ans);

    //double for loop converts vector<int> to string
    for(int i = 0; i < ans.size(); i++) {
        std::string str = "";
        for(int j = 0; j < ans[i].size(); j++) {
            str.push_back(ans[i][j] + 48); //only pushing back 1s and 0s
            // std::cout << ans[i][j] << '\n';
        }
        c.push_back(str);
    }

    //print c
    // for(int i = 0; i < c.size(); i++) {
    //     std::cout << c[i] << '\n';
    // }

    int index = 0;

    for(auto i : c) {
        //printVector(row[index]);
        
        sort(i.begin(), i.end());
        std::vector<std::string> perm; // hold permutations of string i
        permute(0, i, perm, row[index]);
        //std::cout << '\n';
        index++;
        combine.push_back(perm);

    }

    return combine;
}

//https://stackoverflow.com/questions/5279051/how-can-i-create-cartesian-product-of-vector-of-vectors
//Cartesian Product
//used to find all permutations of multiple variable length vectors
std::vector<std::vector<std::string>> cartesian (const std::vector<std::vector<std::string>>& v) {
    std::vector<std::vector<std::string>> s = {{}};
    for (const auto& u : v) {
        std::vector<std::vector<std::string>> r;
        for (const auto& x : s) {
            for (const auto y : u) {
                r.push_back(x);
                r.back().push_back(y);
            }
        }
        s = move(r);
    }

    return s;
}

int main() {
    std::vector<std::vector<int>> row; //matrix holding rowRule
    std::vector<std::vector<int>> col; //matrix holding colRule

    std::string line;
    std::ifstream myfile ("exRuleFile.txt");

    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            //std::cout << line << '\n';
            parseRuleFile(line, row, col);
            // std::cout << '\n';
        }
        row.erase(row.begin());
        col.erase(col.begin());

        myfile.close();
    }
    else std::cout << "Unable to open file";
    

    std::vector<std::vector<int>> M = ForceRule(row);

    // printMatrix(M);

    std::vector<std::vector<std::string>> ans = createCombine( M, row );

    // for(int i = 0; i < ans.size(); i++) {
    //     for(int j = 0; j < ans[i].size(); j++) {
    //         std::cout << ans[i][j] << " ";
    //     }
    //     std::cout << '\n';
    // }
    for(int i = 0; i < cartesian(ans).size(); i++) {
        checkCol(cartesian(ans)[i], col);
    }

    // for(int i = 0; i < 1; i++) {
    //     checkCol(cartesian(ans)[i], col);
    // }

    return 0;
}

