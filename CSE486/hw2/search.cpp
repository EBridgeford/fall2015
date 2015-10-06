/*
Eric Bridgeford
CSE486
HW2

Search.cpp implements BFS for HW2

Compiled with

g++ -o1 -std=c++11 node.cpp parser.cpp search.cpp -o hw2.o

hardcoded to look for "hw2.txt"
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
#include "node.h"
#include "parser.h"

//Updates child node with information from the parent

void updateNode(Node* popped, Node* target, std::string direction) {

  target->setPath(popped);
  target->updatePath(direction);
  target->setDepth(popped->getDepth()+1);
  target->setTotalCost(popped->getTotalCost()+target->getCost());

  if (popped->getNumMsgs() != 0) {target->setNumMsgs(target->getNumMsgs()+popped->getNumMsgs());}

}

/*
Non working BFS implementation. While it can correctly keep track of the path,
cost, and depth the message handling has issues that prevents it from fully
functioning. Giving it the goal state of a Node(4,2,1) will give you a correct result.
But it fails on the back tracking required for something like Node(0,0,3)

*/
void BFS (std::vector<std::vector<Node>> map, int startRow, int startCol) {

std::queue<Node> test;
std::vector<Node> explored;

test.push(map[startRow][startCol]);

Node goal = Node(3,4,1); //goal state node of (row, column, and number of messages)

int i = 0;

bool done = false;

while (done == false) {

    Node popped = test.front();
    explored.push_back(popped);

    //Checks if node currently being looked at is equal to the goal node
  if (popped == goal) {
      done = true;
      std::cout << popped.getPath() << std::endl;
      std::cout << popped.toString() << std::endl;
      std::cout << "Depth is " << popped.getDepth() << std::endl;
      std::cout << "Cost is " << popped.getTotalCost() << std::endl;
      std::cout << "Num of msgs is " << popped.getNumMsgs() << std::endl;
    } else {

    //Grabs the location of the popped Node
    int popRow = popped.getRow();
    int popCol = popped.getCol();
    /*
    A series of 4 checks to enqueue all possible children. If a move is valid it
    adds that node to the queue. For example at 0,0 there are two valid moves so
    only 1,0 and 0,1 are added. But if we were at 3,3 a total of four nodes 2,3
    3,2 4,3 3,4 would be added.
    */
    if (popRow + 1 < map.size()) {

      Node tempNode = map[popRow+1][popCol];
      updateNode(&popped, &tempNode, "N");

      if (std::find(explored.begin(), explored.end(), tempNode) == explored.end()) {

        test.push(tempNode);
      }
    }

    if (popRow - 1 > 0) {

      Node tempNode = map[popRow-1][popCol];
      updateNode(&popped, &tempNode, "S");

      if (std::find(explored.begin(), explored.end(), tempNode) == explored.end()) {
        test.push(map[popRow-1][popCol]);

        test.push(tempNode);
      }
    }

    if (popCol + 1 < map[1].size()) {

      Node tempNode = map[popRow][popCol+1];
      updateNode(&popped, &tempNode, "E");

        if (std::find(explored.begin(), explored.end(), tempNode) == explored.end()) {

          test.push(tempNode);
        }
      }

    if (popCol - 1 > 0) {

      Node tempNode = map[popRow][popCol-1];
      updateNode(&popped, &tempNode, "W");

      if (std::find(explored.begin(), explored.end(), tempNode) == explored.end()) {

        test.push(tempNode);
      }
    }

  }
  //removes the front node and repeats the process
  test.pop();
  }

}


int main() {
  std::vector<std::string> file = readFile("hw2.txt");
  std::vector<std::vector<Node>> ret = parseFile(file);
  int startingRow = getStartingRow(file);
  int startingColumn = getStartingCol(file);

  BFS(ret, startingRow, startingColumn);

  //printAll(ret);

}
