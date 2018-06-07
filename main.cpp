#include <SFML/Graphics.hpp>
#include "iostream"
#include <algorithm>
#include "object.h"
#include "enemy.h"
#include "player.h"
#include "levels.h"



void MoveWall(sf::RectangleShape &wall, sf::Vector2f &direction,  float wallSpeed)
{
    wall.setPosition(wall.getPosition().x + direction.x * wallSpeed, wall.getPosition().y + direction.y * wallSpeed);
}
void Reset(float &playerHealth, int &iteration, std::vector<sf::Vector2f> pastPlayerPos, std::vector<std::vector<sf::RectangleShape>> &enemysShootAgents,
std::vector<std::vector<sf::Vector2f>> &enemysShootAgentsTargetPositions, sf::Vector2f &playerPos)
{
    playerHealth = 3;
    playerPos= sf::Vector2f(0,0);;
    iteration = 0;
    pastPlayerPos.clear();
    enemysShootAgents.clear();
    enemysShootAgentsTargetPositions.clear();
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
    float playerHealth = 3;
    float invincibilityTimR = 1;
    float timerResin = 0;

    bool isHit;
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
    sf::Vector2f playerPastPos;
    int iteration = 0;
    bool getPos = true;
    bool prevGetPos = false;
    bool isGoingBackInTime = false;
    //float timeR;

    std::vector<sf::CircleShape> circles;
    //setup ai
    std::vector<sf::RectangleShape> enemys;
    std::vector<bool>lockedIn;
    std::vector<std::vector<sf::RectangleShape>> enemysShootAgents;
    std::vector<std::vector<sf::Vector2f>> enemysShootAgentsTargetPositions;
    std::vector<sf::Vector2f> enemysTargetPos;
    std::vector<sf::Vector2f> enemysNormalPos;
    std::vector<float> radius;
    std::vector<sf::Vector2f> middle;
    std::vector<float> length;




    //CreateRectangleObject(sf::Vector2f(1,1), sf::Color().Red,sf::Vector2f(-400,100),enemys);

    //setup traps
    std::vector<sf::RectangleShape> traps;

    //setup moving walls
     std::vector<float> wallSpeeds;
    std::vector<sf::RectangleShape> movingWalls;
    std::vector<bool> wallsMoving;
    std::vector<sf::Vector2f> wallDirection;


    //obstacle
    std::vector<sf::RectangleShape> obstacles;

    //create button
    std::vector<sf::RectangleShape> buttons;

    //create door
    std::vector<sf::RectangleShape> doors;

    std::vector<sf::RectangleShape> goals;

    int level = 1;
    GenerateLevel4(obstacles, buttons, doors, goals, traps, movingWalls, wallDirection, wallsMoving, wallSpeeds, lockedIn, enemysTargetPos,
                  enemysNormalPos, radius, middle, length, enemys);


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

    if(enemys.size() > 0)
    {
    MoveEnemys(enemys, player, obstacles, lockedIn, enemysShootAgents, doors, movingWalls, enemysShootAgentsTargetPositions,
               enemysTargetPos, enemysNormalPos, circles, radius, elasped, middle, length);
    }


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
        }
        if(wallsMoving[i])
        {
            MoveWall(movingWalls[i],wallDirection[i], wallSpeeds[i]);
        }
    }

    CheckCollision(player, movingWalls, moveDirectionX, moveDirectionY, true, wallSpeeds, isGoingBackInTime);
    CheckCollision(player, obstacles, moveDirectionX, moveDirectionY, false, wallSpeeds, false);
    CheckCollision(player, doors, moveDirectionX, moveDirectionY, false, wallSpeeds, false);
    CheckCollision(player, enemys, moveDirectionX, moveDirectionY, false, wallSpeeds, false);


    invincibilityTimR -= elasped.asSeconds();
    timerResin += elasped.asSeconds();

    if(DoesCollide(playerPos,enemys) && invincibilityTimR <= 0 && player.getFillColor() != sf::Color(92, 140, 10, 150))
    {
        playerHealth --;
        invincibilityTimR = 1;
        isHit = true;
        if(playerHealth <= 0)
        {
            PlayerDie(player);
        }
    }

    if(invincibilityTimR > 0)
    {
        if(timerResin >= 0.08f)
        {
            if(player.getFillColor() == sf::Color(92, 140, 219))
            {
                player.setFillColor(sf::Color(0, 0, 0,0));
            }
            else
            {
                player.setFillColor(sf::Color(92, 140, 219));
            }
            timerResin = 0;
        }
    }
    else if (invincibilityTimR <= 0 && isHit)
    {
        player.setFillColor(sf::Color(92, 140, 219));
        isHit = false;
    }
    if(!spaceButtonPressed)
    {
        iteration = 0;
        isGoingBackInTime = false;
        moveDirection = sf::Vector2f(moveDirectionX,moveDirectionY);
        MovePlayer(player, playerPos, moveSpeed, moveDirection);

        //stupid, but works
        if(getPos)
        {
            if(playerPos != playerPastPos)
            {
                pastPlayerPos.push_back(playerPos);
                prevGetPos = true;
            }
            playerPastPos = playerPos;
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
    else if(iteration < pastPlayerPos.size() && invincibilityTimR <= 0)
    {
        MovePlayerBackInTime(player,pastPlayerPos,playerPos,iteration);
        isGoingBackInTime = true;
        iteration ++;
    }

    if(DoesCollide(playerPos,goals))
    {
        DestroyLevelObjects(obstacles, buttons, doors, traps, movingWalls, wallDirection, wallsMoving, wallSpeeds, lockedIn, enemysTargetPos,
                            enemysNormalPos, radius, middle, length, enemys, goals);
        Reset(playerHealth, iteration, pastPlayerPos, enemysShootAgents, enemysShootAgentsTargetPositions, playerPos);
        level++;
        LoadNextLevel(level, obstacles, buttons, doors, goals, traps, movingWalls, wallDirection, wallsMoving, wallSpeeds
                      , lockedIn, enemysTargetPos, enemysNormalPos, radius, middle, length, enemys);
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
    for(unsigned i = 0; i < enemysShootAgents.size(); ++i)
    {
        for(unsigned j = 0; j < enemysShootAgents[i].size(); j++)
        {
            window.draw((enemysShootAgents[i][j]));
        }
    }

    for(unsigned i = 0; i < circles.size(); ++i)
    {
        window.draw(circles[i]);
    }
    for(unsigned i = 0; i < goals.size(); ++i)
    {
        window.draw(goals[i]);
    }

    window.display();
  }
    return 0;
}

