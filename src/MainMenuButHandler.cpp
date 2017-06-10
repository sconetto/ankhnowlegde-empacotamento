/*
 * MainMenuButHandler.cpp
 *
 *  Created on: Oct 9, 2013
 *      Author: al
 */

#include "MainMenuButHandler.h"
#include "SDL/SDL_thread.h"


MainMenuButHandler::MainMenuButHandler():GameObject(getX(),getY()) {

//-----------------------SPRITES-------------------------//
	this->bt1_1 = new Sprite(SDLBase::resourcesPath + "host_1.png");
	this->bt1_1->incNumRef();
	this->bt1_2 = new Sprite(SDLBase::resourcesPath + "host_2.png");
	this->bt1_2->incNumRef();
	this->bt1_3 = new Sprite(SDLBase::resourcesPath + "host_3.png");
	this->bt1_3->incNumRef();
	this->bt2_1 = new Sprite(SDLBase::resourcesPath + "connect_1.png");
	this->bt2_1->incNumRef();
	this->bt2_2 = new Sprite(SDLBase::resourcesPath + "connect_2.png");
	this->bt2_2->incNumRef();
	this->bt2_3 = new Sprite(SDLBase::resourcesPath + "connect_3.png");
	this->bt2_3->incNumRef();
	this->bt3_1 = new Sprite(SDLBase::resourcesPath + "options_1.png");
	this->bt3_1->incNumRef();
	this->bt3_2 = new Sprite(SDLBase::resourcesPath + "options_2.png");
	this->bt3_2->incNumRef();
	this->bt3_3 = new Sprite(SDLBase::resourcesPath + "options_3.png");
	this->bt3_3->incNumRef();
	this->bt4_1 = new Sprite(SDLBase::resourcesPath + "credits_1.png");
	this->bt4_1->incNumRef();
	this->bt4_2 = new Sprite(SDLBase::resourcesPath + "credits_2.png");
	this->bt4_2->incNumRef();
	this->bt4_3 = new Sprite(SDLBase::resourcesPath + "credits_3.png");
	this->bt4_3->incNumRef();
	this->bt5_1 = new Sprite(SDLBase::resourcesPath + "quit_1.png");
	this->bt5_1->incNumRef();
	this->bt5_2 = new Sprite(SDLBase::resourcesPath + "quit_2.png");
	this->bt5_2->incNumRef();
	this->bt5_3 = new Sprite(SDLBase::resourcesPath + "quit_3.png");
	this->bt5_3->incNumRef();
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "titlebg.png");
	this->splashSprite->incNumRef();
	box = new Sprite(SDLBase::resourcesPath + "box.png");
	waiting = new Sprite(SDLBase::resourcesPath + "waiting.png");
	disconnect = new Sprite(SDLBase::resourcesPath + "disconnected.png");
	waiting->incNumRef();
	disconnect->incNumRef();
	this->box->incNumRef();
	boxInput = new Sprite(SDLBase::resourcesPath + "box_input.png");
	this->boxInput->incNumRef();
	bg = new Sprite(SDLBase::resourcesPath + "background.png");
	this->bg->incNumRef();
	cursor = new Sprite(SDLBase::resourcesPath + "cursor.png");
	this->cursor->incNumRef();
	loading = new Sprite(SDLBase::resourcesPath + "loading.png");
	this->loading->incNumRef();
//-------------------------------------------------------//

//----------------------BUTTONS-------------------------//
	this->hostButton = new Button(bt1_1,bt1_2,bt1_3,500,300);
	this->connectButton = new Button(bt2_1,bt2_2,bt2_3,500,350);
	this->optionsButton = new Button(bt3_1,bt3_2,bt3_3,500,400);
	this->creditsButton = new Button(bt4_1,bt4_2,bt4_3,500,450);
	this->quitButton = new Button(bt5_1,bt5_2,bt5_3,500,500);
	
//-------------------------------------------------------//

