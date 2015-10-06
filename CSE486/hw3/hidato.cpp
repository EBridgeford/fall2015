/*

Eric Bridgeford
HW3
CSE486
Dr. Zmuda

Hidato solver, the parser doesn't handle lines in the txt files starting with a
space but otherwise works correctly.

Compiles with g++ -std=c++11 -o2 hidato.cpp parser.cpp -o hidato.o
Usage hidato.0 Hidato3.txt

*/
#include <array>
#include <iostream>
#include <set>
#include <vector>
#include "parser.h"

struct Hidato  {

  std::vector<std::vector<int>> puzzle;

 Hidato(std::vector<std::vector<int>> puzzle_) {
   puzzle = puzzle_;
 }

 std::set<int> used; //Set of values that are already used in the puzzle
 std::set<int> possibleValues; //list of potential values at a given 0

 //Only one zero is considered at a time
 int zeroX;
 int zeroY;

 void print() {
   std::cout << "---START---" << std::endl;
   for (int i = 0; i < puzzle.size(); i++) {
     for (int j = 0; j < puzzle.size(); j++) {
       std::cout << puzzle[i][j] << ", ";
     }
   std::cout << std::endl;
      }
    std::cout << "----END----" << std::endl;
 }

//Searches for a zero to fill in and calls the getNeighbors function to fill
//the possibleValues set
 void searchForZeroes() {

   for (int i = 0; i < puzzle.size(); i++) {
     for (int j = 0; j < puzzle.size(); j++) {

       if (puzzle[i][j] == 0) {
         zeroX = i;
         zeroY = j;
         //std::cout << "Zero found at " << i << " and " << j << std::endl;
         getNeighbors(i,j);
         //return;
       }
     }
   }

 }

 void searchForZeroes(int x, int y) {


   for (int i = x; i < puzzle.size(); i++) {
     for (int j = y; j < puzzle.size(); j++) {

       if (puzzle[i][j] == 0) {
         zeroX = i;
         zeroY = j;
         //std::cout << "Zero(i,j) found at " << i << " and " << j << std::endl;
         getNeighbors(i,j);
         return;
       }
     }
   }

 }

//looks at all the values around the passed in and adds them to the possibleValues
//set
 void getNeighbors(int i, int j) {

   std::array<int, 3> arr1 = {-1,0,1};
   std::set<int> mrvCanidate;
   possibleValues.clear();

         for (int x = 0; x < arr1.size(); x++) {
           for (int y = 0; y < arr1.size(); y++) {

             int tempX = i + arr1[x];
             int tempY = j + arr1[y];

             if (puzzle.size() > tempX && tempX >= 0 && puzzle.size() > tempY && tempY >= 0 ) {
              if (puzzle[tempX][tempY] != 0) {

                if (puzzle[tempX][tempY]-1 > 0)
                  mrvCanidate.insert(puzzle[tempX][tempY]-1);
                if ((puzzle.size()*puzzle.size()) > puzzle[tempX][tempY]+1)
                  mrvCanidate.insert(puzzle[tempX][tempY]+1);

                //std::cout << "Tried to add " << puzzle[tempX][tempY]-1 << " and " << puzzle[tempX][tempY]+1 << std::endl;
                setPossibleValues(mrvCanidate);

                if (mrvCanidate.size() > 0)
                  possibleValues = mrvCanidate;
                else
                  searchForZeroes(i+1,j);



                }

              }
           }
         }
        }

 void updateUsed() {
   for (int i = 0; i < puzzle.size(); i++) {
     for (int j = 0; j < puzzle.size(); j++) {
        if (puzzle[i][j] != 0) {
          used.insert(puzzle[i][j]);
        }
     }
   }
 }

 void printUsed() {
   for (auto i : used) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;
 }

 void printPossibleValues() {
   for (auto i : possibleValues) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;
  }

