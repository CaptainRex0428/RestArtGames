#pragma once

#include <vector>

#include "SDL.h"

#include "Math/Color.h"
#include "Racket.h"
#include "Ball.h"

#define PongNDebug
#define KeyNDebug

class Pong
{
public:
	Pong(Pong&) = delete;

	static bool Initialize();
	static void RunLoop();
	static void ShutDown();

private:
	Pong();
	~Pong();

	static Pong& Get();

	void ProcessInput();
	void UpdateGame();
	void GenerateOuput();

private:
	SDL_Window * m_Window;
	SDL_Renderer* m_Renderer;
	bool m_isRunning;

	int m_ticksCount;
	float m_delta;
	
	int m_resolution_w;
	int m_resolution_h;

	std::vector<SDL_Rect> m_walls;

	Racket * m_racket;
	Ball* m_ball;

	bool canHorizonMove;
};