#include "enemy.h"
#include "object.h"
#include <SFML/Graphics.hpp>
#include "iostream"
Enemy::Enemy()
{

}
void CreateEnemy(sf::Vector2f scale, sf::Color color, sf::Vector2f startPos, std::vector<sf::RectangleShape> &enemys,
                 std::vector<bool> &lockedIn, std::vector<sf::Vector2f> &enemysTargetPos,
                 std::vector<sf::Vector2f> &enemysNormalPos, std::vector<float> &radius,
                 std::vector<sf::Vector2f> &middle, std::vector<float> &length)
{
    CreateRectangleObject(scale, color,startPos,enemys);
    lockedIn.push_back(false);
    enemysTargetPos.push_back(sf::Vector2f(0,0));
    enemysNormalPos.push_back(sf::Vector2f(0,0));
    radius.push_back(0);
    middle.push_back(sf::Vector2f(0,0));
    length.push_back(0);
}
sf::Vector2f Normalize(sf::Vector2f vector)
{
    float length = std::sqrt(std::pow(vector.x,2) + std::pow(vector.y,2));
    vector.x = vector.x /length;
    vector.y = vector.y / length;
    return vector;
}
bool DoesCollide(sf::Vector2f pos, std::vector<sf::RectangleShape> &obstacles)
{
    for(unsigned i = 0; i < obstacles.size(); ++i)
    {

        sf::Vector2f objectPos = obstacles[i].getPosition();
        if(pos != objectPos)
        {
            float deltaX = pos.x - objectPos.x;
            float deltaY = pos.y - objectPos.y;
            float rangeX = obstacles[i].getScale().x * 100;
            float rangeY = obstacles[i].getScale().y * 100;
            sf::Vector2f objectScale = obstacles[i].getScale();

            //object on the left side of the agent
            if(deltaX <= rangeX && deltaX >= 0)
            {
                if((deltaY <= rangeY - objectScale.y * 3 && deltaY >= 0) || (deltaY >= -rangeY/objectScale.y + objectScale.x * 3 && deltaY < 0))
                {
                    return true;
                }
            }
            //object to the right of the agent
            if(deltaX >= -rangeX/objectScale.x && deltaX < 0)
            {
                if((deltaY <= rangeY - objectScale.y * 3 && deltaY >= 0) || (deltaY >= -rangeY/objectScale.y + objectScale.x * 3 && deltaY < 0))
                {
                   return true;
                }
            }
            //object above the agent
            if(deltaY <= rangeY && deltaY >= 0)
            {
                if((deltaX <= rangeX - objectScale.x * 3 && deltaX >= 0) || (deltaX >= -rangeX/objectScale.x + objectScale.x * 3 && deltaX < 0))
                {
                   return true;
                }
            }
            //object under the agent
            if(deltaY >= -rangeY/objectScale.y && deltaY < 0)
            {
                if((deltaX <= rangeX - objectScale.x * 3 && deltaX >= 0) || (deltaX >= -rangeX/objectScale.x + objectScale.x * 3 && deltaX < 0))
                {
                   return true;
                }
            }
            return false;
        }
    }
}
std::vector<sf::RectangleShape> EnemyShootAgents(sf::RectangleShape &enemy)
{
    std::vector<sf::RectangleShape> enemyShootAgents;
    for(int i = 0; i < 4; ++i)
    {
       CreateRectangleObject(enemy.getScale(),sf::Color(0,0,255,125),enemy.getPosition(), enemyShootAgents);
    }
    return enemyShootAgents;
}
std::vector<sf::Vector2f> EnemyShootAgentsTargetPositions(sf::Vector2f &playerPos, std::vector<sf::RectangleShape> &obstacles
                                                          , std::vector<sf::RectangleShape> &movingWalls, std::vector<sf::RectangleShape> &doors
                                                          , std::vector<sf::RectangleShape> &enemyShootAgents, std::vector<sf::RectangleShape> &enemys, float deltaAgent)
{
    std::vector<sf::Vector2f> targetPositions;
    targetPositions.push_back(playerPos + sf::Vector2f(deltaAgent ,0)); //right
    targetPositions.push_back(playerPos + sf::Vector2f(-deltaAgent,0)); //left
    targetPositions.push_back(playerPos + sf::Vector2f(0,-deltaAgent)); //above
    targetPositions.push_back(playerPos + sf::Vector2f(0,deltaAgent)); //under
    /* fun
    targetPositions.push_back(playerPos + sf::Vector2f(0,0)); //on top
    targetPositions.push_back(playerPos + sf::Vector2f(220,0)); //far right
    targetPositions.push_back(playerPos + sf::Vector2f(-220,0)); //far left
    targetPositions.push_back(playerPos + sf::Vector2f(0,-220)); // far above
    targetPositions.push_back(playerPos + sf::Vector2f(0,220)); // farunder
    targetPositions.push_back(playerPos + sf::Vector2f(110,110)); //under
    targetPositions.push_back(playerPos + sf::Vector2f(-110,-110)); //under
    targetPositions.push_back(playerPos + sf::Vector2f(-110,110)); //under
    targetPositions.push_back(playerPos + sf::Vector2f(110,-110)); //under
    */



    for(unsigned i = 0; i < targetPositions.size(); ++i)
    {
        bool boolone = DoesCollide(targetPositions[i], obstacles);
        bool booltwo = DoesCollide(targetPositions[i], enemys);
        bool boolthree = DoesCollide(targetPositions[i], movingWalls);
        bool boolfour = DoesCollide(targetPositions[0], doors);
        if(!boolone && !booltwo && !boolthree && !boolfour)
        {

        }
        else
        {
            targetPositions.erase(targetPositions.begin() + i);
            enemyShootAgents.erase(enemyShootAgents.begin() + i);
        }
    }

        return targetPositions;



}
void MoveEnemys(std::vector<sf::RectangleShape> &enemys, sf::Shape &player, std::vector<sf::RectangleShape> & obstacles
                , std::vector<bool> &lockedIn, std::vector<std::vector<sf::RectangleShape>> &enemysShootAgents, std::vector<sf::RectangleShape> &doors
                , std::vector<sf::RectangleShape> &movingWalls, std::vector<std::vector<sf::Vector2f>> &enemysShootAgentsTargetPositions,
                std::vector<sf::Vector2f> &enemysTargetPos,  std::vector<sf::Vector2f> &enemysNormalPos, std::vector<sf::CircleShape> &circles
                , std::vector<float> &radius, sf::Time elasped, std::vector<sf::Vector2f> &middle, std::vector<float> &length)
{
    float moveSpeed = 3;
    sf::Vector2f playerPos = player.getPosition();
    for(unsigned i = 0; i < enemys.size(); ++i)
    {
        sf::Vector2f enemyDirection = Normalize(playerPos - enemys[i].getPosition());

        float deltaX = std::abs(playerPos.x - enemys[i].getPosition().x);
        float deltaY = std::abs(playerPos.y - enemys[i].getPosition().y);
        float rangeX = player.getScale().x * 300;
        float rangeY = player.getScale().y * 300;

        std::vector<float> temp;
        CheckCollision(enemys[i],obstacles, enemyDirection.x, enemyDirection.y, false, temp, false);
        CheckCollision(enemys[i], enemys, enemyDirection.x, enemyDirection.y, false, temp, false);

        if(enemysTargetPos[i] != sf::Vector2f(0,0))
        {
            // circle stuff -- works 90 percent of the time
            float deltaXZ = std::abs(enemys[i].getPosition().x - enemysTargetPos[i].x);
            float deltaYZ = std::abs(enemys[i].getPosition().y - enemysTargetPos[i].y);
            if(length[i] == 0)
            {

                sf::Vector2f lineVector =  enemysTargetPos[i] - enemys[i].getPosition();

                 if(lineVector.x == 0)
                 {
                    middle[i] = sf::Vector2f(0, lineVector.y /2);
                    length[i] = deltaYZ;
                 }
                 else if(lineVector.y == 0)
                 {
                     middle[i] = sf::Vector2f(lineVector.x /2, 0);
                     length[i] = deltaXZ;
                 }
                 else
                 {
                    middle[i] = ((enemys[i].getPosition() - enemysTargetPos[i]) / 2.f + enemysTargetPos[i]);
                    length[i] = std::sqrt(std::pow(lineVector.x,2) + std::pow(lineVector.y,2));
                }

                // CreateCircleObject(sf::Vector2f(1,1),sf::Color().White,enemysNormalPos[i],20, circles);
                 //CreateCircleObject(sf::Vector2f(1,1),sf::Color().White,sf::Vector2f(middle[i].x - length[i]/2, middle[i].y - length[i]/2) ,length[i]/2, circles);
                float xCos = (enemys[i].getPosition().x-middle[i].x)/(length[i]/2);
                while(xCos > 1 && xCos> 0)
                {
                      xCos -= 2;
                }
                while(xCos < -1 && xCos < 0)
                {
                      xCos += 2;
                }

                 radius[i] = std::acos(xCos);
                 if(lineVector.x == 0)
                 {
                     radius[i] = std::asin((enemys[i].getPosition().y-middle[i].y)/(length[i]/2));
                 }
            }
                moveSpeed = 10;
                enemysNormalPos[i] = sf::Vector2f(middle[i].x + cos(radius[i])*length[i]/2, middle[i].y + sin(radius[i])*length[i]/2);
                radius[i] += elasped.asSeconds() * 6;

                std::cout<<"Radius: "<<radius[i]<<"\n";
                //circles[0].setPosition(enemysNormalPos[i]);



            float deltaXP = std::abs(enemys[i].getPosition().x - enemysNormalPos[i].x);
            float deltaYP = std::abs(enemys[i].getPosition().y - enemysNormalPos[i].y);
            //enemysNormalPos[i] = sf::Vector2f(middle.x + cos(radius[i])*length, middle.y + sin(0)*length);
            sf::Vector2f realPos = Normalize(enemysNormalPos[i]);

            //std::cout<<"X: "<<deltaXZ<<"\n "<<"Y: "<<deltaYZ<<"\n";
            if(deltaXP < 20 && deltaYP < 20)
            {
                enemys[i].setPosition(enemysNormalPos[i]);
            }
            if(deltaXZ < 20 && deltaYZ < 20)
            {
                enemysTargetPos[i] = sf::Vector2f(0,0);
                enemysNormalPos[i] = sf::Vector2f(0,0);
                enemysShootAgents.erase(enemysShootAgents.begin() + i);
                enemysShootAgentsTargetPositions.erase(enemysShootAgentsTargetPositions.begin() + i);
                length[i] = 0;
                radius[i] = 180;
                middle[i] = sf::Vector2f(0,0);
                enemysNormalPos[i] = sf::Vector2f(0,0);
            }
            else
            {
                //enemys[i].move(moveSpeed * realPos);
                enemys[i].setPosition(enemysNormalPos[i]);
            }

        }
        else if((deltaX <= rangeX && deltaY <= rangeY) || lockedIn[i])
        {
            if(!lockedIn[i])
            {
                lockedIn[i] = true;
                enemysShootAgents.push_back(EnemyShootAgents(enemys[i]));
                float deltaAgent = 110 * enemys[i].getScale().x;
                enemysShootAgentsTargetPositions.push_back(EnemyShootAgentsTargetPositions(playerPos,obstacles, movingWalls, doors, enemysShootAgents[i], enemys, deltaAgent));
            }
            int readyCheck = 0;
            if(enemysShootAgents[i].size() > 0)
            {
            for(unsigned j = 0; j < enemysShootAgents[i].size(); ++j)
            {
                sf::Vector2f agentDirection = Normalize(enemysShootAgents[i][j].getPosition() - enemysShootAgentsTargetPositions[i][j]);
                enemysShootAgents[i][j].move(-9.f * agentDirection);
                float deltaXE = std::abs(enemysShootAgents[i][j].getPosition().x - enemysShootAgentsTargetPositions[i][j].x);
                float deltaYE = std::abs(enemysShootAgents[i][j].getPosition().y - enemysShootAgentsTargetPositions[i][j].y);
                if(deltaXE < 10 && deltaYE < 10)
                {
                    readyCheck++;
                }

            }

            if(readyCheck == enemysShootAgents[i].size() && readyCheck != 0)
            {
                int j = rand() % enemysShootAgentsTargetPositions[i].size() + 0;
                enemysTargetPos[i] = enemysShootAgentsTargetPositions[i][j];

                lockedIn[i] = false;

            }
            }

        }
        else
        {
            enemys[i].move(moveSpeed * enemyDirection);
        }

    }
}
