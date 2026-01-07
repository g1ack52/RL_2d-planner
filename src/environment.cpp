#include <vector>
#include <iostream>
#include "environment.hpp"

environment::environment(){
  u_map_limit = {9, 4}; 
  l_map_limit = {0, 0};
  goal1 = {9, 1};
  goal2 = {9, 3};
  obstacles = {
  // 0  1  2  3  4  5  6  7  8  9    z/y
    {0, 0, 0, 1, 0, 1, 0, 1, 0, 1}, // 0
    {0, 1, 0, 0, 0, 0, 1, 0, 0, 0}, // 1 
    {0, 0, 1, 0, 1, 0, 0, 1, 1, 1}, // 2
    {0, 1, 0, 1, 0, 1, 0, 1, 1, 0}, // 3
    {0, 0, 0, 0, 1, 0, 1, 0, 0, 1}, // 4
  }; 
  gameStatus = true;
}

 

bool environment::isGoal(coordinates &state){
  return ((state.z == goal1.z && state.y == goal1.y) || (state.z == goal2.z && state.y == goal2.y));
}

bool environment::isValid(coordinates &state){
  return (state.y <= u_map_limit.y && state.y >= l_map_limit.y && state.z <= u_map_limit.z && state.z >= l_map_limit.z);
}

bool environment::isObstacles(coordinates &state){
  return (obstacles[state.y][state.z]);
}

double environment::getReward(coordinates &state, int action){
  double reward = 0.0;
  if(!isValid(state)){
    //std::cout << "Fuori mappa" << std::endl; 
    reward = -100.0;
    return reward;
  }
  if(isGoal(state)){
    //std::cout << "Goal Raggiunto" << std::endl;
    reward = 100.0;
    return reward;
  }
  if(isObstacles(state)){
    //std::cout << "ostacolo" << std::endl;
    reward += -80.0;
  } 
  if(action != 1){
    //std::cout << "movimento lungo y" << std::endl;
    reward += -30.0;
  }
  reward += -1;
  return reward;
}

coordinates environment::reset(){
  coordinates starting_state;
  do{
    starting_state.z = rand() % u_map_limit.z;
    starting_state.y = rand() % (u_map_limit.y + 1);
  }while(isObstacles(starting_state));
  return starting_state;
}


void environment::gameOff(){
  gameStatus = false;
}

void environment::gameOn(){
  gameStatus = true;
}

bool environment::isGameOn(){
  return gameStatus;
}














