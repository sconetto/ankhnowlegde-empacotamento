/*
 * Network.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: al
 */

#include "Network.h"
#include <iostream>

IPaddress Network::ip, * Network::receiverIp;
int Network::rc, Network::id;
TCPsocket Network::currentSocket, Network::communicationSocket;
char Network::buffer[512];
vector<string> Network::messageQueue;
SDL_Thread * Network::thread,* Network::lThread;
bool Network::endGame, Network::connected, Network::firstTime, Network::lost, Network::disconnected;
bool Network::cancel;
SDL_mutex *Network::mutex, *Network::mutex2;
int Network::player1Selection, Network::player2Selection;

Network::Network() {

}

void Network::init(){
	rc = SDLNet_Init();

	if(rc == -1)
	{
		cout << "Erro na inicializacao da NET: " << SDLNet_GetError() << endl;
	}
	connected = 0;
	currentSocket = 0;
	communicationSocket = 0;
	endGame = false;
	mutex = SDL_CreateMutex();
	mutex2 = SDL_CreateMutex();
	id = -1;
	firstTime = false;
	lost = false;
	disconnected = false;
	Network::cancel = false;
	player1Selection = 0;
	player2Selection = 0;

}

void Network::finish(){

	messageQueue.clear();

	SDL_KillThread(thread);
	SDL_KillThread(lThread);
	SDL_DestroyMutex(mutex);

	if(currentSocket)
	{
		SDLNet_TCP_Close(currentSocket);
	}
	
	if(communicationSocket)
	{
		SDLNet_TCP_Close(communicationSocket);
	}
	SDLNet_Quit();
}

Network::~Network() {


}

int Network::connect(string ipaddress){

	rc = SDLNet_ResolveHost(&ip, ipaddress.c_str(), 3000);

	if(rc == -1)
	{
		return -1;
	}

	communicationSocket = SDLNet_TCP_Open(&ip);

	if(communicationSocket == NULL)
	{
		return -1;
	}

	id = 2;
	connected = true;
	firstTime = true;
	lost = false;

	return 0;
}

void Network::disconnect(){

}

void Network::sendMessage(string message){
	if(SDLNet_TCP_Send(communicationSocket, (void *) message.c_str(), message.size()+1) < (int)message.size())
	{
		cout << "Erro no envio da MENSAGEM: " << SDLNet_GetError() << endl;
		return;
	}
}

int Network::receiveMessage(void *){

	while((connected))
	{
		//cout<<"trying to receive message"<<endl;

		if(SDLNet_TCP_Recv(communicationSocket, buffer, 512) > 0)
		{
			if(SDL_mutexP(mutex) == 0)
			{
				string message = buffer;
				//cout<<"recebi a msn: "<<message<<endl;
				messageQueue.push_back(message);
				SDL_mutexV(mutex);
			}
			else
			{
				cout<<"mutex nao funcionou"<<endl;
			}

		}else
		{
			connected = false;
			if(GameManager::currentScene->changeScene("SceneMainMenu") == 1)
					GameManager::fadeScreen->fadeIn(1,2);
			if(currentSocket)
			{
				SDLNet_TCP_Close(currentSocket);
			}

			if(communicationSocket)
			{
				SDLNet_TCP_Close(communicationSocket);
			}
			currentSocket = NULL;
			communicationSocket = NULL;
			id = -1;
			disconnected = true;
		}

	}

	return 0;
}

void Network::receiveThread(){
	thread = SDL_CreateThread(receiveMessage, NULL);
}

void Network::listeningThread(){
	lThread = SDL_CreateThread(listening, NULL);
}

string Network::readMessage()
{
	string message = "";
	if(SDL_mutexP(mutex) == 0)
	{
		if(!messageQueue.empty())
		{
			message = messageQueue.at(0);
			messageQueue.erase(messageQueue.begin());

		}
	SDL_mutexV(mutex);
	}
	return message;
}

int Network::host()
{
	rc = SDLNet_ResolveHost(&ip, NULL, 3000);

	if(rc == -1)
	{
		return -1;
	}

	currentSocket = SDLNet_TCP_Open(&ip);

	if(currentSocket == NULL)
	{
		return -1;
	}

	listeningThread();

	return 0;
}

int Network::listening(void *)
{
	while(!connected)
	{
		if(SDL_mutexP(mutex2) == 0)
		{
			if(cancel)
			{
				SDL_mutexV(mutex2);
				break;
			}
			SDL_mutexV(mutex2);
		}

		
		if((communicationSocket = SDLNet_TCP_Accept(currentSocket)))
		{
			connected = true;
			firstTime = true;
			lost = false;
			id = 1;
			
		}
		SDL_Delay(1);
	}

	return 0;

}

void Network::closeConnection(){
	if(currentSocket)
	{
		SDLNet_TCP_Close(currentSocket);
	}

	if(communicationSocket)
	{
		SDLNet_TCP_Close(communicationSocket);
	}
}

int Network::getID()
{
	return id;
}

bool Network::isFirstTime()
{
	return firstTime;
}

bool Network::didLost()
{
	return lost;
}

void Network::setLost(bool value)
{
	lost = value;
}

void Network::setFirstTime(bool value)
{
	firstTime = value;
}

