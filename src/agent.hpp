#pragma once
#include <vector>
#include <random>

#include "struct.hpp"

class agent{

private:
  double alpha;
  double gamma;

  std::random_device rd;
  std::mt19937 gen;

  int n_states;
  int n_actions;
  int batch_counter;

  std::vector<std::vector<double>> theta;
  std::vector<std::vector<double>> cumulative_gradient;


  std::vector<double> softmax(coordinates& state, std::vector<std::vector<double>> theta);

  int state_to_index(coordinates& state);
  
  std::vector<omega_i> memory;

public:
  agent(double alpha, double gamma);

  int chooseAction(coordinates& state);

  void storeStep(coordinates& state, int action, double reward);

  //void updatePolicy();
  void accumulate_gradients();
  void apply_batch_update(int batchSize);

};
