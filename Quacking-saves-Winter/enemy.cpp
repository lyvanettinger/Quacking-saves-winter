#include "enemy.h"

namespace Tmpl8
{
	Enemy::Enemy(Sprite* a_Sprite, vec2 a_Pos, vec2 a_Dir, bool a_IsBlue) : AnimatedSprite(a_Sprite, a_Dir, a_Pos)
	{
		// inherited
		an_Pos = a_Pos;
		an_Dir = a_Dir;
		an_Sprite = a_Sprite;
		an_NumFrames = Frames();
		an_CurrentFrame = 0;
		an_IsAlive = true;
		// og
		e_IsBlue = a_IsBlue;
	}

	void Enemy::Move(float deltaTime, vec2 offSet)
	{
		// check if the enemy hits any of the screen's bounds
		if (an_Pos.x == offSet.x || an_Pos.x == ScreenWidth - GetWidth() - offSet.x) { an_Dir.x *= -1; }
		if (an_Pos.y == offSet.y || an_Pos.y == ScreenHeight - GetHeight() - offSet.y) { an_Dir.y *= -1; }

		// move enemy
		an_Pos += an_Dir * (deltaTime / 2);

		// clamp enemy within screen bounds
		an_Pos.x = Clamp<float>(an_Pos.x, offSet.x, (float)(ScreenWidth - GetWidth()) - offSet.x);
		an_Pos.y = Clamp<float>(an_Pos.y, offSet.y, (float)(ScreenHeight - GetHeight()) - offSet.y);
	}
}