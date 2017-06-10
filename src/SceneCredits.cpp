#include "SceneCredits.h"

SceneCredits::SceneCredits(string sceneName) : Scene (sceneName)  {
	this->sprite = new Sprite(SDLBase::resourcesPath + "animacao_creditos.png");
	this->sprite->incNumRef();
	this->spriteAnimation = new Animation(20,40,sprite,0);
}

SceneCredits::~SceneCredits() 
{
	this->sprite->decNumRef();
	this->sprite = 0;
}

void SceneCredits::render(float cameraX, float cameraY)
{
	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		(*it)->render(cameraX, cameraY);
	}

	this->spriteAnimation->animate(100, 470, 505);
}

int SceneCredits::update(int dt)
{
	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		(*it)->update(dt);
	}

	this->spriteAnimation->update(dt, true, 0, false);

	return 0;
}


void SceneCredits::Enter()
{
	this->cc = new CreditsController();
	this->addGameObject(cc);
	GameManager::fadeScreen->fadeOut(0,2);
}

void SceneCredits::Exit()
{
	this->cleanGameObjects();
}


