#include "CollisionFlagTest.h"
CollisionFlagTest::CollisionFlagTest()
{

}

CollisionFlagTest::~CollisionFlagTest()
{

}

Scene* CollisionFlagTest::createScene()
{
	CollisionFlagTest* pRet = CollisionFlagTest::create();

	Scene* ptrScene = Scene::create();

	ptrScene->addChild(pRet);

	return ptrScene;
}

bool CollisionFlagTest::init()
{
	if (!HelloWorld::init())
		return false;

	return true;
}

void CollisionFlagTest::initPhysics()
{
	HelloWorld::initPhysics();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(visibleSize.width / 2 / PTM_RATIO, 9);



	b2PolygonShape shape;
	shape.SetAsBox(0.3f, 0.3f);

	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 1;


	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0, 2);
	b2Body* staticBody = m_ptrPhysicsWorld->CreateBody(&bodyDef);



	shape.SetAsBox(5, 0.1f, b2Vec2(visibleSize.width / 2 / PTM_RATIO, 0), 0);//ground
	staticBody->CreateFixture(&fixturedef);
	shape.SetAsBox(5, 0.1f, b2Vec2(visibleSize.width / 2 / PTM_RATIO, 10), 0);//ceiling
	staticBody->CreateFixture(&fixturedef);
	shape.SetAsBox(0.1f, 5, b2Vec2(visibleSize.width / 2 / PTM_RATIO - 5, 5), 0);//left wall
	staticBody->CreateFixture(&fixturedef);
	shape.SetAsBox(0.1f, 5, b2Vec2(visibleSize.width / 2 / PTM_RATIO + 5, 5), 0);//right wall
	staticBody->CreateFixture(&fixturedef);

	b2Color red(1, 0, 0);
	b2Color green(0, 1, 0);
	//large and green are friendly ships
	for (int i = 0; i < 3; i++)
		balls.push_back(new Ball(m_ptrPhysicsWorld, 0.8, green, FRIENDLY_SHIP, BOUNDARY | FRIENDLY_SHIP | ENEMY_SHIP));
	//large and red are enemy ships
	for (int i = 0; i < 3; i++)
		balls.push_back(new Ball(m_ptrPhysicsWorld, 0.8, red, ENEMY_SHIP, BOUNDARY | FRIENDLY_SHIP | ENEMY_SHIP));
	//small and green are friendly aircraft
	for (int i = 0; i < 3; i++)
		balls.push_back(new Ball(m_ptrPhysicsWorld, 0.5f, green, FRIENDLY_AIRCRAFT, BOUNDARY | ENEMY_AIRCRAFT));
	//small and red are enemy aircraft
	for (int i = 0; i < 3; i++)
		balls.push_back(new Ball(m_ptrPhysicsWorld, 0.5f, red, ENEMY_AIRCRAFT, BOUNDARY | FRIENDLY_AIRCRAFT));


}

void CollisionFlagTest::addNewSpriteAtPosition(cocos2d::Point p)
{

}

void CollisionFlagTest::update(float dt)
{
	HelloWorld::update(dt);
	for (unsigned int i = 0; i < balls.size(); i++)
	{
		balls[i]->renderAtBodyPosition();
	}
}

