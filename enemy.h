#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "iostream"

class Enemy
{
public:
    Enemy();
};
void CreateEnemy(sf::Vector2f scale, sf::Color color, sf::Vector2f startPos, std::vector<sf::RectangleShape> &enemys,
                 std::vector<bool> &lockedIn, std::vector<sf::Vector2f> &enemysTargetPos,
                 std::vector<sf::Vector2f> &enemysNormalPos, std::vector<float> &radius,
                 std::vector<sf::Vector2f> &middle, std::vector<float> &length);

void MoveEnemys(std::vector<sf::RectangleShape> &enemys, sf::Shape &player, std::vector<sf::RectangleShape> & obstacles
                , std::vector<bool> &lockedIn, std::vector<std::vector<sf::RectangleShape>> &enemysShootAgents, std::vector<sf::RectangleShape> &doors
                , std::vector<sf::RectangleShape> &movingWalls, std::vector<std::vector<sf::Vector2f>> &enemysShootAgentsTargetPositions,
                std::vector<sf::Vector2f> &enemysTargetPos,  std::vector<sf::Vector2f> &enemysNormalPos, std::vector<sf::CircleShape> &circles
                , std::vector<float> &radius, sf::Time elasped, std::vector<sf::Vector2f> &middle, std::vector<float> &length);

std::vector<sf::Vector2f> EnemyShootAgentsTargetPositions(sf::Vector2f &playerPos, std::vector<sf::RectangleShape> &obstacles
                                                          , std::vector<sf::RectangleShape> &movingWalls, std::vector<sf::RectangleShape> &doors
                                                          , std::vector<sf::RectangleShape> &enemyShootAgents, std::vector<sf::RectangleShape> &enemys);
std::vector<sf::RectangleShape> EnemyShootAgents(sf::RectangleShape &enemy, float deltaAgent);
bool DoesCollide(sf::Vector2f pos, std::vector<sf::RectangleShape> &obstacles)
;

#endif // ENEMY_H
