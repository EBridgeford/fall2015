/*
Eric Bridgeford
CSE 486 Fall 2015
HW1
Compiles on ceclnx01
g++ -std=c++11 -g -o2 vacuum.cpp -o vacuum.o
*/
#include <iostream>
#include <random>

// Function prototypes so the compiler would stop complaining
bool chanceOfHappening(double n);
int calculateScore(bool dirty[]);
int action(bool dirty[], int runs, double S, double P);

// Pass in probability of event happening n. If the number 0-1 generated is
// less than n it returns false. If you pass in .25 the number generated will
// only be less than .25 1/4th of the time.

bool chanceOfHappening(double n) {
  std::random_device rd;
  std::minstd_rand gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  if (n >= dis(gen))
    return true;
  else
    return false;
}

// Calculates the score by summing the number of clean tiles

int calculateScore(bool dirty[]) {
  int score = 0;
  for (int i = 0; i < 4; i++) {
    if (dirty[i] == false) {
      score++;
    }
  }
  return score;
}

// Moves the 'agent' across the tiles one at a time. The main chunk of this is
// in the if/else statement where it can apply suction OR move. The suction has
// S chance of failing. And after each step each tile has D chance of getting
// dirt on it.

// The movement step is done incrementing or decrementing the loc(ation) int.
// It is controlled by the leftToRight bool. When it is true it is incremented,
// when false is decremented. When loc has an illegal value either 4 or -1, the
// bool is flipped and loc has 2 either added or subtracted from it. This lets
// the agent ping back and forth across the array.

int action(bool dirty[], int runs, double S, double D) {
  bool leftToRight = true;
  int score = 0;
  int loc = 0;

  for (int i = 0; i < runs; i++) {
      for (int m = 0; m < 4; m++) {
        if (dirty[m] == false) {
          if (chanceOfHappening(D) == true) {
            dirty[m] = true;
          }
        }
      }

      if (dirty[loc] == true) {
        if (chanceOfHappening(S) == true) {
        dirty[loc] = false;
        }
      } else {
        if (leftToRight == true)
          loc++;
        else
          loc--;

        score += calculateScore(dirty);

        if (loc == 4 || loc == -1) {
          leftToRight = !leftToRight;
            if (loc == 4)
              loc = loc - 2;
            if (loc == -1)
              loc = loc + 2;
            }
          }
        }
return score;
}
int main(int argc, char* argv[]) {
  // std::array<char, 4> squares = {'A', 'B', 'C', 'D'};
  bool dirty[4] = {false, false, false, false};

  int score = 0;

  if (argc == 3) {
  double S = atof(argv[1]);
  double D = atof(argv[2]);
  score = action(dirty, 10000, S, D);
  std ::cout << "Score: " << score << std::endl;
} else {
      std::cout << "Incorrect arguements entered" << std::endl;
    }
  }
