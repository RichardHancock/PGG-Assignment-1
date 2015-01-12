#include "../Texture.h"
#include "../Vec2.h"

#pragma once

class Entity
{
public:
	Entity(Texture*,Vec2);
	~Entity();
	void Entity::render();
	void Entity::move(Vec2);
	Vec2 Entity::getPos();
	Vec2 Entity::getDimensions();
	float getRotation();
	void setRotation(float);
	
	SDL_Rect getAABB();
	virtual void update(float) = 0;
protected:
	Texture* sprite;
	Vec2 pos;
	bool Entity::assignTexture(Texture*);
	Vec2 dimensions;
	float rotation;
	void updateAABB();
	SDL_Rect AABB;
};