#include <iostream>

#include "Entity.h"

Entity::Entity(Texture* inputTexture, Vec2 inputPos)
{
	pos = inputPos;
	assignTexture(inputTexture);

	//Create the Collision box (AABB - Axis-Aligned Bounding Box)
	SDL_Rect tempAABB;
	tempAABB.h = getDimensions().y;
	tempAABB.w = getDimensions().x;
	tempAABB.x = pos.x;
	tempAABB.y = pos.y;

	AABB = tempAABB;
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
	/*
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
	*/
		pos.x += adjustBy.x;
		pos.y += adjustBy.y;
	
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

void Entity::updateAABB()
{
	AABB.x = pos.x;
	AABB.y = pos.y;
}

SDL_Rect Entity::getAABB()
{
	updateAABB();
	return this->AABB;
}