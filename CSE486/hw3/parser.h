#ifndef __Parser_H_INCLUDED__
#define __Parser_H_INCLUDED__


#include <vector>
#include <string>



std::vector<std::string> readFile(std::string filename);
std::vector< std::vector<int> > parseFile(std::vector<std::string> file);

#endif
