#include "GameStates.hpp"

void GameState::Update()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
	{
		if (IsKeyReleased(KEY_SPACE))
		{
			gameState = State::GAMEPLAY;
		}

		break;
	}
	case State::GAMEPLAY:
	{
		game.Update();

		if (game.GameEnd()) {
			gameState = State::ENDSCREEN;
		}
	}
	break;
	case State::ENDSCREEN:
	{
		if (IsKeyReleased(KEY_ENTER) && !game.NewHighscore())
		{
			gameState = State::STARTSCREEN;
			game.reset();
		}

		game.board_update();
		break;
	}
	}
}

void GameState::Render() const
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
		game.Render();
		break;
	}
	case State::ENDSCREEN:
	{
		game.board_render();
		break;
	}
	}
}