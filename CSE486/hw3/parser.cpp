/*
Eric Bridgeford
CSE486
HW3

Parser functions to pull the Hidato puzzle out of the given text file

g++ -o1 -std=c++11 node.cpp parser.cpp search.cpp -o hw2.o
*/
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


std::vector<std::string> readFile(std::string filename) {
  std::ifstream readFile;
  readFile.open(filename);
  std::string tempLine;
  std::vector<std::string> stringVector;
  auto i = 0;
    while (!readFile.eof()) {
      getline(readFile, tempLine);

      if (tempLine != "") {
      stringVector.push_back(tempLine);
      }
      i++;
    }
stringVector.shrink_to_fit();
return stringVector;
}

//Parses the vector of strings and returns a 2D vector of nodes

std::vector<std::vector<int>> parseFile(std::vector<std::string> file) {

  int size = 0;
  size = std::stoi(file[0].substr(0,1));
  //std::cout << "The size of the puzzle is " << size << std::endl;

  std::vector<std::vector<int>> puzzle;
  puzzle.resize(size, std::vector<int>(size));

for (int i = 1; i < file.size(); i++) {

  int position = 0;

  int start = 0;
  auto end = file[i].find(" ");

  while (file[i][end+1] == ' ') {
    end++;
  }
  while (end != std::string::npos)
   {
      while (file[i][end+1] == ' ') {
        end++;
      }

      int number = std::stoi(file[i].substr(start, end - start));
      //std::cout << "Adding " << number << std::endl;
      puzzle[i-1][position] = number;
      start = end+1;
      end = file[i].find(" ", start);
      position++;
   }

   int number = std::stoi(file[i].substr(start, file[i].length()));
   //std::cout << "Adding " << number << std::endl;
    puzzle[i-1][position] = number;
}

return puzzle;
}

//helper function that prints out the 2D vector of nodes

void printAll(std::vector<std::vector<int>> ret) {
  for (int i = 0; i < ret.size(); i++) {
    for (int m = 0; m < ret.size(); m ++) {
    std::cout << ret[i][m] << ", ";
    }
  std::cout << std::endl;
  }

}
/*
int main() {
  std::vector<std::string> file = readFile("Hidato5.txt");
  std::vector<std::vector<int>> ret = parseFile(file);
  printAll(ret);

}
*/
