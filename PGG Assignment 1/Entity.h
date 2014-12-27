#include "Texture.h"
#include "Vec2.h"

#ifndef ENTITY_H
#define ENTITY_H
class Entity
{
public:
	Entity(Texture*,Vec2);
	~Entity();
	void Entity::render();
	void Entity::renderEx();
	void Entity::move(Vec2);
	Vec2 Entity::getPos();
	Vec2 Entity::getDimensions();
	float getRotation();
	void setRotation(float);
	
	virtual void update(float) = 0;
protected:
	Texture* sprite;
	Vec2 pos;
	bool Entity::assignTexture(Texture*);
	Vec2 dimensions;
	float rotation;

};

#endif