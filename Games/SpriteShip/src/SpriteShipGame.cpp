#include "SpriteShipGame.h"

#include "SDL_image.h"

#include "Component/AnimateSpriteComponent.h"

#include "MultiExtend.h"

#include <iostream>

int SDL_SetRenderDrawColor(SDL_Renderer* render, Color& color)
{
	return SDL_SetRenderDrawColor(render, color[R], color[G], color[B], color[A]);
}

SpriteShip::SpriteShip()
	:m_window(nullptr), m_renderer(nullptr),player(nullptr),
	m_resolution_w(SpriteShipResolution_W), m_resolution_h(SpriteShipResolution_H),
	m_tickcount(0), m_delta(0),
	m_isRunning(false)
{
	std::cout << ProcessName << " Constructed" << std::endl;
}

SpriteShip::~SpriteShip()
{
	IMG_Quit();

	if (m_isRunning)
	{
		Get().ShutDown();
		m_isRunning = false;
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}

	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	std::cout << ProcessName << " Destructed" << std::endl;
}

SpriteShip& SpriteShip::Get()
{
	static SpriteShip instance;
	return instance;
}

bool SpriteShip::Initialize()
{
	if (!MultiExtend::Init())
	{
		return false;
	};

	Get().m_window = SDL_CreateWindow(ProcessName, 
		100, 100, 
		Get().m_resolution_w, Get().m_resolution_h,0);

	if (!Get().m_window)
	{
		SDL_Log("SDL create window error:%s", SDL_GetError());
		return false;
	}

	Get().m_renderer = SDL_CreateRenderer(Get().m_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!Get().m_renderer)
	{
		SDL_Log("SDL create renderer error:%s", SDL_GetError());
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		SDL_Log("SDL init image module error:%s", SDL_GetError());
		return false;
	};

	Get().m_isRunning = true;

	Get().bkg = new BackGround(Get().m_renderer);
	Get().player = new Ship(Get().m_renderer, "RocketPlayer", Vector3(100.0f, 200.0f, 0.0f),Vector3(2.0f,2.0f,2.0f));

	

	return true;
}

void SpriteShip::Runloop()
{
	while (Get().m_isRunning)
	{
		Get().ProcessInput();
		Get().UpdateGame();
		Get().GenerateOuput();
	}
}

void SpriteShip::ShutDown()
{
	IMG_Quit();

	SDL_DestroyWindow(Get().m_window);
	SDL_DestroyRenderer(Get().m_renderer);
	
	SDL_Quit();

	Get().m_isRunning = false;
}

void SpriteShip::ProcessInput()
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
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		m_isRunning = false;
	}

	ToggleBorder(state, SDL_SCANCODE_LCTRL, SDL_SCANCODE_F);

	if (state[SDL_SCANCODE_W]) 
	{
		Vector3 location = player->GetPosition();
		float y = location.y - ShipSpeed * m_delta;

		MultiExtend::Math::limit_min(y,0);

		player->SetPosition(Vector3(location.x, y, location.z));
	}

	if (state[SDL_SCANCODE_S])
	{
		Vector3 location = player->GetPosition();
		float y = location.y + ShipSpeed * m_delta;

		MultiExtend::Math::limit_max(y, (float)m_resolution_h);

		player->SetPosition(Vector3(location.x, y, location.z));
	}

	if (state[SDL_SCANCODE_A])
	{
		Vector3 location = player->GetPosition();
		float x = location.x - ShipSpeed * m_delta;

		MultiExtend::Math::limit_min(x, 0);

		player->SetPosition(Vector3(x, location.y, location.z));
	}

	if (state[SDL_SCANCODE_D])
	{
		Vector3 location = player->GetPosition();
		float x = location.x + ShipSpeed * m_delta;

		MultiExtend::Math::limit_max(x, (float)m_resolution_w);

		player->SetPosition(Vector3(x, location.y, location.z));
	}
}

void SpriteShip::UpdateGame()
{
	int ticks;

	// limit the frame time span to 16ms
	while (!SDL_TICKS_PASSED(ticks = SDL_GetTicks(), m_tickcount + 16));

	m_delta = (ticks - m_tickcount) / 1000.0f;
	m_tickcount = ticks;

	MultiExtend::Math::limit_min(m_delta, 0.05f);

	GameOBJECT::Update(m_delta);

#ifdef SpriteShipDebug
	SDL_Log("Delta:%.3f", m_delta);
#endif
}

void SpriteShip::GenerateOuput()
{
	Color bkgcolor(0.05f, 0.05f, 0.1f, 1.0f);
	SDL_SetRenderDrawColor(m_renderer, bkgcolor);
	SDL_RenderClear(m_renderer);

	GameOBJECT::Draw();

	SDL_RenderPresent(m_renderer);
}

void SpriteShip::ToggleBorder(const Uint8* state, const SDL_Scancode& key1, const SDL_Scancode& key2)
{
	if (state[key1])
	{
		KT_pair tag = {key2,"ToggleBorder"};

		if (state[key2])
		{
			if (AssignPressedKeyTagPair(tag))
			{
				if (SDL_GetWindowFlags(m_window) & SDL_WINDOW_BORDERLESS)
				{
					SDL_SetWindowBordered(m_window, SDL_TRUE);
				}
				else
				{
					SDL_SetWindowBordered(m_window, SDL_FALSE);
				}
			}
		}
		else
		{
			ReleasePressedKeyTagPair(tag);
		}
	}
}

bool SpriteShip::AssignPressedKeyTagPair(KT_pair& key)
{
	if (std::find_if(m_pressedkey_tag.begin(), m_pressedkey_tag.end(), [key](const KT_pair& keyCheck)->bool {return key == keyCheck;}) 
		== m_pressedkey_tag.end())
	{
		m_pressedkey_tag.emplace_back(key);
		return true;
	}

#ifdef SpriteShipDebug
	std::cout << "tag count:" << m_pressedkey_tag.size() << std::endl;
#endif

	return false;
}

void SpriteShip::ReleasePressedKeyTagPair(const KT_pair& key)
{
	auto it = std::remove_if(m_pressedkey_tag.begin(), m_pressedkey_tag.end(), [key](const KT_pair& keyCheck)->bool {return key == keyCheck; });
	
	m_pressedkey_tag.erase(it,m_pressedkey_tag.end());

#ifdef SpriteShipDebug
	std::cout << "tag count:" << m_pressedkey_tag.size() << std::endl;
#endif
}

bool KT_pair::operator==(const KT_pair other) const
{
	return (key == other.key && *tag == *other.tag);
}