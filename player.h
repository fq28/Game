#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "iostream"
#include "player.h"


class player
{
public:
    player();
};

void MovePlayer(sf::Shape &player, sf::Vector2f &playerPos, const float moveSpeed, sf::Vector2f direction);
void MovePlayerBackInTime(sf::Shape &player, const std::vector<sf::Vector2f> pastPlayerPos, sf::Vector2f &playerPos, const int iteration);
void CheckInput(float &moveDirectionX, float &moveDirectionY, bool &spaceButtonPressed,bool &eButtonPressed, std::vector<sf::Vector2f> &pastPlayerPos,
                sf::Shape &player);
bool InRange(sf::Vector2f &playerPos, sf::RectangleShape shape);
void PlayerDie(sf::RectangleShape &player);
void MoveView(sf::View &view, sf::Vector2f &playerPos, sf::Time deltaTime);




#endif // PLAYER_H
