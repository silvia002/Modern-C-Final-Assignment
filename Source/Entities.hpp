#include "raylib.h"
#include <string>
#include <vector>
#include "constants.hpp"
#include <cassert>
#include <optional>
#include <algorithm>

struct Player
{
	Player() = default;

	void Set_Position(float pos_x);
	void Set_Speed(float speed);
	void Set_Radius(float radius);
	void Set_Lives(int lives);
	void Set_Direction(int direction);

	float Get_Position() const;
	float Get_Speed() const;
	float Get_Radius() const;
	int   Get_Active_Texture() const;
	int   Get_Lives() const;
	int	  Get_Direction() const;

	void Render(const Texture2D& texture) const noexcept;
	void Update() noexcept;

private:
	Rectangle source = { 0, 0, 352, 352 };

	float timer = 0;
	float _pos_x = FscreenWidth / 2;
	float _speed = 7;
	float _radius = 50;

	int   _activeTexture = 0;
	int   _lives = 3;
	int   _direction = 0;
};


struct Projectile
{
	Projectile(Vector2 pos, bool is_player_bullet) noexcept : _position(pos), _player_Bullet(is_player_bullet){};

	void Set_Position(Vector2 position);
	void Set_Speed(int speed);
	void Set_Inactive();
	void Set_Direction(int direction);

	Rectangle Get_Rec() const;
	Vector2   Get_Position() const;
	int       Get_Speed() const;
	bool      Is_Active() const;
	bool	  Is_Player_Bullet() const;

	void Update() noexcept;
	void Render(const Texture2D& texture) const noexcept;

private:
	Vector2 _position = { 0, 0 };
	int     _speed = 15;
	int     _direction = 0;
	bool    _active = true;
	bool	_player_Bullet{};
	Rectangle _rec = { 0, 0, 6, 30 };
	Rectangle _source = { 0, 0, 176, 176 };
};

struct Wall
{
	Wall(Vector2 pos) noexcept : _position(pos) {};

	void Set_Position(Vector2 position);
	void Set_Health(int health);
	void Set_Radius(float radius);
	void Set_Inactive();
	
	Vector2 Get_Position() const;
	bool    Is_Active() const;
	float   Get_Radius() const;
	int     Get_Health() const;

	void Render(const Texture2D& texture) const noexcept;
	void Update() noexcept;

private:
	Rectangle _source = { 0, 0, 704, 704 };
	Vector2   _position{};
	bool      _active = true;
	int       _health = 50;
	float     _radius = 60;
};

struct Alien
{
	Alien(Vector2 pos) noexcept : _position(pos) {};

	Color color = WHITE;
	Rectangle source = { 0, 0, 352, 352 };

	int x = 0;
	int y = 0;

	void Set_Position(Vector2 position);
	void Set_Radius(float radius);
	void Set_Speed(int speed);
	void Set_Inactive();

	Vector2 Get_Position() const;
	float   Get_Radius() const;
	bool    Is_Active() const;
	int     Get_Speed() const;

	void Update() noexcept;
	void Render(const Texture2D& texture) const noexcept;

private:
	Vector2 _position = { 0, 0 };
	float   _radius = 30;
	bool    _active = true;
	bool    _moveRight = true;
	int		_speed = 2;
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