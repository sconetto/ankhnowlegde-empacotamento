/*
 * OptionsController.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: al
 */

#include "CreditsController.h"
#include <iostream>


CreditsController::CreditsController():GameObject(getX(),getY()) {
	this->back_1 = new Sprite(SDLBase::resourcesPath + "back_1.png");
	this->back_2 = new Sprite(SDLBase::resourcesPath + "back_2.png");
	this->back_3 = new Sprite(SDLBase::resourcesPath + "back_3.png");
	this->back = new Button(back_1,back_2,back_3,500,500);
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "credits.png");
	input = InputManager::getInstance();
	
}

CreditsController::~CreditsController() {
	// TODO Auto-generated destructor stub
}

void CreditsController::render(float cameraX, float cameraY){
	this->splashSprite->render(0,0);
	this->back->render(0,0);
}

int CreditsController::update(int dt){
	mouseOver(back);
	mousePressed(back,"SceneMainMenu");
	this->back->update(dt);
	return 0;
}

void CreditsController::mouseOver(Button *bt){
	bt->setMouseCoord(input->mousePosX(),input->mousePosY());
}

void CreditsController::mousePressed(Button *bt,string scene){

	if(input->isMousePressed(1) && bt->insideButton() == 1)
	{
		bt->mousePressed(true);

		if(bt->getChangeScene())
		{
			changeScene(scene);
		}
	}
	else
	{
		bt->mousePressed(false);
	}
}

void CreditsController::changeScene(string nextScene){
	if(GameManager::currentScene->changeScene(nextScene) == 1)
		GameManager::fadeScreen->fadeIn(1,0.2);
}
