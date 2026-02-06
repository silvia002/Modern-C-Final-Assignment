#include "Entities.hpp"

void Player::Update() noexcept
{
	assert(FscreenWidth > 0);

	Set_Direction(0);

	if (IsKeyDown(KEY_LEFT))  
	{
		Set_Direction(-1);
	}
	if (IsKeyDown(KEY_RIGHT)) 
	{
		Set_Direction(+1);
	}

	
	Set_Position(_pos_x + Get_Speed() * Get_Direction());

	const float minX = Get_Radius();
	const float maxX = FscreenWidth - Get_Radius();
	assert(minX <= maxX);

	Set_Position( std::clamp(Get_Position(), minX, maxX));

	timer += GetFrameTime();
	assert(timer >= 0.0f);

	constexpr int kFrameCount = 3;
	assert(Get_Active_Texture() >= 0 && Get_Active_Texture() < kFrameCount);

	if (timer >= 0.4f)
	{
		_activeTexture = (Get_Active_Texture() + 1) % kFrameCount;
		timer = 0.0f;
	}
}

void Player::Render(const Texture2D& texture) const noexcept
{
	const Rectangle destination = { Get_Position(), FscreenHeight - Get_Radius(), 100, 100};
	DrawTexturePro(texture, source, destination, { 50, 50 }, 0, WHITE);
}

void Projectile::Update() noexcept
{
	assert(Get_Speed() >= 0.0f);

	constexpr float ScreenTop = 0.0f;
	constexpr float ScreenBottom = 1500.0f;

	_direction = (Is_Player_Bullet()) ? -1 : 1;

	Vector2 newPos = { Get_Position().x, Get_Position().y + Get_Speed() * _direction };

	Set_Position(newPos);

	_rec.x = Get_Position().x - _rec.width * 0.5f;
	_rec.y = Get_Position().y - _rec.height * 0.5f;

	if (Get_Position().y < ScreenTop || Get_Position().y > ScreenBottom)
	{
		_active = false;
	}
}

void Projectile::Render(const Texture2D& texture) const noexcept
{
	const Rectangle destination = { Get_Position().x, Get_Position().y, 50, 50,};
	DrawTexturePro(texture, _source, destination, { 25 , 25 }, 0, WHITE);
}

void Wall::Render(const Texture2D& texture) const noexcept
{
	const Rectangle destination = { Get_Position().x, Get_Position().y, 200, 200};

	DrawTexturePro(texture, _source, destination , { 100 , 100 }, 0, WHITE);
	DrawText(TextFormat("%i", _health), static_cast<int>(Get_Position().x) - 21, static_cast<int>(Get_Position().y) + 10, 40, RED);
}

void Wall::Update() noexcept
{
	if (Get_Health() < 1)
	{
		_active = false;
	}
}

void Alien::Update() noexcept
{
	Vector2 newPos = { Get_Position() };
	_moveRight ? newPos.x += Get_Speed() : newPos.x -= Get_Speed();

	if (Get_Position().x >= FscreenWidth)
	{
		_moveRight = false;
		newPos.y += 50;
	}

	if (Get_Position().x <= 0)
	{
		_moveRight = true;
		newPos.y += 50;
	}

	Set_Position(newPos);
}

void Alien::Render(const Texture2D& texture) const noexcept
{
	const Rectangle destination = { Get_Position().x, Get_Position().y, 100, 100 };
	DrawTexturePro(texture, source, destination, { 50 , 50 }, 0, WHITE);
}

void Star::Update(float starOffset) noexcept
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;
}

void Star::Render() const noexcept
{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, color);
}

void Player::Set_Position(float pos_x)
{
	_pos_x = pos_x;
}

void Player::Set_Speed(float speed)
{
	_speed = speed;
}

void Player::Set_Radius(float radius)
{
	_radius = radius;
}

void Player::Set_Lives(int lives)
{
	_lives = lives;
}

void Player::Set_Direction(int direction)
{
	_direction = direction;
}

float Player::Get_Position() const
{
	return _pos_x;
}

float Player::Get_Speed() const
{
	return _speed;
}

void Wall::Set_Position(Vector2 position)
{
	_position = position;
}

void Wall::Set_Health(int health)
{
	_health = health;
}

void Wall::Set_Radius(float radius)
{
	_radius = radius;
}

void Wall::Set_Inactive() {
	_active = false;
}

bool Wall::Is_Active() const {
	return _active;
}

Vector2 Wall::Get_Position() const {
	return _position;
}

float Wall::Get_Radius() const {
	return _radius;
}

int Wall::Get_Health() const {
	return _health;
}

bool Projectile::Is_Active() const
{
	return _active;
}

bool Projectile::Is_Player_Bullet() const
{
	return _player_Bullet;
}

int Projectile::Get_Speed()  const {
	return _speed;
}

void Projectile::Set_Position(Vector2 position)
{
	_position = position;
}

void Projectile::Set_Speed(int speed)
{
	_speed = speed;
}

void Projectile::Set_Direction(int direction) {
	_direction = direction;
}

void Projectile::Set_Inactive()
{
	_active = false;
}

Rectangle Projectile::Get_Rec() const
{
	return _rec;
}

Vector2 Projectile::Get_Position() const {
	return _position;
}

float Player::Get_Radius() const
{
	return _radius;
}

int Player::Get_Active_Texture() const
{
	return _activeTexture;
}

int Player::Get_Lives() const
{
	return _lives;
}

int Player::Get_Direction() const
{
	return _direction;
}

void Alien::Set_Position(Vector2 position) {
	_position = position;
}

void Alien::Set_Radius(float radius) {
	_radius = radius;
}

void Alien::Set_Speed(int speed) {
	_speed = speed;
}

void Alien::Set_Inactive() {
	_active = false;
}

Vector2 Alien::Get_Position() const {
	return _position;
}

float Alien::Get_Radius() const {
	return _radius;
}

bool Alien::Is_Active() const {
	return _active;
}

int Alien::Get_Speed() const {
	return _speed;
}