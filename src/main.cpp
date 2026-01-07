#include <optional>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <string>
#include <fstream>

#include "struct.hpp"
#include "environment.hpp"
#include "agent.hpp"
#include "display.hpp"

int main(int argc, char* argv[]){
  if(argc != 5){
    std::cout << "usage error" << std::endl;
    std::cout << argv[0] << " <alpha> <gamma> <m_updates> <batchSize>" << std::endl;
    return 1;
  }
  double alpha = std::stod(argv[1]);
  double gamma = std::stod(argv[2]);
  int m_updates = std::stod(argv[3]);
  int batchSize = std::stod(argv[4]);
  /*
  double alpha = 0.1;
  double gamma = 0.99;
  int m_updates = 10000;  
  int batchSize = 1;
  int n_episodes = m_updates * batchSize;
  */
 
  environment env;
  agent robot(alpha, gamma);

  std::ofstream Datafile("result.csv");
  Datafile << "update,avg_reward" << std::endl;
  

  for(int ep = 0; ep < m_updates; ep++){
    double batch_rewards = 0.0;

    for(int b = 0; b < batchSize; b++){
      double episode_rewards = 0.0;
      coordinates current_state = env.reset();
      
      env.gameOn();

      while(env.isGameOn()){
      //env.isValid(current_state) || env.isGoal(current_state)
        
        int action = robot.chooseAction(current_state);
        
        coordinates next_state;
        next_state.z = current_state.z + 1;
        next_state.y = current_state.y + action - 1;
        
        double reward = env.getReward(next_state, action);
        episode_rewards += reward;
        
        robot.storeStep(current_state, action, reward);
     
        current_state = next_state;

        if(!env.isValid(current_state) || env.isGoal(current_state)) env.gameOff();
      }

      batch_rewards += episode_rewards;
      //robot.updatePolicy(); 
      robot.accumulate_gradients();
    }

    Datafile << ep << "," << (batch_rewards / batchSize) << std::endl; 
    robot.apply_batch_update(batchSize);
  }

  Datafile.close();

  display gui;

  sf::Clock clock;
  float accumulator = 0.0f;
  const float stepTime = 1.0f;

  //std::vector<coordinates> initial_conditions = { {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}};

  env.gameOn();
  
  coordinates state = {0, 2};

  while(gui.isOpen() && env.isGameOn()){
    sf::Time dt = clock.restart();
    accumulator += dt.asSeconds(); 

    if(!gui.handleEvents()) break;

    if(accumulator >= stepTime){
        
      int action = robot.chooseAction(state);
  
      coordinates next_state;
      next_state.z = state.z + 1;
      next_state.y = state.y + action - 1;
        
      state = next_state;

      if(!env.isValid(state)) env.gameOff();
      
      accumulator = 0.0f;
    }

    gui.render(env, state);

    if(env.isGoal(state)) state = env.reset();
  }

  return 0;
}

