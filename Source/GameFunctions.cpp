#include "game.hpp"

void Game::InitWalls()
{
	constexpr int   kWallCount = 5;
	constexpr float kWallYOffset = 250.0f;

	assert(FscreenWidth > 0);
	assert(FscreenHeight > 0);

	const float wallSpacing = FscreenWidth / (kWallCount + 1);
	assert(wallSpacing > 0.0f);

	for (int i = 0; i < kWallCount; ++i)
	{
		Walls.emplace_back(Vector2{ wallSpacing * (i + 1), FscreenHeight - kWallYOffset });
	}
}

void Game::RemoveDeadEntities()
{
	Projectiles.erase(std::remove_if(Projectiles.begin(), Projectiles.end(), [](const Projectile& p)
		{ return !p.Is_Active(); }), Projectiles.end());

	Aliens.erase(std::remove_if(Aliens.begin(), Aliens.end(), [](const Alien& a)
		{ return !a.Is_Active(); }), Aliens.end());

	Walls.erase(std::remove_if(Walls.begin(), Walls.end(), [](const Wall& w)
		{return !w.Is_Active(); }), Walls.end());
}

void Game::SpawnAliens()
{
	constexpr int formationWidth = 8;
	constexpr int formationHeight = 5;
	constexpr float alienSpacing = 80.0f;
	constexpr float formationX = 100.0f;
	constexpr float formationY = 50.0f;

	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			const Vector2 position = { formationX + 450.0f + (col * alienSpacing), formationY + (row * alienSpacing) };

			Alien newAlien(position);
			Aliens.push_back(newAlien);

			std::print("Find Alien -X: {}\n", newAlien.Get_Position().x);
			std::print("Find Alien -Y: {}\n", newAlien.Get_Position().y);
		}
	}
}

void Game::AlienShootingHandle()
{
	constexpr int ShootIntervalFrames = 1;

	shootTimer += GetFrameTime();

	if (shootTimer < ShootIntervalFrames || Aliens.empty())
	{
		return;
	}

	constexpr float ProjectileYOffset = 40.0f;
	const size_t alienIndex = rand() % Aliens.size();
	auto it = Aliens.begin() + alienIndex;
	Vector2 spawnPos = it->Get_Position();

	spawnPos.y += ProjectileYOffset;

	Projectiles.emplace_back(spawnPos, false);

	shootTimer = 0;
}

std::optional<Vector2> Game::GetPlayerShootPosition() const noexcept
{
	if (player.Get_Lives() <= 0)
	{
		return std::nullopt;
	}

	return Vector2{ player.Get_Position(), screenHeight - 130.0f };
}

void Game::PlayerShootingHandle()
{
	auto pos = GetPlayerShootPosition();

	if (!pos)
	{
		return;
	}

	Projectiles.emplace_back(*pos, true);
}

bool Game::NewHighscore() const
{
	return board.newHighScore;
}

bool Game::GameEnd() const
{
	return gameEnd;
}

void Background::Update(float offset)
{
	for (auto& s : Stars) {
		s.Update(offset);
	}
}

void Background::Render() const noexcept
{
	for (const auto& s : Stars) {
		s.Render();
	}
}

void Game::End() noexcept
{
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	board.newHighScore = board.CheckNewHighScore();
	gameEnd = true;
}

void Game::board_update()
{
	board.Update();
}

void Game::board_render() const
{
	board.Render();
}