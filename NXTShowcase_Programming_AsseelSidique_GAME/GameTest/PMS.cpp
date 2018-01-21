#include "stdafx.h"
#include "PMS.h"


PMS::PMS()
{
	init();
}

void PMS::init() {
	pickups.clear();
	scorePickups.clear();
	pickupSpawnTimer = 14000.0f;
	pickupLife = 7500.0f;
	pickupCount = 0;
	scorePickupCount = 0;
	scorePickupTimer = 7000.0f;
	scorePickupLife = 10000.0f;
}

void PMS::spawn(Vector pos, float _life, int _type, bool pickUp) {
	if (pickUp == true) {
		if (std::size(scorePickups) != 1) {
			scorePickups.push_back(new Pickup(pos, _life, _type));
			scorePickupTimer = 7500.0f;
			scorePickupLife = 7500.0f;
			scorePickupCount++;
		}
	}
	else {
		if (std::size(pickups) != 1) {
			pickups.push_back(new Pickup(pos, _life, _type));
			pickupCount++;
			pickupSpawnTimer = 14000.0f;
			pickupLife = 7500.0f;
		}
	}
}

void PMS::removePickup() {
	pickups.pop_back();
	pickupCount--;
}


void PMS::removeScorePickup() {
	scorePickups.pop_back();
	scorePickupCount--;
}

void PMS::update(float deltaTime) {

	if (scorePickupCount != 0) {
		for (auto Pickup : scorePickups) {
			Pickup->Update(deltaTime);
		}
		if (scorePickupLife < 0) {
			removeScorePickup();
		}
		else {
			scorePickupLife -= deltaTime;
		}
	}
	else {
		if (scorePickupTimer < 0) {
			spawn(Vector(rand() % 400 + 400, rand() % 200 + 400), 8500.0f, rand() % 4, true);
		}
		else {
			scorePickupTimer -= deltaTime;
		}
	}

	if (pickupCount != 0) {
		for (auto Pickup : pickups) {
			Pickup->Update(deltaTime);
		}
		if (pickupLife < 0) {
			removePickup();
		}
		else {
			pickupLife -= deltaTime;
		}
	}
	else {
		if (pickupSpawnTimer < 0) {
			spawn(Vector(rand()%700+200, rand() % 300 + 400), 7500.0f, rand()%4, false);
		}
		else {
			pickupSpawnTimer -= deltaTime;
		}
	}
}

void PMS::draw() {
	for (auto Pickup : pickups) {
		Pickup->Draw();
	}
	for (auto Pickup : scorePickups) {
		Pickup->Draw();
	}
}

std::vector<Pickup*> PMS::getPickupVector() {
	return pickups;
}

std::vector<Pickup*> PMS::getScorePickupVector() {
	return scorePickups;
}

PMS::~PMS()
{

}

void PMS::Clean() {
	for (auto it = pickups.begin(); it != pickups.end(); ++it) {
		delete *it;
	}
	pickups.clear();

	for (auto it = scorePickups.begin(); it != scorePickups.end(); ++it) {
		delete *it;
	}
	scorePickups.clear();
}
