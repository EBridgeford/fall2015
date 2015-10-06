#ifndef __Parser_H_INCLUDED__
#define __Parser_H_INCLUDED__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "node.h"

std::vector<float> getCosts(std::string costs);
std::vector<bool> getMsg(std::string msgs);
std::vector<std::string> readFile(std::string filename);
std::vector<std::vector<Node> > parseFile(std::vector<std::string> file);
int getTotalRow(std::vector<std::string> file);
int getTotalCol(std::vector<std::string> file);

int getStartingRow(std::vector<std::string> file);
int getStartingCol(std::vector<std::string> file);

void printAll(std::vector<std::vector<Node> > ret);
#endif
