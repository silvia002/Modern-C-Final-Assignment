#include "game.hpp"

void Game::Start()
{
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();

	InitWalls();
	SpawnAliens();
	background.Initialize(600);

	assert(!Aliens.empty());
	assert(!Walls.empty());

	board.score = 0;
	shootTimer = 0;
	gameState = State::GAMEPLAY;
}

void Game::End() noexcept
{
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	background.Stars.clear();
	player.lives = 3;
	player.x_pos = FscreenWidth / 2;
	board.newHighScore = board.CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue() noexcept
{
	gameState = State::STARTSCREEN;
}

void Game::Update()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
	{
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();
		}

		break;
	}
	case State::GAMEPLAY:
	{
		RemoveDeadEntities();
		if (IsKeyReleased(KEY_Q)) { End(); }

		if (player.lives < 1) { End(); }

		player.Update();

		for (auto& a : Aliens)
		{
			if (!a.active) 
			{
				continue;
			}
			a.Update();

			if (a.position.y > screenHeight - player.player_base_height) { End(); }
		}

		if (Aliens.size() < 1) { SpawnAliens(); }

		const float offset = -player.x_pos;
		background.Update(offset / 15.0f);

		for (auto& p : Projectiles) {
			p.Update();
		}
		for (auto& w : Walls) {
			w.Update();
		}

		CheckCollision();
		if (IsKeyPressed(KEY_SPACE)) { PlayerShootingHandle(); }
		AlienShootingHandle();
	}
	break;
	case State::ENDSCREEN:
	{
		if (IsKeyReleased(KEY_ENTER) && !board.newHighScore)
		{
			Continue();
		}

		board.Update();
		break;
	}
	}
}

void Game::Render()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
	{
		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
		break;
	}
	case State::GAMEPLAY:
	{
		background.Render();

		DrawText(TextFormat("Score: %i", board.score), 50, 20, 40, YELLOW);
		DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

		int i = 0;
		for (auto& p : resources.shipTextures) {
			if (i++ == player.activeTexture) {
				player.Render(p);
				break;
			}
		}
		for (const auto& p : Projectiles) {
			if (!p.active) continue;
			p.Render(resources.laserTexture);
		}
		for (const auto& w : Walls) {
			if (!w.active) continue;
			w.Render(resources.barrierTexture);
		}
		for (const auto& a : Aliens) {
			if (!a.active) continue;
			a.Render(resources.alienTexture);
		}

		break;
	}
	case State::ENDSCREEN:
	{
		board.Render();
		break;
	}
	}
}