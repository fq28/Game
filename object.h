#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>

void CreateRectangleObject(sf::Vector2f scale, sf::Color color, sf::Vector2f startPos, std::vector<sf::RectangleShape> &obstacles);
void CreateCircleObject(sf::Vector2f scale, sf::Color color, sf::Vector2f startPos,float radius, std::vector<sf::CircleShape> &obstacles)
;
void CheckCollision(sf::RectangleShape &player, std::vector<sf::RectangleShape> &obstacles, float &moveDirectionX, float &moveDirectionY, bool isMoving,
                    std::vector<float> wallSpeeds,  bool isGoingBackInTime, std::vector<int> oneWayDoorDirection);
#endif // OBJECT_H
