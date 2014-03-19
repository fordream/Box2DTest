#ifndef _JOINT_TEST_H

#define _JOINT_TEST_H

#include "../../HelloWorldScene.h"
USING_NS_CC;

enum class JointType
{
	Revolute,  //��ת������
	Prismatic, //ƽ��������
	Distance, //����������
	Friction, //Ħ����������
	Pulley,    //����������
	Gear,    //����������
	Mouse, //���������
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