#include "Background.h"

#include "GameOBJECT.h"

#include "SDL.h"

BackGround::BackGround(SDL_Renderer* renderer)
	:Actor(renderer, "BackGround")
{
	Vector2 Screensize(1280.0f, 762.0f);

	Stars = new BKGComponent(m_renderer, Screensize, -200, 60, "StarComponent");
	Space = new BKGComponent(m_renderer, Screensize, -50, 50, "SpaceComponent");
	
	std::vector<SDL_Texture*> SpaceTextures = {
		GameOBJECT::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Farback01.png"),
		GameOBJECT::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Farback02.png"),
		GameOBJECT::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Farback01.png"),
		GameOBJECT::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Farback02.png")
	};

	std::vector<SDL_Texture*> StarsTextures = {
		GameOBJECT::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Stars.png"),
		GameOBJECT::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Stars.png"),
		GameOBJECT::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Stars.png"),
		GameOBJECT::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Stars.png")
	};


	Space->SetBGTextures(SpaceTextures);
	Stars->SetBGTextures(StarsTextures);

	GetActorComponentRoot()->AddChildActorComponent(Stars);
	GetActorComponentRoot()->AddChildActorComponent(Space);
}

BackGround::~BackGround()
{
}
