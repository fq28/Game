#include <SFML/Graphics.hpp>
#include "iostream"


void Move(sf::Shape &player, sf::Vector2f &playerPos, float moveSpeed, sf::Vector2f direction)
{
    playerPos.x = playerPos.x + direction.x * moveSpeed;
    playerPos.y = playerPos.y + direction.y * moveSpeed + 1;
    player.setPosition(playerPos.x, playerPos.y);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 400), "Go");
    window.setFramerateLimit(60);
    sf::Vector2f shape_1(100,100);
    sf::RectangleShape player(shape_1);
    player.setFillColor(sf::Color(92, 140, 219));
    sf::FloatRect collsionPlayer = player.getGlobalBounds();

    //player movement
    const float moveSpeed = 6.0f;
    sf::Vector2f moveDirection(0,0);
    float moveDirectionX = 0;
    float moveDirectionY = 0;
    sf::Vector2f playerPos(0,0);

    //obstacle
    sf::Vector2f shape_2(400,100);
    sf::RectangleShape shapeR(shape_2);
    shapeR.setFillColor(sf::Color(135, 135, 135));
    shapeR.setPosition(0,200);
    sf::FloatRect collsionObstacle = shapeR.getGlobalBounds();



  while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                           window.close();
        }

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
        Move(player, playerPos, moveSpeed, moveDirection);

        //collsions
        if(collsionPlayer.intersects(collsionObstacle))
        {
            player.setPosition(player.getPosition().x, 0);
        }
        window.clear();
        window.draw(player);
        window.draw(shapeR);
        moveDirection = sf::Vector2f(moveDirectionX,moveDirectionY);
        window.display();
  }
    return 0;
}

