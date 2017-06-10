/*
 * SceneCredits.h
 *
 *  Created on: Oct 28, 2013
 *      Author: al
 */

#ifndef SCENECREDITS_H_
#define SCENECREDITS_H_
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include "CreditsController.h"
#include <string>

class CreditsController;


class SceneCredits : public Scene {
public:
	SceneCredits(string sceneName);
	virtual ~SceneCredits();
	virtual void render(float cameraX, float cameraY);
	virtual int update(int dt);
	void Enter();
	void Exit();

private:
	Sprite * splashSprite;
	CreditsController* cc;
	Sprite* sprite;
	Animation* spriteAnimation;
};

#endif /* SCENECREDITS_H_ */
