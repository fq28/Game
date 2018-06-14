#include <SFML/Graphics.hpp>
#include "iostream"
#include <algorithm>
#include "object.h"
#include "player.h"

void CreateCircleObject(sf::Vector2f scale, sf::Color color, sf::Vector2f startPos,float radius, std::vector<sf::CircleShape> &obstacles)
{
    //sf::Vector2f shape(100,100);
    sf::CircleShape obstacle;;
    obstacle.setScale(scale);
    obstacle.setFillColor(color);
    obstacle.setPosition(startPos);
    obstacle.setRadius(radius);
    obstacles.push_back(obstacle);
}
void CreateRectangleObject(sf::Vector2f scale, sf::Color color, sf::Vector2f startPos, std::vector<sf::RectangleShape> &obstacles)
{
    sf::Vector2f shape(100,100);
    sf::RectangleShape obstacle(shape);
    obstacle.setScale(scale);
    obstacle.setFillColor(color);
    obstacle.setPosition(startPos);
    obstacles.push_back(obstacle);
}

void CheckCollision(sf::RectangleShape &player, std::vector<sf::RectangleShape> &obstacles, float &moveDirectionX, float &moveDirectionY, bool isMoving,
                    std::vector<float> wallSpeeds, bool isGoingBackInTime, std::vector<int> oneWayDoorDirection)
{
   sf::Vector2f playerPos = player.getPosition();
   for(unsigned i = 0; i < obstacles.size(); ++i)
   {

       sf::Vector2f objectPos = obstacles[i].getPosition();
       if(playerPos != objectPos)
       {
           float deltaX = playerPos.x - objectPos.x;
           float deltaY = playerPos.y - objectPos.y;
           float rangeX = obstacles[i].getScale().x * 100;
           float rangeY = obstacles[i].getScale().y * 100;
           sf::Vector2f objectScale = obstacles[i].getScale();

           //object on the left side of the player
           if(deltaX <= rangeX && deltaX >= 0 && oneWayDoorDirection[i] != 0)
           {
               if((deltaY <= rangeY - objectScale.y * 3 && deltaY >= 0) || (deltaY >= -rangeY/objectScale.y + objectScale.x * 3 && deltaY < 0))
               {
                   if(moveDirectionX < 0)
                   moveDirectionX = 0;
                   if(isMoving)
                   {
                       moveDirectionX = 1 * (wallSpeeds[i] / 5);
                       std::cout<<"dX: "<<deltaX;

                        if(deltaX < 10 && deltaX > 0 && !isGoingBackInTime)
                        {
                            PlayerDie(player);
                        }
                   }
               }
           }
           //object to the right of the player
           if(deltaX >= -rangeX/objectScale.x && deltaX < 0 && oneWayDoorDirection[i] != 1)
           {
               if((deltaY <= rangeY - objectScale.y * 3 && deltaY >= 0) || (deltaY >= -rangeY/objectScale.y + objectScale.x * 3 && deltaY < 0))
               {
                   if(moveDirectionX > 0)
                   moveDirectionX = 0;
                   if(isMoving)
                   {
                       moveDirectionX = -1 * (wallSpeeds[i] / 5);
                       std::cout<<"dX: "<<deltaX;
                       if(deltaX < 10 && deltaX > 0 && !isGoingBackInTime)
                       {
                           PlayerDie(player);
                       }
                   }
               }
           }
           //object above the player
           if(deltaY <= rangeY && deltaY >= 0 && oneWayDoorDirection[i] != 3)
           {
               if((deltaX <= rangeX - objectScale.x * 3 && deltaX >= 0) || (deltaX >= -rangeX/objectScale.x + objectScale.x * 3 && deltaX < 0))
               {
                   if(moveDirectionY < 0)
                   moveDirectionY = 0;
                   if(isMoving)
                   {
                       moveDirectionY = 1 * (wallSpeeds[i] / 5);
                       if(deltaY < 10 && deltaY > 0 && !isGoingBackInTime)
                       {
                         PlayerDie(player);
                       }
                   }
               }
           }
           //object under the player
           if(deltaY >= -rangeY/objectScale.y && deltaY < 0 && oneWayDoorDirection[i] != 2)
           {
               if((deltaX <= rangeX - objectScale.x * 3 && deltaX >= 0) || (deltaX >= -rangeX/objectScale.x + objectScale.x * 3 && deltaX < 0))
               {
                   if(moveDirectionY > 0)
                   moveDirectionY = 0;
                   if(isMoving)
                   {
                       moveDirectionY = -1  * (wallSpeeds[i] / 5);
                       if(deltaY < 10 && deltaY > 0 && !isGoingBackInTime)
                       {
                         PlayerDie(player);
                       }
                   }
               }
           }
       }
   }
}
