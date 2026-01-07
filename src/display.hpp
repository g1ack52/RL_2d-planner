#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <utility>
#include <optional>
#include "struct.hpp"
#include "environment.hpp"

class display{
private:
    sf::RenderWindow gui;
    
    std::vector<double> mapToScreen (coordinates state);

    void grid(environment& env);
    void draw_agent(coordinates& state);

public:
    int columns;   
    int rows;
    float cellSize;

    display();
    ~display() = default;

    bool isOpen();
    bool handleEvents();

    void render(environment& env, coordinates& state);


};
