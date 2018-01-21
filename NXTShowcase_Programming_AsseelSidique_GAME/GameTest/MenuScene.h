#pragma once

#include "Scene.h"
#include "MenuObject.h"
#include "BGMS.h"
#include <vector>

class MenuScene : public Scene {
	private: 
		float currentOptionSelected;
		void DrawMenu();
		bool difficulty = false;
		void SelectOption(int a);
		float r = 1; float g = 2; float b = 3;
		BGMS backgroundManagementSys;

	public:
		MenuScene();
		~MenuScene();
		std::vector<MenuObject*> menuObjects;
		void OnCreate();
		void OnDestroy();
		void Update(float deltaTime);
		void Render();


};
