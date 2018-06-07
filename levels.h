#ifndef LEVELS_H
#define LEVELS_H
#include <SFML/Graphics.hpp>
#include "iostream"
#include "object.h"

class levels
{
public:
    levels();
};
void LoadNextLevel(int level, std::vector<sf::RectangleShape> &obstacles,  std::vector<sf::RectangleShape> &buttons, std::vector<sf::RectangleShape> &doors
                   , std::vector<sf::RectangleShape> &goals, std::vector<sf::RectangleShape> &traps, std::vector<sf::RectangleShape> &movingWalls, std::vector<sf::Vector2f> &wallDirection,
                   std::vector<bool> &wallsMoving, std::vector<float> &wallSpeeds, std::vector<bool> &lockedIn, std::vector<sf::Vector2f> &enemysTargetPos,
                   std::vector<sf::Vector2f> &enemysNormalPos, std::vector<float> &radius, std::vector<sf::Vector2f> &middle, std::vector<float> &length,
                        std::vector<sf::RectangleShape> &enemys);

void GenerateLevel1(std::vector<sf::RectangleShape> &obstacles,  std::vector<sf::RectangleShape> &buttons, std::vector<sf::RectangleShape> &doors
               , std::vector<sf::RectangleShape> &goals, std::vector<sf::RectangleShape> &traps, std::vector<sf::RectangleShape> &movingWalls, std::vector<sf::Vector2f> &wallDirection,
               std::vector<bool> &wallsMoving, std::vector<float> &wallSpeeds, std::vector<bool> &lockedIn, std::vector<sf::Vector2f> &enemysTargetPos,
               std::vector<sf::Vector2f> &enemysNormalPos, std::vector<float> &radius, std::vector<sf::Vector2f> &middle, std::vector<float> &length,
                    std::vector<sf::RectangleShape> &enemys);
void GenerateLevel2(std::vector<sf::RectangleShape> &obstacles,  std::vector<sf::RectangleShape> &buttons, std::vector<sf::RectangleShape> &doors
               , std::vector<sf::RectangleShape> &goals, std::vector<sf::RectangleShape> &traps, std::vector<sf::RectangleShape> &movingWalls, std::vector<sf::Vector2f> &wallDirection,
               std::vector<bool> &wallsMoving, std::vector<float> &wallSpeeds, std::vector<bool> &lockedIn, std::vector<sf::Vector2f> &enemysTargetPos,
               std::vector<sf::Vector2f> &enemysNormalPos, std::vector<float> &radius, std::vector<sf::Vector2f> &middle, std::vector<float> &length,
                    std::vector<sf::RectangleShape> &enemys);

void DestroyLevelObjects(std::vector<sf::RectangleShape> &obstacles,  std::vector<sf::RectangleShape> &buttons, std::vector<sf::RectangleShape> &doors
               , std::vector<sf::RectangleShape> &traps, std::vector<sf::RectangleShape> &movingWalls, std::vector<sf::Vector2f> &wallDirection,
               std::vector<bool> &wallsMoving, std::vector<float> &wallSpeeds, std::vector<bool> &lockedIn, std::vector<sf::Vector2f> &enemysTargetPos,
               std::vector<sf::Vector2f> &enemysNormalPos, std::vector<float> &radius, std::vector<sf::Vector2f> &middle, std::vector<float> &length,
                    std::vector<sf::RectangleShape> &enemys, std::vector<sf::RectangleShape> &goals);

#endif // LEVELS_H
