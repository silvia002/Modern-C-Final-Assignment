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

	const float BLINK_INTERVAL = 0.5f;
	bool visible = true;
	float blinkTimer = 0.0f;

	int score = 0;

	std::vector<PlayerData> leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	std::string name{};

	bool CheckNewHighScore() noexcept;

	void InsertNewHighScore(std::string Name);

	std::expected<char, LeaderBoardError> GetKey(int key) noexcept;

	void Update();
	void Render() const noexcept;

	Rectangle textBox = { 600, 500, 225, 50 };
};