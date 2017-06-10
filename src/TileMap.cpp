#include <iostream>

#include "TileMap.h"
#include "BlockMovable.h"
#include "BlockTreasure.h"
#include "BlockSand.h"
#include "BlockWater.h"
#include "BlockFixed.h"

#define MOVABLE_BLOCK 1
#define NORMAL_TILE   0
#define TREASURE 2
#define SAND_BLOCK 3
#define WATER_BLOCK 4
#define FIXED_BLOCK 5

using namespace std;

//Construtor do TileMap, passando o arquivo com o mapa dos tiles, o tileset e o tilesize
TileMap::TileMap(std::string mapa, Sprite* tile, Sprite* block, float posX, float posY)
{
    this->mapColumns = 0;
    this->mapRows = 0;
    this->tile = tile;
    this->block = block;
    this->posX = posX;
    this->posY = posY;
    this->p1Position = 0;
    this->p2Position = 0;
    //carrega o mapa
    load(mapa);

}

void TileMap::load(std::string mapPath)
{
    int fscanf_return;
    //abre o arquivo indicando leitura
    FILE* mapFile = fopen(mapPath.c_str(), "r");
    if(mapFile == NULL) {
        return;
    }
    int index = 0;
    //pega a largura, altura e layers do mapa, indicados na primeira linha do arquivo
    fscanf_return = fscanf(mapFile, "%d,%d,%f,%f,%d,%d,", &mapColumns, &mapRows, &posXOffset, &posYOffset, &p1Position, &p2Position);
    
    if(!fscanf_return)
    {
        cout << "Impossible to read the map file" << endl;
        return;
    }

    posX += posXOffset;
    posY += posYOffset;

    //pula 4 linhas para cair na posição exata dos indices dos tiles indicados no arquivo txt
    fscanf_return = fscanf(mapFile, "\n\n\n\n");
    int id = 0;
    //loop que percorre as colunas, linhas e os layers do arquivo txt
    	//cout<<"POS X "<<posX<<" POS T "<<posY<<"\n"<<endl;

        for(int y = 0;y < mapRows;y++)
        {
            for(int x = 0; x < mapColumns;x++)
            {

                fscanf_return = fscanf(mapFile, "%d,", &index);
                //cout<<"Index "<<index<<endl;
                if(index == NORMAL_TILE)
                {
                	//cout<<"Entrei 1 x: "<<posX+ tile->getWidth()*x<< " y:" <<posY + tile->getHeight()*y<< "id "<<id<<"\n"<<endl;
                	tiles.push_back(new Tile(tile, 0,posX+ tile->getWidth()*((int)(id%mapColumns)), posY + tile->getHeight()*((int)(id/mapColumns)), id));
                }
                else if(index == MOVABLE_BLOCK)
                {
                	//cout<<"Entrei 2 x: "<<posX+ tile->getWidth()*x<< " y:" <<posY + tile->getHeight()*y<< "id "<<id<<"\n"<<endl;
                	tiles.push_back(new Tile(tile
											, new BlockMovable(block,posX+ tile->getWidth()*((int)(id%mapColumns)), posY + tile->getHeight()*((int)(id/mapColumns)))
											, posX+ tile->getWidth()*((int)(id%mapColumns))
											, posY + tile->getHeight()*((int)(id/mapColumns))
											, id));
                }
                else if(index == TREASURE)
                {
                	//cout<<"Entrei 2 x: "<<posX+ tile->getWidth()*x<< " y:" <<posY + tile->getHeight()*y<< "id "<<id<<"\n"<<endl;
                	Sprite *sprite = new Sprite(SDLBase::resourcesPath + "bauanimacao.png");
					tiles.push_back(new Tile(tile
											, new BlockTreasure(sprite,posX+ tile->getWidth()*((int)(id%mapColumns)), posY + tile->getHeight()*((int)(id/mapColumns)))
											, posX+ tile->getWidth()*((int)(id%mapColumns))
											, posY + tile->getHeight()*((int)(id/mapColumns))
											, id));
                }
                else if(index == SAND_BLOCK)
                {
                    //cout<<"Entrei 2 x: "<<posX+ tile->getWidth()*x<< " y:" <<posY + tile->getHeight()*y<< "id "<<id<<"\n"<<endl;
                    Sprite *sprite = new Sprite(SDLBase::resourcesPath + "areiamovedica.png");
                    tiles.push_back(new Tile(tile
                                            , new BlockSand(sprite,posX+ tile->getWidth()*((int)(id%mapColumns)), posY + tile->getHeight()*((int)(id/mapColumns)))
                                            , posX+ tile->getWidth()*((int)(id%mapColumns))
                                            , posY + tile->getHeight()*((int)(id/mapColumns))
                                            , id));
                }
                else if(index == WATER_BLOCK)
                {
                   // cout<<"Entrei 2 x: "<<posX+ tile->getWidth()*x<< " y:" <<posY + tile->getHeight()*y<< "id "<<id<<"\n"<<endl;
                    Sprite *sprite = new Sprite(SDLBase::resourcesPath + "pote_de_agua.png");
                    tiles.push_back(new Tile(tile
                                            , new BlockWater(sprite,posX+ tile->getWidth()*((int)(id%mapColumns)), posY + tile->getHeight()*((int)(id/mapColumns)))
                                            , posX+ tile->getWidth()*((int)(id%mapColumns))
                                            , posY + tile->getHeight()*((int)(id/mapColumns))
                                            , id));
                }
                else if(index == FIXED_BLOCK)
                {
                   
                    Sprite *sprite = new Sprite(SDLBase::resourcesPath + "blocofixocomareia.png");
                    tiles.push_back(new Tile(tile
                                            , new BlockFixed(sprite,posX+ tile->getWidth()*((int)(id%mapColumns)), posY + tile->getHeight()*((int)(id/mapColumns)))
                                            , posX+ tile->getWidth()*((int)(id%mapColumns))
                                            , posY + tile->getHeight()*((int)(id/mapColumns))
                                            , id));
                }
                id++;
            }
            fscanf_return = fscanf(mapFile, "\n");
            fscanf_return = fscanf(mapFile, "\n");
        }
    //fecha arquivo
    fclose(mapFile);

}


vector<Tile* > TileMap::getTiles(){
	return this->tiles;
}

int TileMap::getColumns(){
	return this->mapColumns;
}

int TileMap::getRows(){
	return this->mapRows;
}

int TileMap::getP1Position()
{
	return this->p1Position;
}

int TileMap::getP2Position()
{
	return this->p2Position;
}

float TileMap::getOffsetX()
{
	return this->posX;
}

float TileMap::getOffsetY()
{
	return this->posY;
}

TileMap::~TileMap()
{

}
