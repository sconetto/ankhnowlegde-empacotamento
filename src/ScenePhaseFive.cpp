/*
 * ScenePhaseFive.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: makoto
 */

#include "ScenePhaseFive.h"
#include "AudioHandler.h"

ScenePhaseFive::ScenePhaseFive(string sceneName) : Scene (sceneName) {


}

ScenePhaseFive::~ScenePhaseFive() {
	// TODO Auto-generated destructor stub
}

void ScenePhaseFive::Enter()
{
	AudioHandler * audio = AudioHandler::getInstance();
	audio->stopMusic();
	audio->setMusic("fase5.ogg");
	audio->playMusic(-1);

	this->splashSprite = new Sprite(SDLBase::resourcesPath + "interface.png");
	this->tile = new Sprite(SDLBase::resourcesPath + "tile.png");
	this->block = new Sprite(SDLBase::resourcesPath + "areiamovedicabloco.png");
	this->map = new Map(tile, block, SDLBase::resourcesPath +"tileMap5.txt", 200, 100);
	string nextScene = "ScenePhaseFive" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	this->addGameObject(map);
	GameManager::fadeScreen->fadeOut(0,2);
}

void ScenePhaseFive::Exit()
{
	this->cleanGameObjects();
}

