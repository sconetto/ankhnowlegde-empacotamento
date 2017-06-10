/*
 * SelectSceneController.h
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#ifndef SELECTMAPCONTROLLER_H_
#define SELECTMAPCONTROLLER_H_

#include "GameObject.h"
#include "HoverButton.h"
#include "Sprite.h"
#include "GameManager.h"
#include <iostream>
#include <string>
#include <vector>
#include "Network.h"
#include "Animation.h"

using namespace std;

class SelectMapController:public GameObject {
public:
	SelectMapController();
	virtual ~SelectMapController();
	void render(float cameraX, float cameraY);
	int update(int dt);
	void mouseOver(Button* bt);
	void mousePressed(Button* bt,string nextScene);
	void changeScene();
	void changeMap(int dt);
	void receiveMessage();
	void sendMessage(string action, string info);
	string intToString(int intenger);

private:
	vector<HoverButton*> mapButtons;
	vector<Sprite *> mapNames;
	Sprite* splashSprite, *board;
	Animation* boardAnimation;
	HoverButton* leftButton, *rightButton;
	int boardX, boardY;
	bool onTopBoard;
	int changingMap;
	InputManager* input;
	int mapselected;
	float acumulated, acumulated2;
	unsigned int currentMap;
	void moveLeft();
	void moveRight();
	void chooseMap(int index);
	bool locked;
};

#endif /* SELECTMAPCONTROLLER_H_ */
