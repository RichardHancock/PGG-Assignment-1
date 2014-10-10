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
	void Entity::move(Vec2);
private:
	Texture* sprite = NULL;
	Vec2 pos;
	bool Entity::assignTexture(Texture*);

};

#endif