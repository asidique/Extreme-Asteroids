#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene(bool _difficulty) {
	OnCreate();
	if (!_difficulty) {
		enemyManagementSys = EMS(1.15f);
	}
	else {
		enemyManagementSys = EMS(3.0f);
	}
}
GameScene::~GameScene() {
}

void GameScene::OnCreate() {
	quit = false;
	isSceneRunning = true;
	Player1 = player(mouseOn);
	bulletManagementSys = BMS(Player1.getRateOfFire());
	backgroundManagementSys = BGMS();
	pickupManagementSys = PMS();
	hud = HUD();
	nextScene = 2;
	Player1.init(mouseOn);
}

void GameScene::OnDestroy() {
	backgroundManagementSys.Clean();
	enemyManagementSys.Clean();
	bulletManagementSys.Clean();
	pickupManagementSys.Clean();
	hud.Clean();
}


bool CheckCollision(Vector position, float width, float height, Vector position2, float width2, float height2) {
	return ((abs(position.x - position2.x) * 2 < (width + width2)) &&
		(abs(position.y - position2.y) * 2 < (height + height2)));
}

void GameScene::Update(float deltaTime) {
	Player1.update(deltaTime);
	bulletManagementSys.update(deltaTime);
	enemyManagementSys.update(deltaTime);
	backgroundManagementSys.update(deltaTime);
	pickupManagementSys.update(deltaTime);
	hud.update(deltaTime);
	if (App::IsKeyPressed(VK_SPACE)) {
		bulletManagementSys.fire(1.0f, 10.0f, Player1.getPosition(), Player1.getDirection(), Player1.flamethrower, Player1.getRateOfFire());
	}
	//Player collision with pickups
	for (auto Pickup : pickupManagementSys.getPickupVector()) {
		if (CheckCollision(Player1.getPosition(), Player1.getWidth(), Player1.getWidth(), Pickup->position, Pickup->width, Pickup->height)) {
			Player1.GiveUpgrade(Pickup->type);
			pickupManagementSys.removePickup();
			if (Pickup->type == 2) {
				hud.gainHeart();
				break;
			}
		}
	}
	//Player collision with score pickups
	for (auto Pickup : pickupManagementSys.getScorePickupVector()) {
		if (CheckCollision(Player1.getPosition(), Player1.getWidth(), Player1.getWidth(), Pickup->position, Pickup->width, Pickup->height)) {
			App::PlaySoundW("coin.wav", false);
			if (Pickup->type == 0) {
				hud.addScore(100, Pickup->position);
			}
			else if (Pickup->type == 1) {
				hud.addScore(150, Pickup->position);
			}
			else if (Pickup->type == 2) {
				hud.addScore(125, Pickup->position);
			}
			else if (Pickup->type == 3) {
				hud.addScore(250, Pickup->position);
			}
			pickupManagementSys.removeScorePickup();
		}
	}
	//Enemy collision with player
	for (auto Enemy : enemyManagementSys.getEnemyVector()) {
		if (CheckCollision(Player1.getPosition(), Player1.getWidth(), Player1.getWidth(), Enemy->getPosition(), Enemy->getWidth(), Enemy->getHeight())) {
			enemyManagementSys.removeEnemy(Enemy); //Some kind of feedback would be nice to show damage to player. Add invinsibility for like 2 seconds?
			if (Player1.invincible == false) {
				hud.loseHeart();
			}
			App::PlaySoundW("destroy.wav", false);

			break;
		}
		//Enemy Collision with bullet
		for (auto Bullet : bulletManagementSys.getBulletVector()) {
			if (CheckCollision(Enemy->getPosition(), Enemy->getWidth(), Enemy->getHeight(), Bullet->getPosition(), Bullet->getWidth(), Bullet->getHeight())) {
				bulletManagementSys.removeBullet(Bullet);
				hud.addScore(50, Enemy->getPosition());
				enemyManagementSys.removeEnemy(Enemy);
				hud.setAsteroidsLeft(std::size(enemyManagementSys.getEnemyVector()));
				App::PlaySoundW("destroy.wav", false);
			}
		}
	}
	if (hud.gameOver == true) {
		nextScene = 2;
		isSceneRunning = false;
	}
}



void GameScene::Render() {
	backgroundManagementSys.draw();
	pickupManagementSys.draw();
	bulletManagementSys.draw();
	enemyManagementSys.draw();
	Player1.draw();
	hud.draw();
};