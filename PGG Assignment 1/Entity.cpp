#include <iostream>

#include "Entity.h"

Entity::Entity(Texture* inputTexture, Vec2 inputPos)
{
	pos = inputPos;
	assignTexture(inputTexture);

	//Create the Collision box (AABB - Axis-Aligned Bounding Box)
	AABB.h = getDimensions().y;
	AABB.w = getDimensions().x;
	AABB.x = pos.x;
	AABB.y = pos.y;
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
	(*sprite).draw(pos, rotation);
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

float Entity::getRotation()
{
	return rotation;
}

void Entity::setRotation(float newRotation)
{
	rotation = newRotation;
}

SDL_Rect Entity::getAABB()
{
	return AABB;
}