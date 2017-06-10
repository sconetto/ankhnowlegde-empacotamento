
#include "SceneLogo.h"

SceneLogo::SceneLogo(string sceneName) : Scene (sceneName) {

}

SceneLogo::~SceneLogo() {
}

void SceneLogo::Enter()
{
	AudioHandler * audio = AudioHandler::getInstance();
 	audio->stopMusic();
 	audio->setMusic("intro.ogg");
 	audio->playMusic(1);

	this->splashSprite = new Sprite(SDLBase::resourcesPath + "splashlogo.png");
	string nextScene = "SceneTechnology";
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);

	this->addGameObject(splashScreen);
	//GameManager::fadeScreen->fadeOut(0,2);
}

void SceneLogo::Exit()
{
	this->cleanGameObjects();
}

