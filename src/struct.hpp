#pragma once

struct coordinates{
  int z;
  int y;
};

struct omega_i{
  coordinates current_state;
  int performed_action;
  double obtained_reward;
};


