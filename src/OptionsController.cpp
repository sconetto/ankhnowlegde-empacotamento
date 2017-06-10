/*
 * OptionsController.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: al
 */

#include "OptionsController.h"
#include "AudioHandler.h"
#include <iostream>
#include <sstream>

OptionsController::OptionsController():GameObject(getX(),getY()) {
	this->back_1 = new Sprite(SDLBase::resourcesPath + "back_1.png");
	this->back_2 = new Sprite(SDLBase::resourcesPath + "back_2.png");
	this->back_3 = new Sprite(SDLBase::resourcesPath + "back_3.png");
	this->back = new Button(back_1,back_2,back_3,500,500);
	this->sliderBar = new Sprite(SDLBase::resourcesPath + "slider_bar.png");
	this->sliderButton = new Sprite(SDLBase::resourcesPath + "slider_button.png");
	bgVolume = new Slider(sliderButton,sliderBar,400,230);
	soundEffect = new Slider(sliderButton,sliderBar,400,310);
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "options.png");
	input = InputManager::getInstance();
	SDLBase::initializeSDLTTF();
	const SDL_Color temp = {0, 0, 0, 255};
	color = temp;
	string font_path = SDLBase::resourcesPath + "quicksandbold.ttf";
	font = SDLBase::loadFont(font_path.c_str(),40);
	this->musicVolume = ((int)(100*bgVolume->calculateValue()));
	this->effectVolume = ((int)(100*soundEffect->calculateValue()));

}

OptionsController::~OptionsController() {
	// TODO Auto-generated destructor stub
}

void OptionsController::render(float cameraX, float cameraY){
	this->splashSprite->render(0,0);
	this->back->render(0,0);
	this->bgVolume->render(0,0);
	this->soundEffect->render(0,0);

	int currentMusicVolume = ((int)(100*bgVolume->calculateValue()));
	if(currentMusicVolume != this->musicVolume)
	{
		AudioHandler * audio = AudioHandler::getInstance();
		audio->setMusicVolume(currentMusicVolume);
		this->musicVolume = currentMusicVolume;
		//audio->setEffectVolume(this->effectVolume);
	}

	int currentEffectVolume = ((int)(100*soundEffect->calculateValue()));
	if(currentEffectVolume != this->effectVolume)
	{
		AudioHandler * audio = AudioHandler::getInstance();
		audio->setEffectVolume(currentEffectVolume);
		audio->setEffect("sand_action.wav");
		audio->playEffect(0);
		this->effectVolume = currentEffectVolume;
	}

	stringstream ssbgvolume;
	ssbgvolume << this->musicVolume;
	SDLBase::renderText(font, ssbgvolume.str() + "%" ,color,720,220);
	
	stringstream sssoundeffect;
	sssoundeffect << this->effectVolume;
	SDLBase::renderText(font, sssoundeffect.str() + "%" ,color,720,300);


}

int OptionsController::update(int dt){
	mouseOver(back);
	mousePressed(back,"SceneMainMenu");
	this->back->update(dt);
	if(soundEffect->getSlideButton()== false)
	{	
		this->bgVolume->update(dt);
	}
	if(bgVolume->getSlideButton() == false)
	{	
		this->soundEffect->update(dt);
	}
	return 0;
}

void OptionsController::mouseOver(Button *bt){
	bt->setMouseCoord(input->mousePosX(),input->mousePosY());
}

void OptionsController::mousePressed(Button *bt,string scene){

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

void OptionsController::changeScene(string nextScene){
	if(GameManager::currentScene->changeScene(nextScene) == 1)
		GameManager::fadeScreen->fadeIn(1,0.2);
}
