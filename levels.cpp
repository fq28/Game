#include "levels.h"
#include <SFML/Graphics.hpp>
#include "iostream"
#include "object.h"
#include "enemy.h"
void LoadNextLevel(int level, std::vector<sf::RectangleShape> &obstacles,  std::vector<sf::RectangleShape> &buttons, std::vector<sf::RectangleShape> &doors
                   , std::vector<sf::RectangleShape> &goals, std::vector<sf::RectangleShape> &traps, std::vector<sf::RectangleShape> &movingWalls, std::vector<sf::Vector2f> &wallDirection,
                   std::vector<bool> &wallsMoving, std::vector<float> &wallSpeeds, std::vector<bool> &lockedIn, std::vector<sf::Vector2f> &enemysTargetPos,
                   std::vector<sf::Vector2f> &enemysNormalPos, std::vector<float> &radius, std::vector<sf::Vector2f> &middle, std::vector<float> &length,
                        std::vector<sf::RectangleShape> &enemys)
{
    if(level == 2)
    {
        GenerateLevel2(obstacles, buttons, doors, goals, traps, movingWalls, wallDirection, wallsMoving, wallSpeeds, lockedIn, enemysTargetPos, enemysNormalPos
                       , radius, middle, length, enemys);
    }
}

void GenerateLevel1(std::vector<sf::RectangleShape> &obstacles,  std::vector<sf::RectangleShape> &buttons, std::vector<sf::RectangleShape> &doors
               , std::vector<sf::RectangleShape> &goals, std::vector<sf::RectangleShape> &traps, std::vector<sf::RectangleShape> &movingWalls, std::vector<sf::Vector2f> &wallDirection,
               std::vector<bool> &wallsMoving, std::vector<float> &wallSpeeds, std::vector<bool> &lockedIn, std::vector<sf::Vector2f> &enemysTargetPos,
               std::vector<sf::Vector2f> &enemysNormalPos, std::vector<float> &radius, std::vector<sf::Vector2f> &middle, std::vector<float> &length,
                    std::vector<sf::RectangleShape> &enemys)
{
    CreateRectangleObject(sf::Vector2f(1,3), sf::Color().Yellow,sf::Vector2f(-500,-100),doors);
    CreateRectangleObject(sf::Vector2f(1,1), sf::Color().Green,sf::Vector2f(1300,0),buttons);
    CreateRectangleObject(sf::Vector2f(20,1), sf::Color(150,150,150),sf::Vector2f(-500,-200),obstacles);
    CreateRectangleObject(sf::Vector2f(20,1), sf::Color(150,150,150),sf::Vector2f(-500,200),obstacles);
    CreateRectangleObject(sf::Vector2f(1,3), sf::Color(150,150,150),sf::Vector2f(1400,-100),obstacles);
    CreateRectangleObject(sf::Vector2f(1,3), sf::Color(20,20,20),sf::Vector2f(300,-100),traps);
    CreateRectangleObject(sf::Vector2f(0,0), sf::Color().Red,sf::Vector2f(-400,-100),movingWalls);
    CreateRectangleObject(sf::Vector2f(1,1), sf::Color().Red,sf::Vector2f(-400,0),enemys);
    lockedIn.push_back(false);
    enemysTargetPos.push_back(sf::Vector2f(0,0));
    enemysNormalPos.push_back(sf::Vector2f(0,0));
    radius.push_back(0);
    middle.push_back(sf::Vector2f(0,0));
    length.push_back(0);
    wallDirection.push_back(sf::Vector2f(1,0));
    wallsMoving.push_back(false);
    wallSpeeds.push_back(3.f);

    CreateRectangleObject(sf::Vector2f(1,3), sf::Color().Cyan,sf::Vector2f(-600,-100),goals);

}
void DestroyLevelObjects(std::vector<sf::RectangleShape> &obstacles,  std::vector<sf::RectangleShape> &buttons, std::vector<sf::RectangleShape> &doors
               , std::vector<sf::RectangleShape> &traps, std::vector<sf::RectangleShape> &movingWalls, std::vector<sf::Vector2f> &wallDirection,
               std::vector<bool> &wallsMoving, std::vector<float> &wallSpeeds, std::vector<bool> &lockedIn, std::vector<sf::Vector2f> &enemysTargetPos,
               std::vector<sf::Vector2f> &enemysNormalPos, std::vector<float> &radius, std::vector<sf::Vector2f> &middle, std::vector<float> &length,
                    std::vector<sf::RectangleShape> &enemys, std::vector<sf::RectangleShape> &goals)
{
    obstacles.clear();
    buttons.clear();
    doors.clear();
    traps.clear();
    movingWalls.clear();
    wallDirection.clear();
    wallsMoving.clear();
    wallSpeeds.clear();
    lockedIn.clear();
    enemysTargetPos.clear();
    enemysNormalPos.clear();
    radius.clear();
    middle.clear();
    enemys.clear();
    length.clear();
    goals.clear();
}
void GenerateLevel2(std::vector<sf::RectangleShape> &obstacles,  std::vector<sf::RectangleShape> &buttons, std::vector<sf::RectangleShape> &doors
               , std::vector<sf::RectangleShape> &goals, std::vector<sf::RectangleShape> &traps, std::vector<sf::RectangleShape> &movingWalls, std::vector<sf::Vector2f> &wallDirection,
               std::vector<bool> &wallsMoving, std::vector<float> &wallSpeeds, std::vector<bool> &lockedIn, std::vector<sf::Vector2f> &enemysTargetPos,
               std::vector<sf::Vector2f> &enemysNormalPos, std::vector<float> &radius, std::vector<sf::Vector2f> &middle, std::vector<float> &length,
                    std::vector<sf::RectangleShape> &enemys)
{
    CreateRectangleObject(sf::Vector2f(1,3), sf::Color().Yellow,sf::Vector2f(-500,-100),doors);
    CreateRectangleObject(sf::Vector2f(1,1), sf::Color().Green,sf::Vector2f(1300,0),buttons);
    CreateRectangleObject(sf::Vector2f(20,1), sf::Color(150,150,150),sf::Vector2f(-500,-400),obstacles);
    CreateRectangleObject(sf::Vector2f(20,1), sf::Color(150,150,150),sf::Vector2f(-500,400),obstacles);
    CreateRectangleObject(sf::Vector2f(1,3), sf::Color(150,150,150),sf::Vector2f(1400,-100),obstacles);
    //CreateRectangleObject(sf::Vector2f(1,3), sf::Color(20,20,20),sf::Vector2f(300,-100),traps);
    //CreateRectangleObject(sf::Vector2f(0,0), sf::Color().Red,sf::Vector2f(-400,-100),movingWalls);
    CreateEnemy(sf::Vector2f(1,1), sf::Color().Red, sf::Vector2f(-400,0), enemys, lockedIn, enemysTargetPos,
                enemysNormalPos, radius, middle, length);
    CreateEnemy(sf::Vector2f(1,1), sf::Color().Red, sf::Vector2f(400,0), enemys, lockedIn, enemysTargetPos,
                enemysNormalPos, radius, middle, length);

    wallDirection.push_back(sf::Vector2f(1,0));
    wallsMoving.push_back(false);
    wallSpeeds.push_back(3.f);

    CreateRectangleObject(sf::Vector2f(1,3), sf::Color().Cyan,sf::Vector2f(-600,-100),goals);

}
levels::levels()
{

}
