#ifndef TILEMAP_H
#define TILEMAP_H
#include <vector>
#include <string>
#include "Tile.h"
#include "Sprite.h"

class TileMap
{
    public:
        TileMap(std::string mapa, Sprite*tile,Sprite* block,float posX, float posY);
        void load(std::string mapPath);
        vector<Tile* > getTiles();
        int getColumns();
        int getRows();
        int getP1Position();
        int getP2Position();
        float getOffsetX();
        float getOffsetY();
        virtual ~TileMap();

    private:
        vector<Tile* > tiles;
        Sprite* tile, *block;
        int mapColumns, mapRows;
        float posX, posY;
        float posXOffset, posYOffset;
        int p1Position, p2Position;

};

#endif // TILEMAP_H
