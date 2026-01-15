#include "Leaderboard.hpp"
#include <ranges>
#include <algorithm>
#include <string_view>

inline static void DrawRectangleLines(float x, float y, float width, float height, Color color) noexcept {
	DrawRectangleLines(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), color);
}

inline static void DrawText(const char* text, float posX, float posY, int fontSize, Color color) noexcept {
	DrawText(text, static_cast<int>(posX), static_cast<int>(posY), fontSize, color);
}

inline static int MeasureText(const std::string& text, int fontSize) noexcept {
	return MeasureText(text.c_str(), fontSize);
}

bool Leaderboard::CheckNewHighScore() noexcept
{
	const auto& lowest = std::ranges::min(leaderboard, {}, &PlayerData::_score);
	return score > lowest._score;
}

void Leaderboard::InsertNewHighScore(std::string Name)
{
	PlayerData newData(Name, score);

	for (auto it = leaderboard.begin(); it != leaderboard.end(); ++it) {
		if (newData._score > it->_score) {

			leaderboard.insert(it, newData);
			leaderboard.pop_back();

			break;
		}
	}
}

std::expected<char, LeaderBoardError> Leaderboard::GetKey(int key) noexcept
{
	if (key < 32 || key > 125) 
	{
		return std::unexpected(LeaderBoardError::InvalidKey);
	}

	return static_cast<char>(key);
}

void Leaderboard::Update() {
	if (!newHighScore) 
	{
		return;
	}
	
	const int raw = GetCharPressed();

	auto key = GetKey(raw);

	if (key && name.size() < 8) 
	{
		name.push_back(*key);
	}

	if (IsKeyPressed(KEY_BACKSPACE) && !name.empty()) 
	{
		name.pop_back();
	}

	if (!name.empty() && name.size() <= 8 && IsKeyReleased(KEY_ENTER))
	{
		InsertNewHighScore(name);
		newHighScore = false;
	}

	blinkTimer += GetFrameTime();
	if (blinkTimer >= BLINK_INTERVAL)
	{
		blinkTimer = 0.0f;
		visible = !visible;
	}
}

void Leaderboard::Render() const noexcept{
	if (newHighScore)
	{
		DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);
		DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

		DrawRectangleRec(textBox, LIGHTGRAY);
		DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, RED);

		DrawText(name.c_str(), textBox.x + 5, textBox.y + 8, 40, MAROON);

		DrawText(TextFormat("INPUT CHARS: %zu/%i", name.length(), 8), 600, 600, 20, YELLOW );

		const int textWidth = MeasureText(name.c_str(), 40);

		if (name.length() < 8 && visible)
		{
			DrawText("_", textBox.x + 8 + textWidth, textBox.y + 12, 40, MAROON);
		}

		if (name.length() > 0)
		{
			DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
		}

		return;
	}

	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);
	int i = 0;
	for (const auto& l : leaderboard)
	{
		const int y = 140 + (i++ * 40);
		DrawText(l._name.c_str(), 50, y, 40, YELLOW);
		DrawText(TextFormat("%i", l._score), 350, y, 40, YELLOW);
	}
	
}