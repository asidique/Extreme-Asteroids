#pragma once
#include "HUDElement.h"
#include "App\app.h"
#include <vector>
#include <string>

using namespace App;
class HUD
{
private:
	std::vector<Heart> hearts;
	int score, lives, astLeft;
	float displayTimer;
	std::string displayText;
	Vector displayPosition;

public:
	HUD();
	void draw();
	void update(float deltaTime);
	void init();
	void getScore();
	void addScore(int _score, Vector pos);
	void loseHeart();
	void gainHeart();
	bool gameOver;
	void setAsteroidsLeft(int a);
	void Clean();
	~HUD();
};

