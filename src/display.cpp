#include "display.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

display::display(){
    columns = 10;
    rows = 5;
    cellSize = 80.0f;

    gui.create(sf::VideoMode({
        (unsigned int)(columns*cellSize),
        (unsigned int)(rows*cellSize)
    }), "MDP");

    gui.setFramerateLimit(60);
}   

bool display::isOpen(){
    return gui.isOpen();
}

bool display::handleEvents(){
    while(const std::optional event = gui.pollEvent()){
      if(event->is<sf::Event::Closed>()) {
        gui.close();
        return false;
        } 
    }
    return true;
}


void display::grid(environment& env){

    coordinates current_cell;

    sf::RectangleShape cell({cellSize, cellSize});


    cell.setOutlineColor(sf::Color::Black);
    cell.setOutlineThickness(-1.0f);
    
    for(int r=0; r < rows; r++){
        for(int c=0; c < columns; c++){
            current_cell.y = rows - 1 - r;
            current_cell.z = c;
            cell.setPosition({c * cellSize, r * cellSize});
            
            if(env.isObstacles(current_cell)){
                cell.setFillColor(sf::Color(255, 97, 97));
            }
            else if(env.isGoal(current_cell)){
                cell.setFillColor(sf::Color(251, 255, 120));
            }
            else{
                cell.setFillColor(sf::Color(148, 255, 153));
            }
            
            gui.draw(cell);
        }
    }

}

void display::draw_agent(coordinates& state){
    float padding = cellSize * 0.15f;
    float radius = (cellSize / 2.0f) - padding;

    sf::CircleShape robot(radius);

    robot.setFillColor(sf::Color(77, 96, 255));
    robot.setOutlineThickness(2.0f);

    robot.setOrigin({radius, radius});

    float screenZ = state.z * cellSize + (cellSize / 2.0f);
    float screenY = (rows - 1 - state.y) * cellSize + (cellSize / 2.0f);

    robot.setPosition({screenZ, screenY});

    gui.draw(robot);
}   

void display::render(environment& env, coordinates& state){
    gui.display();  
    grid(env);
    draw_agent(state);
    gui.display();
}
