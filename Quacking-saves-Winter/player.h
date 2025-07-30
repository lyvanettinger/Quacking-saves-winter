#pragma once
#include "template.h"
#include "assetmanager.h"
#include "animatedsprite.h"
#include <vector>

namespace Tmpl8 {

	class Surface;
	class Sprite;
	class AssetManager;
	class Bullet : public AnimatedSprite
	{
	public:
		// structor
		Bullet(Sprite* a_Sprite, vec2 a_Dir, vec2 a_Pos);
		// function
		void Move(float deltaTime, vec2 offSet);
	private:
		// attribute
		bool b_CanBounce;
	};
	class Player : public AnimatedSprite
	{
	public:
		// structors
		Player(Sprite* a_Sprite, vec2 a_Dir, vec2 a_Pos);
		~Player();
		// functions
		void HandleInput(timer* t1, timer* t2, int scancode);
		void HandleKeyRelease(int scancode);
		void HandleBullets(timer* t1, float deltaTime, vec2 offSet);
		void AddBullet(timer* t2, vec2 mousePos);
		bool CollidesWithBullet(AnimatedSprite* enemy);
		void Move(timer* t1, timer* t2, float deltaTime, vec2 offSet);
		void Tick(Surface* screen);
		void HandleFrames();
		void ChangeSprite();
		void Reset();
		void LoseLife() { p_CurrentLives--; };
		// getters
		const unsigned int GetMaxLives() { return MAX_LIVES; };
		unsigned int GetLives() { return p_CurrentLives; };
		bool IsInvincible() { return p_IsInvincible; };
		// setter
		void SetAssetManager(AssetManager* assetMan) { assetManager = assetMan; };
	private:
		// enums
		enum directions
		{
			DOWN = 0,
			UP,
			LEFT,
			RIGHT
		};
		enum states
		{
			IDLE = 0,
			RUN,
			HIDE,
			SLIDE
		};
		// attributes
		const unsigned int MAX_LIVES = 3;
		unsigned int p_Move, p_CurrentLives;
		bool p_IsInvincible, p_IsSpeeding, p_IsRunning;
		// more enum stuff
		directions p_CurrentSpriteDir;
		states p_CurrentState;
		// pointer
		AssetManager* assetManager;
		// vector for bullets
		std::vector<Bullet*> bulletEntities;
	};

};
