/*

Eric Bridgeford
HW3
CSE486
Dr. Zmuda

8Queens hill climbing solver

Compiles with g++ -std=c++11 -o2 8Queens.cpp -o 8queens.o
*/

#include <array>
#include <iostream>
#include <random>


std::array<std::array<char, 8>, 8> queens; /* {{
  {'X','Q','X','X'},
  {'X','X','X','Q'},
  {'Q','X','X','X'},
  {'X','X','Q','X'}
}};*/

std::array<std::array<char, 8>, 8> queens2; /* {{
  {'X','X','X','X'},
  {'X','X','X','X'},
  {'X','X','X','X'},
  {'X','X','X','X'}
}};*/

//Randomly populates the first board by adding one Q to each column

void populateBoard() {

  std::random_device rdev;
  std::default_random_engine e1(rdev());
  std::uniform_int_distribution<int> uniform_dist(0, queens.size()-1);


  for (int i = 0; i < queens.size(); i++) {
    int number = uniform_dist(e1);
    for (int j = 0; j < queens.size(); j++) {

      if (j == number)
        queens[i][j] = 'Q';
      else
        queens[i][j] = 'X';
    }
  }

}

//returns the number of horizontal conflicts

int countHoriz(int x, int y) {

  int count = 0;

  for (int i = 0; i < queens.size(); i++) {
    if (queens[x][i] == 'Q' && (i != y))
    count++;
  }

  return count;
}

//returns the number of vertical conflicts

int countVert(int x, int y) {

  int count = 0;

  for (int i = 0; i < queens.size(); i++) {
    if (queens[i][y] == 'Q' && (i != x))
    count++;
  }

  return count;

}

//returns the number of diagonal conflicts

int countDiag(int x, int y) {
 int count = 0;

 int tempX = x;
 int tempY = y;

 //this checks the diagonals going from left to right, bottom to top

 while (tempX > 0 && queens.size() > tempX && tempY > 0 && queens.size() > tempY) {
   tempX--;
   tempY--;
 }
 //std::cout << tempX << " " << tempY << std::endl;
 for (int i = tempX, j = tempY; queens.size() > i && queens.size() > j; i++, j++) {
   if (queens[tempX][tempY] == 'Q' && tempX != x && tempY != y)
    count++;
 }

 tempX = x;
 tempY = y;

 //this checks the diagonals going from right to left, bottom to top

 while (tempX > 0 && queens.size() > tempX && tempY > 0 && queens.size()-1 > tempY) {
   tempX--;
   tempY++;
 }
 //std::cout << tempX << " " << tempY << std::endl;
 for (int i = tempX, j = tempY; queens.size() > i && j > 0; i++, j--) {
   if (queens[tempX][tempY] == 'Q' && tempX != x && tempY != y)
    count++;
 }

  return count;
}

//uses the vertical, horizontal, and diagonal conflict counters to return the
//total number of conflicts
int countConflicts(int x, int y) {

int horiz = countHoriz(x,y);
int vert = countVert(x,y);
int diag = countDiag(x,y);

return horiz+vert+diag;
}

//checks if a solution is valid by walking through the grid and at each Q it
//checks the number of conflicts. If any Q returns a conflict > 0 it returns false.

bool valid() {

  int conflicts = 0;
  for (int i = 0; i < queens2.size(); i++) {
    for (int j = 0; j < queens2.size(); j++) {

      if (queens2[i][j] == 'Q')
        conflicts = countConflicts(i,j);
      if (conflicts > 0)
        return false;
    }
  }
  return true;
}

//hill climbing algorithm that finds position the lowest number of conflicts in each row
//and sets a queen in a blank board to that position.

void hillClimbing() {

  int conflicts = 0;
  int min = 20; //
  int x;
  int y;
  for (int i = 0; i < queens.size(); i++) {
    min = 20;
    for (int j = 0; j < queens.size(); j++) {


        conflicts = countConflicts(i,j);

        if (min > conflicts) {
          x = i;
          y = j;
          //std::cout << "Setting x and y to " << x << " " << y << std::endl;
          min = conflicts;

        }

    }
  queens2[x][y] = 'Q';
  }

}

//resets the state of the second board
void clearSecondBoard() {

  for (int i = 0; i < queens.size(); i++) {
    for (int j = 0; j < queens.size(); j++) {
      queens2[i][j] = 'X';
    }
  }
}

//prints the second board where the potential solution is stored

void printSecondBoard() {

  for (int i = 0; i < queens2.size(); i++) {
    for (int j = 0; j < queens2.size(); j++) {
      std::cout << queens2[i][j];
    }
    std::cout << std::endl;
  }
}

int main() {
 int solutionsFound = 0;
 int runs = 10000;
for (int i = 0; i < runs; i++) {
  clearSecondBoard();
  populateBoard();
  hillClimbing();
  bool test = valid();

  if (test == true) {
    std::cout << "----START----" << std::endl;
    printSecondBoard();
    std::cout << "----END-----" << std::endl;
    solutionsFound++;
  }

}

std::cout << "Out of " << runs << " runs " << solutionsFound << " solutions were found" << std::endl;
}
