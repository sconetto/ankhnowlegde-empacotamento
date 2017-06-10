#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Network.h"
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "GameManager.h"
#include "Animation.h"
#include "Tile.h"
#include "Skill.h"
#include <string>
#include "Map.h"

class Tile;
class Skill;
class Map;

class Character:public GameObject {
	public:
		Character(Tile* tile, int id);
		void render(float cameraX, float cameraY);
		virtual int update(int dt);
		virtual ~Character();
		bool isUsingSkill();
		bool isPerformingAction();
		enum Direction { up, down, right, left, none };
		virtual void pushUpdate(InputManager * input, Direction dir = none);
		virtual void moveUpdate(InputManager * input, Direction dir = none);
		virtual void move(Direction dir);
		void setSkill(Skill * skill);
		virtual void setSkillDestTile(Tile * tile);
		virtual void push(Direction dir);
		void interpolateMovement(float dt);
		void setTurn(bool on);
		void toogleTurn();
		int getStamina();
		int getInitialStamina();
		void setStamina(int stamina);
		int getId();
		void setCurrentTile(Tile * tile);
		Tile * getCurrentTile();
		void incrementDiscountStamina(int value);
		void resetDiscountStamina();
		bool hasEnoughStamina();
		bool getWin();
		void setWin(bool win);
		bool getTurn();
		Sprite * getHud();
		void activateSkill();
		void deactivateSkill();
		void useSkill(int tileIndex);
		void setMap(Map * map);
		void sendMessage(string action, string info);
		void spawnSand(string msg);

	protected:
		Sprite* sprite, *hud;
		Animation *currentAnimation;
		Skill* skill;
		float vx,vy;
		bool activatedSkill;
		bool performingAction,onLoop;
		float endX;
		float endY;
		float beginX;
		float beginY;
		int stamina;
		int initialStamina;
		bool win;
		bool turn;
		int id;
		int dt;
		int direction;
		Tile * currentTile, * skillDestTile;
		virtual void changeCurrentTile(Tile * tile);
		virtual bool canChangeTile(Tile * tile);
		void setClickableTiles(Tile *origin, int reach, bool considerBlock, bool clickable);
		int discountStamina;
		void receiveMessage();
		string intToString(int intenger);
		Map * map;
};

#endif /* CHARACTER_H_ */
