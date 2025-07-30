#include "assetmanager.h"
#include "surface.h"

namespace Tmpl8
{
	AssetManager::~AssetManager()
	{
		// clean up sprites
		for (auto it = Sprites.cbegin(); it != Sprites.cend();)
		{
			delete it->second;
			Sprites.erase(it++);
		}
	}

	void AssetManager::Init()
	{
		// -- player sprites -- //
		// start and gameover screen
		Sprites["gameoverQuaking"] = new Sprite(new Surface("assets/gameoverAnimationQuaking.png"), 2);
		Sprites["startQuaking"] = new Sprite(new Surface("assets/startAnimationQuaking.png"), 5);
		// idle, move and skills
		Sprites["idleQuaking"] = new Sprite(new Surface("assets/idleAnimationQuaking.png"), 16);
		Sprites["runQuaking"] = new Sprite(new Surface("assets/runAnimationQuaking.png"), 24);
		Sprites["hideQuaking"] = new Sprite(new Surface("assets/hideAnimationQuaking.png"), 40);
		Sprites["slideQuaking"] = new Sprite(new Surface("assets/slideAnimationQuaking.png"), 24);
		// bullet
		Sprites["throwableQuaking"] = new Sprite(new Surface("assets/throwableAnimationQuaking.png"), 8);

		// -- enemy sprites -- //
		Sprites["redSmallSlime"] = new Sprite(new Surface("assets/redSmallSlime.png"), 6);
		Sprites["redLargeSlime"] = new Sprite(new Surface("assets/redLargeSlime.png"), 6);
		Sprites["blueSmallSlime"] = new Sprite(new Surface("assets/blueSmallSlime.png"), 6);
		Sprites["blueLargeSlime"] = new Sprite(new Surface("assets/blueLargeSlime.png"), 6);

		// -- text sprites -- //
		Sprites["quakingsaveswinterText"] = new Sprite(new Surface("assets/quakingsaveswinterText.png"), 1);
		Sprites["pausedText"] = new Sprite(new Surface("assets/pausedText.png"), 1);
		Sprites["controlsText"] = new Sprite(new Surface("assets/controlsText.png"), 1);
		Sprites["gameoverText"] = new Sprite(new Surface("assets/gameoverText.png"), 1);

		// -- button sprites -- //
		Sprites["ESCbutton"] = new Sprite(new Surface("assets/ESCbutton.png"), 1);
		Sprites["WASDbutton"] = new Sprite(new Surface("assets/WASDbutton.png"), 1);
		Sprites["SHIFTbutton"] = new Sprite(new Surface("assets/SHIFTbutton.png"), 1);
		Sprites["CTRLbutton"] = new Sprite(new Surface("assets/CTRLbutton.png"), 1);
		Sprites["SPACEbutton"] = new Sprite(new Surface("assets/SPACEbutton.png"), 1);
		Sprites["LMBbutton"] = new Sprite(new Surface("assets/LMBbutton.png"), 1);
	}

	Sprite* AssetManager::GetSprite(std::string spriteName)
	{
		return Sprites.at(spriteName);
	}
};