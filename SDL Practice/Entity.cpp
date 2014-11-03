#include "Entity.h"
#include <iostream>

Entity::Entity(Texture* inputTexture, Vec2 inputPos)
{
	pos = inputPos;
	assignTexture(inputTexture);
}

Entity::~Entity()
{

}

bool Entity::assignTexture(Texture *texture)
{
	if (!texture)
	{
		std::cout << "Texture supplied to Entity incorrect" << std::endl;
		return false;
	}
	else
	{
		sprite = texture;
		return true;
	}

}

Vec2 Entity::getDimensions()
{	
	return sprite->getDimensions();
}

void Entity::render()
{
	(*sprite).draw(pos);
}

void Entity::move(Vec2 adjustBy)
{
	if (pos.x > 640 - getDimensions().x)
	{
		pos.x = 640 - getDimensions().x;
	} 
	else if (pos.x < 0)
	{
		pos.x = 0;
	}
	else
	{
		pos.x += adjustBy.x;
		pos.y += adjustBy.y;
	}
}

Vec2 Entity::getPos()
{
	return pos;
}