//----------------------POP UPS--------------------------//
	this->animation = new Animation(18,45,cursor,0);
	this->waitAnim = new Animation(50,50,loading,0);
	this->waitingBox = new MessageBox(waiting, "cancel",250,200);
	this->disconnectBox = new MessageBox(disconnect, "ok",250,200);
	this->connectBox = new MessageBox(box, boxInput,"ok",animation,250,200);

//-------------------------------------------------------//

//----------------------OTHERS---------------------------//
	
	input = InputManager::getInstance();
	this->boxX = 250;
	this->boxY = 200;
	this->boxInputX = boxX + box->getWidth()/2 - boxInput->getWidth()/2;
	this->boxInputY = boxY + 45;
	SDLBase::initializeSDLTTF();
	color.r = 0;
	color.g = 0;
	color.b = 0;
	string font_path = SDLBase::resourcesPath + "quicksandbold.ttf";
	font = SDLBase::loadFont(font_path.c_str(),25);
	read = false;
	tryToConnect = false;
	clickOtherButtons = true;
	message = "";
	host = false;
	thread = false;
	Network::cancel = true;
	renderConnectError = false;
	sizeMessage = 0;
}

MainMenuButHandler::~MainMenuButHandler() {
	this->bt1_1->decNumRef();
	this->bt1_1 = 0;
	this->bt1_2->decNumRef();
	this->bt1_2 = 0;
	this->bt1_3->decNumRef();
	this->bt1_3 = 0;
	this->bt2_1->decNumRef();
	this->bt2_1 = 0;
	this->bt2_2->decNumRef();
	this->bt2_2 = 0;
	this->bt2_3->decNumRef();
	this->bt2_3 = 0;
	this->bt3_1->decNumRef();
	this->bt3_1 = 0;
	this->bt3_2->decNumRef();
	this->bt3_2 = 0;
	this->bt3_3->decNumRef();
	this->bt3_3 = 0;
	this->bt4_1->decNumRef();
	this->bt4_1 = 0;
	this->bt4_2->decNumRef();
	this->bt4_2 = 0;
	this->bt4_3->decNumRef();
	this->bt4_3 = 0;
	this->bt5_1->decNumRef();
	this->bt5_1 = 0;
	this->bt5_2->decNumRef();
	this->bt5_2 = 0;
	this->bt5_3->decNumRef();
	this->bt5_3 = 0;

	this->splashSprite->decNumRef();
	this->splashSprite = 0;
	this->box->decNumRef();
	this->box = 0;
	this->waiting->decNumRef();
	this->waiting = 0;
	this->disconnect->decNumRef();
	this->disconnect = 0;
	this->boxInput->decNumRef();
	this->boxInput = 0;
	this->bg->decNumRef();
	this->bg = 0;
	this->cursor->decNumRef();
	this->cursor = 0;
}

void MainMenuButHandler::render(float cameraX, float cameraY){
	this->splashSprite->render(0,0);
	this->hostButton->render(0,0);
	this->connectButton->render(0,0);
	this->optionsButton->render(0,0);
	this->creditsButton->render(0,0);
	this->quitButton->render(0,0);

	if(tryToConnect)
		renderConnect();
	
	if(host)
		renderWaiting();
	if(Network::disconnected)
		renderDisconnect();
}

int MainMenuButHandler::update(int dt){
	mouseOver(hostButton);
	mousePressed(hostButton,"ScenePhaseOne");
	mouseOver(connectButton);
	mousePressed(connectButton,"SceneConnect");
	mouseOver(optionsButton);
	mousePressed(optionsButton,"SceneOptions");
	mouseOver(creditsButton);
	mousePressed(creditsButton,"SceneCredits");
	mouseOver(quitButton);
	mousePressed(quitButton,"Quit");

	this->hostButton->update(dt);
	this->connectButton->update(dt);
	this->optionsButton->update(dt);
	this->creditsButton->update(dt);
	this->quitButton->update(dt);
	
	if(tryToConnect)
		updateConnect(dt);
	updateDisconnect(dt);
	updateWaiting(dt);

	if(Network::connected && thread)
	{
		Network::receiveThread();
		if(GameManager::currentScene->changeScene("SceneSelectCharacter") == 1)
			GameManager::fadeScreen->fadeIn(1,2);
		thread = false;
		clickOtherButtons = true;
	}
	return 0;
}

