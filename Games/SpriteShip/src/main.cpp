#include "SpriteShipGame.h"

int main(int argc, char ** argv)
{
	{
		if (SpriteShip::Initialize())
		{
			SpriteShip::Runloop();
		};

		SpriteShip::ShutDown();
	}
	return 0;
}