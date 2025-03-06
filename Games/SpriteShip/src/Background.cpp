#include "Background.h"
#include "SDL.h"

BackGround::BackGround(SDL_Renderer* renderer)
	:Actor("BackGround")
{
	MultiExtend::Vector2 Screensize(1280.0f, 762.0f);

	Stars = new MultiExtend::ScrollComponent(m_renderer, Screensize, -200, 60, "StarComponent");
	Space = new MultiExtend::ScrollComponent(m_renderer, Screensize, -50, 50, "SpaceComponent");
	
	std::vector<MultiExtend::Texture*> SpaceTextures = {
		MultiExtend::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Farback01.png"),
		MultiExtend::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Farback02.png"),
		MultiExtend::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Farback01.png"),
		MultiExtend::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Farback02.png")
	};

	std::vector<MultiExtend::Texture*> StarsTextures = {
		MultiExtend::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Stars.png"),
		MultiExtend::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Stars.png"),
		MultiExtend::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Stars.png"),
		MultiExtend::LoadTexture(m_renderer,"../Games/SpriteShip/assets/Stars.png")
	};


	Space->SetScrollTextures(SpaceTextures);
	Stars->SetScrollTextures(StarsTextures);

	GetActorComponentRoot()->AddChildActorComponent(Stars);
	GetActorComponentRoot()->AddChildActorComponent(Space);
}

BackGround::~BackGround()
{
}
