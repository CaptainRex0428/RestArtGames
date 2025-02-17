#pragma once

#include <vector>

#include "SDL.h"

#include "Math/Math.h"
#include "Math/Color.h"

#include "GameOBJECT.h"

#include "Ship.h"
#include "Background.h"

#include <vector>

#define SpriteShipNDebug

#define ProcessName "SpriteShip"

#define SpriteShipResolution_W 1280
#define SpriteShipResolution_H 762

#define ShipSpeed 200

struct KT_pair
{
	SDL_Scancode key;
	const char* tag;

	bool operator==(const KT_pair other) const;
};

class SpriteShip
{
public:
	SpriteShip(SpriteShip&) = delete;

	static bool Initialize();
	static void Runloop();
	static void ShutDown();

private:
	SpriteShip();
	virtual ~SpriteShip();

	static SpriteShip& Get();

	void ProcessInput();
	void UpdateGame();
	void GenerateOuput();

	void ToggleBorder(const Uint8* state,const SDL_Scancode& key1, const SDL_Scancode& key2);

	bool AssignPressedKeyTagPair(KT_pair& key);
	void ReleasePressedKeyTagPair(const KT_pair& key);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	int m_resolution_w;
	int m_resolution_h;

	int m_tickcount;
	float m_delta;

	bool m_isRunning;

	std::vector<KT_pair> m_pressedkey_tag;

	Ship* player;
	BackGround* bkg;
};