void MainMenuButHandler::mouseOver(Button *bt){
	bt->setMouseCoord(input->mousePosX(),input->mousePosY());
	if((bt->insideButton() == 1) && (clickOtherButtons == false))
		bt->setChangeSprite(1);

}

void MainMenuButHandler::mousePressed(Button *bt,string scene){

	

	if((input->isMousePressed(1)) && (bt->insideButton()) == 1 && (clickOtherButtons == true))
	{
		bt->mousePressed(true);

		if(bt == hostButton)
		{
			if(!host){
				Network::cancel = false;
				Network::host();
				host = true;
				thread = true;
				clickOtherButtons = false;
			}
		}else

		if(scene.compare("Quit") == 0){
			SDL_Event quit;
		    quit.type = SDL_QUIT;
			SDL_PushEvent( &quit );
		}
		else if(scene.compare("SceneConnect") == 0)
		{
			tryToConnect = true;
			clickOtherButtons = false;
			bt->setChangeSprite(0);
		}
		else if(bt->getChangeScene())
		{
			changeScene(scene);
			clickOtherButtons = false;
			bt->setChangeSprite(0);
		}
	}
	else
	{
		bt->mousePressed(false);
	}
}

void MainMenuButHandler::renderConnect(){
	clickOtherButtons = false;
	connectBox->render(0,0);

	if(message.size() != 0)
	{
	SDLBase::renderText(font, message ,color,boxInputX + 10,boxInputY + 15);
	}
	else if(read){
		connectBox->renderCursor();
	}

	if(renderConnectError)
	{
		SDLBase::renderText(font, "It wasn't possible to connect. Try again.",color,boxInputX - 65,boxInputY - 73);
		
	}
	

}

void MainMenuButHandler::renderDisconnect(){
	clickOtherButtons = false;
	disconnectBox->render(0,0);

}

void MainMenuButHandler::renderWaiting(){
	clickOtherButtons = false;
	waitingBox->render(0,0);
	waitAnim->animate(100,260,260);
}

bool MainMenuButHandler::isInsideBox(MessageBox* messageBox){
	return connectBox->isInsideBox();
}

void MainMenuButHandler::updateConnect(int dt){
	clickOtherButtons = false;
	if(isInsideBox(connectBox) == true && (input->isMousePressed(1)))
	{
		read = true;
		connectBox->activateCursor();
	}
	else if(isInsideBox(connectBox) == false && (input->isMousePressed(1)))
	{
		read = false;
		connectBox->deactivateCursor();
	}

	if(read)
	{
		if (message.size() < 15)
		{
			readInput();
		}
		else
		{
			backspace();
		}
	}
	connectBox->update(dt);
	if(connectBox->confirmPressed())
	{
		if(!Network::connected)
		{
			connectBox->deactivateConfirm();
		  	if(Network::connect(message) == 0)
			{
				renderConnectError = false;
				Network::receiveThread();
				if(GameManager::currentScene->changeScene("SceneSelectCharacter") == 1)
				GameManager::fadeScreen->fadeIn(1,2);											  
			}
			else if (Network::connect(message) == -1) 
			{
				renderConnectError = true;
			}
			
		}
	}

	

}

void MainMenuButHandler::updateDisconnect(int dt){
	disconnectBox->update(dt);
	if(disconnectBox->confirmPressed())
	{
		Network::disconnected = false;
		clickOtherButtons = true;
	}

}

