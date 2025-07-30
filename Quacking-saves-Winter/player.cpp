#include "player.h"
#include "surface.h"
#include "SDL.h"

namespace Tmpl8 {
	// -----------------------------------------------------------
	// Bullet
	// -----------------------------------------------------------
	Bullet::Bullet(Sprite* a_Sprite, vec2 a_Dir, vec2 a_Pos) : AnimatedSprite(a_Sprite, a_Dir, a_Pos)
	{
		// inherited
		if (a_Dir == vec2(0, 0))
			an_Dir = vec2(2, 2);
		else
			an_Dir = a_Dir;
		an_Pos = a_Pos;
		an_Sprite = a_Sprite;
		an_NumFrames = Frames();
		an_CurrentFrame = 0;
		an_IsAlive = true;
		// og
		b_CanBounce = true;
	};

	void Bullet::Move(float deltaTime, vec2 offSet)
	{
		// check if out of bounds and bounce
		if (an_Pos.x < offSet.x || an_Pos.x > ScreenWidth - GetWidth() - offSet.x)
		{
			if (b_CanBounce)
			{
				an_Dir.x *= -1;
				b_CanBounce = false;
			}
			else
				an_IsAlive = false;
		}
		if (an_Pos.y < offSet.y || an_Pos.y > ScreenHeight - GetHeight() - offSet.y)
		{
			if (b_CanBounce)
			{
				an_Dir.y *= -1;
				b_CanBounce = false;
			}
			else
				an_IsAlive = false;
		}

		// move bullet
		an_Pos += an_Dir * deltaTime;
	}

	// -----------------------------------------------------------
	// Player
	// -----------------------------------------------------------
	Player::Player(Sprite* a_Sprite, vec2 a_Dir, vec2 a_Pos) : AnimatedSprite(a_Sprite, a_Dir, a_Pos)
	{	
		// inherited
		an_Dir = a_Dir;
		an_Pos = a_Pos;
		an_Sprite = a_Sprite;
		an_NumFrames = Frames() / 4;
		an_CurrentFrame = 0;
		// og
		p_CurrentState = IDLE;
		p_CurrentSpriteDir = RIGHT;
		p_Move = 1;
		p_CurrentLives = MAX_LIVES;
		p_IsInvincible = false;
		p_IsSpeeding = false;
		p_IsRunning = false;

	}

	Player::~Player()
	{
		for (auto bullet : bulletEntities)
			delete bullet;
		bulletEntities.clear();
	}

	void Player::ChangeSprite()
	{
		// switch sprite
		switch (p_CurrentState)
		{
			case 0:
				an_Sprite = assetManager->GetSprite("idleQuaking");
				break;
			case 1:
				an_Sprite = assetManager->GetSprite("runQuaking");
				break;
			case 2:
				an_Sprite = assetManager->GetSprite("hideQuaking");
				break;
			case 3:
				an_Sprite = assetManager->GetSprite("slideQuaking");
				break;
			default:
				an_Sprite = assetManager->GetSprite("idleQuaking");
		}

		// update numframes and check currentframe
		an_NumFrames = an_Sprite->Frames() / 4;
		if (an_CurrentFrame >= an_NumFrames) an_CurrentFrame = 0;
	}

	void Player::HandleBullets(timer* t1, float deltaTime, vec2 offSet)
	{
		for (Bullet* bullet : bulletEntities)
		{
			// remove bullet
			if (!bullet->IsAlive())
			{
				bulletEntities.erase(std::remove(bulletEntities.begin(), bulletEntities.end(), bullet), bulletEntities.end());
			}
			else
			{
			// move bullet
				bullet->Move(deltaTime, offSet);
			}
			// frames
			if (t1->elapsed() > 100)
			{
				bullet->HandleFrames();
			}
		}
	}

	void Player::AddBullet(timer* t1, vec2 mousePos)
	{
		if (t1->elapsed() > 300)
		{
			bulletEntities.push_back(new Bullet(assetManager->GetSprite("throwableQuaking"), vec2(mousePos - an_Pos).normalized(), an_Pos + vec2((float)(an_Sprite->GetWidth() / 2), (float)(an_Sprite->GetHeight() / 2))));
			t1->reset();
		}
	}

	bool Player::CollidesWithBullet(AnimatedSprite* enemy)
	{
		for (Bullet* bullet : bulletEntities)
		{
			if (bullet->CollidesWith(enemy))
			{
				bullet->IsDead();
				return true;
			}
		}
		return false;
	}

