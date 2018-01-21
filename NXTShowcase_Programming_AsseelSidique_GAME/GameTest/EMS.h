#pragma once
#include "Enemy.h"
#include <math.h>
#include <vector>
#include <time.h>
#include "App\app.h"
#include <string>

using namespace App;

//ENEMY MANAGEMENT SYSTEM
class EMS
{
private:
	std::vector<Enemy*> enemies;
	int round, numberOfEnemies, currentEnemies;
	float difficultyFactor;
	float roundDisplayTimer;
	bool newRound;

public:
	EMS() { difficultyFactor = 1.15f; };
	EMS(float difficulty);
	void spawn();
	void update(float deltaTime);
	void init(int _round);
	void draw();
	int getRound();
	void nextRound();
	std::vector<Enemy*> getEnemyVector();
	void removeEnemy(Enemy*);
	void Clean();
	~EMS();
};

