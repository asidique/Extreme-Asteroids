#include "stdafx.h"
#include "BGMS.h"
#include "App\app.h"

using namespace App;

BGMS::BGMS()
{
	init();
}

void BGMS::init() {
	timer = 9000.0f;
	scrollSpeed = 0.5f;
	for (int i = 0; i < 5; i++) {
		clouds.push_back(new cloud());
		clouds.at(i)->position.x = rand() % 1000;
	}
	for (int i = 0; i < 7; i++) {
		clouds2.push_back(new cloud());
		clouds2.at(i)->init(20.0f, 0.25f);
		clouds2.at(i)->position.x = rand() % 1000;
		clouds2.at(i)->position.y = -(rand() % 200 + 40);
	}
}

void BGMS::update(float deltaTime) {
	for (auto cloud : clouds) {
		cloud->update(deltaTime);
	}
	for (auto cloud : clouds2) {
		cloud->update(deltaTime);
	}
	if (timer < 0) {
		changeColor((rand() % 10) / 10.0f + 0.2f, (rand() % 10) / 10.0f + 0.2f, (rand() % 10) / 10.0f + 0.2f);
		timer = 9000.0f;
	}
	else {
		timer -= deltaTime;
	}
	CheckBoundry();
}

void BGMS::draw() {
	for (auto cloud : clouds2) {
		cloud->draw();
	}
	for (auto cloud : clouds) {
		cloud->draw();
	}
}

void BGMS::changeColor(float r, float g, float b) {
	for (auto cloud : clouds2) {
		cloud->setColor(r,g,b);
	}
	for (auto cloud : clouds) {
		cloud->setColor(r, g, b);
	}
}

void BGMS::CheckBoundry() {
	for (auto cloud : clouds) {
		if (cloud->position.y - 30 > 768) {
			cloud->position.y = -(rand()%200+40);
			cloud->position.x = rand() % 1000;
		}
	}
	for (auto cloud : clouds2) {
		if (cloud->position.y - 30 > 768) {
			cloud->position.y = -(rand() % 200 + 40);
			cloud->position.x = rand() % 1000;
		}
	}
}

BGMS::~BGMS()
{
	//clouds.clear();
	//clouds2.clear();
}

void BGMS::Clean() {
	for (auto it = clouds.begin(); it != clouds.end(); ++it) {
		delete *it;
	}
	clouds.clear();

	for (auto it = clouds2.begin(); it != clouds2.end(); ++it) {
		delete *it;
	}
	clouds2.clear();
}
