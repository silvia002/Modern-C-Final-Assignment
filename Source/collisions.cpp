#include "game.hpp"
#include "raylib.h"
#include <iostream>
#include <print>

void Game::CheckCollision() {
    for (auto& projectile : Projectiles)
    {
        if (!projectile.active)
            continue;

        // PLAYER PROJECTILES
        if (projectile.type == EntityType::PLAYER_PROJECTILE)
        {
            for (auto& alien : Aliens)
            {
                if (!alien.active)
                    continue;

                if (CheckCollisionCircleRec(alien.position, alien.radius, projectile.rec))
                {
                    std::print("Hit\n");
                    projectile.active = false;
                    alien.active = false;
                    board.score += 100;
                    break; 
                }
            }

            if (!projectile.active)
                continue; 
        }

        // ENEMY PROJECTILES
        else if (projectile.type == EntityType::ENEMY_PROJECTILE)
        {
            if (CheckCollisionCircleRec({ player.x_pos, screenHeight - player.player_base_height },
                player.radius, projectile.rec))
            {
                std::print("dead\n");
                projectile.active = false;
                player.lives -= 1;
                continue; 
            }
        }

        // WALLS
        for (auto& wall : Walls)
        {
            if (CheckCollisionCircleRec(wall.position, wall.radius, projectile.rec))
            {
                std::print("Hit\n");
                projectile.active = false;
                wall.health -= 1;
                break;
            }
        }
    }
}