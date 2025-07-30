#include "AnimatedSprite.h"

namespace Tmpl8 {

	AnimatedSprite::AnimatedSprite(Sprite* a_Sprite, vec2 a_Dir, vec2 a_Pos) : Sprite(a_Sprite->GetSurface(), a_Sprite->Frames())
	{
		an_Dir = a_Dir;
		an_Pos = a_Pos;
		an_Sprite = a_Sprite;
		an_NumFrames = Frames();
		an_CurrentFrame = 0;
		an_IsAlive = true;
	}

	bool AnimatedSprite::CollidesWith(AnimatedSprite* other)
	{
		if ((int)an_Pos.x <= ((int)other->GetPos().x + other->GetSize().x) && ((int)an_Pos.x + an_Sprite->GetWidth()) >= (int)other->GetPos().x
			&& (int)an_Pos.y <= ((int)other->GetPos().y + other->GetSize().y) && ((int)an_Pos.y + an_Sprite->GetHeight() >= (int)other->GetPos().y))
			return true;
		return false;
	}

	void AnimatedSprite::HandleFrames()
	{
		if (++an_CurrentFrame == Frames()) an_CurrentFrame = 0;
	}

	void AnimatedSprite::Tick(Surface* screen)
	{
		SetFrame(an_CurrentFrame);
		Draw(screen, (int)an_Pos.x, (int)an_Pos.y);
	}
}