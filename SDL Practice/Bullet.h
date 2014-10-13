#include "Entity.h"

class Bullet: public Entity
{
public:
	Bullet(Texture*, Vec2);
	~Bullet();
	void Bullet::update();
protected:
	
private:
	int speed;
	char direction;
};

