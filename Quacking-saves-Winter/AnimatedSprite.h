#pragma once
#include "surface.h"
#include "template.h"

namespace Tmpl8 {
	class AnimatedSprite : public Sprite
	{
	public:
		// constructor
		AnimatedSprite(Sprite* a_Sprite, vec2 a_Dir, vec2 a_Pos);
		// functions
		virtual void HandleFrames();
		virtual void Tick(Surface* screen);
		virtual bool CollidesWith(AnimatedSprite* other);
		// getters
		vec2 GetPos() { return an_Pos; };
		vec2 GetCentrePos() { return an_Pos + vec2((float)(an_Sprite->GetWidth() / 2), (float)(an_Sprite->GetHeight() / 2)); };
		vec2 GetSize() { return vec2((float)an_Sprite->GetWidth(), (float)an_Sprite->GetHeight()); };
		bool IsAlive() { return an_IsAlive; };
		// setter
		void IsDead() { an_IsAlive = false; };
	protected:
		// attributes
		vec2 an_Dir, an_Pos, an_Size;
		unsigned int an_NumFrames, an_CurrentFrame;
		bool an_IsAlive;
		Sprite* an_Sprite;
	};
}

