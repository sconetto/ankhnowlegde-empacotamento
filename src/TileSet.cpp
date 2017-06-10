#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string filePath) {
	tileSet = NULL;
	tileSet = new Sprite(filePath);

	this->useSingleFile = true;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->vTiles = NULL;

	//Calculo do numero de colunas
	this->columns = (tileSet->getWidth()/tileWidth);

	//Calculo do numero de linhas
	this->lines = (tileSet->getHeight()/tileHeight);
}

TileSet::TileSet(std::string filePath, int lines, int columns) {
	tileSet = NULL;
	tileSet = new Sprite(filePath);

	this->lines = lines;
	this->columns = columns;
	this->useSingleFile = true;
	this->vTiles = NULL;

	//Calculo do comprimento de um tile do sprite
	this->tileWidth = (tileSet->getWidth()/columns);
	//Calculo da altura de um tile do sprite
	this->tileHeight = (tileSet->getHeight()/lines);
}

TileSet::TileSet(int tileWidth, int tileHeight) {
	tileSet = NULL;

	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	this->lines = 0;
	this->columns = 0;
	this->useSingleFile = false;
	this->vTiles = new std::vector<Sprite*>();
}

void TileSet::addTile(std::string filePath){
	if(usingSingleFile())
		return;

	Sprite * tile = new Sprite(filePath);
	vTiles->push_back(tile);
}

void TileSet::render(int index, float posX, float posY){
	if(usingSingleFile()){
		int u = index % columns;
		int v = index / columns;

		int offsetX = u * tileWidth;
		int offsetY = v * tileHeight;

		tileSet->clip(offsetX, offsetY,tileWidth,tileHeight);
		tileSet->render(posX,posY);

	}else{
		vTiles->at(index)->render(posX,posY);
	}
}

bool TileSet::usingSingleFile(){
	return this->useSingleFile;
}

int TileSet::getTileWidth(){
	return this->tileWidth;
}

int TileSet::getTileHeight(){
	return this->tileHeight;
}

TileSet::~TileSet() {
	// TODO Auto-generated destructor stub
}

