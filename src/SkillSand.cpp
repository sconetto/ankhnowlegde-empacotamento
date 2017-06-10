#include "SkillSand.h"
#include "SDLBase.h"
#include "BlockSand.h"
#include "Tile.h"
#include "Character.h"

SkillSand::SkillSand()
{
	this->requiredStamina = 5;
	this->considerBlocks = true;
	this->considerSand = false;
	this->reach = 3;
}

SkillSand::~SkillSand() {}

void SkillSand::execute(Tile * origin, Tile * dest)
{
	AudioHandler * audio = AudioHandler::getInstance();
 	audio->setEffect("sand_action.wav");
 	audio->playEffect(0);

	Block *oldBlock = dest->getBlock();

	if(oldBlock)
	{
		oldBlock->setDestroyedAnimBlock(true);

	}
	else
	{
		Block *newBlock = new BlockSand(new Sprite(SDLBase::resourcesPath + "areiamovedica.png"), dest->getX(), dest->getY());
		dest->setBlock(newBlock);
	}
}

int SkillSand::getRequiredStamina()
{
	return this->requiredStamina;
}

bool SkillSand::getConsiderBlocks()
{
	return this->considerBlocks;
}

int SkillSand::getReach()
{
	return this->reach;
}
