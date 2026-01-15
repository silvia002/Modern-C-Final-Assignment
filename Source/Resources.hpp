#pragma once
#include "raylib.h"
#include "vector"

struct Window {
	Window(int width, int height) noexcept {
		InitWindow(width, height, "SPACE INVADERS");
	}

	~Window() {
		CloseWindow();
	}

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&&) noexcept = default;
	Window& operator=(Window&&) noexcept = default;
};

struct Resources {
	Resources() noexcept {
		alienTexture = LoadTexture("./Assets/Alien.png");
		barrierTexture = LoadTexture("./Assets/Barrier.png");
		shipTextures.push_back(LoadTexture("./Assets/Ship1.png"));
		shipTextures.push_back(LoadTexture("./Assets/Ship2.png"));
		shipTextures.push_back(LoadTexture("./Assets/Ship3.png"));
		laserTexture = LoadTexture("./Assets/Laser.png");
	};

	~Resources() {
		UnloadTexture(alienTexture);
		UnloadTexture(barrierTexture);
		UnloadTexture(laserTexture);

		for (const Texture2D& t : shipTextures) {
			UnloadTexture(t);
		}
	}

	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

	Resources(Resources&&) = default;
	Resources& operator=(Resources&&) = default;

	std::vector<Texture2D> shipTextures{};
	Texture2D alienTexture{};
	Texture2D barrierTexture{};
	Texture2D laserTexture{};
};

struct StartDrawing
{
	StartDrawing() noexcept
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