  void setPossibleValues(std::set<int> &mrvCanidate) {

  for (auto it = used.begin(); it != used.end(); it++) {
    mrvCanidate.erase(*it);
  }

}

bool isDone() {

  //return !hasZeroes();

  if (hasZeroes() == true)
    return false;
  return hasCorrectNeighbors();
  }

//Quick check to see if a puzzle is done by looking for 0's. If any are present
//the puzzle can't be done.

bool hasZeroes() {
  for (int i = 0; i < puzzle.size(); i++) {
    for (int j = 0; j < puzzle.size(); j++) {
       if (puzzle[i][j] == 0) {
         return true;
       }
    }
  }
}

//More detailed done check, it uses two functions to determine if a puzzle is done.
//This one finds the location of the 1 and passes the location of that 1 to the
//second function
bool hasCorrectNeighbors() {

  int x;
  int y;
  for (int i = 0; i < puzzle.size(); i++) {
    for (int j = 0; j < puzzle.size(); j++) {
       if (puzzle[i][j] == 1) {
         x = i;
         y = j;
       }
    }
  }
  return hasCorrectNeighbors(x,y);
}

//This function receives the location of 1 in the puzzle and goes from there.
//It looks at all the values around the location that was passed in for the next
//value in the sequence. If it finds it the function calls itself with the location
//of that next number. So when 1 is passed in it looks for 2, then 3, and so on.
//It it can go from 1 to the maximum value by jumping to adjacent locations on the grid
//the puzzle is done.

bool hasCorrectNeighbors(int i, int j) {

  std::array<int, 3> arr1 = {-1,0,1};
  int maxValue = puzzle.size()*puzzle.size();
  bool ret = false;

        for (int x = 0; x < arr1.size(); x++) {
          for (int y = 0; y < arr1.size(); y++) {

            int tempX = i + arr1[x];
            int tempY = j + arr1[y];

            if (puzzle.size() > tempX && tempX >= 0 && puzzle.size() > tempY && tempY >= 0 ) {

             if (puzzle[i][j] == maxValue) {
              //std::cout << "Max value " << maxValue << "Found" << std::endl;
              return true;
              }

             if (puzzle[tempX][tempY] == puzzle[i][j]+1) {
               //std::cout << "Starting from " << puzzle[i][j] << " found " << puzzle[tempX][tempY] << std::endl;
               return hasCorrectNeighbors(tempX,tempY);
             }

              else
                ret = false;

             }
          }
        }

        return ret;
}

//Sets the value of the 0 being looked at to the passed in value

void setValue(int value) {
  puzzle[zeroX][zeroY] = value;
}
};

void Solve(Hidato &puzzle) {

  //Solver that checks if the puzzle is done, then if it is in an invalid state
  //then tries to solve it recursively
  if (puzzle.isDone() == true) {
    puzzle.print();
  } else if (puzzle.used.size() == (puzzle.puzzle.size() * puzzle.puzzle.size())) {
    //std::cout << "Solution failed" << std::endl;
    //puzzle.print();
  }
  else {
    puzzle.updateUsed(); //updates the set of used values
    puzzle.searchForZeroes(); //finds the next 0, adds all it's neighbors, and removes the values already used

    //Solves the puzzle by making a copy of the puzzle, setting the 0 equal to each value
    //then calling itself to solve that version of the puzzle.
    for (auto it = puzzle.possibleValues.begin(); it != puzzle.possibleValues.end(); ++it) {
      Hidato copy = puzzle;
      copy.setValue(*it);
      Solve(copy);

    }
  }
}
int main (int argc, char *argv[]) {

  if (argc == 2) {
  std::vector<std::string> file = readFile(argv[1]);
  std::vector<std::vector<int>> puzzle = parseFile(file);

  if (puzzle.size() > 0) {
    Hidato test = Hidato(puzzle);
    Solve(test);
  }
  else
    std::cout << "Something is wrong with the puzzle" << std::endl;
  } else
    std::cout << "Too many or too few arguements" << std::endl;


}
