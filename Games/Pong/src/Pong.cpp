#include "Pong.h"

#include <iostream>

#include "Math/Math.h"

int SDL_SetRenderDrawColor(SDL_Renderer* render, Color& color)
{
	return SDL_SetRenderDrawColor(render, color[R], color[G], color[B], color[A]);
}

Pong::Pong()
	:m_isRunning(false),
	m_ticksCount(0),m_delta(0), 
	m_Window(nullptr), m_Renderer(nullptr), 
	m_resolution_w(1024), m_resolution_h(768), 
	m_racket(nullptr), m_ball(nullptr),
	canHorizonMove(false)
{
	std::cout << "Pong Constructed" << std::endl;
}

Pong::~Pong()
{
	if (m_isRunning)
	{
		Get().ShutDown();
		m_isRunning = false;
	}

	if (m_Window)
	{
		SDL_DestroyWindow(m_Window);
	}

	if (m_Renderer)
	{
		SDL_DestroyRenderer(m_Renderer);
	}

	std::cout << "Pong Destructed" << std::endl;
}

Pong& Pong::Get()
{
	static Pong instance;
	return instance;
}

bool Pong::Initialize()
{
	int sdlVedioResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlVedioResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	Get().m_Window = SDL_CreateWindow(
		"Pong",
		100,100,
		Get().m_resolution_w, Get().m_resolution_h,
		0);

	if (!Get().m_Window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	Get().m_Renderer = SDL_CreateRenderer(Get().m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!Get().m_Renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	Get().m_isRunning = true;
	
	// init walls
	int thickness = 20;
	Get().m_walls.emplace_back(SDL_Rect(0,0,Get().m_resolution_w,thickness));
	Get().m_walls.emplace_back(SDL_Rect(0,Get().m_resolution_h - thickness,Get().m_resolution_w,thickness));
	Get().m_walls.emplace_back(SDL_Rect(Get().m_resolution_w - thickness,thickness,thickness,Get().m_resolution_h - thickness));
	Get().m_walls.emplace_back(SDL_Rect(0,thickness,thickness,Get().m_resolution_h - thickness));

	// init racket
	Get().m_racket = new Racket(40.0f,(float)(Get().m_resolution_h/2),20.0f,200.0f,Color(0.8f,0.8f,0.8f,1.0f));

	//init ball
	Get().m_ball = new Ball((float)(Get().m_resolution_w / 2), (float)(Get().m_resolution_h / 2), 25, 25, DefaultBallColor);

	return true;
}

void Pong::RunLoop()
{
	while (Get().m_isRunning)
	{
		Get().ProcessInput();
		Get().UpdateGame();
		Get().GenerateOuput();
	}
}

void Pong::ShutDown()
{
	SDL_DestroyWindow(Get().m_Window);
	SDL_DestroyRenderer(Get().m_Renderer);
	SDL_Quit();

	Get().m_isRunning = false;
}

void Pong::ProcessInput()
{
	// handle events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_isRunning = false;
				break;
			default:
				continue;
		}
	}

	// handle keyboard input
	const Uint8 * state = SDL_GetKeyboardState(NULL);
	
	if (state[SDL_SCANCODE_ESCAPE])
	{
#ifdef KeyDebug
		std::cout << "ESC" << std::endl;
#endif
		m_isRunning = false;
	}

	if (state[SDL_SCANCODE_W])
	{
		m_racket->move(Vector2(0, -1.0f),m_delta);
	}

	if (state[SDL_SCANCODE_S])
	{
		m_racket->move(Vector2(0, 1.0f),m_delta);
	}

	if (canHorizonMove = state[SDL_SCANCODE_LSHIFT])
	{
		if (state[SDL_SCANCODE_A])
		{
			m_racket->move(Vector2(-1.0f, 0), m_delta);
		}

		if (state[SDL_SCANCODE_D])
		{
			m_racket->move(Vector2(1.0f, 0), m_delta);
		}
	}
}

void Pong::UpdateGame()
{
	// ball move
	m_ball->move(m_delta);
	
	int ticks;

	// limit the frame time span to 16ms
	while (!SDL_TICKS_PASSED(ticks = SDL_GetTicks(), m_ticksCount + 16));

	m_delta = (ticks - m_ticksCount)/1000.0f;
	m_ticksCount = ticks;

	MultiExtend::Math::limit_min(m_delta, 0.05f);

#ifdef PongDebug
	SDL_Log("Delta:%.3f", m_delta);
#endif
	
	// collision test

	m_ball->collision(m_racket);

	for (SDL_Rect& wall : m_walls)
	{
		m_racket->collision(&wall);
		m_ball->collision(&wall);
	}

	// end check
	if (m_isRunning) 
	{
		m_isRunning = m_ball->isalive((float)m_resolution_w, (float)m_resolution_h);
	}

}

void Pong::GenerateOuput()
{
	// BKG
	Color bkgcolor(0.2f, 0.1f, 0.3f, 1.0f);
	SDL_SetRenderDrawColor(m_Renderer,bkgcolor);
	SDL_RenderClear(m_Renderer);

	// WALL
	Color wallcolor(1.0f, 1.0f, 1.0f, 1.0f);
	SDL_SetRenderDrawColor(m_Renderer, wallcolor);

	for (auto& wall: m_walls)
	{
		SDL_RenderFillRect(m_Renderer, &wall);
	}

	// RACKET
	SDL_SetRenderDrawColor(m_Renderer, m_racket->getInstanceColor());
	SDL_RenderFillRect(m_Renderer, m_racket->getSDLDrawInstance());

	// Ball
	SDL_SetRenderDrawColor(m_Renderer, m_ball->getInstnaceColor());
	SDL_RenderFillRect(m_Renderer,m_ball->getSDLDrawInstance());

	SDL_RenderPresent(m_Renderer);
}



