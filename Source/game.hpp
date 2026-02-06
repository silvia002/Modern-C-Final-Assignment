#pragma once
#include "raylib.h"
#include <algorithm>
#include "Leaderboard.hpp"
#include "Resources.hpp"
#include "Entities.hpp"
#include <print>

struct Background
{
	Background() {
		for (int i = 0; i < _starAmount; i++)
		{
			const Vector2 position = { static_cast<float>(GetRandomValue(-150, screenWidth + 150)) ,
										static_cast<float>(GetRandomValue(0, screenHeight)) };
			const Star newStar(position, static_cast<float>(GetRandomValue(1, 4) / 2));
			Stars.push_back(newStar);
		}
	}
	
	void Update(float offset);
	void Render() const noexcept;

private:

	std::vector<Star> Stars{};
	int _starAmount = 600;
};

struct Game
{
	Game() = default;

private:

	float shootTimer = 0;
	bool gameEnd = false;
	void End() noexcept;

	void InitWalls();
	void RemoveDeadEntities();
	void SpawnAliens();
	void CheckCollision();

	std::optional<Vector2> 
		GetPlayerShootPosition() const noexcept;
	void AlienShootingHandle();
	void PlayerShootingHandle();

	std::vector<Projectile> Projectiles{};
	std::vector<Wall> Walls{};
	std::vector<Alien> Aliens{};

	Background background;
	Leaderboard board;
	Resources resources;
	Player player;

public:
	bool NewHighscore() const;
	bool GameEnd() const;
	void board_update();
	void board_render() const;

	void Init();
	void Update();
	void Render() const;
};