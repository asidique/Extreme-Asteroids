#include "stdafx.h"
#include "EMS.h"

EMS::EMS(float difficulty)
{
	srand(time(0));
	round = 25; 
	init(round); //always init's from round 1
	spawn();

}

void EMS::init(int _round) {
	numberOfEnemies = (int)(difficultyFactor*round*2 + 15);
	for (int i = 0; i < numberOfEnemies; i++) {
		enemies.push_back(new Enemy()); //adding a certain number enemies into the vector based on the round
	}
	for (auto Enemy : enemies) {
		Enemy->phase = 2;
		if (_round > 10) {
			Enemy->makeElite();
			Enemy->phase = 3; //Determines phase of enemy based on round
		}
		else if(_round > 25) {
			Enemy->makeElite();
			Enemy->phase = 4;
		}
		Enemy->speed *= difficultyFactor;
		Enemy->init();
	}

	currentEnemies = numberOfEnemies;
	roundDisplayTimer = 5000.0f;
}

void EMS::spawn() {
	for (auto Enemy : enemies) {
		Enemy->init();
	}
}

void EMS::draw() {
	for (auto Enemy : enemies) {
		Enemy->draw();
	}
	if (newRound) {
		std::string roundText = "ROUND " + std::to_string(getRound());
		Print(1024 / 2.0f - 60.0f, 600.0f, roundText.c_str(), 1.0f, 1.0f, 1.0f); // This prints the current round
	}
	else {

	}
}

std::vector<Enemy*> EMS::getEnemyVector() {
	return enemies;
}

void EMS::removeEnemy(Enemy* en) {
	for (int i = 0; i <= currentEnemies - 1; ++i) {
		if (enemies.at(i) == en) {
			if (currentEnemies == 1 && enemies.at(i)->phase <= 1) {
				App::PlaySoundW("tada.wav", false); //If the last enemy is shot, 'TADA!'
			}
			if (enemies.at(i)->phase > 1) { //This piece of code takes care of instantiating smaller asteroids!
				enemies.push_back(new Enemy(Vector(enemies.at(i)->getPosition())+ Vector(20.0f, 20.0f), enemies.at(i)->getWidth()/2.0f, enemies.at(i)->getHeight() / 2.0f, enemies.at(i)->phase-1)); //CHECK HERE FOR ERRORS!
				enemies.push_back(new Enemy(Vector(enemies.at(i)->getPosition()) - Vector(20.0f, 20.0f), enemies.at(i)->getWidth()/2.0f, enemies.at(i)->getHeight() / 2.0f, enemies.at(i)->phase-1)); //CHECK HERE FOR ERRORS!
				currentEnemies += 2;
			}
			enemies.erase(enemies.begin() + i); //Find the enemy and remove it from the vector!!
			currentEnemies--;
		}
	}
}

bool CheckCol(Vector position, float width, float height, Vector position2, float width2, float height2) {
	return ((abs(position.x - position2.x) * 2 < (width + width2)) &&
		(abs(position.y - position2.y) * 2 < (height + height2))); //This is only needed in this class to check collision between enemy and enemy
}


void EMS::update(float deltaTime) {
	for (auto Enemy : enemies) {
		Enemy->update(deltaTime);
	}

	for (int i = 0; i < currentEnemies - 1; i++) {
		for (int j = i + 1; j < currentEnemies; j++) {
			if (CheckCol(enemies[i]->getPosition(), enemies[i]->getWidth(), enemies[i]->getHeight(),
				enemies[j]->getPosition(), enemies[j]->getWidth(), enemies[j]->getHeight())) {
				removeEnemy(enemies[i]); //Checks collision between all enemies and not itself.
			}
		}
	}
	if (currentEnemies == 0) {
		if (roundDisplayTimer > 0) {
			newRound = true;
			roundDisplayTimer -= deltaTime;
		}
		else {
			nextRound();
		}
	}
}

void EMS::nextRound() {
	round++;
	init(round); //Increment the round and re-initialize
	newRound = false;
}

int EMS::getRound() {
	return round;
}


EMS::~EMS()
{
}

void EMS::Clean() {
	//error
	/*for (auto it = enemies.begin(); it != enemies.end(); ++it) {
		delete *it;
	}
	enemies.clear();*/
}