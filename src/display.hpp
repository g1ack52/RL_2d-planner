#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

class display{
private:

public:
    int GRID_COLS;
    int GRID_ROWS;
    float CELL_SIZE;

    display();
    ~display() = default;

    bool isOpen();
    void handleEvents();
    void clear();
    void display();

    void drawGrid();

};
