/*
Eric Bridgeford
CSE486 HW6
Dr. Michael Zmuda
*/

#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <string>
#include <set>
#include <chrono>
#include <unordered_map>

//Map to store classifiers/values and their probability
std::unordered_map<std::string, float> probMap;

//File reader
std::vector<std::string> readFile(std::string filename) {
  // Read each line of the given file into a vector.
  std::ifstream readFile(filename);
  std::vector<std::string> stringVector;

  if (!readFile.is_open()) {
    return stringVector;
  }

  std::string tempLine;

  while (!readFile.eof()) {
    getline(readFile, tempLine);
    stringVector.push_back(tempLine);
  }
  readFile.close();
  // Shrink the vector and return it to the function caller.
  stringVector.shrink_to_fit();
  return stringVector;
}

//Reads data into a 2D vector of strings
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

/*
Parses the 2D vector produced by parseData and creates a vector of sets of strings.
The vector cooresponds to the column, and the set contains unique values within that
column. So uniqueValues[0] is the set of all values in column 1.
*/
std::vector<std::set<std::string>> uniqueValues(std::vector<std::vector<std::string>> data) {

  std::vector<std::set<std::string> > uniqueValues(data[0].size());

  for (unsigned int i = 0; i < data.size(); i++) {
    for (unsigned int j = 0; j < data[0].size(); j++) {
      uniqueValues[j].insert(data[i][j]);
    }
  }

  return uniqueValues;
}

void printUnique(std::vector<std::set<std::string>> values) {

  for (unsigned int i = 0; i < values.size(); i++) {
    std::cout << "NEW SET" << std::endl;
    for (auto j: values[i]) {
      std::cout << j << std::endl;
    }
  }

}

/*


*/
int occur(std::vector<std::vector<std::string>> data, std::string classifier, std::string value, int col) {

  int count = 0;
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
        std::cout << "Found " << occur(result,j,y,i) << " instances of " << y << " with the classifier " << j << std::endl;
      }
      std::cout << "Total instances of " << y << " found are " << total(result,y,i) << std::endl;
    }
  }
}

float bayesClassifier(std::vector<std::vector<std::string>> result, std::vector<std::set<std::string>> values) {

  float totalGuess = 0;
  float totalCorrect = 0;

  for (unsigned int i = 0; i < result.size(); i++) {
    float lineProb = 0;
    float predictionProb = 0;
    std::string predictionClassifier = "";

    for (auto j: values[values.size()-1]) {

      auto search = probMap.find(j);
      if (search == probMap.end()) {

        float classifierOccurances = total(result,j,values.size()-1);
        float totalLines = result.size();
        float classifierResult = classifierOccurances/totalLines;
        probMap.emplace(j, classifierResult);
        lineProb = classifierResult;
        //std::cout << "Value for " << j << " is " << classifierResult << std::endl;
      } else {
        lineProb = search->second;
      }

      for (unsigned int m = 0; m < result[m].size()-1; m++) {
        float probValue2;
        auto search = probMap.find(j+result[i][m]);
        if (search == probMap.end()) {

          float probValue = occur(result,j,result[i][m],m);
          float totalValue = total(result,result[i][m],m);
          probValue2 = probValue/totalValue;
          probMap.emplace(j+result[i][m], probValue2);
          //std::cout << "Value for " << j+result[i][m] << " is " << probValue2 << std::endl;

        } else {
          probValue2 = search->second;
        }

        lineProb *= probValue2;

      }
      if (lineProb >  predictionProb) {
        predictionProb = lineProb;
        predictionClassifier = j;
      }
    }

    totalGuess++;

    if (predictionClassifier == result[i][result[i].size()-1]) {
      totalCorrect++;
    }
    //std::cout << "Prediction for line " << i << " is classifier " << predictionClassifier << " with prob of " << predictionProb;
    //std::cout << " actual is " << result[i][result[i].size()-1] << std::endl;
    //std::cout << "Current percent of correct guesses " << totalCorrect/totalGuess << std::endl;
  }
  return totalCorrect/totalGuess;
}

int main() {

  std::vector<std::string> dataSets = {"data0.txt","24242.txt","data1.txt", "data2.txt", "data3.txt","classdata.txt"};


  for (auto i: dataSets) {

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> test = readFile(i);

    if (test.empty()) {
      std::cout << "File " << i << " not read correctly, not processing" << std::endl;
    } else {
      auto result = parseData(test);
      auto values = uniqueValues(result);
      float correct = bayesClassifier(result,values);


      auto end = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_seconds = end-start;
      std::cout << i << ": Percentage correct " << correct << ", Time taken " << elapsed_seconds.count() << std::endl;
      probMap.clear();
    }
  }
}
