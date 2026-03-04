#pragma once
#include "raylib.h"
#include <array>
#include <vector>
#include <string>
#include <string_view>
using namespace std::string_view_literals;
struct Window {
	Window(int width, int height) {
		InitWindow(width, height, "SPACE INVADERS");
		if (!IsWindowReady()) {
			throw std::runtime_error("Failed to initialize window");
		}
	}

	~Window() noexcept {
		CloseWindow();
	}

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&&) noexcept = delete;
	Window& operator=(Window&&) noexcept = delete;
};

struct NewTexture {
	NewTexture(const std::string_view& path)
		: _texture(LoadTexture(path.data()))
	{
		if (_texture.id == 0)
			throw std::runtime_error("Failed to load texture: ");
	}

	~NewTexture() noexcept {
		if (_texture.id != 0) {
			UnloadTexture(_texture);
		}
	}

	NewTexture(const NewTexture&) = delete;
	NewTexture& operator=(const NewTexture&) = delete;

	NewTexture(NewTexture&& other) noexcept
		: _texture(std::exchange(other._texture, {})) {
	}

	NewTexture& operator=(NewTexture&& other) noexcept {
		if (this != &other) {
			UnloadTexture(_texture);
			_texture = std::exchange(other._texture, {});
		}
		return *this;
	}

	const Texture2D& get_texture() const {
		return _texture;
	}

private:
	Texture2D _texture{};
};


struct Resources {	
	NewTexture alien{ "./Assets/Alien.png"sv };
	NewTexture barrier{ "./Assets/Barrier.png"sv };
	NewTexture laser{ "./Assets/Laser.png"sv };

	std::array<NewTexture, 3> ships{ "./Assets/Ship1.png"sv, "./Assets/Ship2.png"sv, "./Assets/Ship3.png"sv };
};


struct StartDrawing
{
	StartDrawing() noexcept
	{
		BeginDrawing();
	}

	~StartDrawing() noexcept
	{
		EndDrawing();
	}

	StartDrawing(const StartDrawing&) = delete;
	StartDrawing& operator=(const StartDrawing&) = delete;
};