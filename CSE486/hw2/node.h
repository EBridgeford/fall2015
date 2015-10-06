#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

#include <vector>
#include <iostream>
#include <string>

class Node {
private:

      int row, col;
      int depth = 0;
      bool hasMsg;
      int numMsg = 0;
      float cost;
      Node* parentNode = nullptr;
      char action = 'X';
      std::string path = "";
      float totalCost = 0;

public:
    Node(int r, int c);
    Node ();
    Node(int r, int c, int m);
    std::string toString();

    void setHasMsg(bool value);
    void setCost(float value);
    bool getHasMsg();
    float getCost();
    int getRow();
    int getCol();

    float getTotalCost();
    void setTotalCost(float totalCost);

    std::string printParent();
    void setParent(Node* node);

    Node* getParent();

    bool operator==(const Node& other);

    char getAction();
    void setAction(char action);

    void setDepth(int depth);
    int getDepth();

    std::string getPath();
    void updatePath(std::string direction);
    void setPath(Node* node);

    void setNumMsgs(int msg);
    int getNumMsgs();

};
#endif
