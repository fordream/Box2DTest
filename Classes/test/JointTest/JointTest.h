#ifndef _JOINT_TEST_H

#define _JOINT_TEST_H

#include "../../HelloWorldScene.h"
USING_NS_CC;

enum class JointType
{
	Revolute,  //旋转连接器
	Prismatic, //平移连接器
	Distance, //距离连接器
	Friction, //摩擦力连接器
	Pulley,    //滑轮连接器
	Gear,    //齿轮连接器
	Mouse, //鼠标连接器
};

class JointTest : public HelloWorld
{
public:
	JointTest();
	virtual ~JointTest();

	CREATE_FUNC(JointTest);

	static Scene* createScene();

	virtual bool init() override;

	virtual void initPhysics() override;

	virtual void update(float dt) override;

	virtual void addNewSpriteAtPosition(cocos2d::Point p) override;


	virtual void addJoint(JointType type);

};
#endif