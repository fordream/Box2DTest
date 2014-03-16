#ifndef _WORLD_TEST_H

#define _WORLD_TEST_H

#include "../../HelloWorldScene.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class WorldTest : public HelloWorld
{
public:
	WorldTest();
	virtual ~WorldTest();

	CREATE_FUNC(WorldTest);

	static Scene* createScene();

	virtual bool init() override;

	virtual void initPhysics() override;
	virtual void onEnter() override;

	virtual void addNewSpriteAtPosition(cocos2d::Point p) override;

private:
	b2Body* bodies[3];
	PhysicsSprite* sprites[3];
};
#endif