#include "game.h"
#include "SDL.h"

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		// timers
		t_Frames.reset();
		t_SpeedSkill.reset();
		t_HideSkill.reset();
		t_EnemySpawn.reset();
		t_BulletSpawn.reset();
		// attributes
		offSet = vec2((float)((ScreenWidth % t_Size) / 2), (float)((ScreenHeight % t_Size) / 2));
		score = 0;
		mouseX = 0;
		mouseY = 0;
		// player
		player = new Player(assetManager->GetSprite("idleQuaking"), vec2(0,0), vec2(100,100));
		player->SetAssetManager(assetManager);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		// clean up player
		//delete player;
		// clean up tiles
		//for (auto tile : tiles)
			//delete tile;
		tiles.clear();
		// clean up enemies
		//for (auto enemy : enemyEntities)
			//delete enemy;
		enemyEntities.clear();
	}

	// -----------------------------------------------------------
	// Enemy handling
	// -----------------------------------------------------------
	vec2 Game::RanDir()
	{
		int rand = IRand(8);

		switch (rand) {
			case 0:
				return vec2(1, 1);
			case 1:
				return vec2(1, -1);
			case 2:
				return vec2(-1, 1);
			case 3:
				return vec2(-1, -1);
			case 4:
				return vec2(0, 1);
			case 5:
				return vec2(1, 0);
			case 6:
				return vec2(0, -1);
			case 7:
				return vec2(-1, 0);
			default:
				return RanDir();
		}
	}

	vec2 Game::RanPos()
	{
		return vec2(Rand(ScreenWidth), Rand(ScreenHeight));
	}

	Enemy* Game::RanEnemy()
	{
		int rand = IRand(5);

		switch (rand)
		{
			// 2 out of 5 enemies is red
			case (3 || 4):
				return new Enemy(assetManager->GetSprite("redLargeSlime"), RanPos(), RanDir(), false);
			default:
				return new Enemy(assetManager->GetSprite("blueLargeSlime"), RanPos(), RanDir(), true);
		}
	}

	void Game::CheckEnemies(float deltaTime)
	{
		// add enemy
		if (t_EnemySpawn.elapsed() > 2000 && enemyEntities.size() < MAX_ENEMIES)
		{
			enemyEntities.push_back(RanEnemy());
			t_EnemySpawn.reset();
		}

		for (Enemy* enemy : enemyEntities)
		{
			// check if enemy collides with player
			if (player->CollidesWith(enemy))
			{
				if (!player->IsInvincible())
				{
					player->LoseLife();
					enemy->IsDead();
				}
			}
			// check if enemy collides with bullet
			else if (player->CollidesWithBullet(enemy))
			{
				enemy->IsDead();
			}
			// when dead
			if (!enemy->IsAlive())
			{
				// add score
				score += 10;
				// draw or remove tiles
				if (enemy->IsBlue())
					AddTile(enemy->GetCentrePos());
				else
					RemoveTile(enemy->GetCentrePos());
				// remove and erase enemy
				enemyEntities.erase(std::remove(enemyEntities.begin(), enemyEntities.end(), enemy), enemyEntities.end());
			}
			// when alive
			else
			{
				enemy->Move(deltaTime, offSet);
				if (t_Frames.elapsed() > 100)
					enemy->HandleFrames();
			}
		}
	}

	// -----------------------------------------------------------
	// Input handling
	// -----------------------------------------------------------

	void Game::MouseDown(int scancode)
	{
		// shoot bullets
		if (scancode == SDL_BUTTON_LEFT)
		{
			player->AddBullet(&t_BulletSpawn, vec2((float)mouseX, (float)mouseY));
		}
	}

	void Game::KeyDown(int scancode)
	{
		// player move and skills
		switch (scancode)
		{
		case (SDL_SCANCODE_W):
		case (SDL_SCANCODE_A):
		case (SDL_SCANCODE_S):
		case (SDL_SCANCODE_D):
		case (SDL_SCANCODE_LSHIFT):
		case (SDL_SCANCODE_SPACE):
			player->HandleInput(&t_SpeedSkill, &t_HideSkill, scancode);
		}
	}

	void Game::KeyUp(int scancode)
	{
		// player stop move
		switch (scancode)
		{
		case (SDL_SCANCODE_W):
		case (SDL_SCANCODE_A):
		case (SDL_SCANCODE_S):
		case (SDL_SCANCODE_D):
			player->HandleKeyRelease(scancode);
		}
	}

	// -----------------------------------------------------------
	// Grid handling
	// -----------------------------------------------------------
	void Game::AddTile(vec2 pos)
	{
		for (int i = 0; i < (ScreenWidth - offSet.x * 2) / t_Size; i++)
		{
			for (int j = 0; j < (ScreenHeight - offSet.y * 2) / t_Size; j++)
			{
				if ((i * t_Size) < pos.x && ((i + 1) * t_Size) > pos.x
					&& (j * t_Size) < pos.y && ((j + 1) * t_Size) > pos.y)
				{
					tiles.push_back(new Tile(vec2((float)i, (float)j), (float)t_Size));
				}
			}
		}
	}

	void Game::RemoveTile(vec2 pos)
	{
		for (Tile* tile : tiles)
		{
			if (pos >= tile->t_Pos && pos <= (tile->t_Pos + (float)t_Size))
				tiles.erase(std::remove(tiles.begin(), tiles.end(), tile), tiles.end());
		}
	}
	

	// -----------------------------------------------------------
	// Other functions
	// -----------------------------------------------------------

	void Game::PrintScore(int x, int y)
	{
		// int to char*
		std::sprintf(score_char, "%d", score);
		// print score
		screen->Print(score_char, x, y, 0xffffff);
	}

	void Game::WriteTexts()
	{
		// int to char*
		std::sprintf(lives_char, "%d", player->GetLives());
		std::sprintf(speed_char, "%d", (((10000 - (int)t_SpeedSkill.elapsed()) % 10000) - ((10000 - (int)t_SpeedSkill.elapsed()) % 1000)) / 1000);
		std::sprintf(hide_char, "%d", (((10000 - (int)t_HideSkill.elapsed()) % 10000) - ((10000 - (int)t_HideSkill.elapsed()) % 1000)) / 1000);

		// print top texts and skill cooldowns
		screen->Print("quaking saves winter", 30, 2, 0xffffff);
		screen->Print("score: ", 300, 2, 0xffffff);
		PrintScore(350, 2);
		screen->Print("lives: ", 400, 2, 0xffffff);
		screen->Print(lives_char, 450, 2, 0xffffff);
		if (t_SpeedSkill.elapsed() < 10000)
		{
			screen->Print("i am speed (SPACE):    sec", 700, 2, 0xaaaaaa);
			screen->Print(speed_char, 820, 2, 0xffffff);
		}
		else
		{
			screen->Print("i am speed (SPACE): READY!!", 700, 2, 0xffffff);
		}
		if (t_HideSkill.elapsed() < 10000)
		{
			screen->Print("aahh hide (LSHIFT):    sec", 900, 2, 0xaaaaaa);
			screen->Print(hide_char, 1020, 2, 0xffffff);
		}
		else
		{
			screen->Print("aahh hide (LSHIFT): READY!!", 900, 2, 0xffffff);
		}
		screen->Print("pause game (CTRL)", 1150, 2, 0xffffff);
	}

	void Game::CalculateScore()
	{
		// add score for every white tile on the screen
		for (Tile* tile : tiles)
		{
			score += 100;
		}
	}
	
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);

		// draw bounds for all moving objects
		screen->Box((int)offSet.x, 9, ScreenWidth - (int)offSet.x, ScreenHeight - (int)offSet.y, 0xffffff);

		// checkenemies
		CheckEnemies(deltaTime);

		// draw tiles
		for (Tile* tile : tiles)
		{
			screen->Bar((int)(tile->t_Pos.x + offSet.x), (int)(tile->t_Pos.y + offSet.y), (int)(tile->t_Pos.x + t_Size + offSet.x), (int)(tile->t_Pos.y + t_Size + offSet.y), 0xffffff);
		}

		//write all texts on screen
		screen->Bar(0, 0, ScreenWidth, 8, 0x000000);
		WriteTexts();

		// draw enemies
		for (Enemy* enemy : enemyEntities)
		{
			enemy->Tick(screen);
		}
		
		// player update and bullets
		player->Move(&t_SpeedSkill, &t_HideSkill, deltaTime, offSet);
		player->HandleBullets(&t_Frames, deltaTime, offSet);
		player->ChangeSprite();
		// frame timer
		if (t_Frames.elapsed() > 100)
		{
			// handle frames
			player->HandleFrames();
			// reset timer
			t_Frames.reset();
		}
		player->Tick(screen);

		// when player is dead
		if (player->GetLives() == 0)
		{
			CalculateScore(); // final score including tiles
			isGameOver = true;
		}
	}

	void Game::Reset()
	{
		isGameOver = false;
		// clean up player and bullets
		player->Reset();
		// clean up enemies
		enemyEntities.clear();
		// clean up tiles
		tiles.clear();
	}
};