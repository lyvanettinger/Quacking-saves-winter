#include "GameStateManager.h"

namespace Tmpl8 {

	void GameStateManager::Init()
	{
		// og stuff
		numFrames = 4;
		currentFrame = 0;
		currentState = START;
		writeTextBlink = true;
		t_TextBlink.reset();
		t_Frames.reset();
		// text sprites
		pausedText = assetManager->GetSprite("pausedText");
		controlsText = assetManager->GetSprite("controlsText");
		gameoverText = assetManager->GetSprite("gameoverText");
		quakingsaveswinterText = assetManager->GetSprite("quakingsaveswinterText");
		// button sprites
		LMBbutton = assetManager->GetSprite("LMBbutton");
		CTRLbutton = assetManager->GetSprite("CTRLbutton");
		SPACEbutton = assetManager->GetSprite("SPACEbutton");
		SHIFTbutton = assetManager->GetSprite("SHIFTbutton");
		ESCbutton = assetManager->GetSprite("ESCbutton");
		WASDbutton = assetManager->GetSprite("WASDbutton");
		// quaking sprites
		quakingStart = assetManager->GetSprite("startQuaking");
		quakingGameover = assetManager->GetSprite("gameoverQuaking");
	}

	void GameStateManager::SetGameState(int state)
	{
		switch (state)
		{
		case 0:
			currentState = START;
			numFrames = quakingStart->Frames();
			break;
		case 1:
			currentState = PLAY;
			break;
		case 2:
			currentState = PAUSE;
			break;
		case 3:
			currentState = GAMEOVER;
			numFrames = quakingGameover->Frames();
			break;
		default:
			break;
		}
	}

	void GameStateManager::WriteStart()
	{
		screen->Clear(0);

		// frames
		if (t_Frames.elapsed() > 200)
		{
			if (++currentFrame == quakingStart->Frames()) currentFrame = 0;
			quakingStart->SetFrame(currentFrame);
			t_Frames.reset();
		}

		// sprites
		quakingStart->Draw(screen, ScreenWidth / 2 - quakingsaveswinterText->GetWidth() / 2 - quakingStart->GetWidth() + 10, ScreenHeight / 2 - 10);
		quakingsaveswinterText->Draw(screen, ScreenWidth / 2 - quakingsaveswinterText->GetWidth() / 2 + 20, ScreenHeight / 2 - 10); // og: 282x22

		// credits :)
		screen->Print("game by: Lon van Ettinger", 1, 1, 0xffffff);

		// blinking text
		if (writeTextBlink)
		{
			screen->Centre("( PRESS ENTER TO START )", ScreenHeight / 2 + 30, 0xffffff);
		}
		if (t_TextBlink.elapsed() > 400)
		{
			writeTextBlink = !writeTextBlink;
			t_TextBlink.reset();
		}
	}

	void GameStateManager::WritePause()
	{
		screen->Clear(0);

		// credits :)
		screen->Print("game by: Lon van Ettinger", 1, 1, 0xffffff);

		// text sprites
		pausedText->DrawScaled((ScreenWidth / 2) - (190 / 2), 180, 190, 30, screen); // og: 95x15
		controlsText->Draw(screen, (ScreenWidth / 2) - (controlsText->GetWidth() / 2), 240);

		// button sprites + text
		WASDbutton->Draw(screen, ScreenWidth / 2 - WASDbutton->GetWidth() - 30, 290);
		screen->Print("move quaking around", ScreenWidth / 2, 295, 0xffffff);
		SPACEbutton->Draw(screen, ScreenWidth / 2 - SPACEbutton->GetWidth() - 30, 315);
		screen->Print("speed up quaking", ScreenWidth / 2, 320, 0xffffff);
		SHIFTbutton->Draw(screen, ScreenWidth / 2 - SHIFTbutton->GetWidth() - 30, 340);
		screen->Print("hide quaking in its barrel", ScreenWidth / 2, 345, 0xffffff);
		LMBbutton->Draw(screen, ScreenWidth / 2 - LMBbutton->GetWidth() - 30, 365);
		screen->Print("aim with quaking and shoot planks", ScreenWidth / 2, 370, 0xffffff);
		CTRLbutton->Draw(screen, ScreenWidth / 2 - CTRLbutton->GetWidth() - 30, 390);
		screen->Print("pause the game", ScreenWidth / 2, 395, 0xffffff);

		// blinking text
		if (t_TextBlink.elapsed() > 400)
		{
			writeTextBlink = !writeTextBlink;
			t_TextBlink.reset();
		}
		if (writeTextBlink)
		{
			screen->Centre("( PRESS ENTER TO CONTINUE )", 440, 0xffffff);
		}
	}

	void GameStateManager::WriteGameOver()
	{
		screen->Clear(0);

		// frames
		if (t_Frames.elapsed() > 200)
		{
			if (++currentFrame >= quakingGameover->Frames()) currentFrame = 0;
			quakingGameover->SetFrame(currentFrame);
			t_Frames.reset();
		}

		// sprites
		gameoverText->DrawScaled((ScreenWidth / 2) - gameoverText->GetWidth(), ScreenHeight / 2 - 20, 286, 30, screen); // og 143x15
		quakingGameover->Draw(screen, ScreenWidth / 2 - quakingGameover->GetWidth() / 2, ScreenHeight / 2 - 50);

		// text
		screen->Print("game by: Lon van Ettinger", 1, 1, 0xffffff);
		screen->Centre("your final score:     ", ScreenHeight / 2 + 30, 0xffffff);
		currentGame->PrintScore(ScreenWidth / 2 + 40, ScreenHeight / 2 + 30);

		// blinking text
		if (t_TextBlink.elapsed() > 400)
		{
			writeTextBlink = !writeTextBlink;
			t_TextBlink.reset();
		}
		if (writeTextBlink)
		{
			screen->Centre("( PRESS ENTER TO RESTART )", ScreenHeight / 2 + 50, 0xffffff);
		}
	}
}