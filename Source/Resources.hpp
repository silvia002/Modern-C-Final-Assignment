#pragma once
#include "raylib.h"
#include "vector"
#include <string>
#include <string_view>

struct Window {
	Window(int width, int height) {
		InitWindow(width, height, "SPACE INVADERS");
		if (!IsWindowReady()) {
			throw std::runtime_error("Failed to initialize window");
		}
	}

	~Window() {
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

	~NewTexture() {
		if (_texture.id != 0) {
			UnloadTexture(_texture);
			_texture = {};
		}
	}

	NewTexture(const NewTexture&) = delete;
	NewTexture& operator=(const NewTexture&) = delete;

	NewTexture(NewTexture&& other) noexcept
		: _texture(other._texture) {
		other._texture = {};
	}

	NewTexture& operator=(NewTexture&& other) noexcept {
		if (this != &other) {
			UnloadTexture(_texture);
			_texture = other._texture;
			other._texture = {};
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
private:
	std::string_view _alien_path = "./Assets/Alien.png";
	std::string_view _barrier_path = "./Assets/Barrier.png";
	std::string_view _ship1_path = "./Assets/Ship1.png";
	std::string_view _ship2_path = "./Assets/Ship2.png";
	std::string_view _ship3_path = "./Assets/Ship3.png";
	std::string_view _laser_path = "./Assets/Laser.png";

public:
	Resources()
		: alien(_alien_path),
		barrier(_barrier_path),
		ship1(_ship1_path),
		ship2(_ship2_path),
		ship3(_ship3_path),
		laser(_laser_path),
		ships{ ship1, ship2, ship3 }
	{
	}

	NewTexture alien;
	NewTexture barrier;
	NewTexture ship1;
	NewTexture ship2;
	NewTexture ship3;
	NewTexture laser;

	std::vector<std::reference_wrapper<const NewTexture>> ships;
};


struct StartDrawing
{
	StartDrawing()
	{
		BeginDrawing();
	}

	~StartDrawing()
	{
		EndDrawing();
	}

	StartDrawing(const StartDrawing&) = delete;
	StartDrawing& operator=(const StartDrawing&) = delete;
};