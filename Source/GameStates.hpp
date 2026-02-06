#include "game.hpp"

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

struct GameState
{
	GameState() {
		gameState = State::STARTSCREEN;
	}

	void Update();
	void Render() const;

private:

	State gameState = {};
	Game game;
};