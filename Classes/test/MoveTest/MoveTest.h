#ifndef _MOVE_TEST_H

#define _MOVE_TEST_H


#include "../../HelloWorldScene.h"
USING_NS_CC;


#include "cocos-ext.h"
USING_NS_CC_EXT;

enum  MoveState
{
	MS_STOP,
	MS_LEFT,
	MS_RIGHT,
};

class MoveTest : public HelloWorld
{
public:
	MoveTest();
	virtual ~MoveTest();

	

	CREATE_FUNC(MoveTest);

	static Scene* createScene();

	virtual bool init() override;

	virtual void initPhysics() override;
	
	virtual void onEnter();

	virtual void update(float dt);

	virtual void addNewSpriteAtPosition(cocos2d::Point p);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;

private:
	b2Body* m_ptrBody;
	MoveState m_MoveState;

};
#endif