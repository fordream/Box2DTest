#include "JointTest.h"

JointTest::JointTest()
{

}

JointTest::~JointTest()
{

}

Scene* JointTest::createScene()
{
	JointTest* pRet = JointTest::create();

	Scene* pScene = Scene::create();

	pScene->addChild(pRet);

	return pScene;
}

bool JointTest::init()
{
	if (!HelloWorld::init())
		return false;

	return true;
}

void JointTest::initPhysics()
{
	HelloWorld::initPhysics();

	addJoint(JointType::Mouse);
}

void JointTest::addNewSpriteAtPosition(cocos2d::Point p)
{

}

void JointTest::addJoint(JointType type)
{
	Size size = Director::getInstance()->getVisibleSize();

	b2Body* bodyA = nullptr;
	b2Body* bodyB = nullptr;

	b2BodyDef bodydef;
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(size.width / 2 / PTM_RATIO, 1);

	b2PolygonShape shape;
	shape.SetAsBox(1, 1);

	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	//没有质量则不会旋转
	fixturedef.density = 100;

	bodyA = m_ptrPhysicsWorld->CreateBody(&bodydef);
	bodyA->CreateFixture(&fixturedef);

	bodydef.position.Set(size.width / 2 / PTM_RATIO + 3, 1);

	b2CircleShape circleShape;
	circleShape.m_p = b2Vec2(0, 0);
	circleShape.m_radius = 1;

	fixturedef.shape = &circleShape;
	fixturedef.density = 0;

	bodyB = m_ptrPhysicsWorld->CreateBody(&bodydef);
	bodyB->CreateFixture(&fixturedef);
	bodyB->SetGravityScale(0);

	switch (type)
	{
	case JointType::Revolute:
	{
		
		//旋转连接器
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = bodyA;
		revoluteJointDef.bodyB = bodyB;
		revoluteJointDef.collideConnected = false;

		revoluteJointDef.localAnchorA.Set(1, 1);
		revoluteJointDef.localAnchorB.Set(0, 0);
		revoluteJointDef.referenceAngle = 45.0f*DEGTORAD;

		revoluteJointDef.enableLimit = true;
		revoluteJointDef.lowerAngle = -45 * DEGTORAD;
		revoluteJointDef.upperAngle = 45 * DEGTORAD;

		revoluteJointDef.enableMotor = true;
		revoluteJointDef.maxMotorTorque = 5;
		revoluteJointDef.motorSpeed = 90 * DEGTORAD;

		m_ptrPhysicsWorld->CreateJoint(&revoluteJointDef);


		break;
	}

	case JointType::Prismatic:
	{
		b2PrismaticJointDef prismaticJointDef;
		prismaticJointDef.bodyA = bodyA;
		prismaticJointDef.bodyB = bodyB;

		prismaticJointDef.collideConnected = false;
		//轴线axis1相对于物体A
		prismaticJointDef.localAxisA.Set(0, 1);

		prismaticJointDef.localAnchorA.Set(2, 0);
		prismaticJointDef.localAnchorB.Set(-1, 0);

		prismaticJointDef.enableLimit = true;
		prismaticJointDef.lowerTranslation = 0;
		prismaticJointDef.upperTranslation = 10;

		prismaticJointDef.enableMotor = true;
		prismaticJointDef.maxMotorForce = 500;
		prismaticJointDef.motorSpeed = 5;

		m_ptrPhysicsWorld->CreateJoint(&prismaticJointDef);


		break;
	}

	case JointType::Distance:
	{

		b2DistanceJointDef distanceJointDef;
		distanceJointDef.bodyA = bodyA;
		distanceJointDef.bodyB = bodyB;
		distanceJointDef.collideConnected = false;

		distanceJointDef.localAnchorA.Set(1, 0);
		distanceJointDef.localAnchorB.Set(-1, 0);
		distanceJointDef.length = 5;

		m_ptrPhysicsWorld->CreateJoint(&distanceJointDef);

		break;
	}

	case JointType::Friction:
	{
		b2FrictionJointDef frictionJointDef;
		frictionJointDef.Initialize(bodyA, bodyB, b2Vec2(0.0f, 0.0f));
		frictionJointDef.collideConnected = false;

		frictionJointDef.maxForce = 100.0f;
		frictionJointDef.maxTorque = 100.0f;
		frictionJointDef.localAnchorA.SetZero();
		frictionJointDef.localAnchorB.Set(-1, 0);

		m_ptrPhysicsWorld->CreateJoint(&frictionJointDef);
		break;
	}

	case JointType::Pulley:
	{
		b2PulleyJointDef pulleyJointDef;
		pulleyJointDef.bodyA = bodyA;
		pulleyJointDef.bodyB = bodyB;
		pulleyJointDef.collideConnected = false;

		pulleyJointDef.localAnchorA.SetZero();
		pulleyJointDef.localAnchorB.SetZero();


		pulleyJointDef.groundAnchorA.Set(size.width/2/PTM_RATIO, 5);
		pulleyJointDef.groundAnchorB.Set(size.width / 2 / PTM_RATIO + 3, 4);



		m_ptrPhysicsWorld->CreateJoint(&pulleyJointDef);


		break;
	}

	case JointType::Gear:
	{

		b2PrismaticJointDef prismaticJointDef;
		prismaticJointDef.bodyA = bodyA;
		prismaticJointDef.bodyB = bodyB;

		prismaticJointDef.collideConnected = false;
		//轴线axis1相对于物体A
		prismaticJointDef.localAxisA.Set(0, 1);

		prismaticJointDef.localAnchorA.Set(2, 0);
		prismaticJointDef.localAnchorB.Set(-1, 0);

		prismaticJointDef.enableLimit = true;
		prismaticJointDef.lowerTranslation = 0;
		prismaticJointDef.upperTranslation = 10;

		prismaticJointDef.enableMotor = true;
		prismaticJointDef.maxMotorForce = 500;
		prismaticJointDef.motorSpeed = 5;

		b2PrismaticJoint* prismaticJoint = (b2PrismaticJoint*)m_ptrPhysicsWorld->CreateJoint(&prismaticJointDef);

		//旋转连接器
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = bodyA;
		revoluteJointDef.bodyB = bodyB;
		revoluteJointDef.collideConnected = false;

		revoluteJointDef.localAnchorA.Set(1, 1);
		revoluteJointDef.localAnchorB.Set(0, 0);
		revoluteJointDef.referenceAngle = 45.0f*DEGTORAD;

		revoluteJointDef.enableLimit = true;
		revoluteJointDef.lowerAngle = -45 * DEGTORAD;
		revoluteJointDef.upperAngle = 45 * DEGTORAD;

		revoluteJointDef.enableMotor = true;
		revoluteJointDef.maxMotorTorque = 5;
		revoluteJointDef.motorSpeed = 90 * DEGTORAD;

		b2RevoluteJoint* revoluteJoint = (b2RevoluteJoint*)m_ptrPhysicsWorld->CreateJoint(&revoluteJointDef);

		b2GearJointDef gearJointDef;
		gearJointDef.bodyA = bodyA;
		gearJointDef.bodyB = bodyB;
		gearJointDef.joint1 = revoluteJoint;
		gearJointDef.joint2 = prismaticJoint;

		gearJointDef.collideConnected = false;
		

		m_ptrPhysicsWorld->CreateJoint(&gearJointDef);


		break;
	}
	case JointType::Mouse:
	{
		break;
	}
	default:
		break;
	}
}

void JointTest::update(float dt)
{
	HelloWorld::update(dt);
}