void MainMenuButHandler::updateWaiting(int dt){
	waitAnim->update(dt,true,0, false);
	if(SDL_mutexP(Network::mutex2) == 0)
	{
		waitingBox->update(dt);
		if(waitingBox->confirmPressed() && !Network::cancel)
		{
			clickOtherButtons = true;
			host = false;
			thread = false;
			Network::closeConnection();
			Network::cancel = true;
			waitingBox->deactivateConfirm();
		}

			SDL_mutexV(Network::mutex2);
	}
}

void MainMenuButHandler::readInput(){
	if(input->isKeyUp(SDLK_0))
	{
		message = message + "0";
		connectBox->increaseCursor(18);		
		sizeMessage++;
	}
	if(input->isKeyUp(SDLK_1))
	{
		message = message + "1";
		connectBox->increaseCursor(8.1);	
		sizeMessage++;	
	}
	if(input->isKeyUp(SDLK_2))
	{
		message = message + "2";
		connectBox->increaseCursor(14);	
		sizeMessage++;	
	}
	if(input->isKeyUp(SDLK_3))
	{
		message = message + "3";
		connectBox->increaseCursor(15);		
		sizeMessage++;
	}
	if(input->isKeyUp(SDLK_4))
	{
		message = message + "4";
		connectBox->increaseCursor(17);	
		sizeMessage++;	
	}
	if(input->isKeyUp(SDLK_5))
	{
		message = message + "5";
		connectBox->increaseCursor(15);	
		sizeMessage++;	
	}
	if(input->isKeyUp(SDLK_6))
	{
		message = message + "6";
		connectBox->increaseCursor(16);	
		sizeMessage++;	
	}
	if(input->isKeyUp(SDLK_7))
	{
		message = message + "7";
		connectBox->increaseCursor(15);	
		sizeMessage++;	
	}
	if(input->isKeyUp(SDLK_8))
	{
		message = message + "8";
		connectBox->increaseCursor(15);	
		sizeMessage++;	
	}
	if(input->isKeyUp(SDLK_9))
	{
		message = message + "9";
		connectBox->increaseCursor(16);	
		sizeMessage++;	
	}
	if(input->isKeyUp(SDLK_PERIOD))
	{
		message = message + ".";
		connectBox->increaseCursor(6);	
		sizeMessage++;	
	}
	backspace();
}

void MainMenuButHandler::backspace(){
	string lastNumber;
	if(input->isKeyUp(SDLK_BACKSPACE) && (sizeMessage > 0 || sizeMessage == 0))
	{
		if(sizeMessage != 0)
		{
			stringstream ss;
			char lastChar = message.at(sizeMessage - 1);
			ss << lastChar;
			ss >> lastNumber;
			message = message.substr(0, message.size()-1);
			sizeMessage--;
		}
	
		if( lastNumber == "1")
		{
			connectBox->decreaseCursor(8.1);		
		}
		else if( lastNumber == "2")
		{
			connectBox->decreaseCursor(14);		
		}
		else if( lastNumber == "3")
		{
			connectBox->decreaseCursor(15);		
		}
		else if( lastNumber == "4")
		{
			connectBox->decreaseCursor(17);		
		}
		else if( lastNumber == "5")
		{
			connectBox->decreaseCursor(15);		
		}
		else if( lastNumber == "6")
		{
			connectBox->decreaseCursor(16);		
		}
		else if( lastNumber == "7")
		{
			connectBox->decreaseCursor(15);		
		}
		else if( lastNumber == "8")
		{
			connectBox->decreaseCursor(15);		
		}
		else if( lastNumber == "9")
		{
			connectBox->decreaseCursor(16);		
		}
		else if( lastNumber == "0")
		{
			connectBox->decreaseCursor(18);		
		}
		else
		{
			connectBox->decreaseCursor(6);
		}
	}
}

void MainMenuButHandler::changeScene(string nextScene){
	if(GameManager::currentScene->changeScene(nextScene) == 1)
		GameManager::fadeScreen->fadeIn(1,0.2);
}

