#pragma once
#include "raylib.h"
#include "Leaderboard.hpp"
#include "Resources.hpp"
#include "Entities.hpp"


enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

struct Background
{
	std::vector<Star> Stars;

	void Initialize(int starAmount);
	void Update(float offset);
	void Render() const noexcept;
};

struct Game
{
	State gameState = {};
	float shootTimer = 0;

	void Start();
	void End() noexcept;
	void Continue() noexcept;

	void Update();
	void Render();

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
};