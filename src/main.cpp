#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
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

  sf::Window window(sf::VideoMode({800, 600}), "MDP");

  while(window.isOpen()){
    while(const std::optional event = window.pollEvent()){
      if(event->is<sf::Event::Closed>()) window.close();
    }
  }
  
  window.display();

  return 0;
}

