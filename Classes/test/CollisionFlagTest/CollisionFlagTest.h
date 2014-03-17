#ifndef  _COLLISION_FLAG_TEST_H

#define _COLLISION_FLAG_TEST_H

#include "../../HelloWorldScene.h"

#include "../ContactTest/ContactTest.h"
USING_NS_CC;

enum _entityCategory {
	BOUNDARY = 0x0001,
	FRIENDLY_SHIP = 0x0002,
	ENEMY_SHIP = 0x0004,
	FRIENDLY_AIRCRAFT = 0x0008,
	ENEMY_AIRCRAFT = 0x0010,
};

class CollisionFlagTest : public HelloWorld
{
public:
	CollisionFlagTest();
	virtual ~CollisionFlagTest();

	CREATE_FUNC(CollisionFlagTest);

	static Scene* createScene();

	virtual bool init() override;

	virtual void initPhysics() override;

	virtual void addNewSpriteAtPosition(cocos2d::Point p) override;

	virtual void update(float dt);

private:
	std::vector<Ball*> balls;
};
#endif