	void Player::HandleInput(timer* t_SpeedSkill, timer* t_HideSkill, int scancode)
	{
		switch (scancode)
		{
			// player movement
		case (SDL_SCANCODE_A):
			p_IsRunning = true;
			p_CurrentSpriteDir = LEFT;
			an_Dir.x = -1;
			break;
		case (SDL_SCANCODE_D):
			p_IsRunning = true;
			p_CurrentSpriteDir = RIGHT;
			an_Dir.x = 1;
			break;
		case(SDL_SCANCODE_W):
			p_IsRunning = true;
			p_CurrentSpriteDir = UP;
			an_Dir.y = -1;
			break;
		case(SDL_SCANCODE_S):
			p_IsRunning = true;
			p_CurrentSpriteDir = DOWN;
			an_Dir.y = 1;
			break;

			// player skills
		case(SDL_SCANCODE_SPACE):
			if (t_SpeedSkill->elapsed() > 10000)
			{
				p_Move = 2;
				t_SpeedSkill->reset();
				p_IsSpeeding = true;
			}
			break;
		case(SDL_SCANCODE_LSHIFT):
			if (t_HideSkill->elapsed() > 10000)
			{
				p_Move = 0;
				t_HideSkill->reset();
				p_IsInvincible = true;
			}
			break;
		}
	}

	void Player::HandleKeyRelease(int scancode)
	{
		// for sprite changes
		p_IsRunning = false;

		switch (scancode)
		{
			// player movement stop
		case(SDL_SCANCODE_A):
			if (an_Dir.x == -1) an_Dir.x = 0;
			break;
		case(SDL_SCANCODE_D):
			if (an_Dir.x == 1) an_Dir.x = 0;
			break;
		case(SDL_SCANCODE_W):
			if (an_Dir.y == -1) an_Dir.y = 0;
			break;
		case(SDL_SCANCODE_S):
			if (an_Dir.y == 1) an_Dir.y = 0;
			break;
		}
	}

	void Player::Move(timer* t_SpeedSkill, timer* t_HideSkill, float deltaTime, vec2 offSet)
	{
		// skill time
		if (t_SpeedSkill->elapsed() > 3000)
		{
			p_IsSpeeding = false;
		}
		if (t_HideSkill->elapsed() > 3000)
		{
			p_IsInvincible = false;
		}

		// when no skill active
		if (t_SpeedSkill->elapsed() > 3000 && t_HideSkill->elapsed() > 3000)
		{
			p_Move = 1;
		}

		// move player
		an_Pos += (an_Dir * (float)p_Move) * (deltaTime / 2);

		// prevents the player from going outside screen
		an_Pos.x = Clamp<float>(an_Pos.x, offSet.x, (float)(ScreenWidth - an_Sprite->GetWidth()) - offSet.x);
		an_Pos.y = Clamp<float>(an_Pos.y, offSet.y, (float)(ScreenHeight - an_Sprite->GetHeight()) - offSet.y);

		// change state related to skills
		p_CurrentState = IDLE;
		if (p_IsRunning) { p_CurrentState = RUN; }
		if (p_IsSpeeding) { p_CurrentState = SLIDE; }
		if (p_IsInvincible) { p_CurrentState = HIDE; }
	}

	void Player::HandleFrames()
	{
		// usual frame handling
		if (++an_CurrentFrame >= an_NumFrames) an_CurrentFrame = 0;

		// stay in barrel during hide animation
		if (p_CurrentState == HIDE && an_CurrentFrame == 7) an_CurrentFrame = 6;
	}

	void Player::Tick(Surface* screen)
	{
		// player
		an_Sprite->SetFrame(an_CurrentFrame + an_NumFrames * p_CurrentSpriteDir);
		an_Sprite->Draw(screen, (int)an_Pos.x, (int)an_Pos.y);

		// bullets
		for (Bullet* bullet : bulletEntities)
		{
			bullet->Tick(screen);
		}
	}

	void Player::Reset()
	{
		// clean up bullets
		bulletEntities.clear();
		// player reset
		p_CurrentLives = MAX_LIVES;
		an_Pos = vec2(100, 100);
		an_Sprite = assetManager->GetSprite("idleQuaking");
		an_NumFrames = an_Sprite->Frames() / 4;
		an_CurrentFrame = 0;
		p_CurrentState = IDLE;
		p_CurrentSpriteDir = RIGHT;
		p_Move = 1;
		p_CurrentLives = MAX_LIVES;
		p_IsInvincible = false;
		p_IsSpeeding = false;
	}
};