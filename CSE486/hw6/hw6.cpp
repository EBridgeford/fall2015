#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <string>
#include <set>
#include <utility>

std::vector<std::string> readFile(std::string filename) {
  // Read each line of the given file into a vector.
  std::ifstream readFile;
  readFile.open(filename);
  std::string tempLine;
  std::vector<std::string> stringVector;
  while (!readFile.eof()) {
    getline(readFile, tempLine);
    stringVector.push_back(tempLine);
  }

  // Shrink the vector and return it to the function caller.
  stringVector.shrink_to_fit();
  return stringVector;
}

std::vector<std::vector<std::string> > parseData(std::vector<std::string> data) {

  std::vector<std::vector<std::string> > dataArr(data.size()-1);
  std::regex regularExpression("(\\S+)");

  for (unsigned int i = 0; i < data.size(); i++) {
    auto begin = std::sregex_iterator(data[i].cbegin(), data[i].cend(), regularExpression);
    auto end = std::sregex_iterator();
    for (; begin != end; ++begin) {
      std::smatch match = *begin;
      std::string temp = match.str();
      dataArr[i].push_back(temp);
    }
  }
  dataArr.shrink_to_fit();
  return dataArr;
}

std::vector<std::set<std::string>> uniqueValues(std::vector<std::vector<std::string>> data) {

  std::vector<std::set<std::string> > uniqueValues(data[0].size());

  for (unsigned int i = 0; i < data.size(); i++) {
    for (unsigned int j = 0; j < data[0].size(); j++) {
      uniqueValues[j].insert(data[i][j]);
    }
  }

  return uniqueValues;
}

void classifierProb(std::vector<std::set<std::string>> uniqueValues, std::vector<std::vector<std::string>> data) {

  std::vector<std::pair<std::string, int>> posValues;

  for (auto j: uniqueValues[uniqueValues.size()-1]) {
    int count = 0;
    std::cout << "Found ";
    for (unsigned int i = 0; i < data.size(); i++) {
      if (j ==  data[i][data[i].size()-1]) {
        count++;
      }
    }
    std::cout << count << " instances of " << j << std::endl;
  }
}

void otherProb(std::vector<std::set<std::string>> uniqueValues, std::vector<std::vector<std::string>> data) {

  std::cout << "POSTIVE" << std::endl;
  for (unsigned int y = 0; y < uniqueValues.size()-1; y++) {
    for (auto j: uniqueValues[y]) {
      int count = 0;
      std::cout << "Found ";
      for (unsigned int i = 0; i < data.size(); i++) {
        if (j ==  data[i][y] && data[i][data[i].size()-1] == "1") {
          count++;
        }
      }
      std::cout << count << " postive instances of " << j << std::endl;
    }
  }
  std::cout << "NEGATIVE" << std::endl;
  for (unsigned int y = 0; y < uniqueValues.size()-1; y++) {
    for (auto j: uniqueValues[y]) {
      int count = 0;
      std::cout << "Found ";
      for (unsigned int i = 0; i < data.size(); i++) {
        if (j ==  data[i][y] && data[i][data[i].size()-1] == "0") {
          count++;
        }
      }
      std::cout << count << " negative instances of " << j << std::endl;
    }
  }
}


void printUnique(std::vector<std::set<std::string>> values) {

  for (unsigned int i = 0; i < values.size(); i++) {
    std::cout << "NEW SET" << std::endl;
    for (auto j: values[i]) {
      std::cout << j << std::endl;
    }
  }

}

int probability(std::vector<std::vector<std::string>> data, std::string classifier, std::string value, int col) {

  int count = 0;
  //std::cout << "Found ";
  for (unsigned int i = 0; i < data.size(); i++) {
    if (value ==  data[i][col] && data[i][data[i].size()-1] == classifier) {
      count++;
    }
  }

  return count;
}

int total(std::vector<std::vector<std::string>> data, std::string value, int col) {

  int count = 0;
  for (unsigned int i = 0; i < data.size(); i++) {
    if (value ==  data[i][col]) {
      count++;
    }
  }
  return count;
}

void printStuff(std::vector<std::vector<std::string>> result, std::vector<std::set<std::string>> values) {

  for (unsigned int i = 0; i < values.size()-2; i++) {

    for (auto y: values[i]) {

      for (auto j: values[values.size()-1]) {
        std::cout << "Found " << probability(result,j,y,i) << " instances of " << y << " with the classifier " << j << std::endl;
      }
      std::cout << "Total instances of " << y << " found are " << total(result,y,i) << std::endl;
    }
  }
}

void bayesClassifier(std::vector<std::vector<std::string>> result, std::vector<std::set<std::string>> values) {

  for (auto i: values[values.size()-1]) {


    float saveValue = 0;
    float classifierOccurances = total(result,i,values.size()-1);
    float totalLines = result.size();
    float classifierResult = classifierOccurances/totalLines;

    for (unsigned int m = 0; m < result.size()-1; m++) {

      float tempResult = classifierResult;
      for (auto y: values[m]) {
          float totalValue = total(result,y,m);
        for (auto j: values[values.size()-1]) {
          float probValue = probability(result,j,y,m);
          float probValue2 = probValue/totalValue;
          tempResult = probValue2 * classifierResult;
        }

      }
    }
  }
}
int main() {

  std::vector<std::string> test = readFile("data2.txt");

  std::vector<std::vector<std::string>> result = parseData(test);
  auto values = uniqueValues(result);
  //classifierProb(values, result);
  //otherProb(values, result);
  //probability(result, "1", "L", 0);
  //printStuff(result,values);
  bayesClassifier(result,values);



}
