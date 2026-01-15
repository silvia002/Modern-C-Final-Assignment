#include "Entities.hpp"
#include <vector>

void Player::Update() noexcept
{
	assert(FscreenWidth > 0);

	direction = 0;

	if (IsKeyDown(KEY_LEFT))  
	{
		direction = -1;
	}
	if (IsKeyDown(KEY_RIGHT)) 
	{
		direction = +1;
	}

	x_pos += speed * direction;

	const float minX = radius;
	const float maxX = FscreenWidth - radius;
	assert(minX <= maxX);

	x_pos = std::clamp(x_pos, minX, maxX);

	timer += GetFrameTime();
	assert(timer >= 0.0f);

	constexpr int kFrameCount = 3;
	assert(activeTexture >= 0 && activeTexture < kFrameCount);

	if (timer >= 0.4f)
	{
		activeTexture = (activeTexture + 1) % kFrameCount;
		timer = 0.0f;
	}
}

void Player::Render(const Texture2D& texture) const noexcept
{
	const Rectangle destination = { x_pos, FscreenHeight - player_base_height, 100, 100 };
	DrawTexturePro(texture, source, destination, { 50, 50 }, 0, WHITE);
}

void Projectile::Update() noexcept
{
	assert(speed >= 0.0f);

	constexpr float ScreenTop = 0.0f;
	constexpr float ScreenBottom = 1500.0f;

	const float dir = (type == EntityType::PLAYER_PROJECTILE) ? -1.0f : 1.0f;
	position.y += speed * dir;

	rec.x = position.x - rec.width * 0.5f;
	rec.y = position.y - rec.height * 0.5f;

	if (position.y < ScreenTop || position.y > ScreenBottom) 
	{
		active = false;
	}
}

void Projectile::Render(Texture2D& texture) const noexcept
{
	const Rectangle destination = { position.x, position.y, 50, 50,};
	DrawTexturePro(texture, source, destination, { 25 , 25 }, 0, WHITE);
}

void Wall::Render(Texture2D& texture) const noexcept
{
	const Rectangle destination = { position.x, position.y, 200, 200 };

	DrawTexturePro(texture, source, destination , { 100 , 100 }, 0, WHITE);
	DrawText(TextFormat("%i", health), static_cast<int>(position.x) - 21, static_cast<int>(position.y) + 10, 40, RED);
}

void Wall::Update() noexcept
{
	if (health < 1)
	{
		active = false;
	}
}

void Alien::Update() noexcept
{
	moveRight ? position.x += speed : position.x -= speed;

	if (position.x >= FscreenWidth)
	{
		moveRight = false;
		position.y += 50;
	}

	if (position.x <= 0)
	{
		moveRight = true;
		position.y += 50;
	}
}

void Alien::Render(Texture2D& texture) const noexcept
{
	const Rectangle destination = { position.x, position.y, 100, 100 };
	DrawTexturePro(texture, source, destination, { 50 , 50 }, 0, WHITE);
}


//BACKGROUND
void Star::Update(float starOffset) noexcept
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;
}

void Star::Render() const noexcept
{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, color);
}
