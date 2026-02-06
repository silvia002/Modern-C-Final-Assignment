#include "game.hpp"

void Game::Update()
{
	RemoveDeadEntities();
	if (IsKeyReleased(KEY_Q)) { End(); }

	if (player.Get_Lives() < 1) { End(); }

	player.Update();

	for (auto& a : Aliens)
	{
		if (!a.Is_Active())
		{
			continue;
		}
		a.Update();

		if (a.Get_Position().y > screenHeight - player.Get_Radius()) { End(); }
	}

	if (Aliens.size() < 1) { SpawnAliens(); }

	const float offset = -player.Get_Position();
	background.Update(offset / 15.0f);

	for (auto& p : Projectiles) {
		p.Update();
	}
	for (auto& w : Walls) {
		w.Update();
	}

	CheckCollision();
	if (IsKeyPressed(KEY_SPACE)) 
	{ 
		PlayerShootingHandle(); 
	}

	AlienShootingHandle();
}

void Game::Render() const
{
	background.Render();

	DrawText(TextFormat("Score: %i", board.score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.Get_Lives()), 50, 70, 40, YELLOW);

	int i = 0;
	for (const auto& p : resources.ships) {
		if (i++ == player.Get_Active_Texture()) {
			player.Render(p.get().get_texture());
			break;
		}
	}

	for (const auto& p : Projectiles) {
		if (!p.Is_Active()) continue;
		p.Render(resources.laser.get_texture());
	}
	for (const auto& w : Walls) {
		if (!w.Is_Active()) continue;
		w.Render(resources.barrier.get_texture());
	}
	for (const auto& a : Aliens) {
		if (!a.Is_Active()) continue;
		a.Render(resources.alien.get_texture());
	}
}