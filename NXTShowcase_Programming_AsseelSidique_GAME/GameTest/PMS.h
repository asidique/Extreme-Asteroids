#pragma once

#include <vector>
#include "Pickup.h"

class PMS
{
private:
	std::vector<Pickup*> pickups;
	std::vector<Pickup*> scorePickups;

public:
	void update(float deltaTime);
	void draw();
	void init();
	float pickupLife, scorePickupLife;
	std::vector<Pickup*> getPickupVector();
	std::vector<Pickup*> getScorePickupVector();
	void removePickup();
	float pickupSpawnTimer, pickupCount;
	float scorePickupTimer, scorePickupCount;
	void spawn(Vector pos, float _life, int _type, bool pickUp);
	void removeScorePickup();
	~PMS();
	PMS();
	void Clean();
};

