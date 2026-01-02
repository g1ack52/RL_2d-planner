#pragma once  
#include <vector>
#include "struct.hpp"


class environment {

private:

  coordinates u_map_limit;
  coordinates l_map_limit; 
  coordinates goal1;
  coordinates goal2;

  std::vector<std::vector<bool>> obstacles;
  
  bool gameStatus;

public:

  environment();
  
  bool isValid(coordinates &state);  
  bool isObstacles(coordinates &state);
  bool isGoal(coordinates &state);
  double getReward(coordinates &state, int action);
  coordinates reset();
  
  void gameOn();
  void gameOff();
  bool isGameOn();
};
