/*
 * ScenePhaseThree.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: makoto
 */

#include "ScenePhaseThree.h"
#include "AudioHandler.h"

ScenePhaseThree::ScenePhaseThree(string sceneName) : Scene (sceneName) {


}

ScenePhaseThree::~ScenePhaseThree() {
	// TODO Auto-generated destructor stub
}

void ScenePhaseThree::Enter()
{
	AudioHandler * audio = AudioHandler::getInstance();
	audio->stopMusic();
	audio->setMusic("fase3.ogg");
	audio->playMusic(-1);

	this->splashSprite = new Sprite(SDLBase::resourcesPath + "interface.png");
	this->tile = new Sprite(SDLBase::resourcesPath + "tile.png");
	this->block = new Sprite(SDLBase::resourcesPath + "areiamovedicabloco.png");
	this->map = new Map(tile, block, SDLBase::resourcesPath +"tileMap3.txt", 200, 100);
	string nextScene = "ScenePhaseThree" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	this->addGameObject(map);
	GameManager::fadeScreen->fadeOut(0,2);
}

void ScenePhaseThree::Exit()
{
	this->cleanGameObjects();
}

