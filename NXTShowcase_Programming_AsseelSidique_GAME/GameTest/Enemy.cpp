#include "stdafx.h"
#include "Enemy.h"
#include <cstdlib>


using namespace App;

Enemy::Enemy()
{
	init();
}

Enemy::Enemy(Vector pos, float _width, float _height, int _phase) {
	phase--;
	position = pos;
	width = _width;
	height = _height;
	phase = _phase;
	if (rand() % 2 == 0) {
		if (eliteEnemies) {
			speed += 0.01f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.35f - 0.01f)));
		}
		else {
			speed += 0.005f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.15f - 0.005f)));
		}
	}

	else {
		if (eliteEnemies) {
			speed += 0.01f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.35f - 0.01f)));
		}
		speed += 0.005f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.15f - 0.005f)));
	}

	if (rand() % 3 == 0) {
		speed *= -1;
	}
}

void Enemy::makeElite() {
	eliteEnemies = true;
}

void Enemy::init() {
	int startYpos = rand() % 700;
	int startXpos = rand() % 300;
	if (rand() % 2 == 0) {
		if (eliteEnemies) {
			speed += 0.01f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.35f - 0.01f)));
		}
		else {
			speed += 0.005f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.15f - 0.005f)));
		}
		startXpos += 700;
	}

	else {
		if (eliteEnemies) {
			speed += 0.01f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.35f - 0.01f)));
		}
		speed += 0.005f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.15f - 0.005f)));
	}

	if (rand() % 3 == 0) {
		speed *= -1;
	}
	width = 40.0f;
	height = 40.0f;

	if (eliteEnemies && phase == 3) {
		width *= 2;
		height *= 2;
	}
	enemyDrawCoords[0] = Vector(0, height);
	enemyDrawCoords[1] = Vector(0, -height);
	enemyDrawCoords[2] = Vector(width, height);
	enemyDrawCoords[3] = Vector(-width, height);
	position = Vector(startXpos, startYpos); //Asteroids positions will vary

}

void Enemy::draw() {
	DrawLine(position.x - width / 2.0f, position.y - height / 2.0f, position.x - width / 2.0f, position.y + height/2.0f);
	DrawLine(position.x - width / 2.0f, position.y + height/ 2.0f, position.x + width / 2.0f, position.y + height/2.0f);
	DrawLine(position.x + width / 2.0f, position.y + height / 2.0f, position.x + width / 2.0f, position.y - height / 2.0f);
	DrawLine(position.x + width / 2.0f, position.y - height / 2.0f, position.x - width / 2.0f, position.y - height / 2.0f);
}

void Enemy::update(float deltaTime) {
	position.x += speed*deltaTime * (0.1f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.1f - 1.0f))));
	position.y += speed*deltaTime * (0.1f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.1f - 1.0f))));;
	CheckBoundary(1024, 768);
}

void Enemy::CheckBoundary(int _width, int _height) {
	if (position.x - width / 2.0f > _width) {
		position.x = 0 - width / 2.0f;
	}
	else if (position.x + width / 2.0f < 0) {
		position.x = _width + width / 2.0f;
	}

	if (position.y - height / 2.0f > _height) {
		position.y = 0 - height / 2.0f;
	}
	else if (position.y + height / 2.0f < 0) {
		position.y = _height + height / 2.0f;
	}
}

Vector Enemy::getPosition() {
	return position;
}

void Enemy::setPosition(Vector pos) {
	position = pos;
}

float Enemy::getWidth() {
	return width;
}

float Enemy::getHeight() {
	return height;
}

Enemy::~Enemy()
{}
