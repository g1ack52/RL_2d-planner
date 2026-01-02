#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "agent.hpp"

agent::agent(double alpha, double gamma){
  this->alpha = alpha;
  this->gamma = gamma;

  n_actions = 3;
  n_states = 50;

  gen.seed(rd());
  
  theta.resize(n_states, std::vector<double>(n_actions, 0.0)); 
  cumulative_gradient.resize(n_states, std::vector<double>(n_actions, 0.0)); 

}


int agent::state_to_index(coordinates& state){
  return (state.y*10 + state.z);
}


std::vector<double> agent::softmax(coordinates& state, std::vector<std::vector<double>> theta){
  int index = state_to_index(state);
  std::vector<double> theta_i = theta[index];
  std::vector<double> probabilities;

  float max_val = *std::max_element(theta_i.begin(), theta_i.end());
  double sum = 0.0;
  for(int j=0; j<theta_i.size(); j++){
    double res = exp(theta_i[j] - max_val);
    probabilities.push_back(res);
    sum += res;
  }
  for(int j=0; j<theta_i.size(); j++){
    probabilities[j] /= sum;
  }
  return probabilities; 
}


int agent::chooseAction(coordinates& state){
  std::vector<double> probabilities = softmax(state, this->theta);
  std::discrete_distribution<> d(probabilities.begin(), probabilities.end());
  int action = d(gen);
  return action;
}


void agent::storeStep(coordinates& state, int action, double reward){
  omega_i episode;
  episode.current_state = state;
  episode.performed_action = action;
  episode.obtained_reward = reward; 
  memory.push_back(episode);
}

/*
void agent::updatePolicy(){
  double G_t = 0.0;
  for(int t = memory.size()-1; t>=0; t--){
    double reward_t = memory[t].obtained_reward;
    coordinates state_t = memory[t].current_state;
    int action_t = memory[t].performed_action;
    const std::vector<std::vector<double>> theta_old = theta;

    G_t = reward_t + G_t*gamma;

    std::vector<double> prob = softmax(state_t, theta_old);
    
    for(int k = 0; k<n_actions; k++){
      double d_gradient;
      if(k == action_t) d_gradient = 1.0 - prob[k];
      else d_gradient = - prob[k];

      theta[state_to_index(state_t)][k] += alpha * d_gradient * G_t;
    }
    memory.clear();
  }
}
*/

void agent::accumulate_gradients(){
  double G_t = 0.0;
  for(int t = memory.size()-1; t>=0; t--){
    double reward_t = memory[t].obtained_reward;
    coordinates state_t = memory[t].current_state;
    int action_t = memory[t].performed_action;
    const std::vector<std::vector<double>> theta_old = theta;

    G_t = reward_t + G_t*gamma;

    std::vector<double> prob = softmax(state_t, theta_old);
    
    for(int k = 0; k<n_actions; k++){
      double d_gradient;
      if(k == action_t) d_gradient = 1.0 - prob[k];
      else d_gradient = - prob[k];

      cumulative_gradient[state_to_index(state_t)][k] += d_gradient * G_t;
    }
  }
 
  memory.clear();
}


void agent::apply_batch_update(int batchSize){
  for(int i=0; i < n_states; i++){
    for(int j=0; j < n_actions; j++){
      theta[i][j] += (alpha / batchSize) * cumulative_gradient[i][j];
      cumulative_gradient[i][j] = 0;
    }
  } 
}

