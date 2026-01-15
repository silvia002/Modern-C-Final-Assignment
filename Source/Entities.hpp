#include "raylib.h"
#include <string>
#include <vector>
#include "constants.hpp"
#include <assert.h>
#include <optional>
#include <algorithm>

enum struct EntityType
{
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

struct Player
{
	Player() = default;

	float x_pos = FscreenWidth / 2;
	float speed = 7;
	float player_base_height = 70.0f;
	float radius = 50;
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	Rectangle source = { 0, 0, 352, 352 };

	void Render(const Texture2D& texture) const noexcept;
	void Update() noexcept;
};


struct Projectile
{
	Projectile(Vector2 pos, EntityType eType) noexcept : position(pos), type(eType) {};

	Vector2 position = { 0, 0 };
	int speed = 15;
	bool active = true;
	EntityType type = {};

	Rectangle rec = { 0, 0, 6, 30 };
	Rectangle source = { 0, 0, 176, 176 };

	void Update() noexcept;
	void Render(Texture2D& texture) const noexcept;
};

struct Wall
{
	Wall(Vector2 pos) noexcept : position(pos) {};

	Vector2 position{};
	bool active = true;
	int health = 50;
	float radius = 60;

	Rectangle source = {0, 0, 704, 704 };

	void Render(Texture2D& texture) const noexcept;
	void Update() noexcept;
};

struct Alien
{
	Alien(Vector2 pos) noexcept : position(pos) {};

	Color color = WHITE;
	Vector2 position = { 0, 0 };
	int x = 0;
	int y = 0;
	float radius = 30;

	bool active = true;

	bool moveRight = true;

	Rectangle source = { 0, 0, 352, 352 };

	int speed = 2;

	void Update() noexcept;
	void Render(Texture2D& texture) const noexcept;
};


struct Star
{
	Star(Vector2 pos, float radius) noexcept : initPosition(pos), size(radius) {};
	Vector2 initPosition = { 0, 0 };
	float size = 0;

	Vector2 position = { 0, 0 };
	Color color = GRAY;

	void Update(float starOffset) noexcept;
	void Render() const noexcept;
};