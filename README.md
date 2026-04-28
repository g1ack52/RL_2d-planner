# Reinforcement Learning Robot Path Planning

Project developed in **C++** with a graphical interface built using **SFML**.

## Description

This project simulates a robot moving on a two-dimensional grid with obstacles.  
The goal is to reach one of the desired final positions while avoiding obstacle cells as much as possible and minimizing unnecessary vertical movements.

The problem is modeled as a **Markov Decision Process (MDP)** and solved using **Policy Gradient** algorithms, comparing a basic version with a stochastic version. The project also includes the visualization of the robot trajectories and the probabilities associated with the selected actions.

## Stack

- C++
- SFML
- Reinforcement Learning
- Policy Gradient

## Features

- Robot movement simulation on a grid
- Obstacle handling and penalty system
- Basic Policy Gradient implementation
- Stochastic Policy Gradient implementation
- Graphical visualization using SFML
- Trajectory and reward analysis

