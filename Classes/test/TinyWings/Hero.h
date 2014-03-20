#ifndef _HERO_H

#define _HERO_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
USING_NS_CC;

#define PTM_RATIO 32

class Hero : public Sprite
{
public:
	Hero();
	virtual ~Hero();

	static Hero* create(b2World* world);

	virtual bool init() override;

	virtual void update(float dt) override;

	void createBody();

	bool isAwake(){ return this->_bIsAwake; }

	void wake();
	void dive();
	void limitVelocity();

	void setWorld(b2World* world)
	{
		this->_world = world;
	}

private:
	b2World* _world;
	b2Body* _body;
	bool _bIsAwake;

};
#endif