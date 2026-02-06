#include "raylib.h"
#include <string>
#include <vector>
#include <expected>
#include <print>

struct PlayerData
{
	PlayerData(std::string name, int score) : _name(name), _score(score) {};

	std::string _name{};
	int _score{};
};

enum class LeaderBoardError {
	None,
	InvalidKey
};

struct Leaderboard {
	bool newHighScore = false;
	float blinkTimer = 0.0f;

	int score = 0;

	bool CheckNewHighScore() noexcept;

	void Update();
	void Render() const noexcept;

private:
	const float BLINK_INTERVAL = 0.5f;
	bool visible = true;

	void InsertNewHighScore(std::string Name);

	std::expected<char, LeaderBoardError> GetKey(int key) noexcept;

	std::vector<PlayerData> leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	std::string name{};
	Rectangle textBox = { 600, 500, 225, 50 };
};