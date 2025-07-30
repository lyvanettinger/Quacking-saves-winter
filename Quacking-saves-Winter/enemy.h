#pragma once
#include "AnimatedSprite.h"

namespace Tmpl8
{
	// include classes
	class Surface;
	class Sprite;

	// actual class
	class Enemy : public AnimatedSprite
	{
	public:
		// structor
		Enemy(Sprite* a_Sprite, vec2 a_Pos, vec2 a_Dir, bool a_IsBlue);
		// functions
		void Move(float deltaTime, vec2 offSet);
		// getter
		bool IsBlue() { return e_IsBlue; };
	private:
		// attribute
		bool e_IsBlue;
	};
}