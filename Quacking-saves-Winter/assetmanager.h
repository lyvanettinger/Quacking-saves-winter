#pragma once
#include <unordered_map>
#include <string>

namespace Tmpl8
{
	class Sprite;
	class AssetManager
	{
	public:
		// structors
		~AssetManager();
		void Init();
		// getter
		Sprite* GetSprite(std::string spriteName);
	private:
		// attribute
		std::unordered_map<std::string, Sprite*> Sprites;
	};
}

