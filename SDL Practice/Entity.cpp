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

void Entity::render()
{
	(*sprite).draw(pos);
}