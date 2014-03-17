#include "MoveTest.h"
MoveTest::MoveTest()
{

}

MoveTest::~MoveTest()
{

}

Scene* MoveTest::createScene()
{
	MoveTest* pRet = MoveTest::create();

	Scene* ptrScene = Scene::create();

	ptrScene->addChild(pRet);

	return ptrScene;
}

bool MoveTest::init()
{
	if (!HelloWorld::init())
		return false;

	return true;
}

void MoveTest::initPhysics()
{
	HelloWorld::initPhysics();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(visibleSize.width/2/PTM_RATIO, 9);

	

	b2PolygonShape shape;
	shape.SetAsBox(0.3f, 0.3f);

	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 1;


	m_ptrBody = m_ptrPhysicsWorld->CreateBody(&bodyDef);
	m_ptrBody->CreateFixture(&fixturedef);

	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0, 2);
	b2Body* staticBody = m_ptrPhysicsWorld->CreateBody(&bodyDef);

	

	shape.SetAsBox(5, 0.1f, b2Vec2(visibleSize.width/2/PTM_RATIO, 0), 0);//ground
	staticBody->CreateFixture(&fixturedef);
	shape.SetAsBox(5, 0.1f, b2Vec2(visibleSize.width/2/PTM_RATIO, 10), 0);//ceiling
	staticBody->CreateFixture(&fixturedef);
	shape.SetAsBox(0.1f, 5, b2Vec2(visibleSize.width/2/PTM_RATIO-5, 5), 0);//left wall
	staticBody->CreateFixture(&fixturedef);
	shape.SetAsBox(0.1f, 5, b2Vec2(visibleSize.width/2/PTM_RATIO+5, 5), 0);//right wall
	staticBody->CreateFixture(&fixturedef);

	m_MoveState = MoveState::MS_STOP;

}

void MoveTest::onEnter()
{
	Layer::onEnter();
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MoveTest::onKeyPressed, this);
	listener->onKeyPressed = CC_CALLBACK_2(MoveTest::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void MoveTest::addNewSpriteAtPosition(cocos2d::Point p)
{
	

}

void MoveTest::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

}

void MoveTest::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_1:
		log("Press 1");
		m_MoveState = MoveState::MS_LEFT;
		break;

	case EventKeyboard::KeyCode::KEY_2:
		log("Press 2");
		m_MoveState = MoveState::MS_STOP;
		break;

	case EventKeyboard::KeyCode::KEY_3:
		log("Press 3");
		m_MoveState = MoveState::MS_RIGHT;
		break;

	default:
		break;
	}
}

void MoveTest::update(float dt)
{
	//让速度变化到我们指定的大小
	//其他的在博客10-11仔细研读
	b2Vec2 vel = m_ptrBody->GetLinearVelocity();
	switch (m_MoveState)
	{
	case MoveState::MS_STOP:
		/*vel.x = 0;*/
		vel.x *= 0.98f;
		break;
	case MoveState::MS_LEFT:
		/*vel.x = -5;*/
		vel.x = b2Max(vel.x - 0.2f, -0.5f);
		break;
	case MoveState::MS_RIGHT:
		/*vel.x = 5;*/
		vel.x = b2Min(vel.x + 0.1f, 5.0f);
		break;
	default:
		break;
	}
	m_ptrBody->SetLinearVelocity(vel);
	HelloWorld::update(dt);
}

