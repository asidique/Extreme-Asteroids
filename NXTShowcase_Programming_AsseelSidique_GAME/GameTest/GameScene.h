#pragma once

#include "Scene.h"
#include "player.h"
#include "BMS.h"
#include "EMS.h"
#include "BGMS.h"
#include "PMS.h"
#include "HUD.h"
#include "App\app.h"

using namespace App;

class GameScene : public Scene {
private:

	public:
		GameScene() {};
		GameScene(bool _difficulty);
		 ~GameScene();

		void OnCreate();
		void OnDestroy();
		void Update(float deltaTime);
		void Render();


		player Player1;
		BMS bulletManagementSys;
		EMS enemyManagementSys;
		BGMS backgroundManagementSys;
		PMS pickupManagementSys;
		HUD hud;
};
