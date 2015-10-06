/*
Eric Bridgeford
CSE486
HW2

Parser functions to pull information of the grid from the text files
and transform them in to a 2D vector of Nodes.

g++ -o1 -std=c++11 node.cpp parser.cpp search.cpp -o hw2.o
*/
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "node.h"
#include "parser.h"

//Returns costs for a given line as a vector of floats. So float at position
//0 is the first cost going left to right, 1 is the second, and so on.

std::vector<float> getCosts(std::string costs) {
  std::vector<float> costFloats;
  int last = 0;
  bool run = true;
  while (run == true) {
    auto space = costs.find(' ', last);

    if (space == std::string::npos){
      std::string temp = costs.substr(last, costs.length());
      costFloats.push_back(stof(temp));
      run = false;
    } else {
    std::string temp = costs.substr(last, space-last);
    costFloats.push_back(stof(temp));
    last = space+1;
    }
  }
return costFloats;
}

//Returns a vector of bools representing if a node contains a message. So a
//true for [0] would represent that the first node going left to right has a message.

std::vector<bool> getMsg(std::string msgs) {


  std::vector<bool> msgExists;
  for (auto i : msgs) {
    if (i == 'X')
      msgExists.push_back(true);
    else
      msgExists.push_back(false);
  }
  return msgExists;
}

//Grabs the number of columns as specified in the files

int getTotalCol(std::vector<std::string> file) {

  int space = file[0].find(" ");
  int columns = std::stoi(file[0].substr(space,file[0].length()));
  return columns;
}

//Grabs the number of columns specified in the file

int getTotalRow(std::vector<std::string> file) {
  int space = file[0].find(" ");
  int rows = std::stoi(file[0].substr(0,space));
  return rows;

}

//Grabs the starting row specified in the file

int getStartingRow(std::vector<std::string> file) {
  int space = file[1].find(" ");
  int startingRow = std::stoi(file[1].substr(0,space));
  return startingRow;
}

//Grabs the starting column specified in the file

int getStartingCol(std::vector<std::string> file) {
  int space = file[1].find(" ");
  int startingCol = std::stoi(file[1].substr(space,file[1].length()));
  return startingCol;

}

//Reads the text file into a vector of strings

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

std::vector<std::vector<Node>> parseFile(std::vector<std::string> file) {

  std::vector<std::vector<Node>> ret; //2D vector of Things to return

  int rows = getTotalRow(file);
  int columns = getTotalCol(file);

  ret.resize(rows, std::vector<Node>(columns));

  for (int m = (1+rows); m != 1; m--) {

  std::vector<float> costFloats = getCosts(file[m+rows]);
  std::vector<bool> msgExists = getMsg(file[m]);

  for (int i = 0; i < columns; i++) {
    Node temp = Node((1+rows)-m,i);
    temp.setHasMsg(msgExists[i]);
    temp.setCost(costFloats[i]);

    if (temp.getHasMsg() == true)
      temp.setNumMsgs(1);

    ret[(1+rows)-m][i] = temp;
  }
}

return ret;
}

//helper function that prints out the 2D vector of nodes

void printAll(std::vector<std::vector<Node>> ret) {
  for (int i = 0; i < ret.size(); i++) {
    for (int m = 0; m < ret[i].size(); m ++)
    std::cout << ret[i][m].toString() << std::endl;
  }
}
/*
int main() {
  std::vector<std::string> file = readFile("hw2.txt");
  std::vector<std::vector<Node>> ret = parseFile(file);
  //BFS(ret);


  for (int i = 0; i < ret.size(); i++) {
    for (int m = 0; m < ret[i].size(); m ++)
    std::cout << ret[i][m].toString() << std::endl;
  }

  std::vector<std::string> file = readFile("hw2.txt");

  parseFile(file);


  std::string test = "1.1 11.2 1111.3 3.143";
  std::string test2 = "X...";
  std::vector<float> costFloats = getCosts(test);
  std::vector<bool> msgExists = getMsg(test2);

  int rows = 10;
  int columns = 4;

  std::vector<std::vector<Thing>> ret;
  ret.resize(rows, std::vector<Thing>(columns));
  Thing test = {true, 1.2};
  ret[5][3] = test;

  std::cout << ret[5][3].cost << std::endl;

}
*/
