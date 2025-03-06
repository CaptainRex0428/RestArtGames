#include "Background.h"
#include "SDL.h"
#include "MultiExtend.h"

BackGround::BackGround(MultiExtend::Renderer* renderer,MultiExtend::GameState * gmState)
	:Actor("BackGround")
{
	MultiExtend::Vector2 Screensize(1280.0f, 762.0f);

	Stars = new MultiExtend::ScrollComponent(gmState, renderer, Screensize, -200, 60, "StarComponent");
	Space = new MultiExtend::ScrollComponent(gmState, renderer, Screensize, -50, 50, "SpaceComponent");
	
	std::vector<MultiExtend::Texture*> SpaceTextures = {
		MultiExtend::LoadTexture(gmState,renderer,"../Games/SpriteShip/assets/Farback01.png"),
		MultiExtend::LoadTexture(gmState,renderer,"../Games/SpriteShip/assets/Farback02.png"),
		MultiExtend::LoadTexture(gmState,renderer,"../Games/SpriteShip/assets/Farback01.png"),
		MultiExtend::LoadTexture(gmState,renderer,"../Games/SpriteShip/assets/Farback02.png")
	};

	std::vector<MultiExtend::Texture*> StarsTextures = {
		MultiExtend::LoadTexture(gmState,renderer,"../Games/SpriteShip/assets/Stars.png"),
		MultiExtend::LoadTexture(gmState,renderer,"../Games/SpriteShip/assets/Stars.png"),
		MultiExtend::LoadTexture(gmState,renderer,"../Games/SpriteShip/assets/Stars.png"),
		MultiExtend::LoadTexture(gmState,renderer,"../Games/SpriteShip/assets/Stars.png")
	};


	Space->SetScrollTextures(SpaceTextures);
	Stars->SetScrollTextures(StarsTextures);

	GetActorComponentRoot()->AddChildActorComponent(Stars);
	GetActorComponentRoot()->AddChildActorComponent(Space);
}

BackGround::~BackGround()
{
}
