#include "Pong.h"

int main(int argc, char** argv)
{
	{
		if (Pong::Initialize())
		{
			Pong::RunLoop();
		}

		Pong::ShutDown();
	}

	return 0;
}