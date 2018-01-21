#include "stdafx.h"
#include "BMS.h"
#include <string>

using namespace App;

BMS::BMS() {}

BMS::BMS(float _rateOfFire) {
	init(_rateOfFire);
}

void BMS::init(float _rateOfFire) {
	rateOfFire = _rateOfFire;
	currentRate = 0.0f;
	currentBullets = 0;
}

void BMS::fire(float _speed, float _damage, Vector _position, Vector _direction, bool flamethrower, float rOF) {
	rateOfFire = rOF;
	if (currentRate > rOF) {
		App::PlaySoundW("pew.wav", false);
		if (flamethrower) {
			bullets.insert(bullets.begin(), new Bullet(_speed, _damage, _position, Vector::rotate_point(0.0f, 0.0f, 0.5f, _direction), 200.0f));
			bullets.insert(bullets.begin(), new Bullet(_speed, _damage, _position, Vector::rotate_point(0.0f, 0.0f, -0.5f, _direction), 200.0f));
			bullets.insert(bullets.begin(), new Bullet(_speed, _damage, _position, Vector::rotate_point(0.0f, 0.0f, 0.25f, _direction), 200.0f));
			bullets.insert(bullets.begin(), new Bullet(_speed, _damage, _position, Vector::rotate_point(0.0f, 0.0f, -0.25f, _direction), 200.0f));
			currentBullets += 4;
			currentRate = 0.0f;
			for (auto Bullet : bullets) {
				Bullet->setColor(1.0f, 0.0f, 0.0f);
			}
		}
		else {
			bullets.insert(bullets.begin(), new Bullet(_speed, _damage, _position, _direction, 2000.0f));
			currentBullets++;
			currentRate = 0.0f;
		}
	}
}

void BMS::draw() {
	if (!bullets.empty()) {
		for (auto Bullet : bullets) {
			Bullet->draw();
		}
	}
}

void BMS::update(float deltaTime) {
	if (currentRate < rateOfFire) {
		currentRate += deltaTime;
	}
	if (!bullets.empty()) {
		for (auto Bullet : bullets) {
			Bullet->update(deltaTime);
			if (!Bullet->isAlive()) {
				removeBullet(Bullet);
				break; 
			}
		}
	}
}

std::vector<Bullet*> BMS::getBulletVector() {
	return bullets;
}



void BMS::removeBullet(Bullet* bu) {
	if (!bullets.empty()) {
		for (int i = 0; i <= currentBullets - 1; ++i) {
			if (bullets.at(i) == bu) {
				bullets.erase(bullets.begin() + i);
				currentBullets--;
			}
		}
	}
}


BMS::~BMS()
{}

void BMS::Clean() {
	for (auto it = bullets.begin(); it != bullets.end(); ++it) {
		delete *it;
	}
	bullets.clear();
}
