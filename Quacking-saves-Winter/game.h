#pragma once
#include "assetmanager.h"
#include "template.h"
#include "enemy.h"
#include "player.h"
#define MAX_DIGITS 10

namespace Tmpl8 {

class Surface;
class AssetManager;
class Enemy;
struct Tile
{
	// attributes
	vec2 t_Pos;
	// structor
	Tile(vec2 a_Pos, float t_Size)
	{
		t_Pos = a_Pos * t_Size;
	};
};
class Game
{
public:
	// standards
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	// functions
	void WriteTexts();
	void AddScore(int add) { score += add; };
	void CalculateScore();
	void PrintScore(int x, int y);
	void CheckEnemies(float deltaTime);
	void Reset();
	vec2 RanDir();
	vec2 RanPos();
	Enemy* RanEnemy();
	void AddTile(vec2 pos);
	void RemoveTile(vec2 pos);
	// getters
	int GetScore() { return score; };
	int* MouseX() { return &mouseX; };
	int* MouseY() { return &mouseY; };
	bool IsGameOver() { return isGameOver; };
	// setters
	void SetTarget(Surface* surface) { screen = surface; };
	void SetAssetManager(AssetManager* assetMan) { assetManager = assetMan; };
	void SetScore(int a_score) { score = a_score; };
	// key and mouse detection
	void MouseDown(int button);
	void KeyUp(int key);
	void KeyDown(int key);
private:
	// player
	Player* player;
	// attributes
	const unsigned int MAX_ENEMIES = 5;
	const int t_Size = 35;
	int score;
	int mouseX, mouseY;
	bool isGameOver;
	vec2 offSet;
	// for the int to char*
	char score_char[MAX_DIGITS + sizeof(char)];
	char lives_char[MAX_DIGITS + sizeof(char)];
	char speed_char[MAX_DIGITS + sizeof(char)];
	char hide_char[MAX_DIGITS + sizeof(char)];
	// pointers and objects
	Surface* screen;
	AssetManager* assetManager;
	timer t_Frames, t_HideSkill, t_SpeedSkill, t_EnemySpawn, t_BulletSpawn;
	// vectors
	std::vector<Enemy*> enemyEntities;
	std::vector<Tile*> tiles;
};
}; // namespace Tmpl8