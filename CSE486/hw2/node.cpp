/*
Eric Bridgeford
CSE486

Node class file that represents a given location. Based on node class given in
class

g++ -o1 -std=c++11 node.cpp parser.cpp search.cpp -o hw2.o
*/

#include <iostream>
#include <string>
#include "node.h"

    //Constructor for row and column
    Node::Node(int r, int c) {
      row = r;
      col = c;
      numMsg = 0;
      depth = 0;
    }

    //Null constructor
    Node::Node() {}

    //Constructor that includes a number of messages
    Node::Node(int r, int c, int m) {
      row = r;
      col = c;
      numMsg = m;
      depth = 0;
    }

    //Returns a string of Node properties
    std::string Node::toString() {
      std::string string = "Row ";
      string += std::to_string(row);
      string += ", Column ";
      string += std::to_string(col);
      string += ", Cost ";
      string += std::to_string(cost);
      if (hasMsg == true)
        string += ", Message present";
      else
        string += ", No message";
      return string;

    }

    void Node::setHasMsg(bool value) {hasMsg = value;}
    void Node::setCost(float value) {cost = value;}
    bool Node::getHasMsg() {return this->hasMsg;}
    float Node::getCost() {return this->cost;}
    int Node::getRow() {return this->row;}
    int Node::getCol() {return this->col;}

    std::string Node::printParent() {
      if (this->parentNode != nullptr)
        return this->parentNode->toString();
      else
        return "No parent";
      }
    void Node::setParent(Node* node) {this->parentNode = node;}

    Node* Node::getParent() {

      if (this->parentNode != nullptr)
        return this->parentNode;
      else
        return nullptr;
    }


    bool Node::operator==(const Node& other) {


      if ((row == other.row) == false)
        return false;
      if ((col == other.col) == false)
          return false;

      if ((numMsg == other.numMsg) == false)
         return false;


      return true;
      }

    void Node::setAction(char action) {this->action = action;}
    char Node::getAction() {return this->action;}

    void Node::setDepth(int depth) {this->depth = depth;}
    int Node::getDepth() {return this->depth;}


    std::string Node::getPath() {return this->path;}

    void Node::updatePath(std::string direction) {
      this->path.append(direction);
      //std::cout << "Updated path " << this->path << std::endl;
    }

    void Node::setPath(Node* node) {
        this->path = node->getPath();
    }

    void Node::setNumMsgs(int msg) {this->numMsg = msg;}
    int Node::getNumMsgs() {return this->numMsg;}

    float Node::getTotalCost() {return this->totalCost;};

    void Node::setTotalCost(float totalCost) {
      this->totalCost = totalCost;
    }
/*
int main() {
  Node test = Node(3,4);
  Node test2 = Node(4,3);
  test.setParent(&test2);

  std::cout << test.printParent() << std::endl;

  Node* test3 = test.getParent();

  std::cout << test3->printParent() << std::endl;

  Node* test4 = test.getParent();

  std::cout << test4->printParent() << std::endl;
  return 0;
  //std::cout << test2.printParent() << std::endl;
}
*/
