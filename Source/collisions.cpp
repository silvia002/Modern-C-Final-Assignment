#include "game.hpp"
#include "raylib.h"
#include <iostream>
#include <print>

void Game::CheckCollision() {
    for (auto& projectile : Projectiles)
    {
        if (!projectile.Is_Active())
            continue;

        // PLAYER PROJECTILES
        if (projectile.Is_Player_Bullet())
        {
            for (auto& alien : Aliens)
            {
                if (!alien.Is_Active())
                    continue;

                if (CheckCollisionCircleRec(alien.Get_Position(), alien.Get_Radius(), projectile.Get_Rec()))
                {
                    std::print("Hit\n");
                    projectile.Set_Inactive();
                    alien.Set_Inactive();
                    board.score += 100;
                    break; 
                }
            }

            if (!projectile.Is_Active())
                continue; 
        }

        // ENEMY PROJECTILES
        else if (!projectile.Is_Player_Bullet())
        {
            if (CheckCollisionCircleRec({ player.Get_Position(), screenHeight - player.Get_Radius()},
                player.Get_Radius(), projectile.Get_Rec()))
            {
                std::print("dead\n");
                projectile.Set_Inactive();
                player.Set_Lives(player.Get_Lives() - 1);
                continue; 
            }
        }

        // WALLS
        for (auto& wall : Walls)
        {
            if (CheckCollisionCircleRec(wall.Get_Position(), wall.Get_Radius(), projectile.Get_Rec()))
            {
                std::print("Hit\n");
                projectile.Set_Inactive();
                wall.Set_Health(wall.Get_Health() -1);
                break;
            }
        }
    }
}