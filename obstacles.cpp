#include "obstacles.h"
#include <SFML/Graphics.hpp>
//#include "object.h"

Obstacles::Obstacles()
{
    class OneWayDoor
    {
        sf::Vector2f scale;
        sf::Color color;
        sf::Vector2f position;
        int wayOpen;
        std::vector<sf::RectangleShape> oneWayDoors;



    public:
        OneWayDoor() {
            void CreateOneWayDoor(sf::Vector2f, sf::Color, sf::Vector2f, int, std::vector<sf::RectangleShape>);

        }
    };

}
void CreateOneWayDoor(sf::Vector2f scale,sf::Color color, sf::Vector2f position,int wayOpen,
                       std::vector<sf::RectangleShape> oneWayDoors)
{
    CreateRectangleObject(scale,color,position, oneWayDoors);

}

