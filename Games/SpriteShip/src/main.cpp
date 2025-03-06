#include "SpriteShipGame.h"

int main(int argc, char ** argv)
{
	{
		if (SpriteShipGame::Initialize())
		{
			SpriteShipGame::Runloop();
		};

		SpriteShipGame::ShutDown();
	}
	return 0;
}