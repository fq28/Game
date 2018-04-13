#include <SFML/Graphics.hpp>
#include "iostream"

sf::Vector2f Lerp(sf::Vector2f start, sf::Vector2f end, float percent)
{
    return (start + percent*(end-start));
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


void MovePlayer(sf::Shape &player, sf::Vector2f &playerPos, float moveSpeed, sf::Vector2f direction)
{
    playerPos.x = playerPos.x + direction.x * moveSpeed;
    playerPos.y = playerPos.y + direction.y * moveSpeed;
    player.setPosition(playerPos.x, playerPos.y);
}
void MoveView(sf::View &view, sf::Vector2f &playerPos, sf::Time deltaTime)
{
    float speed = 3;
    sf::Vector2f targetViewPos = playerPos;
    sf::Vector2f viewPos = view.getCenter();
    view.setCenter(Lerp(viewPos,targetViewPos, deltaTime.asSeconds() * speed));
}
void CheckCollision(sf::Shape &player, std::vector<sf::RectangleShape> &obstacles, float &moveDirectionX, float &moveDirectionY)
{
   sf::Vector2f playerPos = player.getPosition();
   for(unsigned i = 0; i < obstacles.size(); ++i)
   {
       sf::Vector2f objectPos = obstacles[i].getPosition();
       float deltaX = playerPos.x - objectPos.x;
       float deltaY = playerPos.y - objectPos.y;
       float rangeX = obstacles[i].getScale().x * 100;
       float rangeY = obstacles[i].getScale().y * 100;
       sf::Vector2f objectScale = obstacles[i].getScale();

       //object on the left side of the player
       if(deltaX <= rangeX && deltaX > 0 && moveDirectionX != 0)
       {
           if((deltaY <= rangeY - objectScale.y * 3 && deltaY > 0) || (deltaY >= -rangeY/objectScale.y + objectScale.x * 3 && deltaY < 0))
           {
               if(moveDirectionX == -1)
               moveDirectionX = 0;
           }
       }
       //object to the right of the player
       if(deltaX >= -rangeX/objectScale.x && deltaX < 0 && moveDirectionX != 0)
       {
           if((deltaY <= rangeY - objectScale.y * 3 && deltaY > 0) || (deltaY >= -rangeY/objectScale.y + objectScale.x * 3 && deltaY < 0))
           {
               if(moveDirectionX == 1)
               moveDirectionX = 0;
           }
       }
       //object above the player
       if(deltaY <= rangeY && deltaY > 0 && moveDirectionY != 0)
       {
           if((deltaX <= rangeX - objectScale.x * 3 && deltaX > 0) || (deltaX >= -rangeX/objectScale.x + objectScale.x * 3 && deltaX < 0))
           {
               if(moveDirectionY == -1)
               moveDirectionY = 0;
           }
       }
       //object under the player
       if(deltaY >= -rangeY/objectScale.y && deltaY < 0 && moveDirectionY != 0)
       {
           if((deltaX <= rangeX - objectScale.x * 3 && deltaX > 0) || (deltaX >= -rangeX/objectScale.x + objectScale.x * 3 && deltaX < 0))
           {
               if(moveDirectionY == 1)
               moveDirectionY = 0;
           }
       }
   }

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Go");
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0,0,1000,600));
    window.setView(view);
    sf::Clock clock;


    sf::Vector2f shape_1(100,100);
    sf::RectangleShape player(shape_1);
    player.setFillColor(sf::Color(92, 140, 219));

    //player movement
    const float moveSpeed = 6.0f;
    sf::Vector2f moveDirection(0,0);
    float moveDirectionX = 0;
    float moveDirectionY = 0;
    sf::Vector2f playerPos(0,0);

    //obstacles
    std::vector<sf::RectangleShape> obstacles;
    CreateRectangleObject(sf::Vector2f(1,4), sf::Color(150,150,150),sf::Vector2f(100,0),obstacles);
    CreateRectangleObject(sf::Vector2f(4,1), sf::Color(150,150,150),sf::Vector2f(300,100),obstacles);
    CreateRectangleObject(sf::Vector2f(10,1), sf::Color(150,150,150),sf::Vector2f(100,400),obstacles);


  while (window.isOpen())
    {
      sf::Time elasped = clock.restart();
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

        CheckCollision(player, obstacles, moveDirectionX, moveDirectionY);
        moveDirection = sf::Vector2f(moveDirectionX,moveDirectionY);
        MovePlayer(player, playerPos, moveSpeed, moveDirection);
        MoveView(view, playerPos, elasped);
        window.setView(view);

        window.clear();
        window.draw(player);
        for(unsigned i = 0; i < obstacles.size(); ++i)
        {
            window.draw(obstacles[i]);
        }

        window.display();
  }
    return 0;
}

