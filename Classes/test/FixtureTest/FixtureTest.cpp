#include "FixtureTest.h"

FixtureTest::FixtureTest()
{

}

FixtureTest::~FixtureTest()
{

}

Scene* FixtureTest::createScene()
{
	FixtureTest* pRet = FixtureTest::create();
	Scene* ptrScene = Scene::create();
	ptrScene->addChild(pRet);
	return ptrScene;
}

bool FixtureTest::init()
{
	if (!HelloWorld::init())
		return false;

	return true;
}

void FixtureTest::addNewSpriteAtPosition(cocos2d::Point p)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0.0f, 0.0f);
	circleShape.m_radius = 1;

	b2FixtureDef fixturedef;
	fixturedef.shape = &circleShape;

	b2Body* body = m_ptrPhysicsWorld->CreateBody(&bodyDef);
	body->CreateFixture(&fixturedef);

	b2Vec2 vertices[5];
	vertices[0].Set(-1, 2);
	vertices[1].Set(-1, 0);
	vertices[2].Set(0, -3);
	vertices[3].Set(1, 0);
	vertices[4].Set(1, 1);

	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 5); //pass array to the shape

	fixturedef.shape = &polygonShape; //change theshape of the fixture
	bodyDef.position.Set((p.x-100.0f)/PTM_RATIO, p.y/PTM_RATIO); //in the middle
	b2Body* dynamicBody2 = m_ptrPhysicsWorld->CreateBody(&bodyDef);
	dynamicBody2->CreateFixture(&fixturedef); //adda fixture to the body

}

