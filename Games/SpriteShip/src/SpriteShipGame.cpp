#include "SpriteShipGame.h"

#include <iostream>

#include "SDL_image.h"

#include "MultiExtend.h"
#include "Component/AnimateSpriteComponent.h"
#include "Component/ScrollComponent.h"


int SDL_SetRenderDrawColor(MultiExtend::Renderer * render, Color& color)
{
	return SDL_SetRenderDrawColor(render->GetRendererAs<SDL_Renderer>(), color[R], color[G], color[B], color[A]);
}

SpriteShipGame::SpriteShipGame()
	:m_window(nullptr), m_renderer(nullptr),player(nullptr),
	m_resolution_w(SpriteShipResolution_W), m_resolution_h(SpriteShipResolution_H),
	m_tickcount(0), m_delta(0),
	m_isRunning(false)
{
	std::cout << ProcessName << " Constructed" << std::endl;

	gmState = CreateGameState<GameState>();
	gameInstance = CreateActor<Actor>(gmState);
}

SpriteShipGame::~SpriteShipGame()
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
		SDL_DestroyRenderer(m_renderer->GetRendererAs<SDL_Renderer>());
	}

	std::cout << ProcessName << " Destructed" << std::endl;
}

SpriteShipGame& SpriteShipGame::Get()
{
	static SpriteShipGame instance;
	return instance;
}

bool SpriteShipGame::Initialize()
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

	SDL_Renderer * renderer = SDL_CreateRenderer(Get().m_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		SDL_Log("SDL create renderer error:%s", SDL_GetError());
		return false;
	}

	Get().m_renderer = new MultiExtend::RendererSDL(renderer);
	Get().m_isRunning = true;
	
	Get().player = CreateActor<Actor>(Get().gmState);
	Get().player->SetUpdateOrder(100);
	
	std::vector<const char*> shiptextures =
	{
		"../Games/SpriteShip/assets/Ship01.png",
		"../Games/SpriteShip/assets/Ship02.png",
		"../Games/SpriteShip/assets/Ship03.png",
		"../Games/SpriteShip/assets/Ship04.png"
	};
	MultiExtend::AnimateSpriteComponent* shipAnimate = new MultiExtend::AnimateSpriteComponent(10, Get().gmState, Get().m_renderer, shiptextures);
	shipAnimate->SetSize(Vector2(64, 29));
	Get().player->AddActorComponent(shipAnimate);

	Get().bkg = CreateActor<Actor>(Get().gmState);
	Get().bkg->SetUpdateOrder(1);

	std::vector<const char*> skytextures =
	{
		"../Games/SpriteShip/assets/Farback01.png",
		"../Games/SpriteShip/assets/Farback02.png"
	};

	MultiExtend::ScrollSpriteComponent* skySprite = new MultiExtend::ScrollSpriteComponent(Get().gmState, Get().m_renderer, skytextures);
	skySprite->SetRenderSize(Vector2(SpriteShipResolution_W, SpriteShipResolution_H));
	skySprite->SetScrollSpeed(10);
	skySprite->SetUpdateOrder(1);
	Get().bkg->AddActorComponent(skySprite);

	std::vector<const char*> startextures =
	{
		"../Games/SpriteShip/assets/Stars.png"
	};

	MultiExtend::ScrollSpriteComponent* starSprite = new MultiExtend::ScrollSpriteComponent(Get().gmState, Get().m_renderer, startextures);
	starSprite->SetRenderSize(Vector2(SpriteShipResolution_W, SpriteShipResolution_H));
	starSprite->SetScrollSpeed(100);
	starSprite->SetUpdateOrder(2);
	Get().bkg->AddActorComponent(starSprite);

	Get().gameInstance->AddChildActor(Get().player);
	Get().gameInstance->AddChildActor(Get().bkg);

	return true;
}

void SpriteShipGame::Runloop()
{
	while (Get().m_isRunning)
	{	
		Get().ProcessInput();
		Get().UpdateGame();
		Get().GenerateOuput();
	}
}

void SpriteShipGame::ShutDown()
{
	IMG_Quit();

	SDL_DestroyWindow(Get().m_window);
	SDL_DestroyRenderer(Get().m_renderer->GetRendererAs<SDL_Renderer>());
	
	SDL_Quit();

	Get().m_isRunning = false;
}

void SpriteShipGame::ProcessInput()
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
		Vector3 location = player->GetPositionAbsolute();
		float y = location.y - ShipSpeed * m_delta;

		MultiExtend::Math::limit_min(y,0);

		player->SetPositionRelative(Vector3(location.x, y, location.z));
	}

	if (state[SDL_SCANCODE_S])
	{
		Vector3 location = player->GetPositionAbsolute();
		float y = location.y + ShipSpeed * m_delta;

		MultiExtend::Math::limit_max(y, (float)m_resolution_h);

		player->SetPositionRelative(Vector3(location.x, y, location.z));
	}

	if (state[SDL_SCANCODE_A])
	{
		Vector3 location = player->GetPositionAbsolute();
		float x = location.x - ShipSpeed * m_delta;

		MultiExtend::Math::limit_min(x, 0);

		player->SetPositionRelative(Vector3(x, location.y, location.z));
	}

	if (state[SDL_SCANCODE_D])
	{
		Vector3 location = player->GetPositionAbsolute();
		float x = location.x + ShipSpeed * m_delta;

		MultiExtend::Math::limit_max(x, (float)m_resolution_w);

		player->SetPositionRelative(Vector3(x, location.y, location.z));
	}
}

void SpriteShipGame::UpdateGame()
{
	int ticks;

	// limit the frame time span to 16ms
	while (!SDL_TICKS_PASSED(ticks = SDL_GetTicks(), m_tickcount + 16));

	m_delta = (ticks - m_tickcount) / 1000.0f;
	m_tickcount = ticks;

	MultiExtend::Math::limit_min(m_delta, 0.05f);

	Get().gameInstance->Update(m_delta);

#ifdef SpriteShipDebug
	SDL_Log("Delta:%.3f", m_delta);
#endif
}

void SpriteShipGame::GenerateOuput()
{
	Color bkgcolor(0.05f, 0.05f, 0.1f, 1.0f);
	SDL_SetRenderDrawColor(m_renderer, bkgcolor);
	
	ClearRenderer(m_renderer);

	Get().gameInstance->Draw();

	RenderPresent(m_renderer);
}

void SpriteShipGame::ToggleBorder(const Uint8* state, const SDL_Scancode& key1, const SDL_Scancode& key2)
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

bool SpriteShipGame::AssignPressedKeyTagPair(KT_pair& key)
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

void SpriteShipGame::ReleasePressedKeyTagPair(const KT_pair& key)
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