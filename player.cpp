#include "player.h"
#include <SFML/Graphics.hpp>
#include "iostream"
#include "object.h"

player::player()
{

}
sf::Vector2f Lerp(sf::Vector2f start, sf::Vector2f end, float percent)
{
    return (start + percent*(end-start));
}
void MoveView(sf::View &view, sf::Vector2f &playerPos, sf::Time deltaTime)
{
    float speed = 3;
    sf::Vector2f targetViewPos = playerPos;
    sf::Vector2f viewPos = view.getCenter();
    view.setCenter(Lerp(viewPos,targetViewPos, deltaTime.asSeconds() * speed));
}


bool InRange(sf::Vector2f &playerPos, sf::RectangleShape shape)
{
    float rangeX = shape.getScale().x * 110;
    float rangeY = shape.getScale().y * 110;
    float deltaX = std::abs(playerPos.x - shape.getPosition().x);
    float deltaY = std::abs(playerPos.y - shape.getPosition().y);
    if(deltaX < rangeX && deltaY < rangeY)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void MovePlayer(sf::Shape &player, sf::Vector2f &playerPos, const float moveSpeed, sf::Vector2f direction)
{
    playerPos.x = playerPos.x + direction.x * moveSpeed;
    playerPos.y = playerPos.y + direction.y * moveSpeed;
    player.setPosition(playerPos);
}
void MovePlayerBackInTime(sf::Shape &player, const std::vector<sf::Vector2f> pastPlayerPos, sf::Vector2f &playerPos, const int iteration)
{
    playerPos = pastPlayerPos[iteration];
    player.setPosition(playerPos);
}


void CheckInput(float &moveDirectionX, float &moveDirectionY, bool &spaceButtonPressed,bool &eButtonPressed, std::vector<sf::Vector2f> &pastPlayerPos,
                sf::Shape &player)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
          moveDirectionX = -1.f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        moveDirectionX = 1.f;

    }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        moveDirectionX = 0.f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        moveDirectionY = -1.f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        moveDirectionY = 1.f;
    }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        moveDirectionY = 0.f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && pastPlayerPos.size() > 1)
    {
        if(!spaceButtonPressed)
        {

                  std::reverse(pastPlayerPos.begin(), pastPlayerPos.end());
                player.setFillColor(sf::Color(92, 140, 10, 150));

        }
        if(pastPlayerPos.size() != 0)
        {
            if(player.getPosition() == pastPlayerPos.back())
            {
                pastPlayerPos.clear();
            }
        }
        spaceButtonPressed = true;
    }
    else
    {
        if(spaceButtonPressed)
        {

                pastPlayerPos.clear();
                player.setFillColor(sf::Color(92, 140, 219));


        }
        spaceButtonPressed = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        eButtonPressed = true;
    }
    else
    {
        eButtonPressed = false;
    }

}
void PlayerDie(sf::RectangleShape &player)
{
    player.scale(0,0);
}
