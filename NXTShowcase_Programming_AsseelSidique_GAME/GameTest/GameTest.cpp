//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

#include "SM.h"

void Shutdown();
//Define SMG (Scene Manager) Handles menuscene, gamescene
SM *SceneManager;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	SceneManager = new SM();
	SceneManager->Initialize();
}



//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	if (SceneManager->musicOn != NULL && SceneManager->musicOn == false) {
	}
	if (SceneManager->quit == true) {
		Shutdown();
	}
	SceneManager->Update(deltaTime);
}


//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	SceneManager->Render();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	SceneManager->~SM();
	delete SceneManager;
	exit(0);
}