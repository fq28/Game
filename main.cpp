#include <SFML/Graphics.hpp>
#include "iostream"
#include <algorithm>

sf::Vector2f Lerp(sf::Vector2f start, sf::Vector2f end, float percent)
{
    return (start + percent*(end-start));
}
sf::Vector2f Normalize(sf::Vector2f vector)
{
    float length = std::sqrt(std::pow(vector.x,2) + std::pow(vector.y,2));
    vector.x = vector.x /length;
    vector.y = vector.y / length;
    return vector;
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

void MoveWall(sf::RectangleShape &wall, sf::Vector2f &direction,  float wallSpeed)
{
    wall.setPosition(wall.getPosition().x + direction.x * wallSpeed, wall.getPosition().y + direction.y * wallSpeed);
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
void MoveView(sf::View &view, sf::Vector2f &playerPos, sf::Time deltaTime)
{
    float speed = 3;
    sf::Vector2f targetViewPos = playerPos;
    sf::Vector2f viewPos = view.getCenter();
    view.setCenter(Lerp(viewPos,targetViewPos, deltaTime.asSeconds() * speed));
}

void CheckCollision(sf::Shape &player, std::vector<sf::RectangleShape> &obstacles, float &moveDirectionX, float &moveDirectionY, bool isMoving,
                    std::vector<float> wallSpeeds)
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
           if(deltaX <= rangeX && deltaX >= 0)
           {
               if((deltaY <= rangeY - objectScale.y * 3 && deltaY >= 0) || (deltaY >= -rangeY/objectScale.y + objectScale.x * 3 && deltaY < 0))
               {
                   if(moveDirectionX < 0)
                   moveDirectionX = 0;
                   if(isMoving)
                   {
                       moveDirectionX = 1 * (wallSpeeds[i] / 5);
                   }
               }
           }
           //object to the right of the player
           if(deltaX >= -rangeX/objectScale.x && deltaX < 0)
           {
               if((deltaY <= rangeY - objectScale.y * 3 && deltaY >= 0) || (deltaY >= -rangeY/objectScale.y + objectScale.x * 3 && deltaY < 0))
               {
                   if(moveDirectionX > 0)
                   moveDirectionX = 0;
                   if(isMoving)
                   {
                       moveDirectionX = -1 * (wallSpeeds[i] / 5);
                   }
               }
           }
           //object above the player
           if(deltaY <= rangeY && deltaY >= 0)
           {
               if((deltaX <= rangeX - objectScale.x * 3 && deltaX >= 0) || (deltaX >= -rangeX/objectScale.x + objectScale.x * 3 && deltaX < 0))
               {
                   if(moveDirectionY < 0)
                   moveDirectionY = 0;
                   if(isMoving)
                   {
                       moveDirectionY = 1 * (wallSpeeds[i] / 5);
                   }
               }
           }
           //object under the player
           if(deltaY >= -rangeY/objectScale.y && deltaY < 0)
           {
               if((deltaX <= rangeX - objectScale.x * 3 && deltaX >= 0) || (deltaX >= -rangeX/objectScale.x + objectScale.x * 3 && deltaX < 0))
               {
                   if(moveDirectionY > 0)
                   moveDirectionY = 0;
                   if(isMoving)
                   {
                       moveDirectionY = -1  * (wallSpeeds[i] / 5);
                   }
               }
           }
       }
   }
}
void MoveEnemys(std::vector<sf::RectangleShape> &enemys, sf::Shape &player, std::vector<sf::RectangleShape> & obstacles)
{
    float moveSpeed = 3;
    sf::Vector2f playerPos = player.getPosition();
    for(unsigned i = 0; i < enemys.size(); ++i)
    {
        sf::Vector2f enemyDirection = Normalize(playerPos - enemys[i].getPosition());

        float deltaX = std::abs(playerPos.x - enemys[i].getPosition().x);
        float deltaY = std::abs(playerPos.y - enemys[i].getPosition().y);
        float rangeX = player.getScale().x * 100;
        float rangeY = player.getScale().y * 100;

        std::vector<float> temp;
        CheckCollision(enemys[i],obstacles, enemyDirection.x, enemyDirection.y, false, temp);
        CheckCollision(enemys[i], enemys, enemyDirection.x, enemyDirection.y, false, temp);

        if(deltaX <= rangeX && deltaY <= rangeY)
        {

        }
        else
        {
            enemys[i].move(moveSpeed * enemyDirection);
        }

    }
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if(!spaceButtonPressed)
        {
            std::reverse(pastPlayerPos.begin(), pastPlayerPos.end());
            player.setFillColor(sf::Color(92, 140, 10));
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
int main()
{
    //set up window + view
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Go");
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0,0,1000,600));
    window.setView(view);
    sf::Clock clock;
    bool spaceButtonPressed = false;
    bool eButtonPressed = false;

    //setup player
    sf::Vector2f shape_1(100,100);
    sf::RectangleShape player(shape_1);
    player.setFillColor(sf::Color(92, 140, 219));

    //player movement
    const float moveSpeed = 6.0f;
    sf::Vector2f moveDirection(0,0);
    float moveDirectionX = 0;
    float moveDirectionY = 0;
    sf::Vector2f playerPos(0,0);
    std::vector<sf::Vector2f> pastPlayerPos;
    int iteration = 0;
    bool getPos = true;
    bool prevGetPos = false;
    //float timeR;

    //setup ai
    std::vector<sf::RectangleShape> enemys;
    //CreateRectangleObject(sf::Vector2f(1,1), sf::Color().Red,sf::Vector2f(-400,0),enemys);
    //CreateRectangleObject(sf::Vector2f(1,1), sf::Color().Red,sf::Vector2f(-400,100),enemys);

    //setup traps
    std::vector<sf::RectangleShape> traps;
    CreateRectangleObject(sf::Vector2f(1,3), sf::Color(20,20,20),sf::Vector2f(300,-100),traps);

    //setup moving walls
     std::vector<float> wallSpeeds;
    std::vector<sf::RectangleShape> movingWalls;
    std::vector<bool> wallsMoving;
    std::vector<sf::Vector2f> wallDirection;
    CreateRectangleObject(sf::Vector2f(0,0), sf::Color().Red,sf::Vector2f(-400,-100),movingWalls);
    wallDirection.push_back(sf::Vector2f(1,0));
    wallsMoving.push_back(false);
    wallSpeeds.push_back(3.f);

    //obstacles
    std::vector<sf::RectangleShape> obstacles;
    CreateRectangleObject(sf::Vector2f(20,1), sf::Color(150,150,150),sf::Vector2f(-500,-200),obstacles);
    CreateRectangleObject(sf::Vector2f(20,1), sf::Color(150,150,150),sf::Vector2f(-500,200),obstacles);
    CreateRectangleObject(sf::Vector2f(1,3), sf::Color(150,150,150),sf::Vector2f(1400,-100),obstacles);

    //create buttons
    std::vector<sf::RectangleShape> buttons;
    CreateRectangleObject(sf::Vector2f(1,1), sf::Color().Green,sf::Vector2f(1300,0),buttons);


    //create doors
    std::vector<sf::RectangleShape> doors;
    CreateRectangleObject(sf::Vector2f(1,3), sf::Color().Yellow,sf::Vector2f(-500,-100),doors);



  while (window.isOpen())
  {
    sf::Time elasped = clock.restart();
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
                       window.close();
    }
    CheckInput(moveDirectionX,moveDirectionY, spaceButtonPressed, eButtonPressed, pastPlayerPos, player);


    MoveEnemys(enemys, player, obstacles);


    for(unsigned i = 0; i < buttons.size(); ++i)
    {
        if(InRange(playerPos, buttons[i]) && eButtonPressed)
        {
            buttons[i].setScale(sf::Vector2f(0,0));
            doors[i].setScale(sf::Vector2f(0,0));
        }
    }
    for(unsigned i = 0; i < traps.size(); ++i)
    {
        if(InRange(playerPos, traps[i]))
        {
            traps[i].setScale(sf::Vector2f(0,0));
            wallsMoving[i] = true;
            movingWalls[i].setScale(sf::Vector2f(1,3));
        }
        if(wallsMoving[i])
        {
            MoveWall(movingWalls[i],wallDirection[i], wallSpeeds[i]);
        }
    }
    std::cout<<"preX: "<<moveDirectionX<<"\n";

    CheckCollision(player, movingWalls, moveDirectionX, moveDirectionY, true, wallSpeeds);
    CheckCollision(player, obstacles, moveDirectionX, moveDirectionY, false, wallSpeeds);
    CheckCollision(player, doors, moveDirectionX, moveDirectionY, false, wallSpeeds);
    CheckCollision(player, enemys, moveDirectionX, moveDirectionY, false, wallSpeeds);
    if(!spaceButtonPressed)
    {
        iteration = 0;

        moveDirection = sf::Vector2f(moveDirectionX,moveDirectionY);
        MovePlayer(player, playerPos, moveSpeed, moveDirection);
        std::cout<<"X: "<<moveDirectionX<<"\n";

        //stupid, but works
        if(getPos)
        {
            pastPlayerPos.push_back(playerPos);
            prevGetPos = true;
        }
        if(!getPos && prevGetPos)
        {
            prevGetPos = false;
            getPos = true;
        }
        if(getPos && prevGetPos)
        {
            getPos = false;
        }
    }
    else if(iteration < pastPlayerPos.size())
    {
        MovePlayerBackInTime(player,pastPlayerPos,playerPos,iteration);
        iteration ++;
    }

    MoveView(view, playerPos, elasped);
    window.setView(view);

    window.clear();
    window.draw(player);
    for(unsigned i = 0; i < obstacles.size(); ++i)
    {
        window.draw(obstacles[i]);
    }
    for(unsigned i = 0; i < enemys.size(); ++i)
    {
        window.draw(enemys[i]);
    }
    for(unsigned i = 0; i < buttons.size(); ++i)
    {
        window.draw(buttons[i]);
    }
    for(unsigned i = 0; i < doors.size(); ++i)
    {
        window.draw(doors[i]);
    }
    for(unsigned i = 0; i < movingWalls.size(); ++i)
    {
        window.draw(movingWalls[i]);
    }
    for(unsigned i = 0; i < traps.size(); ++i)
    {
        window.draw(traps[i]);
    }


    window.display();
  }
    return 0;
}

