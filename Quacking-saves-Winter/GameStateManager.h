#pragma once
#include "game.h"
#include "surface.h"
#include "template.h"
#include "assetmanager.h"

namespace Tmpl8 {
	class GameStateManager
	{
	public:
		// structor
		void Init();
		// enum
		enum gameStates
		{
			START = 0,
			PLAY,
			PAUSE,
			GAMEOVER
		};
		// functions
		void WriteStart();
		void WritePause();
		void CheckPause();
		void WriteGameOver();
		void CheckGameOver();
		void CheckGamePlay();
		bool IsGameState(int state) { if (currentState == state) { return true; } else return false; };
		// getter
		int GetGameState() { return currentState; };
		// setters
		void SetGame(Game* game) { currentGame = game; };
		void SetTarget(Surface* surface) { screen = surface; };
		void SetAssetManager(AssetManager* assetMan) { assetManager = assetMan; };
		void SetGameState(int state);
	private:
		// attributes
		unsigned int currentFrame, numFrames;
		bool writeTextBlink;
		gameStates currentState;
		timer t_TextBlink, t_Frames;
		// pointers
		Game* currentGame;
		Surface* screen;
		AssetManager* assetManager;
		Sprite *pausedText, *controlsText, *gameoverText, *quakingsaveswinterText;
		Sprite *quakingStart, *quakingGameover;
		Sprite *LMBbutton, *SPACEbutton, *CTRLbutton, *SHIFTbutton, *WASDbutton, *ESCbutton;
	};
}


